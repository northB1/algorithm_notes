#include<iostream>
#include<vector> 
#include<algorithm>
using namespace std;

/*	����ϲ�
	����: 1  2  3  4  5  6  7  8  9
	      ----        ----  ---- 
		     -------        -------
		  
 �ϲ����� ==========  ====  ======= 
����
5
1 2
2 4
5 6
7 8
7 9

���
3 

   *1. ��������˵�����(̰��) 
	2. ά��һ������  st =========== ed 
		a.���䱻����      ------ 
		b.���������         ----------  
		c.���䲻����                    ------ 
		
		��a:��������
		��b:�ӳ�ά������
		��c:����ά�������� 
		
	
*/ 
const int N = 1e5+01;
typedef pair<int,int>  St_Ed;
vector<St_Ed> area;
void merge(){
	vector<St_Ed> ans;
	sort(area.begin(),area.end());
	
	int st=-2e9,ed=-2e9;//�ȳ�ʼ��ά������ 
	for(int i=0;i<area.size();i++){
		if(ed<area[i].first){      //������c���� 
			if(ed != -2e9)	ans.push_back(make_pair(st,ed));//���ų���ʼ��� 
			st=area[i].first;
			ed=area[i].second;
			
		}else if(area[i].second > ed)	ed=area[i].second; //���b 
		  //else ed = max(ed,area[i].second);
	}
	if(st!=-2e9)	ans.push_back(make_pair(st,ed));//���һ������(�ų�areaΪ�����) 
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
