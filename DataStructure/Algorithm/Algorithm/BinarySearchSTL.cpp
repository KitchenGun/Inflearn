#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int n,m;

	vector<int> arr(10,0);

	for (int i = 0; i < 10; i++)
	{
		cin>>arr[i];
	}
	//
	cout<<"�˻��� ���� �Է��ϼ���"<< endl;
	sort(arr.begin(),arr.end());
	int t;
	cin>>t;
	cout<<binary_search(arr.begin(),arr.end(),t)<<endl;
}
