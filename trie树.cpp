#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/*	trie树 字典树 
	操作:用于快速存储查找字符串集合的数据结构,数字,仅大写,仅小写 O(n) 
	*单词结尾标记
	例如:(存储) 
abcdef 
abdef 
aced 
bcdf 
bcff 
abc 
                       root 
					  /    \ 
					a 		b				
				   / \		 \											
				  b	  c		  c																
				 / \   \	 / \																
                c*  d   d   d   f 
               /    /    \  |    \ 
              d    e      e f     f 
             /    /       * *     * 
			e    f 
		   /     * 
		  f 
		  * 
查找:
abcf,一路沿着树发现不存在f
abcd,发现d并没有* 标记,不存在


例题:

两种操作:
I x 插入字符串x
Q x询问字符串x 
串总长 <1e5

4
I abcd
I acd
Q acd
Q ace

输出
1
0 
*/ 

/* son数组结构
	son[p][u]  从节点p出发,字符u 对应的子节点的索引 
	   
	   存储:ef ed 
	   
 	        	   root son[0][4]=1 从根出发,字母为e的节点编号为 1 
 	        	  /    
			     e 				
son[1][5]=2     / \ 	son[1][3]=3从e出发,字母为d的节点编号为 3
               f   d
	
  	
*/ 
const int N = 1000;
int son[N][26]; //26个映射对应26个字母 
int cnt[N];  	//结束点记录 
int idx;		//创建的第idx个点 
char str[N]; 
 
void insert(char str[]){
	int p=0;
	for(int i=0;str[i];i++){
		int u=str[i]-'a';    // u 是字符在数组的映射 
		if(!son[p][u])	son[p][u]= ++idx;//如果没有 创建
		p=son[p][u];    // 从p出发,寻找字母为u 的子节点 
	}
	cnt[p]++; 
}
bool search(char str[]){
	int p=0;
	for(int i=0;str[i];i++){
		int u=str[i]-'a';    // u 是字符在数组的映射 
		if(!son[p][u])	return false;//如果没有 没找到 
		p=son[p][u];    // 
	}
	return cnt[p]!=0; 
}


void test1(){
	int n;
	scanf("%d",&n);
	
	while(n--){
		char op[2];           
		scanf("%s%s",op,str);//例如输入 I abcd可以用两个字符串数组来接收,%s以空格等分开 
		if(op[0]=='I')	insert(str);
		else printf("%d",search(str));
	} 
}
int main(){
	test1();
}
