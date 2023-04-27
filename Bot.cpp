#include "Bot.h"

#include <bits/stdc++.h>

const std::string Bot::BOT_NAME = "NuPuneBotul"; /* Edit this, escaped characters are forbidden */
extern PlaySide getEngineSide();

Bot::Bot() { /* Initialize custom fields here */
  for(int i = 0; i < 8; i++)  {
    switch (i)
    {
    case 0:
      chessBoard[0][i] = Pis(ROOK, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(ROOK, WHITE);
      break;
    
    case 1:
      chessBoard[0][i] = Pis(KNIGHT, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(KNIGHT, WHITE);
      break;
    
    case 2:
      chessBoard[0][i] = Pis(BISHOP, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(BISHOP, WHITE);
      break;

    case 3:
      chessBoard[0][i] = Pis(QUEEN, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(QUEEN, WHITE);
      break;

    case 4:
      chessBoard[0][i] = Pis(KING, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(KING, WHITE);
      break;

    case 5:
      chessBoard[0][i] = Pis(BISHOP, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(BISHOP, WHITE);
      break;

    case 6:
      chessBoard[0][i] = Pis(KNIGHT, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(KNIGHT, WHITE);
      break;
    
    case 7:
      chessBoard[0][i] = Pis(ROOK, BLACK);
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[7][i] = Pis(ROOK, WHITE);
      break;
    }
  }
}

void Bot::recordMove(Move* move, PlaySide sideToMove) {
    /* You might find it useful to also separately
     * record last move in another custom field */

    std::string source, destination;
    if(move->source) {
      source = move->source.value();
    }

    if(move->destination) {
      destination = move->destination.value();
    }

    int source_x, source_y;
    int destination_x, destination_y;

    source_x = source[0] - 'a';
    destination_x = destination[0] - 'a';

    source_y = atoi(&source[1]);
    destination_y = atoi(&destination[1]);

    chessBoard[destination_y][destination_x] = chessBoard[source_y][source_x];
    chessBoard[source_y][source_x] = Pis();
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
