#include "iostream"

using namespace std;

int main()
{
	int n=0, start=1;

	cin >> n;
	while (start < n)
	{
		int i = start;
		int element = 0;
		while (i!=0)
		{
			element += i % 10;
			i /= 10;
		}

		int sum = element + start;

		if (sum == n)
		{
			cout << start << endl;
			return 0;
		}
		start++;

	}
	cout << 0 << endl;
	return 0;

}