#include<iostream>
#include<vector> 
#include<algorithm>
#include<utility>
using namespace std;
/* ��ɢ��
���� 1e5����,��ɢ�ֲ��� 1e9�ķ�Χ��,���ڲ��ܿ�һ��a[1e9]��ô�������
���Խ���һ��ӳ���
	
  ԭ����:λ��: 1 . . . . 5 ......... 100 .... 2000 .......... 1e9 (��Χ) 
  		 ����  100       200         400      600             800 
  	//��һ��vector�洢���д���ɢ��������
 	  
     add[] :<1,100> <5,200> <100,400> <2000,600> ....<1e9,800> ��1e5����Ԫ��
     //��λ��:λ��1��,����Ԫ��100 ,�����ݴ洢ʱ���б�Ҫ ,
     
	 alls[]: 1,5,100,2000,...,1e9   ��1e5������
	 �����: 0,1, 2 ,  3,,   ,1e5
	  
	 //ӳ���:��ɢ�����걻ѹ��ӳ�� �� �������
	  
     a[]   :0,100,200,400,600,...,800 
     // ����alls����� �洢���ݵ�ѹ������ 
     
     ����:��Ѱ�Ҵ洢��λ��2000��Ԫ��ʱ,
	 	1.��ֱ�����ö�Ԫ�����,O(n) 
	 	2.���ֲ���alls[],�ҵ�Ԫ��λ��,�����±�(ӳ���ϵ) ,int x = find( alls,2000 );
	 ��ͨ���õ���λ��Ѱ�� int ans = a[ x ] ;����λ��λ��2000 ��Ԫ�� ,O(logn) 
     
     
     	alls������: 
		sort(alls.begin(),alls.end());				//���������� 
		alls.erase(unique(alls.begin(),alls.end()),alls.end());  //�������ظ�Ԫ�� 

	    alls�Ѿ���һ�����򵥵�����,�����ö��������� 
	     
*/ 

/*	����:һ�����޳�����,-------------------0-------------------->(-1e9��1e9) 
	n����:��������ĳЩ����+c,(1e5) 
	mѯ��:һ������[l,r]�ĺ�  (1e5)
	����:
3 3
1 200 
3 600 
7 500 
1 3
4 6
7 8 
���:
8
0
5 
*/ 
const int N = 30;//��Ϊ������ǰ׺��,����ѯ�ʲ���������Ҳ��Ҫ����¼,�ܳ���<=3e5(������,������,ѯ�ʸ�1e5) 

typedef pair<int,int>  PII;
vector<int> alls; //ӳ��� 
vector<PII> add;  //��Ԫ��,���ڱ���<����,ֵ>
vector<PII> query;//��Ԫ��,���ڱ���<��ѯ��,��ѯ��>
 /*
                                 200 600     500                
			-------------------|-------------------->
                               0 1   3       7        
                               
        ѯ��                    [1---3]     [7-8] 
                                      [4---6]  
	alls:[ 1,3,4,6,7,8]
	add:[<1,200> <3,600> <7,500>] 
	query: [<1,3> <4,6> <7,8>] 

 */ 
int find(int x){	//���ֲ���Ѱ������ 
	int l=0,r=alls.size()-1;
	while(l<r){
		int mid=l+r >>1;
		if(alls[mid]>=x)	r=mid;
		else	l=mid+1;
	}
	return r+1;//ԭ����r,��������Ҫ�õ�ǰ׺��,����Ҫӳ�䵽1λ��������λ 
}

void test(){
	int n,m;
	scanf("%d%d",&n,&m);
	
	for(int i=0;i<n;i++){//�洢 <λ��,Ԫ��> ��ϵ�� 
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
		query.push_back(make_pair(l,r));//�洢 <��ѯ��,��ѯ��>
		alls.push_back(l); 
		alls.push_back(r); 
	}
	// query: [<1,3> <4,6> <7,8>]
	
	sort(alls.begin(),alls.end());	//���������� 
	alls.erase(unique(alls.begin(),alls.end()),alls.end());  //�������ظ�Ԫ�� 
	// alls:[ 1,3,4,6,7,8] ��ɢ��-���������ѯ������ ��ӳ���ϵ 
	
//---------------------------------------------��ɢ������� 

	int a[N]={0};
	int S[N]={0}; 
	for(int i=0;i<add.size();i++){ //���� ��λ�� ���� ѹ�����ݱ� 
		int x=find(add[i].first);
		a[x]+=add[i].second;
	} 
	
	
	//Ԥ����ǰ׺�� 
	for(int i=1;i<=alls.size();i++){
		S[i]=S[i-1]+a[i];
	}
	
	//����ѯ�� 
	for(int i=0;i<query.size();i++){
		int l=find(query[i].first);
		int r=find(query[i].second);
		cout<<S[r]-S[l-1]<<endl;
	}
} 

int main(){
	test();
} 
