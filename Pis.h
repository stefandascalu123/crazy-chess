#ifndef PIS_H
#define PIS_H
#include <bits/stdc++.h>

#include "PlaySide.h"
#include "Piece.h"
#include "Moved.h"

class Pis {
public:
    Piece origin;
    Piece type;
    PlaySide side;
    bool didEnPassant;
    bool hasMoved;

    Pis();
    Pis(Piece origin, PlaySide side);
};
#endif