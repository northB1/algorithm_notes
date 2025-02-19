#include<iostream>
#include<vector> 
#include<algorithm>
#include<utility>
using namespace std;
/* 离散化
当有 1e5个数,离散分布在 1e9的范围内,由于不能开一个a[1e9]这么大的数组
所以建造一个映射表
	
  原数据:位置: 1 . . . . 5 ......... 100 .... 2000 .......... 1e9 (范围) 
  		 数据  100       200         400      600             800 
  	//用一个vector存储所有待离散化的数据
 	  
     add[] :<1,100> <5,200> <100,400> <2000,600> ....<1e9,800> 共1e5个二元组
     //数位表:位置1上,存有元素100 ,在数据存储时很有必要 ,
     
	 alls[]: 1,5,100,2000,...,1e9   共1e5个坐标
	 数组标: 0,1, 2 ,  3,,   ,1e5
	  
	 //映射表:离散的坐标被压缩映射 在 数组标上
	  
     a[]   :0,100,200,400,600,...,800 
     // 利用alls数组标 存储数据的压缩数据 
     
     例如:当寻找存储于位置2000的元素时,
	 	1.若直接利用二元组查找,O(n) 
	 	2.二分查找alls[],找到元素位置,数组下标(映射关系) ,int x = find( alls,2000 );
	 在通过得到的位置寻找 int ans = a[ x ] ;便获得位于位置2000 的元素 ,O(logn) 
     
     
     	alls整理技巧: 
		sort(alls.begin(),alls.end());				//将数据排序 
		alls.erase(unique(alls.begin(),alls.end()),alls.end());  //并擦除重复元素 

	    alls已经是一个有序单调数列,可利用二分来查找 
	     
*/ 

/*	例题:一个无限长数轴,-------------------0-------------------->(-1e9至1e9) 
	n操作:给数轴上某些个数+c,(1e5) 
	m询问:一个区间[l,r]的和  (1e5)
	数据:
3 3
1 200 
3 600 
7 500 
1 3
4 6
7 8 
输出:
8
0
5 
*/ 
const int N = 30;//因为类似于前缀和,所以询问操作的坐标也需要被记录,总长度<=3e5(正半轴,负半轴,询问各1e5) 

typedef pair<int,int>  PII;
vector<int> alls; //映射表 
vector<PII> add;  //二元组,用于保存<坐标,值>
vector<PII> query;//二元组,用于保存<左询问,右询问>
 /*
                                 200 600     500                
			-------------------|-------------------->
                               0 1   3       7        
                               
        询问                    [1---3]     [7-8] 
                                      [4---6]  
	alls:[ 1,3,4,6,7,8]
	add:[<1,200> <3,600> <7,500>] 
	query: [<1,3> <4,6> <7,8>] 

 */ 
int find(int x){	//二分查找寻找坐标 
	int l=0,r=alls.size()-1;
	while(l<r){
		int mid=l+r >>1;
		if(alls[mid]>=x)	r=mid;
		else	l=mid+1;
	}
	return r+1;//原本是r,但这里需要用到前缀和,所以要映射到1位起点的坐标位 
}

void test(){
	int n,m;
	scanf("%d%d",&n,&m);
	
	for(int i=0;i<n;i++){//存储 <位置,元素> 关系表 
		int x,c;
		cin>>x>>c;
		
		add.push_back(make_pair(x,c));
		alls.push_back(x); 
	}
	// alls:[ 1,3,7 ]
	// add:[<1,200> <3,600> <7,500>]
	
	for(int i=0;i<m;i++){ 
		int l,r;
		cin>>l>>r;
		query.push_back(make_pair(l,r));//存储 <左询问,右询问>
		alls.push_back(l); 
		alls.push_back(r); 
	}
	// query: [<1,3> <4,6> <7,8>]
	
	sort(alls.begin(),alls.end());	//将数据排序 
	alls.erase(unique(alls.begin(),alls.end()),alls.end());  //并擦除重复元素 
	// alls:[ 1,3,4,6,7,8] 离散表-插入坐标和询问坐标 的映射关系 
	
//---------------------------------------------离散表构造完成 

	int a[N]={0};
	int S[N]={0}; 
	for(int i=0;i<add.size();i++){ //根据 数位表 构造 压缩数据表 
		int x=find(add[i].first);
		a[x]+=add[i].second;
	} 
	
	
	//预处理前缀和 
	for(int i=1;i<=alls.size();i++){
		S[i]=S[i-1]+a[i];
	}
	
	//处理询问 
	for(int i=0;i<query.size();i++){
		int l=find(query[i].first);
		int r=find(query[i].second);
		cout<<S[r]-S[l-1]<<endl;
	}
} 

int main(){
	test();
} 
