#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define N 10
int tmp[N];

void printArr(int a[]);
void initArr(int a[]);
void swap(int a[],int i,int j);
//void QuickSort(int a[],int l,int r);
void MergeSort(int a[],int l,int r);
 
int main(){
	int arr[N];
	initArr(arr);
	printArr(arr);
	
	MergeSort(arr,0,N-1);
	//QuickSort(arr,0,N-1);
	printArr(arr);
}

void printArr(int a[]){
	for(int i=0;i<N;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}

void initArr(int a[]){
	for(int i=0;i<N;i++){
		a[i]=rand()%100;
	}
}
/*
void QuickSort(int a[],int l,int r){
	if(l>=r)  return;  //出口 
	int i=l-1;    //      i  {3,......,9}  j
	int j=r+1;    //位: l-1  [l,      ,r]  r+1
	              //          x 
	int x=a[l];    //选取被比较数字(轴) 
	
	while(i<j){  //一次整理 
		do i++;while(a[i]<x);   //右移 i-> 
		do j--;while(a[j]>x);   //左移  <-j 
		if(i<j)	  swap(a,i,j);  //将元素交换 
	} 
	//一次整理后          i 
	//元素为奇数:    [l,   ,e,   ,r]   结束时 i=j 
	//		       (      j)(    ) 
	// 				  
	//					   i 
	//元素为偶数:    [l,    ,e,   ,r]   结束时 i>j                    
	//               (    j)(j+1   ) 
	
	QuickSort(a,l,j);     
	QuickSort(a,j+1,r);
}*/

void MergeSort(int a[],int l,int r){
	if(l >= r)  return;
	int mid = (l+r)/2;  //l+r >> 1;
	MergeSort(a,l,mid);
	MergeSort(a,mid+1,r);//先分 后治 
	
	//对任意一段数组,进行双指针扫描 
	//                                          相当于      i->
	//对数组a:   [l,      ,mid,mid+1,   ,r]      ====>     [l,      ,mid] 
	//            i->              j->                     [mid+1,    ,r]
	//                                                      j->
	//临时数组tmp   [  ,  ,           ,  ,  ] 
    //               k-> 
	
	int k=0,i=l,j=mid+1;
	while( i<=mid && j<=r ){   //在两个指针都没滑空的情况下,谁小计入tmp数组中 
		if(a[i] <= a[j])		tmp[k++] = a[i++];//为了保证稳定性,当q[i]=q[j]时,i先被存入
		else if(a[i] > a[j])	 tmp[k++] = a[j++];
	}
	//当某个指针滑空后,进行扫尾工作 
	while(i<=mid)  tmp[k++]=a[i++];
	while(j<=r)   tmp[k++]=a[j++];
	//把tmp临时数组的数据还给a数组 
	for(i=l,j=0;i<=r;i++,j++){
		a[i]=tmp[j];
	}
	
	//边界条件: 最小满足条件的数组为[l,r]  mid=(l+r)/2,也就是mid==l;  
	//                               i j
}
	
	
void swap(int a[],int i,int j){
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}


