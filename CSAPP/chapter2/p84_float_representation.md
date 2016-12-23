## Chapter 2, Problem 84

k 位指数，n 位小数。偏置 $ \textit{Bias} = 2^{k-1} - 1 $。

### Quiz A

$ V = 5.0 = (101.0)_2 = (1.01)_2 \times 2^{-2} $

所以 $ E = -3, M = (1.01)_2, f = (0.01)_2 $ .

### Quiz B

能够被描述的最大奇整数。

最大的2指数为 $ E_m = (2^k - 2) - \textit{Bias} = 2^{k-1} - 1 $ .

如果 $ n >= E_m $ ：

- 指数取最大值 $E_m$ ，阶码 $ e = (\underbrace{1111....111}_{k-1 \textrm{ copies of } 1}0)_2 $ .

- 尾数部分取不产生小数的最大值（最高 $ E_m $ 位取1，剩下取0）。

表示的数值为 $ V = (1.\underbrace{1111...111}_{E_m \textrm{ copies of } 1})_2 \times 2^{E_m} = (\underbrace{11111...111}_{E_m+1 \textrm{ copies of } 1})_2 = 2^{E_m + 1} - 1$ .

如果 $ n < E_m $ ：

- 尾数部分取最大值，$ f = (.\underbrace{1111....111}_{n \textrm{ copies of } 1})_2 $ .
- 指数取正好使表示数值没有小数部分的值，偏置后阶码 $ E = e - \textit{Bias} = 2^n $ .

表示的数值为 $ V = (1.\underbrace{1111...111}_{n \textrm{ copies of } 1})_2 \times 2^n = (\underbrace{11111...111}_{n+1 \textrm{ copies of } 1})_2 = 2^{n + 1} - 1$ .

### Quiz C

最小的（正？）规格化数的倒数。

最小的规格化数 $ V_m  = 2^{-2^{k-1} + 2} $ ，其倒数 $ V_m  = 2^{2^{k-1} - 2} $ 。

- 阶码 $ e = E + \textit{Bias} = (2^{k-1}-2) + (2^{k-1} - 1) = 2^k - 3 $ .
- 尾数为 1。