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
	cout<<"검색할 숫자 입력하세요"<< endl;
	sort(arr.begin(),arr.end());
	int t;
	cin>>t;
	cout<<binary_search(arr.begin(),arr.end(),t)<<endl;
}
