#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/* 并查集
	快速处理:
		1.将两个集合合并
		2.询问两个元素是否在用一个集合当中
	暴力:两个数组分别有m个,n个 ,合并,排序,去重O((m+n)log(m+n)) 
	并查集:近乎O(1)  用一个树来维护一个集合
	     []树根的编号就是整个树的编号,让每一个节点存储其父节点
		/ \      p[x]表示x的父节点 
	  []   []
     /  \  / \ 
    []  [][]  [] 

1.如何判断树根if(p[x]==x)
2.如何求任意节点x地集合编号
	while(p[x]!=x) 	x=p[x];
3.合并:令集合2的根等于集合1的儿子 
	 	p[x]      =    y 
       [ y ]
	 /	/ | \ 
   [x] [] [] [] 
  / | \   
[] [] [] 	 	
	 	
4.优化:路径压缩 
  当有: 
    	 []
		/ 
	  []                                            [ ] 
     /                                             / | \ 
   [x] 时 ,求x的根节点,顺便重置各个子节点的根    [] [] [x] 此时每个询问的时间复杂度为O(1) 
   
   
操作:合并两个集合,询问两个元素是否在同一个集合当中
4 5
M 1 2
M 3 4
Q 1 3
M 1 3
Q 1 3 
其他维护操作:
	1.统计元素个数:来一个额外的数组来维护各个集合点的个数O(1)
	size[N],而且仅有根节点的size是有意义的,在每次合并时记录
	size[find(b)]+=size[find(a)]; 
 
*/
const int N = 100;
int n,m;//n个节点,m次操作 
int p[N];
int find(int x){ //返回x的祖宗节点 
	if(p[x]!=x)		p[x]=find(p[x]); //天才一般的递归,同时对路径进行压缩 
	return p[x];
}
void merge(int a,int b){
	p[find(a)] = find(b); //让a的祖宗节点等于b的祖宗节点 
} 
bool isInSame(int a,int b){
	return find(a)==find(b);	
}
void test(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		p[i]=i;		//每次读入一个新的节点,先让其孤立 且节点默认为1 2 3 4 ... 
	}
	while(m--){
		char op[2];
		int a,b;
		scanf("%s%d%d",&op,&a,&b);
		
		if(op[0]=='M')  	merge(a,b);
		else if(op[0]=='Q'){
			if(isInSame(a,b))	puts("yes");
			else puts("no");
		}else puts("ERROR");
	}
} 

int main(){
	test();
} 
