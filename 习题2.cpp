#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/* 双指针例题:
	给两个有序序列A和B,以及一个目标值x;
	给出满足的A[i]+B[j]=x
	
	暴力:双for,O(nm) 
	双指针:
		由于数组A,B均递增有序,找到一个Ai+Bj >= x ,且j最小时
		
		例如:一开始i,j的位置如: 
		   i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		           j 
		x=6; 
		
		找到一个Ai+Bj >= x ,且j最小时while(A[i]+B[j]>x) 	j--;
		   i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		       j 
		       
		此时: A[i]+B[j] > x 而A是递增的,所有后面的数均不能满足答案,i不能++,
		因此:j-- 
		
		   i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		     j 
		此时: A[i]+B[j] < x,而B是递增的,所有前面的数不能满足答案,j不能--,
		因此:i++
		
		     i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		     j 
		此时:A[i]+B[j]==x  保证一组解 
		     
		寻找一个模型
		for(int i=0,j=m-1;i<n;i++){
			while(j>=0 && a[i]+b[j]>x)	j--;
			if(a[i]+b[j]==x)	printf("<%d,%d>\n",a[i],b[j]);
        }
	
*/
const int N = 100;
int a[N];
int b[N]; 
int n,m,x;

void voilent(){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i]+b[j]==x)	printf("<%d,%d>\n",a[i],b[j]);
		}
	}
} 
void doublePointer(){
	for(int i=0,j=m-1;i<n;i++){
		while(j>=0 && a[i]+b[j]>x)	j--;
		if(a[i]+b[j]==x)	printf("<%d,%d>\n",a[i],b[j]);
    }
}

void test1(){
	scanf("%d%d%d",&n,&m,&x);
	for(int i=0;i<n;i++)	scanf("%d",&a[i]);
	for(int i=0;i<m;i++)	scanf("%d",&b[i]);
	
	//voilent();
	doublePointer();
} 
/*
4 5 6
1 2 4 7
3 4 6 8 9
*/

int main(){
	test1();
}
