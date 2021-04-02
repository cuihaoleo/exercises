#include <vector>
#include <string>
#include <algorithm>

using std::string;

class Solution {
public:
    string addStrings(string num1, string num2) {
        int l1 = num1.length(), l2 = num2.length();
        int max_len = std::max(l1, l2);
        std::string result(max_len + 1, '0');
        unsigned char carry = 0;
        int i = 0;
        
        for (; i < std::min(l1, l2); i++) {
            unsigned char digit1 = num1[l1 - i - 1] - '0';
            unsigned char digit2 = num2[l2 - i - 1] - '0';
            unsigned char tmp = digit1 + digit2 + carry;

            result[max_len - i] += tmp % 10;
            carry = tmp / 10;
        }
        
        string &ref = (l1 > l2) ? num1 : num2;
        for (; i < ref.length(); i++) {
            unsigned char digit = ref[max_len - i - 1] - '0';
            unsigned char tmp = digit + carry;
            
            result[max_len - i] += tmp % 10;
            carry = tmp / 10;
        }
        
        if (carry) {
            result[max_len - i] += carry;
            return result;
        } else {
            return result.substr(1);
        }
    }
};
