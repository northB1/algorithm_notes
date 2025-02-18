#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/*	�������ڽӱ�
		����ģ������ 
			1.����ģ�ⵥ���� ,�ڽӱ�,�洢ͼ,�� (��̬����)
				������ head->[3|*]->[5|*]->[8|*]->NULL
							 0      1      2 
				������������ֱ��ʾ,Ԫ����,ָ����
			Ԫ���� elem[x] ���� x�Žڵ��Ԫ��ֵ 
				elem[0]=3,elem[1]=5,elem[2]=8, 
				
			ָ���� next[p] ����ָ����һ��Ԫ�ص������ 
				next[0]=1,next[1]=2,next[2]=-1,
				
			�ŵ�:����new�����ᵼ�³�ʱ,�Ҿ�̬�����ٶȺܿ�,�����ΪO(1)���� 
		
			
*/ 
const int N = 100;
int elem[N];
int next[N];
int head;   //ͷ�ڵ� 
int idx;	//�洢��ǰ�õ��ĵ� 

void init(){
	head=-1;
	idx=0;
} 
void add_to_head(int x){ // ͷ�巨 O(1)
	next[idx]=head;
	elem[idx]=x;
	head=idx;
	idx++;
}
void insert(int k,int x){ //���뵽k��֮�� O(1) 
	next[idx]=next[k];
	elem[idx]=x;
	next[k]=idx;
	idx++; 
}
void remove(int k){  //��k�����ĵ�ɾ�� O(1)
	next[k] = next[next[k]]; 
	//k->next = k->next->next 
} 
/* ����:������²���
m������ 
H x ͷ��xԪ��;
I k x ��kλ�ò���Ԫ��x
D k ɾ��k����ĵ� 

10
H 9
I 1 1
D 1
D 0
H 6
I 3 6
I 4 5
I 4 5
I 3 4
D 6 
*/ 

void test(){
	int m;
	cin>>m;
	init();
	/**/
	while(m--){
		char op;
		cin>>op;
		if(op=='H'){
			int x;
			cin>>x;
			add_to_head(x);
		}
		else if(op=='I'){
			int k,x;
			cin>>k>>x;
			insert(k-1,x);
		}
		else if(op=='D'){
			int k;
			cin>>k;
			if(k==0)	head=next[head];//ɾ��ͷ�ڵ��������
			remove(k-1);
		}
	} 
	for(int i = head;i != -1;i = next[i])	cout<<elem[i]<<' ';
	cout<<endl;
} 

/*	2.����ģ��˫���� 
	˫����  head->[*|3|*]<=>[*|5|*]<=>[*|8|*]<-tail
	          0                                 1 
	��ʼ���ʱ:headΪ���, tailΪһ��
	int elem[]
	int l[],r[]; 
	 

*/
int elem_[N];
int l[N],r[N]; 
void init_(){
	r[0] = 1;
	l[1] = 0;
	idx = 2;
}                     //   k
void add(int k,int x){//[l|*|r]<=>[l|*|r]
					  //     [l|*|r]idx
	elem_[idx]=x;
	r[idx]=r[k];
	l[idx]=k;
	l[r[k]]=idx;
	r[k]=idx;
}
                   //  k
void remove_(int k){//[l|*|r]<=>[l|*|r]<=>[l|*|r]
	r[l[k]]=r[k];
	l[r[k]]=l[k];
}
/*	����ģ��ջ�Ͷ���
	STL�����ģ��,����ȡ�������
	 
*/
int stk[N];
int top=-1;

void push(int x){
	stk[++top];
}
int pop(){
	return stk[top--];
}
bool isEmpty(){
	return top<0;
}
int getTop(){
	return stk[top];
}

int que[N];
int hh=0,tt=-1;

void push_(int x){
	que[++tt];
}
int pop_(){
	return que[hh++];
}
bool isEmpty_(){
	return hh>tt;
}
int gethh(){
	return que[hh];
}
int gettt(){
	return que[tt];
}

