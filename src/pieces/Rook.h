#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(CColor color);

    std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) override;
};
