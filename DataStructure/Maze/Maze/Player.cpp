#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;
	//이동한 좌표를 초기화
	_path.clear();
	_path.push_back(pos);
	//목적지 도착 전까지 계속 실행
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
		//1.현재 바라보는 방향 기준 오른쪽으로 갈수있는지 파악
		if (CanGo(pos+front[newDir]))//하고 전진
		{
			//오른쪽 방향으로 90도 회전
			_dir = newDir;
			//앞으로 한보전진
			pos += front[_dir];
			//이동한 좌표를 저장
			_path.push_back(pos);
		}
		//2.바라보는 방향을 기준으로 전진가능한지 확인
		else if (CanGo(pos+front[_dir]))
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
