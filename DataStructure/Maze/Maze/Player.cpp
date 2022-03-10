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
