#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/* 双映射
   给你一个无序数组Arr[],你要用一个数组Cnt[]来保存元素被录入的顺序,将数组进行交换操作 
   根据"第k个被录入的元素" ,O(1)访问该元素 


 */
const int N = 100;
int Arr[N];
int Arr_Order[N]; //Arr_Order[k]在数组Arr中,数组标为k的元素,是第几个被插入的元素 (在录入元素时,就可以顺序记录元素插入顺序的数组) 
int Order_Arr[N]; //Order_Arr[k],第k个被插入的点,是Arr数组中哪个元素的下标 
int size;

/*
7
9 5 10 6 8 1 7

*/
void swap_Arr(int a,int b){
	int temp = Arr[a];
	Arr[a] = Arr[b];
	Arr[b] = temp;
	
	swap(Order_Arr[Arr_Order[a]],Order_Arr[Arr_Order[b]]); 
	swap(Arr_Order[a],Arr_Order[b]);
} 
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;	
}
void printArr(){
	for(int i=0;i<size;i++){
		printf(" %d\t",Arr[i]);
	}
	printf("\n");
	for(int i=0;i<size;i++){
		printf("(%d)\t",Arr_Order[i]);
	}
	for(int i=1;i<=size;i++){
		printf("\n第%d个被插入的元素Arr[%d]:%d",i,Order_Arr[i],Arr[Order_Arr[i]]); 
	}
	
}


void test(){
	int n;
	scanf("%d",&n);
	
	while(n--){
		scanf("%d",&Arr[size]);
		Arr_Order[size] = size+1;
		Order_Arr[size+1] = size; 
		size++;
	}
	printf("原数组,原顺序\n"); 
	printArr();
	
	swap_Arr(2,5);
	
	printf("\n\n交换\n"); 
	printArr();
	
	
}
int main(){
	test(); 
}
