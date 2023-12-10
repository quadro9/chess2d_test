#include "Board.h"
#include "pieces/Bishop.h"
#include "pieces/King.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"
#include "pieces/Queen.h"
#include "pieces/Rook.h"

Board::Board(): _size(0, 0), _selected(0)
{

}

Vector2 getPos(const Point& p)
{
    Vector2 pos;
    pos.x = p.x * PieceSize.x;
    pos.y = p.y * PieceSize.y;
    pos += PieceSize / 2;

    return pos;
}

void Board::init(int w, int h)
{
    _size.x = w;
    _size.y = h;

    _view = new Sprite;

    _field.resize(_size.x * _size.y);
    _dots.resize(_size.x * _size.y);

    for (int y = 0; y < _size.y; ++y)
    {
        for (int x = 0; x < _size.x; ++x)
        {
            _field[x + y * _size.x].pos = Point(x, y);

            spSprite dot = new ColorRectSprite;
            dot->setSize(50, 50);
            dot->setColor(Color::Green);
            dot->setAlpha(50);
            dot->setPosition(getPos(Point(x, y)) - dot->getSize() / 2);
            dot->attachTo(getView());
            dot->setVisible(false);
            _dots[x + y * _size.x] = dot;
        }
    }

    _view->setSize(_size.x * PieceSize.x, _size.y * PieceSize.y);

    _view->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Board::touched));
    _view->setTouchChildrenEnabled(false);

    setupBoard();
}

void Board::setupBoard()
{
    _current = CColor::White;

    for (int col = 0; col < 8; ++col)
    {
        placePiece(1, col, new Pawn(CColor::Black));
        placePiece(6, col, new Pawn(CColor::White));
    }

    placePiece(0, 0, new Rook(CColor::Black));
    placePiece(0, 7, new Rook(CColor::Black));
    placePiece(7, 0, new Rook(CColor::White));
    placePiece(7, 7, new Rook(CColor::White));

    placePiece(0, 1, new Knight(CColor::Black));
    placePiece(0, 6, new Knight(CColor::Black));
    placePiece(7, 1, new Knight(CColor::White));
    placePiece(7, 6, new Knight(CColor::White));

    placePiece(0, 2, new Bishop(CColor::Black));
    placePiece(0, 5, new Bishop(CColor::Black));
    placePiece(7, 2, new Bishop(CColor::White));
    placePiece(7, 5, new Bishop(CColor::White));

    placePiece(0, 3, new Queen(CColor::Black));
    placePiece(7, 3, new Queen(CColor::White));

    placePiece(0, 4, new King(CColor::Black));
    placePiece(7, 4, new King(CColor::White));
}

void Board::placePiece(int row, int col, spPiece piece)
{
    float last_y = 0;
    last_y -= PieceSize.y + 10 + rand() % 65;
    auto& sp = _field[col + row * _size.x];
    spActor view = piece->getView();
    view->setPosition(Vector2(getPos(Point(col, row)).x, last_y));
    view->attachTo(_view);
    piece->fall(getPos(Point(col, row)));
    sp.piece = piece;
}

void Board::moved(Event* event)
{
    if (_current == CColor::White)
    {
        _current = CColor::Black;
    }
    else
    {
        _current = CColor::White;
    }
}

bool Board::isPositionValid(const Point& pos) const
{
    if (pos.x < 0 || pos.x >= _size.x)
        return false;
    if (pos.y < 0 || pos.y >= _size.y)
        return false;
    
    return true;
}

const space* Board::getSpace(const Point& pos, bool check) const
{
    if (!isPositionValid(pos))
        return nullptr;

    const space& sp = _field[pos.x + pos.y * _size.x];
    if (check)
    {
        if (!sp.piece)
            return nullptr;
        if (sp.piece->isExploding())
            return nullptr;
        if (sp.piece->isMoving())
            return nullptr;
        if (sp.piece->isDead())
            return nullptr;
        if (sp.piece->isFalling())
            return nullptr;
    }
    return &sp;
}

space* Board::getSpace(const Point& pos, bool check)
{
    const Board* constThis = const_cast<const Board*>(this);
    return const_cast<space*>(constThis->getSpace(pos, check));
}

spTween Board::move(space& a, const Point& pos)
{
    spTween tween = a.piece->move(getPos(pos));
    space& cur = _field[a.pos.x + a.pos.y * _size.x];
    space& new_p = _field[pos.x + pos.y * _size.x];
    new_p.piece = a.piece;
    cur.piece = 0;

    return tween;
}

void Board::touched(Event* event)
{
    TouchEvent* te = safeCast<TouchEvent*>(event);
    Vector2 pos = te->localPosition;
    //logs::messageln("%d - %d: %.2f, %.2f", event->target->getObjectID(), event->currentTarget->getObjectID(), pos.x, pos.y);
    Point spacePos;
    spacePos.x = (int)(pos.x / PieceSize.x);
    spacePos.y = (int)(pos.y / PieceSize.y);

    space* sp = getSpace(spacePos);

    if (_selected)
    {
        _selected->piece->unselect();
        hideMoves();
        auto moves = _selected->piece->getMoves(_selected->pos, *this);
        if (moves.count(spacePos))
        {
            if (sp)
            {
                sp->piece->explode();
            }
            spTween tween = move(*_selected, spacePos);
            tween->setDoneCallback(CLOSURE(this, &Board::moved));
            _selected = 0;
            return;
        }
    }

    if (sp && sp->piece->getColor() == _current && _selected != sp)
    {
        _selected = sp;
        sp->piece->select();
        auto moves = _selected->piece->getMoves(_selected->pos, *this);
        showMoves(moves);
    }
    else {
        _selected = 0;
    }
}

void Board::showMoves(const std::unordered_set<Point>& moves)
{
    for (auto& move : moves)
    {
        auto dot = _dots[move.x + move.y * _size.x];
        dot->setVisible(true);
    }
}

void Board::hideMoves()
{
    for (auto dot : _dots)
    {
        dot->setVisible(false);
    }
}

spActor Board::getView()
{
    return _view;
}

void Board::free()
{
    _field.clear();
    _view->detach();
    _view = 0;
}
