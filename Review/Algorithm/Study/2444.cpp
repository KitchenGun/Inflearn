#include "iostream"
using namespace std;


int main()
{
	int count;
	cin >> count;


	for (int i = 1; i <= count*2 - 1; i++)
	{
		int spaceNum = count >= i+1 ? count - i : i-count;

		for (int j = 0; j <= count*2 - 2; j++)
		{
			if ( j<spaceNum)
				cout << ' ';	
			else
			{
				if (j > count * 2 - 2 - spaceNum)
				{
					//마지막 space 생략
					if (i <= count * 2 - 1)
						cout << endl;
					break;
				}
				else
				{
					cout << '*';
					if (i == count&&j== count * 2 - 2)
						cout << endl;
				}
			}
				
		}
	}
	return 0;

}