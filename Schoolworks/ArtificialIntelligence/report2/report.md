# 判别式实验报告

```
pbs.py [-h] [-m METHOD] trainset testset config
```

`trainset`、`testset` 分别为训练集和测试集数据，CSV 格式。

`config` 文件格式同上次聚类实验。

其中系统聚类法是确定性的算法。后三种算法初始点都是随机选取的。

`-m METHOD` 参数指定聚类算法，支持的算法如下：

1.  `simple_perception`：自己实现的固定步长的感知器算法；
2. `linear_svm`：sklearn 库实现的线性二分类SVM算法。

辅助脚本 `divide.py ` 随机地将数据分割成训练集和测试集（保持每一类的比例不变）。例如：

```
./divide.py data.csv -p 0.6 emotion > training.csv 2> test.csv
```

将 data.csv 中的数据按 6:4 划分成训练集和测试集，分别保存到 training.csv 和 test.csv。


## 测试1：感知器算法

手写的固定步长多分类感知器算法，采用第三类多类模式。默认步长 1e-10，100轮后不收敛则停止迭代。

### 简单的测试数据

`trainset` 和 `testset` 使用同一组数据（来自课本）：
```
x1,x2,flag
0,0,10
1,1,20
-1,1,30
```

运行：
`./pbs.py data.csv data.csv config`

输出：

```
[[  0.00000000e+00  -2.00000000e-10   0.00000000e+00]
 [  2.00000000e-10   0.00000000e+00  -2.00000000e-10]
 [ -2.00000000e-10   0.00000000e+00  -2.00000000e-10]]
Correct: 1.000000
```

这组数据是线性可分的，算法很快收敛。同时也验证了算法的正确性。

### 一个年龄段中的表情数据

这组数据取自 `personIndependentFeatures_Faces.xlsx` 中 Age 标签为1的数据，共有348条。总共有6个 Expression 分类，每一类的数据数量是相同的。

先划分一下训练集和测试集：

```
$ ./divide.py data.csv -p 0.6 Expression > training.csv 2> test.csv
```

测试：

```
$ ./pbs.py training.csv training.csv config
Didn't convergence after 100 rounds
Correct: 0.220588
$ ./pbs.py training.csv test.csv config    
Didn't convergence after 100 rounds
Correct: 0.201389
```

感知器算法100轮后没有收敛。按照最后得到的 w 来划分，在训练集和测试集上分类准确率都在20%多一些。考虑到总共有6类，大概还是比随机分要强一些的。

增大迭代次数到1000次（直接改代码了）：
```
$ ./pbs.py training.csv test.csv config
Didn't convergence after 1000 rounds
Correct: 0.354167
```

还没有收敛，但分类准确率确有明显提高。

增大迭代次数到10000次：
```
$ ./pbs.py training.csv test.csv config
Didn't convergence after 10000 rounds
Correct: 0.437500
```

准确率又明显提高了，但还没收敛。大概还是有些希望的吧。


## 测试2：Linear SVM 算法

并没有读代码。根据文档，应该是用线性SVM算法对每一类进行“是/不是”的二分类训练，然后组合成一个分类器。仅比对一下结果：

```
$ ./pbs.py training.csv test.csv config -m linear_svm
Correct: 0.388889
$ ./pbs.py training.csv training.csv config -m linear_svm 
Correct: 0.490196
```

其实识别率也不是很高。

