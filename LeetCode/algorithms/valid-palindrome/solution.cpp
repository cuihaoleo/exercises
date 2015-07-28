class Solution {
public:
    bool isPalindrome(string s) {
        int l = s.length() - 1, i = 0;
        while (i < l) {
            while (i < l && !isalnum(s[i]))
                i++;
            while (i < l && !isalnum(s[l]))
                l--;
            if (i < l && tolower(s[i++]) != tolower(s[l--]))
                return false;
        }

        return true;

        /* fallback to normal case
        l = s.length() - 1, i = 0;
        while (i < l)
            if (s[i++] != s[l--])
                return false;
        return true; */
    }
};
