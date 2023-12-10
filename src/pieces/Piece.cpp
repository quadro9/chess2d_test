#include "Piece.h"
#include "../shared.h"

const Vector2 PieceSize(75, 75);

Piece::Piece(CColor color, const std::string& name): _moving(false), _exploding(false), _dead(false), _falling(false), _color(color)
{
    _view = new Sprite;

    std::string color_name = color == CColor::White ? "w_" : "b_";
    color_name += name;
    ResAnim* rs = res.getResAnim(color_name);

    _view->setResAnim(rs);

    //set pilot to center of sprite
    Vector2 center = _view->getSize() / 2;
    //round center to avoid blurred image
    center.x = int(center.x);
    center.y = int(center.y);
    _view->setAnchorInPixels(center);
}

spActor Piece::getView() const
{
    return _view;
}

void Piece::explode()
{
    _exploding = true;
    float angle = 360 * (rand() % 2 ? -1 : 1);
    spTween tween = _view->addTween(Actor::TweenRotationDegrees(angle), 500);
    _view->addTween(Actor::TweenAlpha(0), 500);
    tween->setDoneCallback(CLOSURE(this, &Piece::exploded));
}

void Piece::exploded(Event*)
{
    _dead = true;
    _view->detach();
}

void Piece::select()
{
    _view->addTween(Actor::TweenScale(1.2f), 300, -1, true);
}

void Piece::unselect()
{
    _view->removeTweens(false);
    _view->addTween(Actor::TweenScale(1), 250);
}

void Piece::fall(const Vector2& pos)
{
    _falling = true;
    _view->addTween(Actor::TweenPosition(pos), 500) ->setDoneCallback(CLOSURE(this, &Piece::fallen));
}

spTween Piece::move(const Vector2& pos)
{
    _moving = true;
    spTween tween = _view->addTween(Actor::TweenPosition(pos), 200);
    tween->addDoneCallback(CLOSURE(this, &Piece::moved));
    return tween;
}

void Piece::moved(Event*)
{
    _moving = false;
}

void Piece::fallen(Event*)
{
    _falling = false;
}