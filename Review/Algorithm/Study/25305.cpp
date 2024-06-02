#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int n, k;

	cin >> n >> k;

	vector<int> v(n);

	for (int& temp : v)
	{
		cin>>temp;
	}
	sort(v.begin(), v.end(),greater<int>());

	cout<< v[k - 1] << endl;
}