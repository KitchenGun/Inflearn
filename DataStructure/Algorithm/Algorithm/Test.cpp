#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int strcmp(const char* a, const char* b)
{	
	string astr = a;
	string bstr = b;

	if (astr.size() == bstr.size())
	{
		for (int i = 0; i < astr.size(); i++)
		{
			if (astr[i] != bstr[i])
			{
				if (astr[i] > bstr[i])
				{
					return 1;
				}
				else
				{
					return -1;
				}
			}
		}

		return 0;
	}
	else if(astr.size() > bstr.size())
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


int main()
{

}