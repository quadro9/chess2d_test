#include "Knight.h"
#include "../Board.h"
#include "../shared.h"


Knight::Knight(CColor color) : Piece(color, "knight")
{
}

std::unordered_set<Point> 
Knight::getMoves(const Point& pos, const Board& board)
{
    std::unordered_set<Point> validMoves;

    // Все возможные относительные позиции для хода коня
    int knightMoves[][2] = {
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1},
        {-2, 1}, {-1, 2}, {1, 2}, {2, 1}
    };

    for (const auto& move : knightMoves)
    {
        int toRow = pos.y + move[0];
        int toCol = pos.x + move[1];

        const space* sp = board.getSpace({toCol, toRow});
        if (board.isPositionValid({toCol, toRow}) && (!sp || sp->piece->getColor() != _color))
        {
            validMoves.insert({toCol, toRow});
        }
    }

    return validMoves;
}
