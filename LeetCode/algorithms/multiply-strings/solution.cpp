#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int l1 = num1.length(), l2 = num2.length();
        std::vector<unsigned char> result(l1 + l2, 0);
        
        for (int i = 0; i < l1; i++) {
            unsigned char digit1 = num1[l1 - i - 1] - '0';
            if (digit1 == 0) continue;

            int j = 0;
            unsigned char carry = 0;

            for (; j < l2; j++) {
                unsigned char digit2 = num2[l2 - j - 1] - '0';
                unsigned char tmp = result[i + j] + digit1 * digit2 + carry;
                result[i + j] = tmp % 10;
                carry = tmp / 10;
            }
            
            while (carry > 0) {
                unsigned char tmp = result[i + j] + carry;
                result[i + j] = tmp % 10;
                carry = tmp / 10;
                j++;
            }
        }
        
        while (result.back() == 0 && result.size() > 1)
            result.pop_back();

        std::stringstream ss;
        while (result.size() > 0) {
            ss << (int)result.back();
            result.pop_back();
        }

        return ss.str();
    }
};
