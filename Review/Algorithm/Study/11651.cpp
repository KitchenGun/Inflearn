#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;


int main()
{
	int n;
	cin >> n;
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		v.push_back({ y, x });
	}
	sort(v.begin(), v.end());
	for (auto var : v)
	{
		cout << var.second << " " << var.first << "\n";
	}
	return 0;
}