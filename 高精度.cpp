#include<iostream> 
#include<vector>
#include<string>
#include<algorithm> 
using namespace std;
const int N = 1e6 +10; 
/*�߾���-��cpp 
   A+B   N<=1e6 
   A-B
   A*b
   A%b A/b 
    
*/ 
 
/* 
 * �߾��ȼӷ�ԭ�� A+B 
   ģ��
        1 2 3
    +     8 9 
	----*-*---- 
        2 1 2 
    �Ĺ��� 
    
 * ���ݴ洢��ʽ 
                           �����: 0  1  2  3  4  5 
  ������345678�洢��һ�������� A  [8, 7, 6, 5, 4, 3] 
                                  �� ʮ �� ǧ ��  .. 
  //����洢��ԭ��:���㲹�����λ��λ1,�Լ�����������ȥ��ǰ��0 

*/ 
vector<int> add(vector<int> &A,vector<int> &B){
	vector<int> C;
	int t=0;  //��λ 
	for(int i=0;i<A.size()||i<B.size();i++){
		if(i<A.size())   t+=A[i];     //�ó����������� 
		if(i<B.size())   t+=B[i];
		//��ʱtΪ��λ���֮�� ����ʱ��λ�� t=12 
		C.push_back(t%10);  //��t��λ¼��     * 
		t/=10;		         
	}
	if(t)	C.push_back(1);//���һ����λ
	return C;
}
/* 
 * �߾��ȼ���ԭ�� A-B 
 ��֤ A > B
    �� A < B ,�� -(B - A) 
 ģ��:  * *       
        1 2 3
    -     8 9 
	----------- 
          3 4      
    �Ĺ��� 
 ��ʽ: 
        A3 A2 A1 
    -      B2 B1 
	----------- 
       �� Ai-Bi-t >= 0 ֱ����
	              <0  �� Ai-Bi-t+10 
    
*/ 
bool cmp(vector<int> &A,vector<int> &B){
	if(A.size() != B.size())   return A.size()>B.size();
	for(int i = A.size()-1;i>=0;i--){
		if(A[i]!=B[i]) 
		    return A[i] > B[i];
	}
	return true;
}
vector<int> sub(vector<int> &A,vector<int> &B){
	vector<int> C;
	int t=0;//��λ 
	for(int i =0;i<A.size();i++){ //123  A[3,2,1]
		t=A[i]-t;                 //#����:����Ai,��ȥ��λ 
		if(i<B.size())   t-=B[i]; //��ΪB��A��,���Լ��Biλ�Ƿ���� 
		C.push_back((t+10)%10);
		//#����:��t<0��t>0�������һ������ 
		
		if(t<0)		t=1;  //���ý�λ 
		else        t=0;
	}
	while(C.size()>1&&C.back()==0) 		C.pop_back();//��ȥǰ���� 
	                              //��111-111ʱ,����ִ�Ϊ000,ȥ�����õ�0 
	return C;
}

/* �߾��ȳ˷�ԭ�� A*b
  ģ��  A5 A4 A3 A2 A1            ����:  2 3 4 5 
	*	            B                   *      23 
	-------------t1-------     -------5-7-10-11-------- 
        .. .. C3 C2 C1                5  3 9 3  5 
        
    C1 = ( A1*B )%10          
    ��λt1 =(A1*B)/10            
    
    C2 = ( A2*B + t1 )%10
    ��λt2 =( A2*B + t1 )/10
    
    ͨʽ:Ci = ( Ai*B + t[i-1] ) % 10 
	     ti = ( Ai*B + t[i-1] ) / 10 
*/ 
vector<int> mul(vector<int> &A,int b){
	vector<int> C;
	int t=0;  //��λ 
	for(int i=0;i<A.size()||t;i++){  //#����:t��Ϊ�ж�Ϊ����,���������λ�˷��Ľ�λ���� 
		if(i<A.size())   t+=A[i]*b;     //�ó����������� 
		
		//��ʱtΪ��,����������λ��        t=123 
		C.push_back(t%10);  //��t��λ¼��     3 
		t/=10;		        //����10,��λ t=12 
	}
	//��������������λ��λ����
	//while(t){
	//      C.push_back(t%10);
	//      t/=10;
	//}  
	while(C.size()>1&&C.back()==0) 		C.pop_back();//��ȥǰ����,0*x=0 
	return C;
}
/* �߾��ȳ���ԭ�� A/b
         0 1 1 2              C3 C2       
       |---------           |--------------
    11 | 1 2 3 4          b | A3 A2 A1 A0 
         1 1                 b*C3              (r=A3)
    --------------      --------------------------
	       1 3                  r*             (r* =[ r-(b*C3) ]*10 + A2)
           1 1                 b*C2
    --------------      --------------------------
	         2 4                               (r** =[ r*-(b*C2) ]*10 + A1)
	         2 2
	--------------
	           2 
	           
*/   
vector<int> div(vector<int> &A,int b,int &r){//r���ڱ������� 
	vector<int> C;
	r=0;//���� 
	for(int i=A.size()-1;i>=0;i--){
		r=r*10 + A[i];     //ÿ��ʣ������Ӹ�λ�Ĺ��� 
		C.push_back(r/b);  //r/b��Cx 
		r%=b;              //�������� 
	}
	reverse(C.begin(),C.end());                      //��ת���� 
	while(C.size()>1&&C.back()==0) 		C.pop_back();//��ȥǰ����
	return C;
}


void test(){//���ù淶 
	string a,b;
	vector<int> A,B;
	int d;
	//cin>>a>>b;  //a = "34567"
	cin>>a>>d;
	for(int i = a.size()-1;i>=0;i--)   A.push_back(a[i]-'0');  //A = [7,6,5,4,3]
	for(int i = b.size()-1;i>=0;i--)   B.push_back(b[i]-'0');
	
	//vector<int> C = add(A,B);  *�ӷ� 
	
	//vector<int> C;  *���� 
	//if(cmp(A,B)){
	//	C = sub(A,B);
	//}else{
	//	C = sub(B,A); //���� 
	//	printf("-");
	//}
	
	//vector<int> C = mul(A,d);  *�˷� 
	
	//int r; 
	//vector<int> C = div(A,d,r); *���� 
	
	for(int i = C.size()-1;i>=0;i--)   printf("%d",C[i]);
	
	printf("...%d",r);	
}


int main(){
	test(); 
}
