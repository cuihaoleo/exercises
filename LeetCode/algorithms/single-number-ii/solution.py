class Solution:
    # @param {integer[]} nums
    # @return {integer}
    def singleNumber(self, nums):
        # Python 里用 (n<<p)&1 对负整数取二进制位
        # 会得到和有限长整数一样的结果
        bits = [sum((n >> i) & 1 for n in nums) for i in range(32)]
        ans = reduce(lambda a, b: a * 2 + b % 3, reversed(bits), 0)
        return ans if bits[-1] % 3 == 0 else ans - (1 << 32)
