#include <iostream>
#include <vector>
#include <map>

using namespace std;

//이진 탐색 트리

//이진 탐색 binary search

/*
작동방식 
up down 게임 방식과 유사함
log n 의 시간 복잡도 
*/

//정렬이 되어 있는 경우에서만 사용이 가능함
//중간 삽입 삭제가 느림
//정렬된 연결리스트로는 불가
vector<int> numbers;

void BinarySearch(int N)
{
	int size = numbers.size();
	int left =0;
	int right = size-1;

	while (left <= right)
	{
		int mid = (left+ right)/2;//정수 평균을 구해줌

		cout<<"탐색 범위 :" <<left<< "~" << right;

		if (N < numbers[mid])
		{
			cout <<"작음"<<endl;
			right = mid -1;
		}
		else if(N > numbers[mid])
		{
			cout << "큼" << endl;
			left = mid+1;
		}
		else if(N== numbers[mid])
		{
			cout<<endl;
			cout<<"찾음"<<N<<endl;
			break;
		}
	}

}

int main()
{
	numbers = vector<int>{1,8,15,23,32,44,56,64,81,91};

	BinarySearch(81);
	
}