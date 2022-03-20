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
	//�̵��� ��ǥ�� �ʱ�ȭ
	_path.clear();
	_path.push_back(pos);
	//������ ���� ������ ��� ����
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
		//1.���� �ٶ󺸴� ���� ���� ���������� �����ִ��� �ľ�
		if (CanGo(pos + front[newDir]))//�ϰ� ����
		{
			//������ �������� 90�� ȸ��
			_dir = newDir;
			//������ �Ѻ�����
			pos += front[_dir];
			//�̵��� ��ǥ�� ����
			_path.push_back(pos);
		}
		//2.�ٶ󺸴� ������ �������� ������������ Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			//�����ϸ� ������ ����
			pos += front[_dir];
			//�̵��� ��ǥ�� ����
			_path.push_back(pos);
		}
		else//���� �������� 90�� ȸ��
		{
			//ȸ���� ����
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
	//������ ����
	if (_path.empty() == false)
		s.push(_path.back());
	vector<Pos> path;
	while (s.empty() == false)
	{
		path.push_back(s.top());
		s.pop();
	}
	//stack ���·� �� �����͸� �������� ����
	std::reverse(path.begin(), path.end());
	_path = path;

}

void Player::Bfs()
{
	Pos pos = _pos;
	//������ ���� ������ ��� ����
	Pos dest = _board->GetExitPos();
	Pos front[4]
	{
		Pos {-1,0},//up
		Pos {0,-1},//left
		Pos {1,0},//down
		Pos {0,1}//right
	};

	//���� Ȯ��
	const int32 size =_board->GetSize();
	vector<vector<bool>> discovered(size,vector<bool>(size,false));
	//������ ���� ����
	map<Pos,Pos> parent;
	queue<Pos> q;
	//������ġ �־��ֱ�
	q.push(pos);

	discovered[pos.y][pos.x] = true;
	while (q.empty()==false)
	{
		pos = q.front();
		q.pop();
		//�湮
		if (pos == dest)
		{
			break;
		}

		for (int32 dir = 0; dir < 4; dir++)
		{
			Pos nextPos = pos+front[dir];
			//�����ִ� ������ Ȯ��
			if (!CanGo(pos))
				continue;
			//�̹� �߰��� �������� Ȯ��
			if (discovered[nextPos.y][nextPos.x])
				continue;

			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true;
			parent[nextPos] = pos;
		}
	}

	//�̵��� ��ǥ�� �ʱ�ȭ
	_path.clear();
	//�Ž��� �ö󰣴�
	pos = dest;

	while (true)
	{
		_path.push_back(pos);
		//�������� �ڽ��� �� �θ��
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
	//���� �ű�� = = ����ġ�� ��
	// F = G + H
	//F ��������
	//G ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (�������� ����)
	//H ���������� �󸶳� ������� (�������� ����)

	Pos start = _pos;
	//������ ���� ������ ��� ����
	Pos dest = _board->GetExitPos();

	enum//���� 4������ �� �밢�� ������ �̵��� üũ�ϱ� ���ؼ� ����
	{
		DIR_COUNT=4
	};
	//���ư� ���� ��ǥ
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
	//�̵� ���
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
	//���� Ȯ��
	const int32 size = _board->GetSize();
	//closedlist  y,x�� ���Ͽ� �湮�Ͽ����� ���θ� �˻�
	vector<vector<bool>> closed(size,vector<bool>(size,false));
	//���ݱ��� y,x�� ���� ���� ���� ����� �����ϱ����� ����
	vector<vector<int32>> best(size,vector<int32>(size,INT32_MAX));
	//�θ� ���� �뵵
	map<Pos,Pos> parent;
	//�켱���� ť openlist -> ����� �ֵ��� �����ϴ� ���� //�ڵ忡���� �߰ߵ� �ֵ��� ��������
	priority_queue<PQNode,vector<PQNode>,greater<PQNode>> pq; 
	//1)���� �߰� �ý��� ����
	//2)�ڴʰ� �߰ߵǴ� ���� ��� -> ���� ó�� �ʼ�
	//�ʱⰪ
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
		//������ ��ǥ�� ������η� ã�Ƽ� ������ ��η� ���ؼ� �̹� �湮�� ��� ��ŵ
		//����
		if(closed[node.pos.y][node.pos.x])  
			continue;
		if(best[node.pos.y][node.pos.x]<node.f)//����� �ĺ��� ���� ��� ��ŵ
			continue;
		//�湮
		closed[node.pos.y][node.pos.x] = true;


		//�������� �����ϸ� �ٷ� ����
		if(node.pos ==dest)
			break;
		for(int32 dir =0;dir<DIR_COUNT;dir++)
		{
			Pos nextPos = node.pos+ front[dir];
			//�����ִ� �������� Ȯ�� 
			if (CanGo(nextPos)==false)
			{
				continue;
			}
			//����
			//�̹� �湮�Ѱ��̸� ��ŵ
			if (closed[nextPos.y][nextPos.x])
			{
				continue;
			}
			//��� ���
			int32 g = node.g +cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));
			//�ٸ� ��ο��� �� ���� ���� ã������ ��ŵ
			if(best[nextPos.y][nextPos.x]<=g+h)
				continue;
			//���� ���� �� ���� ���� ���
			best[nextPos.y][nextPos.x] = g+h;
			pq.push(PQNode{g+h,g,nextPos});
			parent[nextPos]=node.pos;
		}
	}

	//�̵��� ��ǥ�� �ʱ�ȭ
	//�Ž��� �ö󰣴�
	Pos pos = dest;
	_path.clear();
	_pathIndex =0;

	while (true)
	{
		_path.push_back(pos);
		//�������� �ڽ��� �� �θ��
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}


	reverse(_path.begin(), _path.end());

}
