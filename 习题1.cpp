#include<iostream> 

/*��Ŀ:��һ������������Ѱ�ҵ�kС���� 

һ�������         
	l     Sl              Sr        r
	[------------|------------------]
	    <=x              >=x
	���Ԫ��Sl һ��С���ұ�Ԫ��Sr 
	���Ե� k<Sl ʱ,˵����kСԪ�ؾ�������Sl��,�ݹ���� 
	    �� k>Sl ʱ,˵����kСԪ�ؾ�������Sr��,�ݹ��ұ�
	    	�� ��kСԪ��,���ұ�������,���ǵ� k-Sl СԪ�� 
	    	
	һ�������            i 
	Ԫ��Ϊ����:    [l,   ,e,   ,r]   ����ʱ i=j 
    		       (      j)(    ) 
					  
						   i 
	Ԫ��Ϊż��:    [l,    ,e,   ,r]   ����ʱ i>j                    
	               (    j)(j+1   ) 
	���� Sl = j-l+1 //
	
*/
int q[10]={7,3,8,0,5,2,6,7,4,1};//0,1,2,3,4,5,6,7,8
void swap(int i,int j){
	int temp=q[i];
	q[i]=q[j];
	q[j]=temp;
}
int quick_select(int l,int r,int k){
	if(l>=r)	return q[l];
	int x=q[l],i=l-1,j=r+1;
	while(i<j){
		do i++;while(q[i]<x);
		do j--;while(q[j]>x);
		if(i<j)  swap(i,j);
	}
	int Sl=j-l+1;
	if(k<=Sl)	return quick_select(l,j,k);
	
	return	quick_select(j+1,r,k-Sl);
}
void test1(){
	printf("%d",quick_select(0,9,5));	
}

/*��Ŀ:��һ�����е������ 
	1.�������O(n^2)
	2.�鲢����,������,�����,����һ������q[] 
		[l,.9..,mid] [mid+1..1.,r]
		    *                * 
		����ĳ��Ԫ���ڰ������������ƶ�,������ı�����˳��
		���Կ���ʹ�ù鲢�������������������, �ںϲ�Ϊ�� 
	
		������һ������
		[l,....,mid,....,r]�ᱻ�ֳ���������,��˫ָ���������
		
		i-> 
		[l,....,mid]
		[mid+1,...r] 
		j-> 
		
		�Ҷ���ÿһ�����䶼�ǵ��������,Ҳ����˵
		��� q[i] > q[j]����,��i��mid������������jȫ������
	  ��     i 
		[1,3,5,7,9]    ��ʱ q[i] > q[j]����,��7,9����3Ҳȫ������ 
		[3,4,6,8,10]   ����Կ�ֱ�Ӽ���Ϊ mid-i+1 
		 j 
		ÿ�εݹ鷵�ؼ�������������,�Ϳɵó��������� 
		 
		temp:[1,3] (Ϊ�˱�֤�ȶ���,��q[i]=q[j]ʱ,i�ȱ�����) 
*/
const int N = 6;
int qq[N];
int temp[N];
int merge_calculate(int l,int r){
	if(l>=r)  return 0;
	int mid=(l+r)/2;
								//�����������������������������֮�� 
	int rev = merge_calculate(l,mid) + merge_calculate(mid+1,r);  
	
	int i=l,j=mid+1,k=0;
	
	while(i<=mid&&j<=r){
		if(qq[i]<=qq[j])  temp[k++]=qq[i++];
		else if(qq[i]>qq[j])  {
			rev+=mid-i+1;       //���������� 
			temp[k++]=qq[j++];
		}
	}
	while(i<=mid)	temp[k++]=qq[i++];//ɨβ 
	while(j<=r)		temp[k++]=qq[j++];
	
	for(i=l,j=0;i<=r;i++,j++)   qq[i]=temp[j];
		
	return rev;
} 
void test2(){
	int init[N]={2,3,4,5,6,1};
	for(int i=0;i<N;i++)   qq[i]=init[i];
	
	printf("%d",merge_calculate(0,N-1));	
}
/* 
����������:��һ���������θ�
*/ 
int max(int a,int b){
	return a>b?a:b;
} 
double bisearch(double x){
	double  l=0,r=max(1,x);
	while(r-l > 1e-8){
		double mid = (l+r)/2;
		if(mid*mid*mid >= x)    r = mid;
		else                l = mid;
	}
	return l;
}
void test3(){
	double a;
	scanf("%lf",&a);
	printf("%lf",bisearch(a));
}

int main(){
	//test1();
	//test2();
	test3();


} 

