#!/usr/bin/env python3

import requests
from bs4 import BeautifulSoup
from collections import namedtuple
from urllib.parse import urljoin

KCDB_URL = "http://kancolle-db.net"

Kan = namedtuple("Kan", ["name", "type"])


class KanColleDB:
    def __init__(self):
        kan_map = {}
        req = requests.get(KCDB_URL)
        html = BeautifulSoup(req.text)

        kan_menu = html.select("#left_frame ul")[1]

        kan_types = [t.text for t in kan_menu.select(".main_menu")]
        for kan_type, sub_menu in zip(kan_types, kan_menu.select(".sub_menu")):
            for ship_li in sub_menu.select(".ship"):
                kan = Kan(ship_li.text.split()[0], kan_type)
                kan_map[int(ship_li["id"])] = kan

        self.kan_types = kan_types
        self.kan_map = kan_map

    def build_info(self, you, dan, gang, lyu):
        url = urljoin(KCDB_URL,
                      "ship/%d-%d-%d-%d.html" % (you, dan, gang, lyu))
        req = requests.get(url)
        html = BeautifulSoup(req.text)

        bytype = {k: 0.0 for k in self.kan_types}
        for tr in html.find_all("tr")[1:]:
            kid = int(tr.select("td a")[0]["id"])
            tp = self.kan_map[kid].type
            bytype[tp] += float(tr.select("td")[-1].text.strip("%")) / 100

        return {
            "bytype": bytype,
        }

if __name__ == "__main__":
    import sys
    import math

    fmls = [
        "30/30/30/30",
        "250/30/200/30",
        "250/130/200/30",
        "300/30/400/300",
        "400/30/600/30",
        "300/30/400/330",
        "300/300/600/600",
        "350/30/600/350",
        "250/30/200/31",
        "250/30/250/30",
        "350/30/400/350",
        "400/100/600/30",
        "30/30/999/30",
        "301/31/502/400",
        "300/100/200/30",]

    tp = sys.argv[1]

    yuz = 0.80

    db = KanColleDB()
    for fml in fmls:
        fml = [int(i) for i in fml.split("/")]
        print("=== %d/%d/%d/%d ===" % tuple(fml))
        bt = db.build_info(*fml)["bytype"]
        for k in bt:
            if bt[k] > 0.0:
                print("%s: %.2f" % (k, bt[k]))
        possibility = bt[tp]
        if possibility != 0.0:
            times = math.log(1-yuz, 1-possibility)
            print(times)
            print(" ".join("%.2f" % (times*i) for i in fml))
            print(int(sum([times*i for i in fml])))
