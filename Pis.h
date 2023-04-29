#ifndef PIS_H
#define PIS_H
#include <bits/stdc++.h>

#include "PlaySide.h"
#include "Piece.h"

class Pis {
public:
    Piece origin;
    Piece type;
    PlaySide side;
    bool hasMoved;

    Pis();
    Pis(Piece origin, PlaySide side);
};
#endif