#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int max(int a,int b){
	return a>b?a:b;
}
/* ˫ָ���㷨
	����:����,�鲢����Ҳ������˫ָ�� 
	��Ҫ����:�Ż�O(n^2)��˫ѭ��,����i,j֮������ʼ��ٴ�������
		O(n^2)�汾 
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				//ִ���߼� 
			}
		}
		
	˫ָ���Ż���: ͨ�����i,j֮�������,���絥���Ե�,���ٴ�������
		for(int i=0;i<n;i++){
			while(j<i && check(i,j)){
				//ִ���߼�
			}
		} 
*/
/*
	����:����һ������,�ҳ���������ظ����ֵ�������,���ݷ�Χ(0,10) 
		���� [1,2,2,3,5]  ans:5 
	1.˫for��������,i��jö�ٳ����������ִ�,��һ����Ƿ����ظ�,
	��check(i,j)ΪO(1)ʱ,�ܸ��Ӷ�Ϊ O(n^2)
	2.˫ָ�� 
	(j	 i->
	[1,2,2,3,5]
    ��i��Ϊͷ��.j��Ϊβ��,
	i�����ƶ���ö��,���(i,j) �����Ƿ����ظ�Ԫ�� 
		1.���ظ�  jһֱ����,ֱ���ų��ظ�Ԫ�� 
		2.û���ظ�  ������󳤶�,i����ö�� 
	�ܸ��Ӷ�Ϊ O(2n) = O(n)
	
	����:check(i,j)�������O(1)? ����һ������䵱��¼�� 
	int S[N]; N��������,S[2]�洢��'2'���ֵĴ��� 
	����S[q[i]]++��ʾq[i]������һ�� 
	
	Ҳ���ù�ϣ�����洢 
*/
const int N = 10; 
int q[N];
int S[N]; 

int doublePointer(int n){
	int ans=0;
	for(int i=0,j=0;i<n;i++){
		S[q[i]]++; 			// S[q[i]]++;Ԫ��q[i]���ֵĴ���+1 
		while(S[q[i]]>1){	// S[q[i]]>1;��Ԫ��q[i]���ֹ�һ������ʱ(�ظ�����),˵��(j,i)֮�����ظ�Ԫ�� 
			S[q[j]]--;	//���ų���Ԫ��ȡ�����  
			j++;		// jһֱ����,ֱ���ų��ظ�Ԫ��,i���ܼ���ö�� 
		}	
		ans=max(ans,i-j+1); 
	}
	return ans;
}

void test1(){
	int n=5;//������ 
	int a[n]={1,2,2,3,5};
	for(int i=0;i<n;i++)	q[i]=a[i];
	printf("%d",doublePointer(n));
}


/* λ����
				x=10 
Դ��:1010       x 
����:0101		~x 
����:����+1 	~x+1 

	����1:n�Ķ����Ʊ�ʾ�е�kλ�Ǽ�
		����n=10=(1010),����1λ(101) 
		˼·:1.����kλ���Ƶ����һλ,n>>k
			 2.����λ ��1,&1; 
		 
		 
*/ 
void DtoB(int n){	//λ����ת������  
	int k=0; 
	vector<int> ans; 
	while(n>>k){
		ans.push_back((n>>k & 1)); 
		k++; 
	}
	reverse(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)	printf("%d",ans[i]);
		
} 
/*	����x�����һλ1,���� x&-x = x&(~x+1)
	         * 
		 x=101000  lowbit(x)=1000 
	����x=10100001000
	   ~x=01011110111 
   (~x+1)=01011111000 =x&-x
 x&(~x+1)=00000001000 
 lowbit�ô�:ͳ��x��1�ĸ��� 
*/
int lowbit(int x){ 
		return 	x&-x;		 		 
} 
int lowbit_calculate_numof1(int n){ //ͳ��x��1�ĸ��� 
	int ans=0;
	while(n){
		n-=lowbit(n),ans++;//ÿ�μ������һλ1,�����ξ��м���1 
	}
	printf("%d",ans);
	return ans;
} 


void test2(){
	DtoB(15);
	lowbit_calculate_numof1(15);
}

int main(){
	//test1();
	 test2();
} 
 
