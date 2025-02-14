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
	if(l>=r)  return;  //���� 
	int i=l-1;    //      i  {3,......,9}  j
	int j=r+1;    //λ: l-1  [l,      ,r]  r+1
	              //          x 
	int x=a[l];    //ѡȡ���Ƚ�����(��) 
	
	while(i<j){  //һ������ 
		do i++;while(a[i]<x);   //���� i-> 
		do j--;while(a[j]>x);   //����  <-j 
		if(i<j)	  swap(a,i,j);  //��Ԫ�ؽ��� 
	} 
	//һ�������          i 
	//Ԫ��Ϊ����:    [l,   ,e,   ,r]   ����ʱ i=j 
	//		       (      j)(    ) 
	// 				  
	//					   i 
	//Ԫ��Ϊż��:    [l,    ,e,   ,r]   ����ʱ i>j                    
	//               (    j)(j+1   ) 
	
	QuickSort(a,l,j);     
	QuickSort(a,j+1,r);
}*/

void MergeSort(int a[],int l,int r){
	if(l >= r)  return;
	int mid = (l+r)/2;  //l+r >> 1;
	MergeSort(a,l,mid);
	MergeSort(a,mid+1,r);//�ȷ� ���� 
	
	//������һ������,����˫ָ��ɨ�� 
	//                                          �൱��      i->
	//������a:   [l,      ,mid,mid+1,   ,r]      ====>     [l,      ,mid] 
	//            i->              j->                     [mid+1,    ,r]
	//                                                      j->
	//��ʱ����tmp   [  ,  ,           ,  ,  ] 
    //               k-> 
	
	int k=0,i=l,j=mid+1;
	while( i<=mid && j<=r ){   //������ָ�붼û���յ������,˭С����tmp������ 
		if(a[i] <= a[j])		tmp[k++] = a[i++];//Ϊ�˱�֤�ȶ���,��q[i]=q[j]ʱ,i�ȱ�����
		else if(a[i] > a[j])	 tmp[k++] = a[j++];
	}
	//��ĳ��ָ�뻬�պ�,����ɨβ���� 
	while(i<=mid)  tmp[k++]=a[i++];
	while(j<=r)   tmp[k++]=a[j++];
	//��tmp��ʱ��������ݻ���a���� 
	for(i=l,j=0;i<=r;i++,j++){
		a[i]=tmp[j];
	}
	
	//�߽�����: ��С��������������Ϊ[l,r]  mid=(l+r)/2,Ҳ����mid==l;  
	//                               i j
}
	
	
void swap(int a[],int i,int j){
	int temp=a[i];
	a[i]=a[j];
	a[j]=temp;
}


