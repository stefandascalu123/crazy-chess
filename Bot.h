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

  bool moveIsLegal(Move* move);

  bool isCastleLegal(int type);

  bool didEnPassant(Move* move);
  void getCastleMove(std::vector<Move*> &allMoves);

  void getPawnMove(int i, int j, std::vector<Move*> &allMoves);
  void getKnightMove(int i, int j, std::vector<Move*> &allMoves);
  void getRookMove(int i, int j, std::vector<Move*> &allMoves);
  void getBishopMove(int i, int j, std::vector<Move*> &allMoves);
  void getQueenMove(int i, int j, std::vector<Move*> &allMoves);
  void getKingMove(int i, int j, std::vector<Move*> &allMoves);
  void getDropInMove(std::vector<Move*> &allMoves);

  Move* calculateNextMove();

  bool isCheck(Pis chessBoard[boardSize][boardSize]);



  static std::string getBotName();
};
#endif
