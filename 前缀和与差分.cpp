#include<iostream> 

/* 一维前缀和
	
	原数组:[a1,a2,a3,a4......an]     例如[1,2,3,4 ,5 ]
	前缀和:[S1,S2,S3,S4......Sn]     例如[1,3,6,10,15]
	Si = a1+a2+a3+ ... + ai 
	
	*如何算出前缀和数组:Si = S[i-1] +ai 
	
	*作用: 可以快速求出 部分和            =========== 
		例如求出数组A中,al到ar的和 [a1,...al.......ar...,an]
		用循环,O(n) 
		可用前缀和数组 Sr - S[l-1] 时间复杂度O(1) 
		
	*注:下标最好从一开始!  
		为了避免边界问题,统一保存0 
			例如 求a1到an时计算为Sn-S0 
*/ 

/*  例题:给定一个长为n的数组,进行m次询问
	     每次询问一个区间和,al到ar的和 
	测试数据: 
10 2
1 2 3 4 5 6 7 8 9 10
5 7
1 10 
*/
const int N = 100; 
 
int a[N];
void Test1(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]); //读入数组 
	
	int S[N]; 
	S[0]=0;                                    //前缀和S0=0 
	for(int i=1;i<=n;i++)	S[i]=S[i-1]+a[i];  //前缀和初始化 
	
	int l,r;
	while(m--){
		scanf("%d%d",&l,&r);
		int sum = S[r]-S[l-1];                 //计算答案 
		printf("ans:%d\n",sum); 
	}
}
 
/* 二维前缀和 
	二维数组a[][] 
	二维前缀S[][] 
	
	*如何算出前缀和数组:S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + aij 
	
	|------------------------ y
	|        |         | 
	|        |         | 
	|--------a(x1y1)---| 
	|        |\\\\\\\\\|<-----询问这个区间 
	|        |\\\\\\\\\| 
	|----------------a(x2y2) 
	| 
	|
	x
	 
	S(x2 y2) - S(x2 y1-1) - S(x1-1 y2) + S(x1-1,y1-1) 

*/ 
/*  例题:给定一个长n宽m的数组,进行q次询问
	     每次询问一个区间和,a[i][j]到a[k][l]的和 
*/
int aa[N][N];
void Test2(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=m;j++)
			scanf("%d",&aa[i][j]); //读入数组 
		
	int S[N][N];               //前缀和二位数组的边界全都要成0 
	for(int i=0;i<=n||i<=m;i++){
		S[i][0]=0;
		S[0][i]=0;
	}
	                                  
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=m;j++)
			S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1]+aa[i][j];	  //前缀和二维组初始化 
	
	int x1,y1,x2,y2;
	while(q--){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		int sum = S[x2][y2]-S[x1-1][y2]-S[x2][y1-1]+S[x1-1][y1-1];//计算答案 
		printf("ans:%d\n",sum); 
	}
}
/*
测试数据: 
3 3 1
1 1 1
1 1 1
1 1 1
1 1 3 3 
*/

/*  一维差分 
	原数组:[a1,a2,a3,a4......an]     例如[1,2,3,4,5]
	构造差分数组: 使得 ai=b1+b2+...+bn,使得 a[]是b[]的前缀和 
	差分数组:[b1,b2,b3,b4......bn]     例如[1,1,1,1,1]
*/ 
/*  例题:给定一个长为n的数组,进行m次询问
	     每次给区间和(l,r)区间所有数 +c 
	     
	     1.暴力 O(n)
		 2.差分 O(1)
		 	原数组a:1-              差分数组b:1- 
			 		2-- 					  2-
					3---                      3- 
					4----                     4- 
					5-----                    5- 
					6------                   6- 
					7-------                  7-
			为了给l到r之间所有元素 +c ,只需要在 差分数组b[l]+c,b[r+1]-c,
			例:给3到5之间+4 
	    	差分数组b:  1-              
			     		2- 					 
				    	3-----                   
				  		4-                  
					 ---5               
						6-                
						7-             			 
	*如何构造差分数组:
		可以假设原数组初始为a[0,0,0,0,0]	差分数组也为b[0,0,0,0,0]
		每次录入数据等价于在(1,1)区间内插入一个数,只需要在b[1]+1,b[2]-1即可
		即 在(i,i)插入一个数, b[i]+1,b[i+1]-1 
*/
int b[N];
void insert(int l,int r,int c){  //b[i]+1,b[i+1]-1 
	b[l] += c;
	b[r+1] -= c;
} 

void Test3(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	scanf("%d",&a[i]); //读入数组 
	
	for(int i=1;i<=n;i++)	b[i]=0;            //初始化 
	for(int i=1;i<=n;i++)	insert(i,i,a[i]);  //读入数组 
	
	int l,r,c;
	while(m--){
		scanf("%d%d%d",&l,&r,&c);
		insert(l,r,c);              
	}
	
	for(int i=1;i<=n;i++)	b[i]+=b[i-1];
	for(int i=1;i<=n;i++)	printf(" %d",b[i]); 
}
/* 实验数据:
7 1
1 2 3 4 5 6 7
3 5 100 
*/

/*  二维差分:
	二维原矩阵  a[][]
	二维差分矩阵b[][] 
		
 a: |------------------------ y
	|                        | 
	|                        | 
	|        a(x1y1)---|-----| 
	|        |         |+c -c| 
	|        |   +c    |     | 
	|        --------a(x2y2)_| 
	|        |  +c -c  | +c -c -c +c 
	|------------------------| 
	x	
    给某个子矩阵(x1,y1)到(x2,y2)加上一个值
	b[x1][y1]  += c
	b[x2+1][y1] -= c
	b[x1][y2+1] -= c
	b[x2+1][y2+1] += c
*/
/*
    例题:给定一个长n宽m的数组,进行q次询问
	     每次给一个子矩阵加上值c 
*/
int bb[N][N]; 
void Insert(int x1,int y1,int x2,int y2,int c){
	bb[x1][y1]  += c;
	bb[x2+1][y1] -= c;
	bb[x1][y2+1] -= c;
	bb[x2+1][y2+1] += c;
}
void Test4(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	
	for(int i=0;i<=n||i<=m;i++){  //初始化边界 
		bb[i][0]=0;
		bb[0][i]=0;
	}
	
	for(int i=1;i<=n;i++)	   
		for(int j=1;j<=m;j++){
			scanf("%d",&aa[i][j]);    //输入值 
			Insert(i,j,i,j,aa[i][j]); //构造差分数组 
		}
			
	
	int x1,y1,x2,y2,c;
	while(q--){
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&c);
		Insert(x1,y1,x2,y2,c);
	}
	
	for(int i=1;i<=n;i++)	    //构造完成后,重新计算原数组 
		for(int j=1;j<=m;j++){
			int sum = bb[i][j]+bb[i-1][j]+bb[i][j-1]-bb[i-1][j-1];    
			bb[i][j] = sum;
		}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf(" %d",bb[i][j]);
		}
		printf("\n");
	}			
}
/*
测试数据: 
3 3 1
1 2 3
2 3 4
3 4 5
1 1 3 3 -1
*/

 
int main(){
	//Test1(); 
	//Test2();
	//Test3();
	Test4();
} 
