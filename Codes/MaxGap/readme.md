# 最大间隙问题
元素分段法/分桶法（bucket）

算法实现题1-5 P10

![题目](https://github.com/GaofengDong/Computer-Algorithms/raw/master/Codes/MaxGap/suanfa1_5.png)

给定 n 个实数，求这n个实数在数轴上相邻2个数之间的最大差值，设计求解最大间隙问题的线性时间算法。

参考：https://blog.csdn.net/legend050709/article/details/38986157

## 思路
要求时间复杂度为O(n)，不能先排序再计算，使用元素分段法/分桶法（bucket）。

1. 首先遍历一遍数组，找到数组中的最大值max，最小值min.

2. 将[min,max]区间分为n-1份区域/桶，则每一个区域/桶的大小为len=(max-min)/(n-1);

    区间分别为：[min,min+len),[min+len,min+2* len),[min+2* len,min+3* len),...[max-len,max].
    

3. 由于是将n-2个数放入n-1个区间，因此至少有一个区间为空。这意味着，最大间隙至少要涉及到两个区间

    最大间距=相邻的两个区间 or 不相邻的两个区间，但中间区间没有元素； 且 是前一个区间的最大值与后一个区间的最小值之间产生。

4. 遍历一遍求出每个区间的最大值，以及最小值；然后再遍历一遍区域，比较每个区间的最小值与前一个非空区间的差，取最大就是最大间距。

