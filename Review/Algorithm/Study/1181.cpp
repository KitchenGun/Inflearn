#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;


bool StringCompareValue(string a,string b)
{
	int value = 0;
	for (int i =0;i<a.length();i++)
	{
		if (a[i] != b[i])
		{
			return (int)a[i] < (int)b[i];
		}
	}
	return true;
}

bool compare(string a, string b)
{
	if (a.length() != b.length())
	{
		return a.length() < b.length() ? true : false;
	}
	else
		return StringCompareValue(a, b);
}

int main() {
	int count;
	cin >> count;
	vector <string> words;
	set<string> wordSet;
	for (int i = 0; i < count; i++)
	{
		string str;
		cin >> str;
		wordSet.insert(str);
	}
	for (string s : wordSet)
	{
		words.push_back(s);
	}

	sort(words.begin(), words.end(), compare);

	for (string val : words)
	{
		cout << val << "\n";
	}
}