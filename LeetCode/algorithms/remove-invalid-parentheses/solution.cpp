#include <iostream>
#include <deque>
#include <tuple>
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        // find minimum number of removals (greedy)
        int leftRemoval = 0, rightRemoval = 0;

        for (auto c: s)
            if (c == '(')
                leftRemoval++;
            else if (c == ')') {
                if (leftRemoval > 0)
                    leftRemoval--;
                else
                    rightRemoval++;
            }

        // compress consecutive identical characters to a compactNode
        struct compactNode {
            char ch;
            int count = 1, maxUnusedRemoval = 0;
            explicit compactNode(char ch): ch(ch) {};
        };

        deque<compactNode> compact;
        char previousChar = '\0';

        for (auto ch: s)
            if (ch == previousChar)
                compact.back().count++;
            else {
                compact.emplace_back(ch);
                previousChar = ch;
            }

        // set `maxUnusedRemoval` at each compactNode
        int leftBracketCount = 0, rightBracketCount = 0;

        for (auto it = compact.rbegin(); it != compact.rend(); ++it) {
            if (it->ch == '(') {
                it->maxUnusedRemoval = min(leftBracketCount, leftRemoval);
                leftBracketCount += it->count;
            } else if (it->ch == ')') {
                it->maxUnusedRemoval = min(rightBracketCount, rightRemoval);
                rightBracketCount += it->count;
            }
        }

        // BFS
        struct searchStatus {
            string str;
            int unusedRemoval[2];
            int bracketCount;
            searchStatus(const string &s, int l, int r, int c): str(s), unusedRemoval{l, r}, bracketCount(c) {};
        };

        deque<searchStatus> bfsQueue;
        bfsQueue.emplace_back("", leftRemoval, rightRemoval, 0);

        for (const auto &p: compact)
            if (p.ch != '(' && p.ch != ')') {
                for (auto &item: bfsQueue)
                    item.str += string(p.count, p.ch);
            } else {
                for (auto i = bfsQueue.size(); i > 0; --i) {
                    auto &item = bfsQueue.front();
                    int j;
                    int &unusedRemoval = item.unusedRemoval[p.ch != '('];

                    // remove as much as possible
                    if (unusedRemoval > p.count) {
                        j = 0;
                        unusedRemoval -= p.count;
                    } else {
                        j = p.count - unusedRemoval;
                        unusedRemoval = 0;
                    }

                    int bracketCount = item.bracketCount + (p.ch == '(' ? j : -j);

                    while (j <= p.count && unusedRemoval <= p.maxUnusedRemoval && bracketCount >= 0) {
                        bfsQueue.emplace_back(
                            item.str + string(j, p.ch),
                            item.unusedRemoval[0], item.unusedRemoval[1],
                            bracketCount
                        );

                        unusedRemoval++, j++;
                        p.ch == '(' ? bracketCount++ : bracketCount--;
                    }

                    bfsQueue.pop_front();
                }
            }

        vector<string> result;
        for (auto &item: bfsQueue)
            if (item.bracketCount == 0)
                result.emplace_back(std::move(item.str));

        return result;
    }
};

int main(int argc, char **argv) {
    Solution solution;
    auto result = solution.removeInvalidParentheses(argv[1]);

    for (auto &s: result)
        cout << s << endl;

    return 0;
}
