#pragma once
#include <vector>
#include "oxygine-framework.h"
#include "pieces/Piece.h"

using namespace oxygine;

struct space
{
    Point pos;
    spPiece piece;
};

class Board
{
public:
    Board();

    void init(int w, int h);
    void free();

    spActor getView();
    bool isPositionValid(const Point& pos) const;
    const space* getSpace(const Point& pos, bool check = true) const;

private:
    void setupBoard();
    void placePiece(int row, int col, spPiece piece);

    void showMoves(const std::unordered_set<Point>& moves);
    void hideMoves();

    space* getSpace(const Point& pos, bool check = true);
    spTween move(space& a, const Point& pos);

    void touched(Event*);
    void moved(Event*);

    spSprite              _view;
    space*                _selected;
    CColor                _current;
    std::vector<space>    _field;
    std::vector<spSprite> _dots;
    Point                 _size;
};