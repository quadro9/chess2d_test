#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "../shared.h"


Queen::Queen(CColor color) : Piece(color, "queen")
{
}

std::unordered_set<Point> 
Queen::getMoves(const Point& pos, const Board& board)
{
    std::unordered_set<Point> validMoves;

    Bishop bishop(_color);
    Rook rook(_color);

    auto bishopMoves = bishop.getMoves(pos, board);
    auto rookMoves = rook.getMoves(pos, board);

    validMoves.insert(bishopMoves.begin(), bishopMoves.end());
    validMoves.insert(rookMoves.begin(), rookMoves.end());

    return validMoves;
}
