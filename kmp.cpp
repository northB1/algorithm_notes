#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;


const int N = 10;
const int M = 5;
char S[]="abcdababc";//原串 
char p[]="dabab";//字串 
int next[M];// 

int voilent(){
	bool flag;
	int i=0;
	while(S[i]!='\0'){
		int k=i;
		int j=0;

		while(p[j]!='\0' && S[k]==p[j]){
			j++,k++;
		}
		if(p[j]=='\0')	return i;
		i++;
	}	
	return -1;
} 

/*	kmp字串匹配问题 
	一个人能走的多远不在于他在顺境时能走的多快，而在于他在逆境时多久能找到曾经的自己。

	暴力求解:双for ,原串长n,子串长m,则时间复杂度为O(nm) 
	
	
	在kmp算法中,出现以下情况时: 
	原串:A B A B A B C D D 
	子串 A B A B C
	             ^  
	    给子串设立一个next数组,也就是跳过匹配的字符个数
		达到以下效果
	             
	原串:A B A B|A|B C D D 
	子串 A B A B|C| 
	next 0 0 1 2|0|   //C不匹配,跳过两个字符进行匹配 
                 j 
    原串:A B A B|A|B C D D 
	子串     A B|A|B C
	next     0 0|1|2 0 
                 j -> 
                 
	由于*指针不进行回溯,时间复杂度O(n),求解next数组时间复杂度为O(m)	,总复杂度O(m+n)	 
	通俗的来说:由于某次比较发现,子串如果具有一定规律或周期,就可以跳过周期段进行比较 
	 
*/
int kmpSearch(){
	int i=0;//主串指针 
	int j=0;//字串指针
	while(i<N){
		if (p[j] == S[i]) { // 如果当前字符匹配，继续匹配下一个字符
            i++,j++;
        }
        
		if (j == M) {//如果完全匹配，输出匹配的位置
            return i-j;
            //j = next[j - 1];  // 继续寻找下一个匹配
        }else if (i < N && p[j] != S[i]) {  // 如果不匹配
            if (j != 0)    j = next[j - 1]; //且j不为0，跳过next[j - 1]个字符进行比较 
            else i++;                       // 且j为0，则继续下一个字符
        }
	}
	return -1; 
} 
/* next数组 
	求解next数组时,仅需要对字串进行操作, 
	当子串的前缀和后缀是一样的,就可以跳过比较
	(因为当主串和子串在比较到C时,说明前四个字符已经匹配成功也就知道了主串的信息)
	且前后缀一定要最长的 
	      A B A B|A|B C D D   
	例如  A B A B C
	      --- ~~~
		  前缀和后缀是一样的,便可以 跳过前两个
		   
		  
	求解next数组:
		A B A B C
		*             //第一个字符肯定为0,因为前后缀不能是自己 
   next:0 
   
   		A B A B C
		  *           //前缀A,后缀B,不一样,0 
   next:0 0 

		A B A B C
		    *         //最长前缀A,最长后缀A, 可跳过1个 
   next:0 0 1
   
   		A B A B C
		      *       //最长前缀AB,最长后缀AB, 可跳过2个 
   next:0 0 1 2 
    
    	A B A B C
		        *     //没有一样的前后缀.0 
   next:0 0 1 2 0     
--------------------------------------------递归求解前后缀 
    当(A B)A C[A B]A B 为子串时: 
           *       * 
       0 0 1 0 1 2    如果下一个字符依然相同的话,当前缀长为:前缀长+1

    当(A B A)C[A B A]B 为子串时: 
             *       * 
       0 0 1 0 1 2 3    如果不同了,不着急填0,因为有可能出现比如 AB这样的更长的缀 
	  					 我们知道B 前面的[ABA]和(ABA)两个缀是相等的,因此可以利用dp,
		     将: (A B A)C[A B A]B 求解前后缀 相当于  (A B A) B 求解前后缀,也就是前面求过的子问题的解 
						 										  0 0 1   
						 此时len = next[len - 1];  相当于ABAB 求 
	   A B A C A B A B				 
       0 0 1 0 1 2 3 2					 
*/

void buildNextArr(){
	int len = 0;  // len表示当前最长前缀的长度
    next[0] = 0;  // 第一个字符的next值总是0
	//i是串指针,len不仅代表长度,也是最长前缀的指针 
	int i=1;
	while(i < M){ 
		if (p[i] == p[len]) { // 如果当前字符与最长前缀的下一个字符匹配，则next[i] = len + 1
            len++;
            next[i] = len;
            i++;
        } else { // 如果不匹配，
            if (len != 0) { // 且len不为0，则回退到next[len-1]
                len = next[len - 1];
            } else {       // 如果len为0，则next[i] = 0，并继续下一个字符
                next[i] = 0;
                i++;
            }
        }
	}
}


void test(){
	//printf("%d",voilent());
	buildNextArr(); 
	printf("%d",kmpSearch());
	printf("(index)");
} 

int main(){
	test();
}
