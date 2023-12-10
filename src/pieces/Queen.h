#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(CColor color);

    std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) override;
};