/*	����ջ����
	�ҵ����������С��������,����������,�����ڷ���1
	����:3  4  2  7  5
	ans: -1 3  -1 2  2
	
	����:i��������������,j��i��ǰ����Ѱ��,O(n^2) 

*/
const int N2 = 5;
int q[N2]; 

void voilent(){
	for(int i=0;i<N2;i++){
		int j;
		for(j=i;j>=0;j--){
			//printf("[%d,%d]",q[i],q[j]);
			if(q[j]<q[i]){
				printf(" %d",q[j]);	
				break;
			}	
		}
		if(j==-1)	printf(" %d",j);
	} 
} 
/*	����ջ�Ż�:
		���ֹ���,���������Ԫ��������ջ,����ջ������Ѱ��,�ᷢ��
			[ 2 3 4 ]  <-1 
				  top	
		��һ����һ��Ԫ����ջʱ,�������ջ��Ԫ�ظ�С,ջ��Ԫ������Զ���ᱻ����, ���Լ��ٷ��ʴ��� 
		�ҵ���������Ԫ�ص�����ջ�����Ǵ� 

*/
void monotone_stack(){
	int stk[N2]={0};
	int top=-1;
	
	for(int i=0;i<N2;i++){
		while(q[i]<stk[top] && top!=-1)	top--;	//��ջ 
		
		if(top == -1)	printf(" -1"); //ջ�����Ǵ� 
		else printf(" %d",stk[top]);
		
		stk[++top]=q[i];	//��ջ 
	}
	
}

void test1(){
	int a[N2]={3,4,2,7,5};
	for(int i=0;i<N2;i++)	q[i]=a[i];
	//voilent();
	monotone_stack();
} 

/* ����_������������:
	һ������,��һ����������,����ÿ�ΰ���3��Ԫ��,����ÿ�������ƶ�һ��,�����������С������
	[1 3 -1] -3 5 3 6 7 	-1 
	1 [3 -1 -3] 5 3 6 7     -3 
	1 3 [-1 -3 5] 3 6 7     -3 
	1 3 -1 [-3 5 3] 6 7     -3 

ans: -1 -3 -3 -3 3 3

����:˫ָ��ά������,ÿ�ƶ�һ��,����ȡ��С 
��������: [3 -3]	  ����ͷԪ��<ǰ���Ԫ��ʱ,ǰ���Ԫ����Զ������Ϊ�� ,��β���� 
	      hh  tt     
	�� [-3 -1 ] -2  ����Ԫ��<��ͷԪ��,���ͷ���� 
	��ά��������Զ��[-3 -1 1] �����������,���βp[hh]����� 


*/ 
const int N3 = 8;
int a[N3]; 
int min(int a,int b){
	return a<b?a:b;
}
void voilent_(int k){
	int m;
	for(int i=0;i<N3-k+1;i++){
		int j=i+k-1;
		m=a[i];
		while(j>i)	m=min(m,a[j--]);
		printf("%d ",m);
	}
} 
void monotone_queue(int k){
	int qu[N3]={0};
	int hh=0,tt=-1;
	for(int i=0;i<N3;i++){
		if(hh<=tt && i-k+1 > q[hh]) 	hh++;//�ж϶�ͷ�Ƿ񻬳�����  i-k+1 > q[hh]  
		                                     //                                 i 
	                                         //���д洢�±�            1 [2  5  9]   k=3; 
	                                         //                    �±�0 {1  2  3}
	                                          //                         hh
		while(hh<=tt && a[q[tt]] >= a[i])	tt--;//������Ԫ��<��ͷԪ��,��ͷ���� 
		                   
		q[++tt]=i;
		if(i>=k-1) 	printf("%d ",a[q[hh]]);
	}
	
}
int test2(){
	int q[N3]={1,3,-1,-3,5,3,6,7};
	for(int i=0;i<N3;i++)	a[i]=q[i];
	//voilent_(3);
	monotone_queue(3);
}

int main(){
	//test();
	//test1();
	test2();
	
}
