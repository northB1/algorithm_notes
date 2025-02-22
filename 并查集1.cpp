#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/* ���鼯
	���ٴ���:
		1.���������Ϻϲ�
		2.ѯ������Ԫ���Ƿ�����һ�����ϵ���
	����:��������ֱ���m��,n�� ,�ϲ�,����,ȥ��O((m+n)log(m+n)) 
	���鼯:����O(1)  ��һ������ά��һ������
	     []�����ı�ž����������ı��,��ÿһ���ڵ�洢�丸�ڵ�
		/ \      p[x]��ʾx�ĸ��ڵ� 
	  []   []
     /  \  / \ 
    []  [][]  [] 

1.����ж�����if(p[x]==x)
2.���������ڵ�x�ؼ��ϱ��
	while(p[x]!=x) 	x=p[x];
3.�ϲ�:���2�ĸ����ڼ���1�Ķ��� 
	 	p[x]      =    y 
       [ y ]
	 /	/ | \ 
   [x] [] [] [] 
  / | \   
[] [] [] 	 	
	 	
4.�Ż�:·��ѹ�� 
  ����: 
    	 []
		/ 
	  []                                            [ ] 
     /                                             / | \ 
   [x] ʱ ,��x�ĸ��ڵ�,˳�����ø����ӽڵ�ĸ�    [] [] [x] ��ʱÿ��ѯ�ʵ�ʱ�临�Ӷ�ΪO(1) 
   
   
����:�ϲ���������,ѯ������Ԫ���Ƿ���ͬһ�����ϵ���
4 5
M 1 2
M 3 4
Q 1 3
M 1 3
Q 1 3 
����ά������:
	1.ͳ��Ԫ�ظ���:��һ�������������ά���������ϵ�ĸ���O(1)
	size[N],���ҽ��и��ڵ��size���������,��ÿ�κϲ�ʱ��¼
	size[find(b)]+=size[find(a)]; 
 
*/
const int N = 100;
int n,m;//n���ڵ�,m�β��� 
int p[N];
int find(int x){ //����x�����ڽڵ� 
	if(p[x]!=x)		p[x]=find(p[x]); //���һ��ĵݹ�,ͬʱ��·������ѹ�� 
	return p[x];
}
void merge(int a,int b){
	p[find(a)] = find(b); //��a�����ڽڵ����b�����ڽڵ� 
} 
bool isInSame(int a,int b){
	return find(a)==find(b);	
}
void test(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		p[i]=i;		//ÿ�ζ���һ���µĽڵ�,��������� �ҽڵ�Ĭ��Ϊ1 2 3 4 ... 
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
