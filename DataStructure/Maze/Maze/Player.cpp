#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;
	//�̵��� ��ǥ�� �ʱ�ȭ
	_path.clear();
	_path.push_back(pos);
	//������ ���� ������ ��� ����
	Pos dest = board->GetExitPos();
	Pos front[4]
	{
		Pos {-1,0},//up
		Pos {0,-1},//left
		Pos {1,0},//down
		Pos {0,1}//right
	};

	while (pos != dest)
	{
		int32 newDir = (_dir - 1 + DIR_COUNT)%DIR_COUNT;
		//1.���� �ٶ󺸴� ���� ���� ���������� �����ִ��� �ľ�
		if (CanGo(pos+front[newDir]))//�ϰ� ����
		{
			//������ �������� 90�� ȸ��
			_dir = newDir;
			//������ �Ѻ�����
			pos += front[_dir];
			//�̵��� ��ǥ�� ����
			_path.push_back(pos);
		}
		//2.�ٶ󺸴� ������ �������� ������������ Ȯ��
		else if (CanGo(pos+front[_dir]))
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
