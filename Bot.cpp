#include "Bot.h"

#include <bits/stdc++.h>

const std::string Bot::BOT_NAME = "NuPuneBotul"; /* Edit this, escaped characters are forbidden */
extern PlaySide getEngineSide();

Bot::Bot() { /* Initialize custom fields here */
//pula
}

void Bot::recordMove(Move* move, PlaySide sideToMove) {
    /* You might find it useful to also separately
     * record last move in another custom field */
}

Move* Bot::calculateNextMove() {
  /* Play move for the side the engine is playing (Hint: getEngineSide())
   * Make sure to record your move in custom structures before returning.
   *
   * Return move that you are willing to submit
   * Move is to be constructed via one of the factory methods declared in Move.h */
  return Move::resign();
}

std::string Bot::getBotName() { return Bot::BOT_NAME; }
