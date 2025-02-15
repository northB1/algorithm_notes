#include<iostream>
#define SIZE 17 

int bisearch_1(int l ,int r); 
int bisearch_2(int l ,int r); 

int Bisearch_1(int arr[],int x); 
int Bisearch_2(int arr[],int x); 

double test1(double x);
double bisearch_float(double x);
int max(int a,int b);

int arr[SIZE]={1,2,3,3,4,4,6,6,6,7,7,8,8,8,9,9,9};

bool check(int mid){
	
}

int main(){
	printf("%lf",test1(0.01));
}
/* ��������ģ�� 
//����һ����֤�н�!!! 
int bisearch_1(int l ,int r,int x){
	//                                [l,.......,mid,...........,r]
	while(l<r){
		int mid = (l+r)/2;         //             r     ����ȡ��
		if(q[mid] >= x)  r = mid;  // [l,..x....,mid]
		else             l = mid+1;//            mid [mid+1,..x..r]
	}                              //                   l
	return l;
	//�� l=rʱ,�Ǵ� 
	//arr[]={3,5,5,5,5,5,8}; ����Ԫ��5ʱ,�����׸�5��λ�� 
	//         * (1��λ)
	// *����: �ڱ���Ԫ�ز�����ʱ,�򱣴�������Ԫ��λ�� ��:arr[]={3,3,5,5,5,5,8}��4
	//                                                           *
}

int bisearch_2(int l ,int r,int x){
	//                                [l,.........,mid,.........,r]
	while(l<r){
		int mid = (l+r+1)/2;       //               l
		if(q[mid] <= x)  l = mid;  //             [mid.....x.....r]
		else             r = mid-1;// [l,.x..mid-1]mid
	}	                           //         r       ����ȡ��                           
	return l;
	//�� l=rʱ,�Ǵ� 
	//arr[]={3,5,5,5,5,5,8}; ����Ԫ��5ʱ,�������һ��5��λ�� 
	//                 * (5��λ) 
}

//��:Ѱ�������е�Ԫ��λ�� 
int Bisearch_1(int arr[],int x){ //Ѱ���׸�λ�� 
	int l=0,r=SIZE-1;
	while(l<r){
		int mid=(l+r)/2;
		if(arr[mid]>=x)   r=mid;
		else              l=mid+1;
	}
	return l;
}
int Bisearch_2(int arr[],int x){ //Ѱ�����λ�� 
	int l=0,r=SIZE-1;
	while(l<r){
		int mid=(l+r+1)/2;
		if(arr[mid]<=x)   l=mid;
		else              r=mid-1;
	}
	return l;
}

*/

/* ����������:
	ע��:��x<1ʱ,����� ����x>x ��˴𰸲�����0~x֮��
	����:��0.01�ĸ�,Ϊ0.1,��������Ϊ0~0.01,����Ҫ�涨
	r=max(1,x); 
*/
int max(int a,int b){
	return a>b?a:b;
} 
double test1(double x){
	//�������x
	
	double  l=0,r=max(1,x);
	while(r-l > 1e-8){
		double mid = (l+r)/2;
		if(mid*mid >= x)    r = mid;
		else                l = mid;
	}
	return l;
	
}

	
	
	
	
	
	
