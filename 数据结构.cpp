#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/*	链表与邻接表
		数组模拟链表 
			1.数组模拟单链表 ,邻接表,存储图,树 (静态链表)
				单链表 head->[3|*]->[5|*]->[8|*]->NULL
							 0      1      2 
				利用两个数组分别表示,元素域,指针域
			元素域 elem[x] 保存 x号节点的元素值 
				elem[0]=3,elem[1]=5,elem[2]=8, 
				
			指针域 next[p] 保存指向下一个元素的数组标 
				next[0]=1,next[1]=2,next[2]=-1,
				
			优点:由于new操作会导致超时,且静态链表速度很快,大多数为O(1)访问 
		
			
*/ 
const int N = 100;
int elem[N];
int next[N];
int head;   //头节点 
int idx;	//存储当前用到的点 

void init(){
	head=-1;
	idx=0;
} 
void add_to_head(int x){ // 头插法 O(1)
	next[idx]=head;
	elem[idx]=x;
	head=idx;
	idx++;
}
void insert(int k,int x){ //插入到k点之后 O(1) 
	next[idx]=next[k];
	elem[idx]=x;
	next[k]=idx;
	idx++; 
}
void remove(int k){  //将k点后面的点删掉 O(1)
	next[k] = next[next[k]]; 
	//k->next = k->next->next 
} 
/* 例题:完成以下操作
m个操作 
H x 头插x元素;
I k x 在k位置插入元素x
D k 删除k后面的点 

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
			if(k==0)	head=next[head];//删除头节点特殊情况
			remove(k-1);
		}
	} 
	for(int i = head;i != -1;i = next[i])	cout<<elem[i]<<' ';
	cout<<endl;
} 

/*	2.数组模拟双链表 
	双链表  head->[*|3|*]<=>[*|5|*]<=>[*|8|*]<-tail
	          0                                 1 
	初始情况时:head为零号, tail为一号
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
/*	数组模拟栈和队列
	STL库存在模板,但存取并不灵活
	 
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

/*	单调栈问题
	找到离他最近的小于他的数,返回其数字,不存在返回1
	例如:3  4  2  7  5
	ans: -1 3  -1 2  2
	
	暴力:i来便利所有数字,j从i向前遍历寻找,O(n^2) 

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
/*	单调栈优化:
		发现规律,如果将所有元素依此入栈,并从栈顶向下寻找,会发现
			[ 2 3 4 ]  <-1 
				  top	
		当一个下一个元素入栈时,如果他比栈顶元素更小,栈顶元素则永远不会被访问, 可以减少访问次数 
		且当所有逆序元素弹出后栈顶就是答案 

*/
void monotone_stack(){
	int stk[N2]={0};
	int top=-1;
	
	for(int i=0;i<N2;i++){
		while(q[i]<stk[top] && top!=-1)	top--;	//出栈 
		
		if(top == -1)	printf(" -1"); //栈顶就是答案 
		else printf(" %d",stk[top]);
		
		stk[++top]=q[i];	//入栈 
	}
	
}

void test1(){
	int a[N2]={3,4,2,7,5};
	for(int i=0;i<N2;i++)	q[i]=a[i];
	//voilent();
	monotone_stack();
} 

/* 队列_滑动窗口问题:
	一个数列,有一个滑动窗口,窗口每次包含3个元素,窗口每次向右移动一个,输出窗口中最小的数子
	[1 3 -1] -3 5 3 6 7 	-1 
	1 [3 -1 -3] 5 3 6 7     -3 
	1 3 [-1 -3 5] 3 6 7     -3 
	1 3 -1 [-3 5 3] 6 7     -3 

ans: -1 -3 -3 -3 3 3

暴力:双指针维护区间,每移动一格,遍历取最小 
单调队列: [3 -3]	  当队头元素<前面的元素时,前面的元素永远不会作为答案 ,对尾出队 
	      hh  tt     
	当 [-3 -1 ] -2  发现元素<对头元素,则队头出队 
	则维护队列永远是[-3 -1 1] 有序递增序列,则对尾p[hh]保存答案 


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
		if(hh<=tt && i-k+1 > q[hh]) 	hh++;//判断对头是否滑出窗口  i-k+1 > q[hh]  
		                                     //                                 i 
	                                         //队列存储下标            1 [2  5  9]   k=3; 
	                                         //                    下标0 {1  2  3}
	                                          //                         hh
		while(hh<=tt && a[q[tt]] >= a[i])	tt--;//当插入元素<对头元素,对头出队 
		                   
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
