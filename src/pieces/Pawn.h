#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(CColor color);

    std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) override;
};
