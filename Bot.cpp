#include "Bot.h"

#include <bits/stdc++.h>

const std::string Bot::BOT_NAME = "NuPuneBotul"; /* Edit this, escaped characters are forbidden */
extern PlaySide getEngineSide();

Bot::Bot() { /* Initialize custom fields here */

  inCheck = false;
  for(int i = 0; i < 8; i++)  {
    switch (i) {
    case 0:
      chessBoard[0][i] = Pis(ROOK, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(ROOK, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;
    
    case 1:
      chessBoard[0][i] = Pis(KNIGHT, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(KNIGHT, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;
    
    case 2:
      chessBoard[0][i] = Pis(BISHOP, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(BISHOP, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;

    case 3:
      chessBoard[0][i] = Pis(QUEEN, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(QUEEN, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;

    case 4:
      chessBoard[0][i] = Pis(KING, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      king = chessBoard[0][i];
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(KING, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;

    case 5:
      chessBoard[0][i] = Pis(BISHOP, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(BISHOP, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;

    case 6:
      chessBoard[0][i] = Pis(KNIGHT, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(KNIGHT, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;
    
    case 7:
      chessBoard[0][i] = Pis(ROOK, BLACK);
      chessBoard[0][i].coordX = i;
      chessBoard[0][i].coordY = 0;
      chessBoard[1][i] = Pis(PAWN, BLACK);
      chessBoard[1][i].coordX = i;
      chessBoard[1][i].coordY = 1;
      chessBoard[6][i] = Pis(PAWN, WHITE);
      chessBoard[6][i].coordX = i;
      chessBoard[6][i].coordY = 6;
      chessBoard[7][i] = Pis(ROOK, WHITE);
      chessBoard[7][i].coordX = i;
      chessBoard[7][i].coordY = 7;
      break;
    }
    whitePieces.push_back(chessBoard[7][i]);
    whitePieces.push_back(chessBoard[6][i]);
    blackPieces.push_back(chessBoard[1][i]);
    blackPieces.push_back(chessBoard[0][i]);
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
    source_y = boardSize - source_y;
    destination_y = atoi(&destination[1]);
    destination_y = boardSize - destination_y;

    chessBoard[destination_y][destination_x] = chessBoard[source_y][source_x];
    chessBoard[source_y][source_x] = Pis();

    std::ofstream fout("out.txt");

    if(isInCheck()) {
      std::cout << "CHECK!\n";
    } else {
      std::cout << "Not in check\n";
    }
}

bool isInCheck() {
  for(Pis piece : whitePieces) {
    case(piece.type) {
      case PAWN:
        if(chessBoard[piece.coordY - 1][piece.coordX].type == KING && chessBoard[piece.coordY - 1][piece.coordX].side == BLACK) {
          return true;
        }
        if(!piece.hasMoved) {
          if(chessBoard[piece.coordY - 2][piece.coordX].type == KING && chessBoard[piece.coordY - 2][piece.coordX].side == BLACK) {
          return true;
        }
        }
        break;
        
      case ROOK:
        bool blockUp = false, blockDown = false, blockLeft = false, blockRight = false;
        for(int i = 1; i < boardSize; i++) {
          
          if(!blockUp && piece.coordY - i >=0 && chessBoard[piece.coordY - i][piece.coordX] == KING && chessBoard[piece.coordY - i][piece.coordX].side == BLACK) {
            return true;
          }
          if(!blockDown && piece.coordY + i < 8 && chessBoard[piece.coordY + i][piece.coordX] == KING && chessBoard[piece.coordY + i][piece.coordX].side == BLACK) {
            return true;
          }
          if(!blockLeft && piece.coordX - i >=0 && chessBoard[piece.coordY][piece.coordX - i] == KING && chessBoard[piece.coordY][piece.coordX - i].side == BLACK) {
            return true;
          }
          if(!blockRight && piece.coordY + i < 8 && chessBoard[piece.coordY][piece.coordX + i] == KING && chessBoard[piece.coordY][piece.coordX + i].side == BLACK) {
            return true;
          }
          if(chessBoard[piece.coordY - i][piece.coordX].side != NONE) {
            blockUp = true;
          }

          if(chessBoard[piece.coordY + i][piece.coordX].side != NONE) {
            blockDown = true;
          }

          if(chessBoard[piece.coordY][piece.coordX - i].side != NONE) {
            blockLeft = true;
          }

          if(chessBoard[piece.coordY][piece.coordX + i].side != NONE) {
            blockRight = true;
          }
        }
        break;

      case BISHOP:
      bool blockUpRight = false, blockUpLeft = false, blockDownLeft = false, blockDownRight = false;
        for(int i = 1; i < boardSize; i++) {
          
          if(!blockUpLeft && piece.coordY - i >=0 && piece.coordX - i >=0 && chessBoard[piece.coordY - i][piece.coordX - i] == KING && chessBoard[piece.coordY - i][piece.coordX - i].side == BLACK) {
            return true;
          }
          if(!blockUpRight && piece.coordX + i < 8 && piece.coordY - i >=0 && chessBoard[piece.coordY - i][piece.coordX + 1] == KING && chessBoard[piece.coordY - i][piece.coordX + i].side == BLACK) {
            return true;
          }
          if(!blockDownLeft && piece.coordY + i < 8 && piece.coordX - i >=0 && chessBoard[piece.coordY + i][piece.coordX - i] == KING && chessBoard[piece.coordY + i][piece.coordX - i].side == BLACK) {
            return true;
          }
          if(!blockDownRight && piece.coordY + i < 8 && piece.coordX + i < 8 && chessBoard[piece.coordY + i][piece.coordX + i] == KING && chessBoard[piece.coordY + i][piece.coordX + i].side == BLACK) {
            return true;
          }
          if(chessBoard[piece.coordY - i][piece.coordX - i].side != NONE) {
            blockUpLeft = true;
          }

          if(chessBoard[piece.coordY - i][piece.coordX + i].side != NONE) {
            blockUpRight = true;
          }

          if(chessBoard[piece.coordY + i][piece.coordX - i].side != NONE) {
            blockDownLeft = true;
          }

          if(chessBoard[piece.coordY + i][piece.coordX + i].side != NONE) {
            blockDownRight = true;
          }
        }
        break;

      case QUEEN:
        bool blockUp = false, blockDown = false, blockLeft = false, blockRight = false,
          blockUpRight = false, blockUpLeft = false, blockDownLeft = false, blockDownRight = false;
        for(int i = 1; i < boardSize; i++) {
          
          if(!blockUp && piece.coordY - i >=0 && chessBoard[piece.coordY - i][piece.coordX] == KING && chessBoard[piece.coordY - i][piece.coordX].side == BLACK) {
            return true;
          }
          if(!blockDown && piece.coordY + i < 8 && chessBoard[piece.coordY + i][piece.coordX] == KING && chessBoard[piece.coordY + i][piece.coordX].side == BLACK) {
            return true;
          }
          if(!blockLeft && piece.coordX - i >=0 && chessBoard[piece.coordY][piece.coordX - i] == KING && chessBoard[piece.coordY][piece.coordX - i].side == BLACK) {
            return true;
          }
          if(!blockRight && piece.coordY + i < 8 && chessBoard[piece.coordY][piece.coordX + i] == KING && chessBoard[piece.coordY][piece.coordX + i].side == BLACK) {
            return true;
          }

          if(!blockUpLeft && piece.coordY - i >=0 && piece.coordX - i >=0 && chessBoard[piece.coordY - i][piece.coordX - i] == KING && chessBoard[piece.coordY - i][piece.coordX - i].side == BLACK) {
            return true;
          }
          if(!blockUpRight && piece.coordX + i < 8 && piece.coordY - i >=0 && chessBoard[piece.coordY - i][piece.coordX + 1] == KING && chessBoard[piece.coordY - i][piece.coordX + i].side == BLACK) {
            return true;
          }
          if(!blockDownLeft && piece.coordY + i < 8 && piece.coordX - i >=0 && chessBoard[piece.coordY + i][piece.coordX - i] == KING && chessBoard[piece.coordY + i][piece.coordX - i].side == BLACK) {
            return true;
          }
          if(!blockDownRight && piece.coordY + i < 8 && piece.coordX + i < 8 && chessBoard[piece.coordY + i][piece.coordX + i] == KING && chessBoard[piece.coordY + i][piece.coordX + i].side == BLACK) {
            return true;
          }

          if(chessBoard[piece.coordY - i][piece.coordX].side != NONE) {
            blockUp = true;
          }

          if(chessBoard[piece.coordY + i][piece.coordX].side != NONE) {
            blockDown = true;
          }

          if(chessBoard[piece.coordY][piece.coordX - i].side != NONE) {
            blockLeft = true;
          }

          if(chessBoard[piece.coordY][piece.coordX + i].side != NONE) {
            blockRight = true;
          }

          if(chessBoard[piece.coordY - i][piece.coordX - i].side != NONE) {
            blockUpLeft = true;
          }

          if(chessBoard[piece.coordY - i][piece.coordX + i].side != NONE) {
            blockUpRight = true;
          }

          if(chessBoard[piece.coordY + i][piece.coordX - i].side != NONE) {
            blockDownLeft = true;
          }

          if(chessBoard[piece.coordY + i][piece.coordX + i].side != NONE) {
            blockDownRight = true;
          }
        }
        break;

        case KNIGHT:
          if(piece.coordY - 1 >=0 && piece.coordX - 2 >=0 && chessBoard[piece.coordY - 1][piece.coordX - 2].type == KING && chessBoard[piece.coordY - 1][piece.coordX - 2].side == BLACK) {
            return true;
          }

          if(piece.coordY - 2 >=0 && piece.coordX - 1 >=0 && chessBoard[piece.coordY - 2][piece.coordX - 1].type == KING && chessBoard[piece.coordY - 2][piece.coordX - 1].side == BLACK) {
            return true;
          }

          if(piece.coordY - 1 >=0 && piece.coordX + 2 < 8 && chessBoard[piece.coordY - 1][piece.coordX + 2].type == KING && chessBoard[piece.coordY - 1][piece.coordX + 2].side == BLACK) {
            return true;
          }

          if(piece.coordY - 2 >= 0 && piece.coordX + 1 < 8 && chessBoard[piece.coordY - 2][piece.coordX + 1].type == KING && chessBoard[piece.coordY - 2][piece.coordX + 1].side == BLACK) {
            return true;
          }

          if(piece.coordY + 1 < 8 && piece.coordX - 2 >=0 && chessBoard[piece.coordY + 1][piece.coordX - 2].type == KING && chessBoard[piece.coordY + 1][piece.coordX - 2].side == BLACK) {
            return true;
          }

          if(piece.coordY + 2 < 8 && piece.coordX - 1 >=0 && chessBoard[piece.coordY + 2][piece.coordX - 1].type == KING && chessBoard[piece.coordY + 2][piece.coordX - 1].side == BLACK) {
            return true;
          }

          if(piece.coordY + 1 < 8 && piece.coordX + 2 < 8 && chessBoard[piece.coordY + 1][piece.coordX + 2].type == KING && chessBoard[piece.coordY + 1][piece.coordX + 2].side == BLACK) {
            return true;
          }

          if(piece.coordY + 2 < 8 && piece.coordX + 1 < 8 && chessBoard[piece.coordY + 2][piece.coordX + 1].type == KING && chessBoard[piece.coordY + 2][piece.coordX + 1].side == BLACK) {
            return true;
          }
          break;
    }
  }
  return false;
}

Move* Bot::calculateNextMove() {
  /* Play move for the side the engine is playing (Hint: getEngineSide())
   * Make sure to record your move in custom structures before returning.
   *
   * Return move that you are willing to submit
   * Move is to be constructed via one of the factory methods declared in Move.h */

  std::vector<Move> allMoves;
  for(Pis piece : blackPieces) {
    
  }

  return Move::resign();
}

std::string Bot::getBotName() { return Bot::BOT_NAME; }
