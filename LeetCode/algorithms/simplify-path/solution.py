class Solution:
    # @param {string} path
    # @return {string}
    def simplifyPath(self, path):
        ps = []
        for d in path.split('/'):
            if d == '.' or d == '':
                continue
            elif d == '..':
                try:
                    ps.pop()
                except IndexError:
                    pass
            else:
                ps.append(d)
        return '/' + '/'.join(ps)
