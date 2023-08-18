#include "Move.h"

Move::Move()
{
    posr = 0, posl = 0, posb = 0, post = 0;
}

Move::Move(double _posr, double _posl, double _post, double _posb)
{
    posr = _posr;
    posl = _posl;
    post = _post;
    posb = _posb;
}

Move::~Move()
{
    posr = 0, posl = 0, posb = 0, post = 0;
}

void Move::SetposR(double _posr)
{
    posr = _posr;
}

double Move::GetposR()
{
    return posr;
}

void Move::SetposL(double _posl)
{
    posl = _posl;
}

double Move::GetposL()
{
    return posl;
}

void Move::SetposT(double _post)
{
    post = _post;
}

double Move::GetposT()
{
    return post;
}

void Move::SetposB(double _posb)
{
    posb = _posb;
}

double Move::GetposB()
{
    return posb;
}
