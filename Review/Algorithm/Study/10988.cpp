#include "iostream"
#include "stack"
#include "string"
using namespace std;

int main()
{
	string s;
	stack <char> ss;
	cin >> s;


	for (int i = 0; i < s.length(); i++)
	{
		ss.push(s[i]);
	}

	for (int i = 0; i < s.length(); i++)
	{
		if (ss.top() == s[i])
		{
			ss.pop();
		}
		else
		{
			cout << 0;
			return 0;
		}
	}
	cout << 1;
	return 0;
}