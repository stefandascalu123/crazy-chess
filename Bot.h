#ifndef BOT_H
#define BOT_H
#include <bits/stdc++.h>

#include "Move.h"
#include "PlaySide.h"
#include "Pis.h"

#define boardSize 8

class Bot {
 private:
  static const std::string BOT_NAME;

 public:
  /* Declare custom fields below */

  Pis chessBoard[boardSize][boardSize];
  bool isInCheck;

  /* Declare custom fields above */
  Bot();

  /**
   * Record move (either by enemy in normal mode, or by either side
   * in force mode) in custom structures
   * @param move received move
   * @param sideToMode side to move
   */
  void recordMove(Move* move, PlaySide sideToMove);

  /**
   * Calculates and return the bot's next move
   * @return your move
   */
  Move* calculateNextMove();

  bool isCheck();

  static std::string getBotName();
};
#endif
