#include "pch.h"
#include "Board.h"
#include "ConsoleHelpers.h"
#include "Player.h"

const char* TILE = "бс";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
    _size = size;
    GenerateMap();
    this->player = player;
}

void Board::Render()
{
    ConsoleHelpers::SetCursorPosition(0, 0);
    ConsoleHelpers::ShowConsoleCursor(false);
    for (int32 y = 0; y < 25; y++)
    {
        for (int32 x = 0; x < 25; x++)
        {
            ConsoleColor color = GetTileColor(Pos{ y,x });
            ConsoleHelpers::SetCursorColor(color);

            cout << TILE;
        }
        cout << endl;
    }
}

void Board::GenerateMap()
{
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
            //if (x == 0 || x == _size - 1 || y == 0 || y == _size - 1)
                _tile[y][x] = TileType::WALL;
            else
                _tile[y][x] = TileType::EMPTY;
        }
    }

    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x % 2 == 0 || y % 2 == 0)
                continue;
            if (x == _size-2 && y == _size - 2)
                continue;

            if (y == _size - 2)
            {
                _tile[y][x + 1] = TileType::EMPTY;
                continue;
            }
            if (x == _size - 2)
            {
                _tile[y + 1][x] = TileType::EMPTY;
                continue;
            }
            const int32 randValue = rand() % 2;

            if (randValue == 0)
            {
                _tile[y][x + 1] = TileType::EMPTY;
            }
            else
            {
                _tile[y+1][x] = TileType::EMPTY;
            }
        }
    }
}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;
    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;

    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    if (player!= nullptr&&player->GetPos()==pos)
        return ConsoleColor::WHITE;

    if (GetExitPos() == pos)
        return ConsoleColor::BLUE;

    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::EMPTY:
        return ConsoleColor::GREEN;
    case TileType::WALL:
        return ConsoleColor::RED;
    }
    return ConsoleColor::YELLOW;
}
