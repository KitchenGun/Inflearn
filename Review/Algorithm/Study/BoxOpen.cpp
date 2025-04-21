#include "iostream"
#include "vector"
using namespace std;



int main() 
{
	int n, w, num;
	//상자수 : n, 한줄의 상자수 : w, 상자번호 : num
	cin>> n >> w >> num;
	//시간복잡도 O(floor)로 계산
	int answer = 0;
	//꼭대기 층 도달하면 반환
	while (num <= n) 
	{
		//층수 올리기
		answer++;
		/*
			(w + num - 1) % w :	현재 상자의 열 위치 계산
			w - 1 -  : 	현재 상자의 열 위치를 반영하여 위층의 같은 열로 이동하는 상자 번호 증가량
			* 2 + 1  :  다음 상자 번호까지 이동해야할 거리
		*/
		
		num += (w - 1 - (w + num - 1) % w) * 2 + 1;
		//시뮬레이션으로 풀려고 했으나 수학적으로 푸는 방법이 더 효율적임
	}
	cout<< answer;

	return 0;
}