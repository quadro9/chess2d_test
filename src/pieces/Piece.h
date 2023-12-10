#pragma once
#include "oxygine-framework.h"

#include <unordered_set>

using namespace oxygine;

class Board;

DECLARE_SMART(Piece, spPiece);

extern const Vector2 PieceSize;

// Шаблон специализации хэш-функции для класса Point
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            // Пример простой хэш-функции, можете заменить ее на свою
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}

enum class CColor {
    White,
    Black
};

class Piece: public Object
{
public:
    Piece(CColor color, const std::string& name);

    spActor getView() const;

    virtual std::unordered_set<Point> 
    getMoves(const Point& pos, const Board& board) = 0;

    bool isExploding() const {return _exploding;}
    bool isMoving() const {return _moving;}
    bool isDead() const {return _dead;}
    bool isFalling() const {return _falling;}

    CColor getColor() const {return _color;}

    void explode();
    void select();
    void unselect();

    void fall(const Vector2& pos);
    spTween move(const Vector2& pos);

protected:
    void exploded(Event*);
    void fallen(Event*);
    void moved(Event*);

    bool _exploding;
    bool _moving;
    bool _dead;
    bool _falling;
    spSprite _view;

    CColor _color;
};
