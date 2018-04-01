
/*
 * Copyright (C) 2018 GaofengDong @USTC
 * 
 * My github: https://github.com/GaofengDong
 *
 * Have fun!!!
 */

#include "stdafx.h"
#include "float.h"
#include "fstream"

//初始化每个区域最小值为double变量最大值，最大值为double型最小值
typedef struct _bucket
{
	double min = DBL_MAX, max = DBL_MIN;
}Bucket;

double maxGap(double *a, int n)
{
	double max = a[0], min = a[0];
	double bucketlen;

	//求最大最小值
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	//计算桶（每段区域）大小
	bucketlen = (max - min)*1.0 / (n - 1);
	Bucket *bucket = new Bucket[n - 1];

	//第一个和最后一个区域的最大最小值
	bucket[0].max = min; bucket[0].min = min;
	bucket[n - 2].max = max; bucket[n - 2].min = max;

	//将其他n-2个值放到n-1个区域中 并计算每个区域最大最小值
	for (int i = 0; i < n; i++)
	{
		int index;
		if (a[i] != min && a[i] != max)
		{
			index = (a[i] - min)*1.0 / bucketlen;
			if (bucket[index].max < a[i])
				bucket[index].max = a[i];
			if (bucket[index].min > a[i])
				bucket[index].min = a[i];
		}
	}

	//low最大间距前一个数 high最大间距后一个数 maxGap最大间距 curGap当前间距
	//最大间距出现的两个区域的前一个区域编号
	double low = 0, high = 0, maxGap = 0, curGap = 0;
	int pre = 0;

	//n-2个值分到n-1个区域 必有一个空区域
	//所以最大间距一定不在同一个区域出现：在相邻区域 或者 两个不相邻且中间区域为空的区域
	//最大间距一定是某一个区域的最小值与其前面一个区域的最大值的差 如果空区域跳过
	for (int i = 1; i < n - 1; i++)
	{
		if (bucket[i].max != DBL_MIN)//区域非空
		{
			curGap = bucket[i].min - bucket[pre].max;
			if (curGap > maxGap)
			{
				maxGap = curGap;
				low = bucket[pre].max;
				high = bucket[i].min;
			}
			pre = i;
		}
	}

	printf("the maxGap is %lf, between %lf and %lf\n", maxGap, low, high);
	return maxGap;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int count;
	double *num;
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("cannot open read file!\n");
		exit(0);
	}
	fscanf(fp, "%d", &count);
	num = new double[count];
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%lf", &num[i]);
	}
	fclose(fp);

	double a[] = { 2.3, 3.1, 7.5, 1.5, 6.3 };
	maxGap(num, count);
	return 0;
}

