#include "Pawn.h"
#include "../Board.h"
#include "../shared.h"


Pawn::Pawn(CColor color) : Piece(color, "pawn")
{
}

std::unordered_set<Point> 
Pawn::getMoves(const Point& pos, const Board& board)
{
    std::unordered_set<Point> validMoves;

    int direction = (_color == CColor::Black) ? 1 : -1;
    int initialRow = (_color == CColor::Black) ? 1 : 6;

    // Проверка хода на одну клетку вперед
    int oneStepForward = pos.y + direction;
    const space* sp = board.getSpace({pos.x, oneStepForward});
    if (board.isPositionValid({pos.x, oneStepForward}) && !sp)
    {
        validMoves.insert({pos.x, oneStepForward});

        // Проверка хода на две клетки вперед при первом ходе
        int twoStepsForward = pos.y + 2 * direction;
        sp = board.getSpace({pos.x, twoStepsForward});
        if (pos.y == initialRow && !sp)
        {
            validMoves.insert({pos.x, twoStepsForward});
        }
    }

    // Проверка возможности взятия фигур на диагоналях
    int leftDiagonal = pos.x - 1;
    int rightDiagonal = pos.x + 1;

    sp = board.getSpace({leftDiagonal, oneStepForward});
    if (sp && sp->piece->getColor() != _color)
    {
        validMoves.insert({leftDiagonal, oneStepForward});
    }

    sp = board.getSpace({rightDiagonal, oneStepForward});
    if (sp && sp->piece->getColor() != _color)
    {
        validMoves.insert({rightDiagonal, oneStepForward});
    }

    return validMoves;
}
