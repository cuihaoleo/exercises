# 聚类分析实验报告

## 程序说明

```
julei.py [-h] [-m METHOD] [-p N] [-k NCLUSTER] csv_file config
```

`-m METHOD` 参数指定聚类算法，支持的算法如下：

1.  `system`：最长距离准则的系统聚类法（默认，自己实现）
2. `maxmin`：最大最小距离算法（自己实现）
3. `kmeans_np`：KMeans 算法（scipy 库实现）
4. `kmeans`：KMeans 算法（sklearn 库实现）

其中系统聚类法是确定性的算法。后三种算法初始点都是随机选取的。

`-p N` 参数指定PCA法降维后的维度。PCA算法是 sklearn 库提供的，默认值 `0` 表示不降维。

`-k NCLUSTER` 参数指定结果的聚类数目。如果不指定，则和 CSV 数据中的参考分类的数目相同。

`csv_file` 是逗号分隔的 CSV 表格，第一列是表头。

`config` 文件用于指定使用表格中哪些列作为聚类特征，以及哪一列作为参考分类。比如要设置 f1~f5 列作为聚类特征，Expression 列作为参考分类：

```
f1,f2,f3,f4,f5
Expression
```

程序聚类后，会根据参考分类为每个聚类确定一个参考分类（该聚类中各个参考分类占比最多的一个）。然后以 Radial Plots 的形式画出最终的分类结果和参考分类（坐标取降维后的），并在终端输出正确率。

## 测试1：表情数据（NVIE_PS_feature.xls）

以 Expression 列为参考标签，各坐标点作为聚类特征。

测试结果（图片略）：
```
$ ./julei.py data.csv config -m system
Correct: 0.219844
$ ./julei.py data_all.csv config -m maxmin
Correct: 0.214981
$ ./julei.py data_all.csv config -m kmeans
Correct: 0.242218
$ ./julei.py data_all.csv config -m kmeans_np
Correct: 0.245136
```

分类准确性都不到1/4，使用PCA降维对结果影响也不大。为了说明数据特征，附上PCA降到6维后的 KMeans 完整聚类结果：
```
$ ./julei.py data_all.csv config -m kmeans -p6
0.247082
```
![](/home/cuihao/Development/artificial/figure_1.png) 

左图是参考分类，右图是聚类结果。可以看到各个参考分类的采样点并不能有效分开，全都堆在一起。可见该组数据的采样点选取不够合理，无法有效地区分各类数据。


## 测试2：一个年龄段中的表情数据

这组数据取自 `personIndependentFeatures_Faces.xlsx` 中 Age 标签为1的数据，共有348条。主要是考虑到年龄影响可能比较大，所以手动排除一下，看看能不能得到更好的结果。

以 Expression 列为参考标签，各坐标点作为聚类特征。

测试结果（图片略，波动较大的附上两组数据，代表较好的和较差的结果）：
```
$ ./julei.py data.csv config -m system
Correct: 0.488506
$ ./julei.py data.csv config -m system -p 8
Correct: 0.502874
$ ./julei.py data.csv config -m maxmin
Correct: 0.390805
Correct: 0.465517
$ ./julei.py data.csv config -m kmeans
Correct: 0.543103
$ ./julei.py data.csv config -m kmeans_np
Correct: 0.491379
Correct: 0.551724
```

这组数据聚类准确性较高，能达到50%左右。附上PCA降到4维后的 KMeans 完整聚类结果：
```
$ ./julei.py data.csv config -m kmeans -p4
0.537356
```
![](/home/cuihao/Development/artificial/figure_2.png) 

原来的数据确实稍微呈现出一些聚类的分布。因此能够进行聚类分析。

最大最小距离法结果很不稳定，而且准确率也不太高：
```
$ ./julei.py data.csv config -m kmeans -p4
Correct: 0.362069
```
![](/home/cuihao/Development/artificial/figure_3.png) 

左边的一坨数据被混在了一起。调试一下可以发现，这种结果的出现可能是由于初始聚类中心选在分界面附近导致的。

## 讨论

三种算法比较下来，kmeans 算法一般表现较好，系统聚类法其次，最大最小距离法较差。

初始点的选取对最大最小距离法影响很大。可以考虑在算法过程中根据类中的样本调整聚类中心位置，这样应该会稳定一些，但算法复杂度会提高。

sklearn 库里面的 KMeans 法用了一种叫 K-means++ 的迭代算法确定初始的 K 个聚类中心，似乎结果比较稳定。看了看维基百科，大概是这样：

1. 在采样点中随机选取第一个聚类中心
2. 对每个采样点，计算到最近的聚类中心的距离 D(x)
3. 每个采样点设置 D(x)^2 的权重（概率），以这个概率分布随机选取下一个聚类中心
4. 重复2、3，直到找到 k 个聚类中心，然后进行正常的 KMeans 聚类算法。

scipy 库的 KMeans 算法默认是随机选取初始的聚类中心的。不过对于所给的数据，和 K-means++ 的准确率差别不太明显。

