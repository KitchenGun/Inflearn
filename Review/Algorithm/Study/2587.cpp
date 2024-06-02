#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v;
	int result = 0;

	for (int i = 0; i <= 4; i++)
	{
		int n;
		cin >> n;
		v.push_back(n);
		result += n;
	}
	sort(v.begin(), v.end());

	cout << result / 5 << endl;
	cout<< v[2] << endl;
}