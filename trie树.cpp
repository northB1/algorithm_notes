#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;
/*	trie�� �ֵ��� 
	����:���ڿ��ٴ洢�����ַ������ϵ����ݽṹ,����,����д,��Сд O(n) 
	*���ʽ�β���
	����:(�洢) 
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
����:
abcf,һ·���������ֲ�����f
abcd,����d��û��* ���,������


����:

���ֲ���:
I x �����ַ���x
Q xѯ���ַ���x 
���ܳ� <1e5

4
I abcd
I acd
Q acd
Q ace

���
1
0 
*/ 

/* son����ṹ
	son[p][u]  �ӽڵ�p����,�ַ�u ��Ӧ���ӽڵ������ 
	   
	   �洢:ef ed 
	   
 	        	   root son[0][4]=1 �Ӹ�����,��ĸΪe�Ľڵ���Ϊ 1 
 	        	  /    
			     e 				
son[1][5]=2     / \ 	son[1][3]=3��e����,��ĸΪd�Ľڵ���Ϊ 3
               f   d
	
  	
*/ 
const int N = 1000;
int son[N][26]; //26��ӳ���Ӧ26����ĸ 
int cnt[N];  	//�������¼ 
int idx;		//�����ĵ�idx���� 
char str[N]; 
 
void insert(char str[]){
	int p=0;
	for(int i=0;str[i];i++){
		int u=str[i]-'a';    // u ���ַ��������ӳ�� 
		if(!son[p][u])	son[p][u]= ++idx;//���û�� ����
		p=son[p][u];    // ��p����,Ѱ����ĸΪu ���ӽڵ� 
	}
	cnt[p]++; 
}
bool search(char str[]){
	int p=0;
	for(int i=0;str[i];i++){
		int u=str[i]-'a';    // u ���ַ��������ӳ�� 
		if(!son[p][u])	return false;//���û�� û�ҵ� 
		p=son[p][u];    // 
	}
	return cnt[p]!=0; 
}


void test1(){
	int n;
	scanf("%d",&n);
	
	while(n--){
		char op[2];           
		scanf("%s%s",op,str);//�������� I abcd�����������ַ�������������,%s�Կո�ȷֿ� 
		if(op[0]=='I')	insert(str);
		else printf("%d",search(str));
	} 
}
int main(){
	test1();
}
