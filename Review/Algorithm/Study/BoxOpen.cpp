#include "iostream"
#include "vector"
using namespace std;



int main() 
{
	int n, w, num;
	//���ڼ� : n, ������ ���ڼ� : w, ���ڹ�ȣ : num
	cin>> n >> w >> num;
	//�ð����⵵ O(floor)�� ���
	int answer = 0;
	//����� �� �����ϸ� ��ȯ
	while (num <= n) 
	{
		//���� �ø���
		answer++;
		/*
			(w + num - 1) % w :	���� ������ �� ��ġ ���
			w - 1 -  : 	���� ������ �� ��ġ�� �ݿ��Ͽ� ������ ���� ���� �̵��ϴ� ���� ��ȣ ������
			* 2 + 1  :  ���� ���� ��ȣ���� �̵��ؾ��� �Ÿ�
		*/
		
		num += (w - 1 - (w + num - 1) % w) * 2 + 1;
		//�ùķ��̼����� Ǯ���� ������ ���������� Ǫ�� ����� �� ȿ������
	}
	cout<< answer;

	return 0;
}