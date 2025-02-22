#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/* ˫ָ������:
	��������������A��B,�Լ�һ��Ŀ��ֵx;
	���������A[i]+B[j]=x
	
	����:˫for,O(nm) 
	˫ָ��:
		��������A,B����������,�ҵ�һ��Ai+Bj >= x ,��j��Сʱ
		
		����:һ��ʼi,j��λ����: 
		   i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		           j 
		x=6; 
		
		�ҵ�һ��Ai+Bj >= x ,��j��Сʱwhile(A[i]+B[j]>x) 	j--;
		   i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		       j 
		       
		��ʱ: A[i]+B[j] > x ��A�ǵ�����,���к�����������������,i����++,
		���:j-- 
		
		   i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		     j 
		��ʱ: A[i]+B[j] < x,��B�ǵ�����,����ǰ��������������,j����--,
		���:i++
		
		     i 
		A [1 2 4 7]
		B [3 4 6 8 9] 
		     j 
		��ʱ:A[i]+B[j]==x  ��֤һ��� 
		     
		Ѱ��һ��ģ��
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
