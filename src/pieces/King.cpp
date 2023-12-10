#include "King.h"
#include "../Board.h"
#include "../shared.h"


King::King(CColor color) : Piece(color, "king")
{
}

std::unordered_set<Point> 
King::getMoves(const Point& pos, const Board& board)
{
    std::unordered_set<Point> validMoves;

    // Все возможные относительные позиции для хода короля
    int kingMoves[][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1 },          {0, 1 },
        {1, -1 }, {1, 0 }, {1, 1 }
    };

    for (const auto& move : kingMoves)
    {
        int toRow = pos.y + move[0];
        int toCol = pos.x + move[1];

        const space* sp = board.getSpace({toCol, toRow});
        if (board.isPositionValid({toCol, toRow}) &&
            (!sp || sp->piece->getColor() != _color))
        {
            validMoves.insert({toCol, toRow});
        }
    }

    return validMoves;
}
