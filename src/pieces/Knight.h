#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(CColor color);

    std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) override;
};
