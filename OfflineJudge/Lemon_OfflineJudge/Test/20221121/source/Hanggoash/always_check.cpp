#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T=10000;
	while(T--)
	{
		system("always_generator.exe");
		system("always.exe");
		system("always_std.exe");
		
		if(system("fc always.out ans.out"))
			{puts("WA");return 0;}
		else 
			puts("AC");
	}

	return 0;
}