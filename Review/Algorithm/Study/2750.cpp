#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
	int n = 0;
	set<int> s;
	cin>> n;
	while (n != 0)
	{
		int temp;
		cin >> temp;
		s.insert(temp);
		n--;
	}


	set<int>::iterator iter;
	for (iter = s.begin(); iter != s.end(); iter++) 
	{ 
		cout<<*iter<< endl;
	}

}