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
		v.push_back({ x,y });
	}

	
	sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b)
		{
			return (a.first < b.first) || (a.first == b.first && a.second < b.second);
		});

	for (int i = 0; i < n; i++)
	{
		cout << v[i].first << " " << v[i].second << "\n";
	}
}
