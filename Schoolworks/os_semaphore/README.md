# 操作系统实验：使用信号量模拟生产者消费者模型

崔灏 PB13007103

## 问题概述

用 Java 语言模拟生产者消费者问题，使用信号量控制资源访问。

伪代码：
```py
empty = Semaphore(N_SLOTS)
full = Semaphore(0)
mutex = Semaphore(1)

def Producer():
    down(empty)
    down(mutex)
    produceItem()
    up(mutex)
    up(full)

def Consumer():
    down(full)
    down(mutex)
    consumeItem()
    up(mutex)
    up(empty)
```

信号量 ``empty`` 表示空货架数量，在产品囤积过多时可以限制生产者生产，即限制最大可用资源数。

信号量 ``full`` 表示已占用的货架数量，当货架为空时可以限制消费者消费，即缺少资源时限制资源访问。

``empty + full`` 应当不大于最大可用资源数 ``N_SLOTS``。

信号量 ``mutex`` 实际上被当作互斥量使用，用于控制临界区访问。


## 代码讲解

### 代码的编译和使用

```bash
$ javac SemaphoreDemo.java
$ java SemaphoreDemo <产品队列长度> <消费间隔> <一次消费时间> <生产间隔> <一次生产时间>
```

### 产品队列，信号量和互斥量

使用 Java 标准库的 ``Semaphore`` 类实现信号量功能。

同题目要求，全局设置两个信号量控制资源访问，和一个互斥量控制临界区访问。
```java
private Semaphore empty; 
private Semaphore full;
private final Object mutex = new Object();

private String[] task_buffer;

SemaphoreDemo (int capacity) throws InterruptedException {
    task_buffer = new String[capacity];
    empty = new Semaphore(capacity, true);  // empty = capacity
    full = new Semaphore(capacity, true);
    full.acquire(capacity);  // full = 0
}
```

### 抽象类 AbstractMan

我们注意到生产者和消费者都有同样的抽象行为：
```py
down(semaphore1)
down(mutex)
critical_region()
up(mutex)
up(semaphore2)
```

因此首先实现了抽象类 ``AbstractMan`` 代表这一模式（删除了一些不影响讲解的代码）：
```java
private abstract class AbstractMan implements Runnable {
    private Semaphore first, second;
    private int max_time_in_cr;
    private int max_time_sleep;
    // ......

    protected abstract void critical_region();

    public void run() {
        while (true) {
            try {
                Thread.sleep(rand.nextInt(max_sleep_time));
                first.acquire();
                synchronized (mutex) {  // down(mutex)
                    critical_region();
                    Thread.sleep(rand.nextInt(max_work_time));
                }  // up(mutex)
                second.release();
           } catch (InterruptedException e) {
                break;
           }
        }
    }
}
```

抽象方法 ``critical_region`` 定义了临界区内的做的事情。

这里用 Java 的 ``synchronized`` 语句实现了互斥量的功能，而没有使用信号量，是为了用语句块更清晰的标识临界区。这一改变不影响讨论。

为了更加真实地模拟现实情境，额外设置了两个属性：

- ``max_time_in_cr`` 代表临界区内工作花费的最大时间
- ``max_time_sleep`` 代表临界区外休息的时间
可以用来模拟购买频率、生产速度等。

### 生产者类 Producer 和消费者类 Consumer

利用 ``AbstractMan`` 抽象类很容易派生出生产者类和消费者类：

- 生产者 ``Producer`` 就是 ``semaphore1 = empty`` 且 ``semaphore2 = full`` 的 ``AbstractMan``
- 消费者 ``Consumer`` 就是 ``semaphore1 = full`` 且 ``semaphore2 = empty`` 的 ``AbstractMan``

### 演示代码
```java
private void demo(int c1, int c2, int p1, int p2) {
    Thread customer_thread = new Thread(new Customer(c1, c2));
    Thread producer_thread = new Thread(new Producer(p1, p2));
    customer_thread.start();
    producer_thread.start();
}
```
演示程序分别启动了一个消费者线程和一个生产者线程进行模拟。

