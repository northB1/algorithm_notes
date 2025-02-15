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
/* 整数二分模板 
//二分一定保证有解!!! 
int bisearch_1(int l ,int r,int x){
	//                                [l,.......,mid,...........,r]
	while(l<r){
		int mid = (l+r)/2;         //             r     向下取整
		if(q[mid] >= x)  r = mid;  // [l,..x....,mid]
		else             l = mid+1;//            mid [mid+1,..x..r]
	}                              //                   l
	return l;
	//当 l=r时,是答案 
	//arr[]={3,5,5,5,5,5,8}; 查找元素5时,返回首个5的位置 
	//         * (1号位)
	// *特殊: 在被找元素不存在时,则保存左侧最近元素位置 例:arr[]={3,3,5,5,5,5,8}找4
	//                                                           *
}

int bisearch_2(int l ,int r,int x){
	//                                [l,.........,mid,.........,r]
	while(l<r){
		int mid = (l+r+1)/2;       //               l
		if(q[mid] <= x)  l = mid;  //             [mid.....x.....r]
		else             r = mid-1;// [l,.x..mid-1]mid
	}	                           //         r       向上取整                           
	return l;
	//当 l=r时,是答案 
	//arr[]={3,5,5,5,5,5,8}; 查找元素5时,返回最后一个5的位置 
	//                 * (5号位) 
}

//例:寻找数组中的元素位置 
int Bisearch_1(int arr[],int x){ //寻找首个位置 
	int l=0,r=SIZE-1;
	while(l<r){
		int mid=(l+r)/2;
		if(arr[mid]>=x)   r=mid;
		else              l=mid+1;
	}
	return l;
}
int Bisearch_2(int arr[],int x){ //寻找最后位置 
	int l=0,r=SIZE-1;
	while(l<r){
		int mid=(l+r+1)/2;
		if(arr[mid]<=x)   l=mid;
		else              r=mid-1;
	}
	return l;
}

*/

/* 浮点数二分:
	注意:当x<1时,会出现 根号x>x 因此答案并不在0~x之间
	例如:求0.01的根,为0.1,但查找域为0~0.01,所以要规定
	r=max(1,x); 
*/
int max(int a,int b){
	return a>b?a:b;
} 
double test1(double x){
	//计算根号x
	
	double  l=0,r=max(1,x);
	while(r-l > 1e-8){
		double mid = (l+r)/2;
		if(mid*mid >= x)    r = mid;
		else                l = mid;
	}
	return l;
	
}

	
	
	
	
	
	
