#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include <queue>
using namespace std;

int main()
{
	vector<queue<char >> v(15);
	

	for (int i = 0; i < 5; i++)
	{
		string s;
		cin>>s;
		for (int j = 0; j < s.size(); j++)
		{
			v[j].push(s[j]);
		}
	}


	for (int i = 0; i < 15; i++)
	{
		while (!v[i].empty())
		{
			cout << v[i].front();
			v[i].pop();
		}
	}
	
}