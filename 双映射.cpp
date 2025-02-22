#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/* ˫ӳ��
   ����һ����������Arr[],��Ҫ��һ������Cnt[]������Ԫ�ر�¼���˳��,��������н������� 
   ����"��k����¼���Ԫ��" ,O(1)���ʸ�Ԫ�� 


 */
const int N = 100;
int Arr[N];
int Arr_Order[N]; //Arr_Order[k]������Arr��,�����Ϊk��Ԫ��,�ǵڼ����������Ԫ�� (��¼��Ԫ��ʱ,�Ϳ���˳���¼Ԫ�ز���˳�������) 
int Order_Arr[N]; //Order_Arr[k],��k��������ĵ�,��Arr�������ĸ�Ԫ�ص��±� 
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
		printf("\n��%d���������Ԫ��Arr[%d]:%d",i,Order_Arr[i],Arr[Order_Arr[i]]); 
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
	printf("ԭ����,ԭ˳��\n"); 
	printArr();
	
	swap_Arr(2,5);
	
	printf("\n\n����\n"); 
	printArr();
	
	
}
int main(){
	test(); 
}
