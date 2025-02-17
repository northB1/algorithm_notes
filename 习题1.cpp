#include<iostream> 

/*题目:在一个无序数组中寻找第k小的数 

一次整理后         
	l     Sl              Sr        r
	[------------|------------------]
	    <=x              >=x
	左边元素Sl 一定小于右边元素Sr 
	所以当 k<Sl 时,说明第k小元素就在区间Sl内,递归左边 
	    当 k>Sl 时,说明第k小元素就在区间Sr内,递归右边
	    	且 第k小元素,在右边区间内,就是第 k-Sl 小元素 
	    	
	一次整理后            i 
	元素为奇数:    [l,   ,e,   ,r]   结束时 i=j 
    		       (      j)(    ) 
					  
						   i 
	元素为偶数:    [l,    ,e,   ,r]   结束时 i>j                    
	               (    j)(j+1   ) 
	所以 Sl = j-l+1 //
	
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

/*题目:求一组数中的逆序对 
	1.暴力求解O(n^2)
	2.归并排序,边排序,便求解,对于一个数组q[] 
		[l,.9..,mid] [mid+1..1.,r]
		    *                * 
		无论某个元素在半个区间内如何移动,都不会改变逆序顺序
		可以考虑使用归并排序计算子区间逆序数, 在合并为答案 
	
		对任意一个区间
		[l,....,mid,....,r]会被分成两个区间,用双指针进行排序
		
		i-> 
		[l,....,mid]
		[mid+1,...r] 
		j-> 
		
		且对于每一个区间都是单调有序的,也就是说
		如果 q[i] > q[j]逆序,则i到mid的所有数对于j全部逆序
	  例     i 
		[1,3,5,7,9]    此时 q[i] > q[j]逆序,则7,9对于3也全部逆序 
		[3,4,6,8,10]   逆序对可直接计算为 mid-i+1 
		 j 
		每次递归返回计算的所有逆序对,就可得出总逆序数 
		 
		temp:[1,3] (为了保证稳定性,当q[i]=q[j]时,i先被存入) 
*/
const int N = 6;
int qq[N];
int temp[N];
int merge_calculate(int l,int r){
	if(l>=r)  return 0;
	int mid=(l+r)/2;
								//总逆序数等于两个子区间的逆序数之和 
	int rev = merge_calculate(l,mid) + merge_calculate(mid+1,r);  
	
	int i=l,j=mid+1,k=0;
	
	while(i<=mid&&j<=r){
		if(qq[i]<=qq[j])  temp[k++]=qq[i++];
		else if(qq[i]>qq[j])  {
			rev+=mid-i+1;       //计算逆序数 
			temp[k++]=qq[j++];
		}
	}
	while(i<=mid)	temp[k++]=qq[i++];//扫尾 
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
浮点数二分:求一个数的三次根
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

