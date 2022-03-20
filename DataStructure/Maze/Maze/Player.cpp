#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>
void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//RightHand();
	//Bfs();
	AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		//_board->GenerateMap();
		//Init(_board);
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

struct PQNode
{
	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int f;//F = G + H
	int g;
	Pos pos;
};


void Player::AStar()
{
	//점수 매기기 = = 가중치의 합
	// F = G + H
	//F 최종점수
	//G 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을수록 좋음)
	//H 목적지에서 얼마나 가까운지 (작을수록 좋음)

	Pos start = _pos;
	//목적지 도착 전까지 계속 실행
	Pos dest = _board->GetExitPos();

	enum//현재 4번까지 즉 대각선 제외한 이동만 체크하기 위해서 만듬
	{
		DIR_COUNT=4
	};
	//나아갈 방향 좌표
	Pos front[]
	{
		Pos {-1,0},//up
		Pos {0,-1},//left
		Pos {1,0},//down
		Pos {0,1},//right
		Pos {-1,-1},//up left
		Pos {1,-1},//down right
		Pos {1,-1},//down left
		Pos {-1,1}//up right
	};
	//이동 비용
	int32 cost[]=
	{
		10,//UP
		10,//Left
		10,//down
		10,//right
		14,
		14,
		14,
		14
	};
	//공간 확보
	const int32 size = _board->GetSize();
	//closedlist  y,x에 대하여 방문하였는지 여부를 검사
	vector<vector<bool>> closed(size,vector<bool>(size,false));
	//지금까지 y,x에 대한 가장 좋은 비용을 저장하기위한 공간
	vector<vector<int32>> best(size,vector<int32>(size,INT32_MAX));
	//부모 추적 용도
	map<Pos,Pos> parent;
	//우선순위 큐 openlist -> 예약된 애들을 관리하는 구조 //코드에서는 발견된 애들을 관리해줌
	priority_queue<PQNode,vector<PQNode>,greater<PQNode>> pq; 
	//1)예약 발견 시스템 구현
	//2)뒤늦게 발견되는 좋은 경로 -> 예외 처리 필수
	//초기값
	{
		int32 g = 0;
		int32 h = 10*(abs(dest.y-start.y)+abs(dest.x - start.x));
		pq.push(PQNode{g+h,g,start});
		best[start.y][start.x] = g+h;
		parent[start] = start;
	}

	while (pq.empty())
	{
		PQNode node = pq.top();
		pq.pop();
		//동일한 좌표를 여러경로로 찾아서 더빠른 경로로 인해서 이미 방문된 경우 스킵
		//선택
		if(closed[node.pos.y][node.pos.x])  
			continue;
		if(best[node.pos.y][node.pos.x]<node.f)//우수한 후보가 들어온 경우 스킵
			continue;
		//방문
		closed[node.pos.y][node.pos.x] = true;


		//목적지에 도착하면 바로 종료
		if(node.pos ==dest)
			break;
		for(int32 dir =0;dir<DIR_COUNT;dir++)
		{
			Pos nextPos = node.pos+ front[dir];
			//갈수있는 지역인지 확인 
			if (CanGo(nextPos)==false)
			{
				continue;
			}
			//선택
			//이미 방문한곳이면 스킵
			if (closed[nextPos.y][nextPos.x])
			{
				continue;
			}
			//비용 계산
			int32 g = node.g +cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			//다른 경로에서 더 빠른 길을 찾았으면 스킵
			if(best[nextPos.y][nextPos.x]<=g+h)
				continue;
			//예약 진행 더 빠른 길일 경우
			best[nextPos.y][nextPos.x] = g+h;
			pq.push(PQNode{g+h,g,nextPos});
			parent[nextPos]=node.pos;
		}
	}

	//이동한 좌표를 초기화
	//거슬러 올라간다
	Pos pos = dest;
	_path.clear();
	_pathIndex =0;

	while (true)
	{
		_path.push_back(pos);
		//시작점은 자신이 곧 부모다
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}


	reverse(_path.begin(), _path.end());

}
