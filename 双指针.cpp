#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int max(int a,int b){
	return a>b?a:b;
}
/* 双指针算法
	例如:快排,归并排序也是运用双指针 
	主要作用:优化O(n^2)的双循环,利用i,j之间的性质减少大量计算
		O(n^2)版本 
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				//执行逻辑 
			}
		}
		
	双指针优化版: 通过检查i,j之间的性质,例如单调性等,减少大量计算
		for(int i=0;i<n;i++){
			while(j<i && check(i,j)){
				//执行逻辑
			}
		} 
*/
/*
	例题:给定一个数组,找出最长不包含重复数字的子序列,数据范围(0,10) 
		例如 [1,2,2,3,5]  ans:5 
	1.双for暴力搜索,i和j枚举出所有连续字串,逐一检查是否有重复,
	当check(i,j)为O(1)时,总复杂度为 O(n^2)
	2.双指针 
	(j	 i->
	[1,2,2,3,5]
    让i作为头部.j作为尾部,
	i向右移动并枚举,检查(i,j) 区间是否有重复元素 
		1.有重复  j一直右移,直到排除重复元素 
		2.没有重复  计算最大长度,i继续枚举 
	总复杂度为 O(2n) = O(n)
	
	问题:check(i,j)如何做到O(1)? 利用一个数组充当记录表 
	int S[N]; N是数据域,S[2]存储了'2'出现的次数 
	利用S[q[i]]++表示q[i]出现了一次 
	
	也可用哈希表来存储 
*/
const int N = 10; 
int q[N];
int S[N]; 

int doublePointer(int n){
	int ans=0;
	for(int i=0,j=0;i<n;i++){
		S[q[i]]++; 			// S[q[i]]++;元素q[i]出现的次数+1 
		while(S[q[i]]>1){	// S[q[i]]>1;当元素q[i]出现过一次以上时(重复出现),说明(j,i)之间有重复元素 
			S[q[j]]--;	//被排出的元素取消标记  
			j++;		// j一直右移,直到排除重复元素,i才能继续枚举 
		}	
		ans=max(ans,i-j+1); 
	}
	return ans;
}

void test1(){
	int n=5;//数据量 
	int a[n]={1,2,2,3,5};
	for(int i=0;i<n;i++)	q[i]=a[i];
	printf("%d",doublePointer(n));
}


/* 位运算
				x=10 
源码:1010       x 
反码:0101		~x 
补码:反码+1 	~x+1 

	例题1:n的二进制表示中第k位是几
		例如n=10=(1010),右移1位(101) 
		思路:1.将第k位右移到最后一位,n>>k
			 2.将个位 与1,&1; 
		 
		 
*/ 
void DtoB(int n){	//位运算转二进制  
	int k=0; 
	vector<int> ans; 
	while(n>>k){
		ans.push_back((n>>k & 1)); 
		k++; 
	}
	reverse(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)	printf("%d",ans[i]);
		
} 
/*	反回x的最后一位1,利用 x&-x = x&(~x+1)
	         * 
		 x=101000  lowbit(x)=1000 
	例如x=10100001000
	   ~x=01011110111 
   (~x+1)=01011111000 =x&-x
 x&(~x+1)=00000001000 
 lowbit用处:统计x中1的个数 
*/
int lowbit(int x){ 
		return 	x&-x;		 		 
} 
int lowbit_calculate_numof1(int n){ //统计x中1的个数 
	int ans=0;
	while(n){
		n-=lowbit(n),ans++;//每次剪掉最后一位1,见几次就有几个1 
	}
	printf("%d",ans);
	return ans;
} 


void test2(){
	DtoB(15);
	lowbit_calculate_numof1(15);
}

int main(){
	//test1();
	 test2();
} 
 
