#include<iostream> 
#include<vector>
#include<string>
#include<algorithm> 
using namespace std;
const int N = 1e6 +10; 
/*高精度-仅cpp 
   A+B   N<=1e6 
   A-B
   A*b
   A%b A/b 
    
*/ 
 
/* 
 * 高精度加法原理 A+B 
   模拟
        1 2 3
    +     8 9 
	----*-*---- 
        2 1 2 
    的过程 
    
 * 数据存储格式 
                           数组标: 0  1  2  3  4  5 
  大数字345678存储在一个数组中 A  [8, 7, 6, 5, 4, 3] 
                                  个 十 百 千 万  .. 
  //逆序存储的原因:方便补齐最高位进位1,以及其他运算中去除前导0 

*/ 
vector<int> add(vector<int> &A,vector<int> &B){
	vector<int> C;
	int t=0;  //进位 
	for(int i=0;i<A.size()||i<B.size();i++){
		if(i<A.size())   t+=A[i];     //用长度条件控制 
		if(i<B.size())   t+=B[i];
		//此时t为两位相加之和 可能时两位数 t=12 
		C.push_back(t%10);  //将t个位录入     * 
		t/=10;		         
	}
	if(t)	C.push_back(1);//最后一个进位
	return C;
}
/* 
 * 高精度减法原理 A-B 
 保证 A > B
    若 A < B ,则 -(B - A) 
 模拟:  * *       
        1 2 3
    -     8 9 
	----------- 
          3 4      
    的过程 
 公式: 
        A3 A2 A1 
    -      B2 B1 
	----------- 
       若 Ai-Bi-t >= 0 直接算
	              <0  算 Ai-Bi-t+10 
    
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
	int t=0;//借位 
	for(int i =0;i<A.size();i++){ //123  A[3,2,1]
		t=A[i]-t;                 //#巧妙:加上Ai,减去进位 
		if(i<B.size())   t-=B[i]; //因为B比A短,所以检查Bi位是否存在 
		C.push_back((t+10)%10);
		//#巧妙:将t<0和t>0两种情况一并计算 
		
		if(t<0)		t=1;  //重置借位 
		else        t=0;
	}
	while(C.size()>1&&C.back()==0) 		C.pop_back();//除去前导零 
	                              //当111-111时,会出现答案为000,去除无用的0 
	return C;
}

/* 高精度乘法原理 A*b
  模拟  A5 A4 A3 A2 A1            例如:  2 3 4 5 
	*	            B                   *      23 
	-------------t1-------     -------5-7-10-11-------- 
        .. .. C3 C2 C1                5  3 9 3  5 
        
    C1 = ( A1*B )%10          
    进位t1 =(A1*B)/10            
    
    C2 = ( A2*B + t1 )%10
    进位t2 =( A2*B + t1 )/10
    
    通式:Ci = ( Ai*B + t[i-1] ) % 10 
	     ti = ( Ai*B + t[i-1] ) / 10 
*/ 
vector<int> mul(vector<int> &A,int b){
	vector<int> C;
	int t=0;  //进位 
	for(int i=0;i<A.size()||t;i++){  //#巧妙:t作为判断为条件,处理了最高位乘法的进位问题 
		if(i<A.size())   t+=A[i]*b;     //用长度条件控制 
		
		//此时t为积,可能是两三位数        t=123 
		C.push_back(t%10);  //将t个位录入     3 
		t/=10;		        //除以10,进位 t=12 
	}
	//如果单独处理最高位进位问题
	//while(t){
	//      C.push_back(t%10);
	//      t/=10;
	//}  
	while(C.size()>1&&C.back()==0) 		C.pop_back();//除去前导零,0*x=0 
	return C;
}
/* 高精度除法原理 A/b
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
vector<int> div(vector<int> &A,int b,int &r){//r用于保存余数 
	vector<int> C;
	r=0;//余数 
	for(int i=A.size()-1;i>=0;i--){
		r=r*10 + A[i];     //每次剩余数添加个位的过程 
		C.push_back(r/b);  //r/b是Cx 
		r%=b;              //计算余数 
	}
	reverse(C.begin(),C.end());                      //反转容器 
	while(C.size()>1&&C.back()==0) 		C.pop_back();//除去前导零
	return C;
}


void test(){//调用规范 
	string a,b;
	vector<int> A,B;
	int d;
	//cin>>a>>b;  //a = "34567"
	cin>>a>>d;
	for(int i = a.size()-1;i>=0;i--)   A.push_back(a[i]-'0');  //A = [7,6,5,4,3]
	for(int i = b.size()-1;i>=0;i--)   B.push_back(b[i]-'0');
	
	//vector<int> C = add(A,B);  *加法 
	
	//vector<int> C;  *减法 
	//if(cmp(A,B)){
	//	C = sub(A,B);
	//}else{
	//	C = sub(B,A); //负号 
	//	printf("-");
	//}
	
	//vector<int> C = mul(A,d);  *乘法 
	
	//int r; 
	//vector<int> C = div(A,d,r); *除法 
	
	for(int i = C.size()-1;i>=0;i--)   printf("%d",C[i]);
	
	printf("...%d",r);	
}


int main(){
	test(); 
}
