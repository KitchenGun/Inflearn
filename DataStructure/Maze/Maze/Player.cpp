#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	Bfs();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		return;
	}
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_pos = _path[_pathIndex];
		_pathIndex++;
	}

}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);

	return tileType == TileType::EMPTY;
}

void Player::RightHand()
{
	Pos pos = _pos;
	//이동한 좌표를 초기화
	_path.clear();
	_path.push_back(pos);
	//목적지 도착 전까지 계속 실행
	Pos dest = _board->GetExitPos();
	Pos front[4]
	{
		Pos {-1,0},//up
		Pos {0,-1},//left
		Pos {1,0},//down
		Pos {0,1}//right
	};

	while (pos != dest)
	{
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		//1.현재 바라보는 방향 기준 오른쪽으로 갈수있는지 파악
		if (CanGo(pos + front[newDir]))//하고 전진
		{
			//오른쪽 방향으로 90도 회전
			_dir = newDir;
			//앞으로 한보전진
			pos += front[_dir];
			//이동한 좌표를 저장
			_path.push_back(pos);
		}
		//2.바라보는 방향을 기준으로 전진가능한지 확인
		else if (CanGo(pos + front[_dir]))
		{
			//가능하면 앞으로 전진
			pos += front[_dir];
			//이동한 좌표를 저장
			_path.push_back(pos);
		}
		else//왼쪽 방향으로 90도 회전
		{
			//회전만 진행
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}
	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}
	//목적지 도착
	if (_path.empty() == false)
		s.push(_path.back());
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}
	//stack 형태로 들어간 데이터를 역순으로 돌림
	std::reverse(path.begin(), path.end());
	_path = path;

}

void Player::Bfs()
{
	Pos pos = _pos;
	//목적지 도착 전까지 계속 실행
	Pos dest = _board->GetExitPos();
	Pos front[4]
	{
		Pos {-1,0},//up
		Pos {0,-1},//left
		Pos {1,0},//down
		Pos {0,1}//right
	};

	//공간 확보
	const int32 size =_board->GetSize();
	vector<vector<bool>> discovered(size,vector<bool>(size,false));
	//추적을 위한 변수
	map<Pos,Pos> parent;
	queue<Pos> q;
	//시작위치 넣어주기
	q.push(pos);

	discovered[pos.y][pos.x] = true;
	while (q.empty()==false)
	{
		pos = q.front();
		q.pop();
		//방문
		if (pos == dest)
		{
			break;
		}

		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos+front[dir];
			//갈수있는 곳인지 확인
			if (!CanGo(pos))
				continue;
			//이미 발견한 지역인지 확인
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	//이동한 좌표를 초기화
	_path.clear();
	//거슬러 올라간다
	pos = dest;

	while (true)
	{
		_path.push_back(pos);
		//시작점은 자신이 곧 부모다
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}


	reverse(_path.begin(),_path.end());


}
