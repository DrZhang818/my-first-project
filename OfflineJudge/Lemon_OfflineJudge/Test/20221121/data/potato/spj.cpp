#include<bits/stdc++.h>
#define pb push_back
using namespace std;
ifstream fin,fout,fstd;
ofstream fscore,freport;
int T,n,m,ans1,ans2,res1,res2;
vector<vector<int> > a;
bool check()
{
	fin>>n>>m;
	a.clear();
	a.resize(n,vector<int>(m,0));
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			fin>>a[i][j];
	fstd>>ans1;if (ans1!=-1)fstd>>ans2,--ans1,--ans2;
	fout>>res1;if (res1!=-1)fout>>res2,--res1,--res2;
	if ((ans1==-1&&res1!=-1)||(ans1!=-1&&res1==-1))
		return 0;
	if (ans1==-1&&res1==-1)
		return 1;
	for(int i=0;i<n;i++)
		swap(a[i][res1],a[i][res2]);
	for(int i=0;i<n;i++)
		for(int j=1;j<m;j++)
			if (a[i][j-1]>a[i][j])
				return 0;
	return 1;
}
bool judge() 
{
	bool flag=1;
	int T;fin>>T;
	while(T--)
		flag&=(check());
	if (flag)
	{
		freport<<"yarimasune!"<<endl;
		return 1;
	}
	freport<<"heng,heng,heng,aaaaaaaaa!"<<endl;
	return 0;
}
int main(int argc,char *argv[])
{
	/*
	argv[1]：输入文件
	argv[2]：选手输出文件
	argv[3]：标准输出文件
	argv[4]：单个测试点分值
	argv[5]：输出最终得分的文件
	argv[6]：输出错误报告的文件
	*/
    fin.open(argv[1]);
    fout.open(argv[2]);
    fstd.open(argv[3]);
    fscore.open(argv[5]);
    freport.open(argv[6]);
    int score = atoi(argv[4]);
    fscore<<score*judge()<<endl;
    fin.close();
    fout.close();
    fstd.close();
    fscore.close();
    freport.close();
    return 0;
}
