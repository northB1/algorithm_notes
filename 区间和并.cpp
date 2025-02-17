#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;

/*	区间合并
	例如: 1  2  3  4  5  6  7  8  9
	      ----        ----  ---- 
		     -------        -------
		  
 合并区间 ==========  ====  ======= 
输入
5
1 2
2 4
5 6
7 8
7 9

输出
3 

   *1. 按区间左端点排序(贪心) 
	2. 维护一个区间  st =========== ed 
		a.区间被涵盖      ------ 
		b.区间有溢出         ----------  
		c.区间不连续                    ------ 
		
		对a:不做处理
		对b:延长维护区间
		对c:开辟维护新区间 
		
	
*/ 
const int N = 1e5+01;
typedef pair<int,int>  St_Ed;
vector<St_Ed> area;
void merge(){
	vector<St_Ed> ans;
	sort(area.begin(),area.end());
	
	int st=-2e9,ed=-2e9;//先初始化维护区间 
	for(int i=0;i<area.size();i++){
		if(ed<area[i].first){      //如果情况c发生 
			if(ed != -2e9)	ans.push_back(make_pair(st,ed));//且排除初始情况 
			st=area[i].first;
			ed=area[i].second;
			
		}else if(area[i].second > ed)	ed=area[i].second; //情况b 
		  //else ed = max(ed,area[i].second);
	}
	if(st!=-2e9)	ans.push_back(make_pair(st,ed));//最后一个区间(排除area为空情况) 
	area = ans;
}

void test(){
	int n;
	cin>>n;
	
	int l,r;
	while(n--){
		cin>>l>>r;
		area.push_back(make_pair(l,r));
	}	
	merge();
	printf("%d",area.size());
	
} 

int main(){
	test();
} 
