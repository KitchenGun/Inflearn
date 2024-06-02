#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
	{
		int k = 0;
		cin >> k;
		v[i] = k;
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++)
	{
		cout<< v[i] << '\n';
	}
}