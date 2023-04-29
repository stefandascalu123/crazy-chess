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
      chessBoard[source_y][source_x] = Pis();
    } else if(!move->source && move->getReplacement()) {
      int destination_x, destination_y;

      destination_x = destination[0] - 'a';
      destination_y = atoi(&destination[1]);
      destination_y = boardSize - destination_y;

      chessBoard[destination_y][destination_x] = Pis(replacement, sideToMove);
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

    isInCheck = isCheck();
    if(isInCheck) {
      fout << "Check\n";
    } else {
      fout << "Not Check\n";
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

bool Bot::isCheck() {
  int king_x, king_y;
  for(int i = 0; i < boardSize ; i++) {
    for(int j = 0 ; j < boardSize ; j++) {
      if(chessBoard[i][j].type == KING && chessBoard[i][j].side == getEngineSide()) {
        king_x = j;
        king_y = i;
        break;
      }
    }
  }

  std::ofstream fout("out2.txt");
  fout << "King is at " << king_y << " " << king_x << '\n';

  for(int i = king_y + 1 ; i < boardSize ; i++) {
    if(chessBoard[i][king_x].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][king_x].side != getEngineSide() && chessBoard[i][king_x].side != NONE) {
      if(chessBoard[i][king_x].type == QUEEN || chessBoard[i][king_x].type == ROOK) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_y - 1 ; i >= 0 ; i --) {
    if(chessBoard[i][king_x].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][king_x].side != getEngineSide() && chessBoard[i][king_x].side != NONE) {
      if(chessBoard[i][king_x].type == QUEEN || chessBoard[i][king_x].type == ROOK) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_x + 1 ; i < boardSize ; i++) {
    if(chessBoard[king_y][i].side == getEngineSide()) {
      break;
    } else if(chessBoard[king_y][i].side != getEngineSide() && chessBoard[king_y][i].side != NONE) {
      if(chessBoard[king_y][i].type == QUEEN || chessBoard[king_y][i].type == ROOK) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_x - 1 ; i >= 0 ; i--) {
    if(chessBoard[king_y][i].side == getEngineSide()) {
      break;
    } else if(chessBoard[king_y][i].side != getEngineSide() && chessBoard[king_y][i].side != NONE) {
      if(chessBoard[king_y][i].type == QUEEN || chessBoard[king_y][i].type == ROOK) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_y + 1, j = king_x + 1 ; i < boardSize && j < boardSize ; i++, j++) {
    if(chessBoard[i][j].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][j].side != getEngineSide() && chessBoard[i][j].side != NONE) {
      if(chessBoard[i][j].type == QUEEN || chessBoard[i][j].type == BISHOP) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_y - 1, j = king_x - 1 ; i >= 0 && j >= 0 ; i--, j--) {
    if(chessBoard[i][j].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][j].side != getEngineSide() && chessBoard[i][j].side != NONE) {
      if(chessBoard[i][j].type == QUEEN || chessBoard[i][j].type == BISHOP) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_y + 1, j = king_x - 1 ; i < boardSize && j >= 0 ; i++, j--) {
    if(chessBoard[i][j].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][j].side != getEngineSide() && chessBoard[i][j].side != NONE) {
      if(chessBoard[i][j].type == QUEEN || chessBoard[i][j].type == BISHOP) {
        return true;
      } else {
        break;
      }
    }
  }
  for(int i = king_y - 1, j = king_x + 1 ; i >= 0 && j < boardSize ; i--, j++) {
    if(chessBoard[i][j].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][j].side != getEngineSide() && chessBoard[i][j].side != NONE) {
      if(chessBoard[i][j].type == QUEEN || chessBoard[i][j].type == BISHOP) {
        return true;
      } else {
        break;
      }
    }
  }
  if(getEngineSide() == WHITE) {
    if(king_y - 1 >= 0 && king_x - 1 >= 0 && chessBoard[king_y - 1][king_x - 1].side == BLACK && chessBoard[king_y - 1][king_x - 1].type == PAWN) {
      return true;
    }
    if(king_y - 1 >= 0 && king_x + 1 < boardSize && chessBoard[king_y - 1][king_x + 1].side == BLACK && chessBoard[king_y - 1][king_x + 1].type == PAWN) {
      return true;
    }
  } else {
    if(king_y + 1 < boardSize && king_x - 1 >= 0 && chessBoard[king_y + 1][king_x - 1].side == WHITE && chessBoard[king_y + 1][king_x - 1].type == PAWN) {
      return true;
    }
    if(king_y + 1 < boardSize && king_x + 1 < boardSize && chessBoard[king_y + 1][king_x + 1].side == WHITE && chessBoard[king_y + 1][king_x + 1].type == PAWN) {
      return true;
    }
  }
  if(king_y - 1 >= 0 && king_x - 2 >= 0 && chessBoard[king_y - 1][king_x - 2].type == KNIGHT && chessBoard[king_y - 1][king_x - 2].side != getEngineSide()) {
    return true;
  }
  if(king_y - 2 >= 0 && king_x - 1 >= 0 && chessBoard[king_y - 2][king_x - 1].type == KNIGHT && chessBoard[king_y - 2][king_x - 1].side != getEngineSide()) {
    return true;
  }
  if(king_y - 2 >= 0 && king_x + 1 < boardSize && chessBoard[king_y - 2][king_x + 1].type == KNIGHT && chessBoard[king_y - 2][king_x + 1].side != getEngineSide()) {
    return true;
  }
  if(king_y - 1 >= 0 && king_x + 2 < boardSize && chessBoard[king_y - 1][king_x + 2].type == KNIGHT && chessBoard[king_y - 1][king_x + 2].side != getEngineSide()) {
    return true;
  }
  if(king_y + 1 < boardSize && king_x + 2 < boardSize && chessBoard[king_y + 1][king_x + 2].type == KNIGHT && chessBoard[king_y + 1][king_x + 2].side != getEngineSide()) {
    return true;
  }
  if(king_y + 2 < boardSize && king_x + 1 < boardSize && chessBoard[king_y + 2][king_x + 1].type == KNIGHT && chessBoard[king_y + 2][king_x + 1].side != getEngineSide()) {
    return true;
  }
  if(king_y + 2 < boardSize && king_x - 1 >= 0 && chessBoard[king_y + 2][king_x - 1].type == KNIGHT && chessBoard[king_y + 2][king_x - 1].side != getEngineSide()) {
    return true;
  }
  if(king_y + 1 < boardSize && king_x - 2 >= 0 && chessBoard[king_y + 1][king_x - 2].type == KNIGHT && chessBoard[king_y + 1][king_x - 2].side != getEngineSide()) {
    return true;
  }
  return false;
}

std::string Bot::getBotName() { return Bot::BOT_NAME; }
