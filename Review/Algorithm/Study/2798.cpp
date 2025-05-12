#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

int Maxcount = 0;
int Maxsum = 0;
int CurResult = 0;
vector<int> Cards(0);

void PickCard()
{
	vector<int> PickIndex;
	
	for (int i = 0; i < Cards.size(); i++)
	{
		PickIndex.push_back(i);
		for (int j = 0; j < Cards.size(); j++)
		{
			if (find(PickIndex.begin(), PickIndex.end(), j) == PickIndex.end())
			{
				PickIndex.push_back(j);
			}
			else
			{
				continue;
			}
			for (int k = 0; k < Cards.size(); k++)
			{
				if (find(PickIndex.begin(), PickIndex.end(), k) == PickIndex.end())
				{
					PickIndex.push_back(k);
					int sum = Cards[PickIndex[0]] + Cards[PickIndex[1]] + Cards[PickIndex[2]];
					if (sum <= Maxsum)
					{
						if(sum>=CurResult)
							CurResult = sum;
					}
					PickIndex.pop_back();
				}
				else
				{
					continue;
				}
			}
			PickIndex.pop_back();
		}
		PickIndex.pop_back();
	}
}



int main()
{

	cin >> Maxcount >> Maxsum;
	for (int i = 0; i < Maxcount; i++)
	{
		int temp;
		cin >> temp;
		Cards.push_back(temp);
	}

	int sum = 0;

	PickCard();

	cout << CurResult;

}