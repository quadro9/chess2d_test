#include "Rook.h"
#include "../Board.h"
#include "../shared.h"


Rook::Rook(CColor color) : Piece(color, "rook")
{
}

std::unordered_set<Point> 
Rook::getMoves(const Point& pos, const Board& board)
{
    std::unordered_set<Point> validMoves;

    // Проверка доступности всех клеток вдоль вертикали
    for (int toRow = pos.y - 1; toRow >= 0; --toRow)
    {
        const space* sp = board.getSpace({pos.x, toRow});
        if (!sp)
        {
            validMoves.insert({pos.x, toRow});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({pos.x, toRow});
            break; // Прекращаем движение вдоль вертикали, если встречена фигура противоположного цвета
        }
        else
        {
            break; // Прекращаем движение вдоль вертикали, если встречена фигура того же цвета
        }
    }

    for (int toRow = pos.y + 1; toRow < 8; ++toRow)
    {
        const space* sp = board.getSpace({pos.x, toRow});
        if (!sp)
        {
            validMoves.insert({pos.x, toRow});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({pos.x, toRow});
            break;
        }
        else
        {
            break;
        }
    }

    // Проверка доступности всех клеток вдоль горизонтали
    for (int toCol = pos.x - 1; toCol >= 0; --toCol)
    {
        const space* sp = board.getSpace({toCol, pos.y});
        if (!sp)
        {
            validMoves.insert({toCol, pos.y});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({toCol, pos.y});
            break;
        }
        else
        {
            break;
        }
    }

    for (int toCol = pos.x + 1; toCol < 8; ++toCol)
    {
        const space* sp = board.getSpace({toCol, pos.y});
        if (!sp)
        {
            validMoves.insert({toCol, pos.y});
        }
        else if (sp->piece->getColor() != _color)
        {
            validMoves.insert({toCol, pos.y});
            break;
        }
        else
        {
            break;
        }
    }

    return validMoves;
}
