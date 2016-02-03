#!/usr/bin/env python2

import json
import hashlib
import os
import sys
import urllib2
import tempfile
import shelve
import subprocess
import atexit
import shutil


SF_BASE = "http://sourceforge.net/"
WORKING_DIRNAME = ".sf_sync"


# from: https://stackoverflow.com/questions/1131220/get-md5-hash-of-big-files-in-python
def md5_for_file (f, block_size=2**20):
    md5 = hashlib.md5()
    while True:
        data = f.read(block_size)
        if not data:
            break
        md5.update(data)
    return md5.hexdigest()

def sha1_for_file (f, block_size=2**20):
    sha1 = hashlib.sha1()
    while True:
        data = f.read(block_size)
        if not data:
            break
        sha1.update(data)
    return sha1.hexdigest()


class MD5_Getter:

    def __init__ (self, cache_file):
        self.db = shelve.open(cache_file, "c")

    def __del__ (self):
        self.db.close()

    def remove_cache (self, path):

        k = os.path.basename(str(path))

        if k in self.db:
            self.db.remove(k)

    def get (self, path):

        act_mtime = os.stat(path).st_mtime
        filename = str(os.path.basename(path))

        # try read from cache
        try:
            rec_mtime, rec_md5 = self.db[filename]
        except KeyError:
            pass
        else:
            if rec_mtime == act_mtime:
                return rec_md5

        act_md5 = md5_for_file(open(path))
        self.db[filename] = (act_mtime, act_md5)

        return act_md5 


def check_files (proj, local_cd, md5getter):

    get_filelist_url = lambda path: \
        SF_BASE + "/projects/%s/files/%s/list" % (proj, path)

    def sync (cd = ''):

        lcd = os.path.join(local_cd, cd)
        print("Checking: " + lcd)
        
        response = urllib2.urlopen(get_filelist_url(cd))
        rlist = json.load(response)

        try:
            local_files = os.listdir(lcd)
        except OSError as err:
            if err.errno == 2:
                local_files = []
            else:
                raise err
        else:
            if cd == '':
                local_files.remove(WORKING_DIRNAME)

        for f in local_files:

            lpath = os.path.join(lcd, f)
            
            if f not in rlist:
                if os.path.isdir(lpath):
                    dirs_to_remove.add(lpath)
                else:
                    files_to_remove.add(lpath)
            else:


                if str(rlist[f]["type"]) != 'd':
                    if os.path.isdir(lpath) or \
                        md5getter.get(lpath) != str(rlist[f]['md5']):
                        # remote is file, local is dir
                        # or: remote and local file not the same
                        files_to_update.add(tuple(rlist[f].items()))

                else:
                    if not os.path.isdir(lpath):
                        # remote is dir, local is file
                        files_to_remove.add(lpath)

        # remote files not found in local
        for f in set(rlist.keys()) - set(local_files):
            if str(rlist[f]["type"]) != 'd':
                files_to_update.add(tuple(rlist[f].items()))

        # check next level
        for f in rlist:
            if str(rlist[f]["type"]) == 'd':
                sync(rlist[f]["full_path"])


    dirs_to_remove = set() 
    files_to_remove = set()
    files_to_update = set()

    sync()

    return files_to_update, files_to_remove, dirs_to_remove


def download_file (url, downto):
    cmd = ['/usr/bin/wget', "-nv", url, "-O", downto]
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    status = p.wait()
    errmsg = p.stderr.read()

    print(errmsg)
    return status == 0


if __name__ == "__main__":

    proj = sys.argv[1]
    dest = sys.argv[2]

    WORKING_DIR = os.path.join(dest, WORKING_DIRNAME)
    
    if not os.path.isdir(WORKING_DIR):
        print("I work with this directory for the first time.")
        print("Create working directory...")
        os.mkdir(WORKING_DIR)

    md5cache_file = os.path.join(WORKING_DIR, "md5")
    md5getter = MD5_Getter(md5cache_file)
    files_to_update, files_to_remove, dirs_to_remove = \
                check_files(proj, dest, md5getter)

    DOWNLOAD_DIR = tempfile.mkdtemp(dir=WORKING_DIR)
    atexit.register(lambda: shutil.rmtree(DOWNLOAD_DIR))

    for f in files_to_update:

        info = dict(f)

        print("[UPDATE] %s" % info['full_path'])

        downto = tempfile.NamedTemporaryFile(dir=DOWNLOAD_DIR).name
        url = info['download_url']
        
        if download_file(url, downto):

            print "Checking SHA1... ",

            if sha1_for_file(open(downto)) == str(info['sha1']):
                print("Success!")
                actpath = os.path.join(dest, info['full_path'])
                shutil.move(downto, actpath)
            else:
                print("Fail!")

    for f in files_to_remove:
        print("[REMOVE] %s" % f)
        md5getter.remove_cache(f)
        os.remove(f)

    for d in dirs_to_remove:
        print("[RMTREE] %s" % d)
        try:
            os.rmdir(d)
        except OSError:
            pass # Do nothing for security.

