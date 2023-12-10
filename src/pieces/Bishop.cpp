#include "Bishop.h"
#include "../Board.h"
#include "../shared.h"


Bishop::Bishop(CColor color) : Piece(color, "bishop")
{
}

std::unordered_set<Point> 
Bishop::getMoves(const Point& pos, const Board& board)
{
    std::unordered_set<Point> validMoves;

    // Проверка доступности всех клеток по диагонали вправо вверх
    for (int toRow = pos.y - 1, toCol = pos.x + 1; toRow >= 0 && toCol < 8; --toRow, ++toCol)
    {
        const space* sp = board.getSpace({toCol, toRow});
        if (!sp)
        {
            validMoves.insert({toCol, toRow});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({toCol, toRow});
            break;
        }
        else
        {
            break;
        }
    }

    // Проверка доступности всех клеток по диагонали вправо вниз
    for (int toRow = pos.y + 1, toCol = pos.x + 1; toRow < 8 && toCol < 8; ++toRow, ++toCol)
    {
        const space* sp = board.getSpace({toCol, toRow});
        if (!sp)
        {
            validMoves.insert({toCol, toRow});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({toCol, toRow});
            break;
        }
        else
        {
            break;
        }
    }

    // Проверка доступности всех клеток по диагонали влево вверх
    for (int toRow = pos.y - 1, toCol = pos.x - 1; toRow >= 0 && toCol >= 0; --toRow, --toCol)
    {
        const space* sp = board.getSpace({toCol, toRow});
        if (!sp)
        {
            validMoves.insert({toCol, toRow});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({toCol, toRow});
            break;
        }
        else
        {
            break;
        }
    }

    // Проверка доступности всех клеток по диагонали влево вниз
    for (int toRow = pos.y + 1, toCol = pos.x - 1; toRow < 8 && toCol >= 0; ++toRow, --toCol)
    {
        const space* sp = board.getSpace({toCol, toRow});
        if (!sp)
        {
            validMoves.insert({toCol, toRow});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({toCol, toRow});
            break;
        }
        else
        {
            break;
        }
    }

    return validMoves;
}
