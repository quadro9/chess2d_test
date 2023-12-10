#pragma once
#include "Piece.h"

class King : public Piece
{
public:
    King(CColor color);

    std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) override;
};
