#include <iostream>
#include <vector>
#include <map>

using namespace std;

//���� Ž�� Ʈ��

//���� Ž�� binary search

/*
�۵���� 
up down ���� ��İ� ������
log n �� �ð� ���⵵ 
*/

//������ �Ǿ� �ִ� ��쿡���� ����� ������
//�߰� ���� ������ ����
//���ĵ� ���Ḯ��Ʈ�δ� �Ұ�
vector<int> numbers;

void BinarySearch(int N)
{
	int size = numbers.size();
	int left =0;
	int right = size-1;

	while (left <= right)
	{
		int mid = (left+ right)/2;//���� ����� ������

		cout<<"Ž�� ���� :" <<left<< "~" << right;

		if (N < numbers[mid])
		{
			cout <<"����"<<endl;
			right = mid -1;
		}
		else if(N > numbers[mid])
		{
			cout << "ŭ" << endl;
			left = mid+1;
		}
		else if(N== numbers[mid])
		{
			cout<<endl;
			cout<<"ã��"<<N<<endl;
			break;
		}
	}

}

int main()
{
	numbers = vector<int>{1,8,15,23,32,44,56,64,81,91};

	BinarySearch(81);
	
}