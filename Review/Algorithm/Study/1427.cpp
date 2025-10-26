#include "iostream"
#include "map"
using namespace std;


int main()
{
	string s;
	cin >> s;
	map<int, int> m;
	for(char var : s)
	{
		int temp = var-'0';
		m[temp]++;
	}


	for (int i = 9; i >= 0; i--) 
	{            
		// 0 Æ÷ÇÔ
		int count = m[i];
		for (int j = 0; j < count; j++) 
		{
			cout << i;
		}
	}
	return 0;
}