# Taxi Searcher

马子轩 2015012283

## 需求分析

### 原始需求

乘客给出起点,寻找5辆满足条件的出租车.

条件1: 出租车距离乘客的距离不超过10km

条件2: 出租车上如果有乘客,乘客的绕路距离不超过10km

提供交互UI

使用路网数据

### 扩展需求

乘客给出起点与终点

要求出租车距离乘客起点不超过10km



我针对绕路设定进行了修改细化

因为我们不知道车上乘客的起点,因此我使用当前乘客所在位置,即出租车位置进行计算.

对于每个乘客:

绕路距离=实际走的距离-应该走的距离

每个乘客,在规划好的路线上,绕路距离均不超过10km



UI显示:

返回的车辆数据,规划的行车路线,乘客的送达顺序,绕路距离等

使用路网数据



## 算法分析

### 数据分析

首先，地图中横坐标差值不超过190000m,纵坐标差值不超过160000m

同时，路网数据中，两点间距离就是两点欧几里得距离.即所有线均为直线。

因此，有两点间路网距离>两点间欧几里得距离

### 算法设计

使用candidate-validate模型

第一轮

首先,将整个地图分成38\*32块.每块5000\*5000.

这时,可以把搜索范围降低到25个块

0 0 0 0 0 0 0

0 1 2 3 2 1 0

0 2 4 5 4 1 0

0 3 5 6 5 3 0

0 2 4 5 4 1 0

0 1 2 3 2 1 0

0 0 0 0 0 0 0

按优先度从大到小顺序搜索

可知，不在这25方格内的数据欧几里得距离一定不满足，因此路网距离也一定不满足

第二轮

对搜索到的车辆，先使用欧几里得距离判断

车辆距离是否满足条件

针对乘客使用先送最近的策略.此策略平均绕路距离最短.

而实际生活中，司机往往也是采用这个策略，也能拿到比较好的结果.

针对每个乘客计算绕路距离.

如果车辆距离和乘客绕路距离均满足条件，进入下一轮

第三轮

使用之前的送达顺序，使用单源最短路算法，判断是否满足条件

过程和之前一致。

### 算法分析

优点，能够有效减少搜索量，提高速度

缺点，理论上存在路网中绕路最优顺序和欧几里得绕路最优顺序不同的情况，这时算法可能有遗漏

但是由于数据是实际数据，这种情况出现的可能性较低.



## 设计实现

### 设计环境

由于考虑到UI设计,我使用了python语言，方便进行设计.

但是由于python语言的特性，其运行速度缓慢，同样的算法比c++慢10倍以上.

我的算法在c++中可以1s之内出结果，但是在使用python重写并接进UI后可能需要3~8s的时间.

这一情况可以在使用python嵌入c++来实现.但是其工作量较大，而且和本课程内容无关.因此,我没有做这个工作

后续扩展可以考虑这一点.

### 界面设计

左上角两个文本框表示起点与终点的编号

按下search按钮后弹出地图

地图包括5辆车的行车路线和停车节点

其中黑色是起点，空心黑色是终点，其他颜色为乘客下车点

主界面左下角会显示地图比例尺,右侧为候选出租车的信息，包括行车路线，绕路距离等

这一部分实现较为粗糙，但是能够明确地把信息显示出来.



## 程序框架

环境依赖

wxpython

```shell
pip install wxpython --user
```

组织结构

data/

三个数据文件

src/所有代码

初始化

```shell
cd src
python clean.py
python net.py
python ana.py
```

会在data/中生成若干文件,简化后续操作

运行

```shell
python app.py
```



## 总结展望

我在这个大作业中使用了课程中学习到的candidate-validate框架.有效的提高了程序效率

同时针对路网数据与地图这种数据，有了一定的认识与了解.

这个作业设计中，遇到的挑战有.python语言运行速度太慢，同样算法在c++能拿到很好的结果，但是python就比较慢.

收获有.就是学习了python语言实现桌面app的过程.同时复习了图论的一些算法.

整学期下来，我觉得最重要的一个思想就是，索引。这也是我理解中，数据库非常重要的组成部分。

针对不同的查询需求，对数据建立索引，用来减少搜索空间。加快速度，这个思想是我认为的这学期最大的收获。希望将来能够利用起来。