为了更好的模拟现实场景，该程序可以指定产品队列长度、消费间隔、消费者完成一次消费的时间、生产间隔、生产者完成一次生产的时间。


## 实验演示

**一点说明**：为了更好模拟现实场景，应该可以增加**消费者数量**的，而且消费者应当能够在资源充足的条件下同时消费（不存在临界区互斥）。但这里为了简便起见，就用不同的消费间隔、一次消费时间去模拟了。

1、**买方市场**

生产者产能旺盛，2ms 就能产出一个产品，然而消费者 40ms 才消费一次：

```bash
$ java SemaphoreDemo 10 40 10 10 2
[P] submit P_1 at slot #1
[P] submit P_2 at slot #2
[P] submit P_3 at slot #3
[C] finish P_3 at slot #3
[P] submit P_4 at slot #3
[P] submit P_5 at slot #4
...
[P] submit P_10 at slot #9
[P] submit P_11 at slot #10
...
[P] submit P_136 at slot #10
[C] finish P_136 at slot #10
[P] submit P_137 at slot #10
...

```
货架（产品队列）几乎一直是满的，东西卖不出去。这就是所谓买方市场。

2、**卖方市场**

产能低下，消费者每 2ms 就要消费一次，然而生产者 40ms 才能生产一个：
```bash
$ java SemaphoreDemo 10 2 10 10 40
[P] submit P_1 at slot #1
[C] finish P_1 at slot #1
[P] submit P_2 at slot #1
[C] finish P_2 at slot #1
[P] submit P_3 at slot #1
[P] submit P_4 at slot #2
[C] finish P_4 at slot #2
[C] finish P_3 at slot #1
[P] submit P_5 at slot #1
...
[C] finish P_69 at slot #1
[P] submit P_70 at slot #1
[C] finish P_70 at slot #1
...
```
货架几乎总是空的，供不应求。这就是所谓卖方市场。

3、**平衡的状态**

生产速度和消费速度基本持平：
```bash
$ java SemaphoreDemo 10 20 20 20 20 > result  # wait for some time
^C
$ cat record | awk '{print $NF}' | sort | uniq -c | sort -nk1
   1030 #6
   1142 #4
   1211 #1
   1220 #5
   1282 #7
   1301 #2
   1306 #3
   1384 #8
   1404 #9
   1642 #10
```
货架空的时候和满的时候都是有的。不过看起来相较不空不满的状态，空和满的状态出现的比较多，为什么呢？~~可见人就是容易冲动走极端。~~

其实是模型的问题。货架全空（全满）时，消费（生产）常常被阻塞；而不空不满时，货架状态倾向于顺畅地变化。所以，处于全空或全满的时间会久一些。

就像弹簧的简谐振动，原长附近速度较大，最短/最长处速度较小。如果等时间间隔地采样，会发现弹簧处于最短/最长处的概率大一些。


## 实验演示：错误的程序

交换信号量操作与临界区互斥锁：
```java
private abstract class AbstractMan implements Runnable {
    public void run() {
        while (true) {
            try {
                Thread.sleep(rand.nextInt(max_sleep_time));
                synchronized (mutex) {  // down(mutex)
                    first.acquire();
                    critical_region();
                    Thread.sleep(rand.nextInt(max_work_time));
                    second.release();
                }  // up(mutex)
           } catch (InterruptedException e) {
                break;
           }
        }
    }
}
```

运行后很快就**死锁**了：
```bash
$ java SemaphoreDemo 10 20 20 20 20
[P] submit P_1 at slot #1
[C] finish P_1 at slot #1
[P] submit P_2 at slot #1
[C] finish P_2 at slot #1
[P] submit P_3 at slot #1
[C] finish P_3 at slot #1
^C  # 死锁，手动杀死
```

原因也是显而易见的。至少以下两种情况都会死锁：

1. 货架空时，消费者进入临界区，进行消费时被阻塞住，而生产者被阻塞在临界区外；
2. 货架满时，生产者进入临界区，进行生产时被阻塞住，而消费者被阻塞在临界区外。
