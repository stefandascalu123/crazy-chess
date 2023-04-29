#include "Pis.h"

#include <bits/stdc++.h>

Pis::Pis() {
    side = NONE;
}

Pis::Pis(Piece origin, PlaySide side){
    this->origin = origin;
    this->type = origin;
    this->side = side;
    hasMoved = false;
}

