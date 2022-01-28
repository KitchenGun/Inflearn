#pragma once

class Board;


class Player
{
	enum
	{
		MOVE_TICK = 100
	};

public:
	void Init(Board* board);
	void Update(uint64 deltaTick);

	Pos GetPos() { return _pos; }
	
	bool CanGo(Pos pos);

private:
	void RightHand();
	void Bfs();
private:
	Pos _pos = {};
	int32 _dir = DIR_UP;
	Board* _board = nullptr;

	vector<Pos> _path;
	int32 _pathIndex = 0;
	uint64 _sumTick = 0;
};

