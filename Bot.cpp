#include "Bot.h"

#include <bits/stdc++.h>

const std::string Bot::BOT_NAME = "NuPuneBotul"; /* Edit this, escaped characters are forbidden */
extern PlaySide getEngineSide();

Bot::Bot() { /* Initialize custom fields here */
  isInCheck = false;
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
    Piece replacement;
    if(move->source) {
      source = move->source.value();
    }

    if(move->destination) {
      destination = move->destination.value();
    }

    if(move->getReplacement()) {
      replacement = move->getReplacement().value();
    }

    if(move->source && !move->getReplacement()) {
    int source_x, source_y;
    int destination_x, destination_y;

    source_x = source[0] - 'a';
    destination_x = destination[0] - 'a';

    source_y = atoi(&source[1]);
    source_y = boardSize - source_y;
    destination_y = atoi(&destination[1]);
    destination_y = boardSize - destination_y;

    chessBoard[destination_y][destination_x] = chessBoard[source_y][source_x];
    chessBoard[destination_y][destination_x].hasMoved = true;
    chessBoard[source_y][source_x] = Pis();
    } else if(move->source && move->getReplacement()) {
      int source_x, source_y;
      int destination_x, destination_y;

      source_x = source[0] - 'a';
      destination_x = destination[0] - 'a';

      source_y = atoi(&source[1]);
      source_y = boardSize - source_y;
      destination_y = atoi(&destination[1]);
      destination_y = boardSize - destination_y;

      chessBoard[destination_y][destination_x] = Pis(replacement, sideToMove);
      chessBoard[destination_y][destination_x].hasMoved = true;
      chessBoard[source_y][source_x] = Pis();
    } else if(!move->source && move->getReplacement()) {
      int destination_x, destination_y;

      destination_x = destination[0] - 'a';
      destination_y = atoi(&destination[1]);
      destination_y = boardSize - destination_y;

      chessBoard[destination_y][destination_x] = Pis(replacement, sideToMove);
      chessBoard[destination_y][destination_x].hasMoved = true;
    }

    std::ofstream fout("out.txt");

  for(int i = 0 ; i < boardSize; i ++){
    for(int j = 0 ; j < boardSize; j++) {
      if(chessBoard[i][j].side == NONE) {
        fout << "X ";
      } else {
        fout << chessBoard[i][j].type << " ";
      }
    }
    fout << '\n';
  }    
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
