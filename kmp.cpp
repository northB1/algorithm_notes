#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;


const int N = 10;
const int M = 5;
char S[]="abcdababc";//ԭ�� 
char p[]="dabab";//�ִ� 
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

/*	kmp�ִ�ƥ������ 
	һ�������ߵĶ�Զ����������˳��ʱ���ߵĶ�죬�����������澳ʱ������ҵ��������Լ���

	�������:˫for ,ԭ����n,�Ӵ���m,��ʱ�临�Ӷ�ΪO(nm) 
	
	
	��kmp�㷨��,�����������ʱ: 
	ԭ��:A B A B A B C D D 
	�Ӵ� A B A B C
	             ^  
	    ���Ӵ�����һ��next����,Ҳ��������ƥ����ַ�����
		�ﵽ����Ч��
	             
	ԭ��:A B A B|A|B C D D 
	�Ӵ� A B A B|C| 
	next 0 0 1 2|0|   //C��ƥ��,���������ַ�����ƥ�� 
                 j 
    ԭ��:A B A B|A|B C D D 
	�Ӵ�     A B|A|B C
	next     0 0|1|2 0 
                 j -> 
                 
	����*ָ�벻���л���,ʱ�临�Ӷ�O(n),���next����ʱ�临�Ӷ�ΪO(m)	,�ܸ��Ӷ�O(m+n)	 
	ͨ�׵���˵:����ĳ�αȽϷ���,�Ӵ��������һ�����ɻ�����,�Ϳ����������ڶν��бȽ� 
	 
*/
int kmpSearch(){
	int i=0;//����ָ�� 
	int j=0;//�ִ�ָ��
	while(i<N){
		if (p[j] == S[i]) { // �����ǰ�ַ�ƥ�䣬����ƥ����һ���ַ�
            i++,j++;
        }
        
		if (j == M) {//�����ȫƥ�䣬���ƥ���λ��
            return i-j;
            //j = next[j - 1];  // ����Ѱ����һ��ƥ��
        }else if (i < N && p[j] != S[i]) {  // �����ƥ��
            if (j != 0)    j = next[j - 1]; //��j��Ϊ0������next[j - 1]���ַ����бȽ� 
            else i++;                       // ��jΪ0���������һ���ַ�
        }
	}
	return -1; 
} 
/* next���� 
	���next����ʱ,����Ҫ���ִ����в���, 
	���Ӵ���ǰ׺�ͺ�׺��һ����,�Ϳ��������Ƚ�
	(��Ϊ���������Ӵ��ڱȽϵ�Cʱ,˵��ǰ�ĸ��ַ��Ѿ�ƥ��ɹ�Ҳ��֪������������Ϣ)
	��ǰ��׺һ��Ҫ��� 
	      A B A B|A|B C D D   
	����  A B A B C
	      --- ~~~
		  ǰ׺�ͺ�׺��һ����,����� ����ǰ����
		   
		  
	���next����:
		A B A B C
		*             //��һ���ַ��϶�Ϊ0,��Ϊǰ��׺�������Լ� 
   next:0 
   
   		A B A B C
		  *           //ǰ׺A,��׺B,��һ��,0 
   next:0 0 

		A B A B C
		    *         //�ǰ׺A,���׺A, ������1�� 
   next:0 0 1
   
   		A B A B C
		      *       //�ǰ׺AB,���׺AB, ������2�� 
   next:0 0 1 2 
    
    	A B A B C
		        *     //û��һ����ǰ��׺.0 
   next:0 0 1 2 0     
--------------------------------------------�ݹ����ǰ��׺ 
    ��(A B)A C[A B]A B Ϊ�Ӵ�ʱ: 
           *       * 
       0 0 1 0 1 2    �����һ���ַ���Ȼ��ͬ�Ļ�,��ǰ׺��Ϊ:ǰ׺��+1

    ��(A B A)C[A B A]B Ϊ�Ӵ�ʱ: 
             *       * 
       0 0 1 0 1 2 3    �����ͬ��,���ż���0,��Ϊ�п��ܳ��ֱ��� AB�����ĸ�����׺ 
	  					 ����֪��B ǰ���[ABA]��(ABA)����׺����ȵ�,��˿�������dp,
		     ��: (A B A)C[A B A]B ���ǰ��׺ �൱��  (A B A) B ���ǰ��׺,Ҳ����ǰ�������������Ľ� 
						 										  0 0 1   
						 ��ʱlen = next[len - 1];  �൱��ABAB �� 
	   A B A C A B A B				 
       0 0 1 0 1 2 3 2					 
*/

void buildNextArr(){
	int len = 0;  // len��ʾ��ǰ�ǰ׺�ĳ���
    next[0] = 0;  // ��һ���ַ���nextֵ����0
	//i�Ǵ�ָ��,len����������,Ҳ���ǰ׺��ָ�� 
	int i=1;
	while(i < M){ 
		if (p[i] == p[len]) { // �����ǰ�ַ����ǰ׺����һ���ַ�ƥ�䣬��next[i] = len + 1
            len++;
            next[i] = len;
            i++;
        } else { // �����ƥ�䣬
            if (len != 0) { // ��len��Ϊ0������˵�next[len-1]
                len = next[len - 1];
            } else {       // ���lenΪ0����next[i] = 0����������һ���ַ�
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
