#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(CColor color);

    std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) override;
};
