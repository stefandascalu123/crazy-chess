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
    chessBoard[destination_y][destination_x].hasMoved = true;
      if(chessBoard[destination_y][destination_x].type == PAWN) {
        if(abs(destination_y - source_y) == 2) {
          chessBoard[destination_y][destination_x].didEnPassant = true;
        } else {
          chessBoard[destination_y][destination_x].didEnPassant = false;
        }
      }
      if(chessBoard[destination_y][destination_x].type == KING) {
        if(abs(destination_x - source_x) == 2) {
          chessBoard[destination_y][destination_x].hasMoved = true;
          if(destination_x == 2) {
            chessBoard[destination_y][3] = chessBoard[destination_y][0];
            chessBoard[destination_y][0] = Pis();
            chessBoard[destination_y][3].hasMoved = true;
          } else {
            chessBoard[destination_y][5] = chessBoard[destination_y][7];
            chessBoard[destination_y][7] = Pis();
            chessBoard[destination_y][5].hasMoved = true;
          }
        }
      }
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

    isInCheck = isCheck(chessBoard);
    if(isInCheck) {
      fout << "Check\n";
    } else {
      fout << "Not Check\n";
    }
}

bool Bot::moveIsLegal(Move *move) {

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

    Pis chessBoardCopy[boardSize][boardSize];
    memcpy(chessBoardCopy, chessBoard, sizeof(chessBoard));

    if(move->source && !move->getReplacement()) {
    int source_x, source_y;
    int destination_x, destination_y;

    source_x = source[0] - 'a';
    destination_x = destination[0] - 'a';

    source_y = atoi(&source[1]);
    source_y = boardSize - source_y;
    destination_y = atoi(&destination[1]);
    destination_y = boardSize - destination_y;

    chessBoardCopy[destination_y][destination_x] = chessBoardCopy[source_y][source_x];
    chessBoardCopy[source_y][source_x] = Pis();
    if(chessBoardCopy[destination_y][destination_x].type == KING) {
        if(abs(destination_x - source_x) == 2) {
          chessBoardCopy[destination_y][destination_x].hasMoved = true;
          if(destination_x == 2) {
            chessBoardCopy[destination_y][3] = chessBoardCopy[destination_y][0];
            chessBoardCopy[destination_y][0] = Pis();
            chessBoardCopy[destination_y][3].hasMoved = true;
          } else {
            chessBoardCopy[destination_y][5] = chessBoardCopy[destination_y][7];
            chessBoardCopy[destination_y][7] = Pis();
            chessBoardCopy[destination_y][5].hasMoved = true;
          }
        }
      }
    } else if(move->source && move->getReplacement()) {
      int source_x, source_y;
      int destination_x, destination_y;

      source_x = source[0] - 'a';
      destination_x = destination[0] - 'a';

      source_y = atoi(&source[1]);
      source_y = boardSize - source_y;
      destination_y = atoi(&destination[1]);
      destination_y = boardSize - destination_y;

      chessBoardCopy[destination_y][destination_x] = Pis(replacement, getEngineSide());
      chessBoardCopy[source_y][source_x] = Pis();
    } else if(!move->source && move->getReplacement()) {
      int destination_x, destination_y;

      destination_x = destination[0] - 'a';
      destination_y = atoi(&destination[1]);
      destination_y = boardSize - destination_y;

      chessBoardCopy[destination_y][destination_x] = Pis(replacement, getEngineSide());
    }

    return !isCheck(chessBoardCopy);
}


void Bot::getCastleMove(std::vector<Move*> &allMoves){
  if(getEngineSide() == WHITE){
    if(!chessBoard[7][4].hasMoved && !chessBoard[7][7].hasMoved && chessBoard[7][5].side == NONE && chessBoard[7][6].side == NONE && !isCheck(chessBoard)){
      if(moveIsLegal(Move::moveTo("e1", "g1")))
        allMoves.push_back(Move::moveTo("e1", "g1"));
    }
    if(!chessBoard[7][4].hasMoved && !chessBoard[7][0].hasMoved && chessBoard[7][1].side == NONE && chessBoard[7][2].side == NONE && chessBoard[7][3].side == NONE && !isCheck(chessBoard)){
      if(moveIsLegal(Move::moveTo("e1", "c1")))
        allMoves.push_back(Move::moveTo("e1", "c1"));
    }
  } else if (getEngineSide() == BLACK) {
    if(!chessBoard[0][4].hasMoved && !chessBoard[0][7].hasMoved && chessBoard[0][5].side == NONE && chessBoard[0][6].side == NONE && !isCheck(chessBoard)){
      if(moveIsLegal(Move::moveTo("e8", "g8")))
        allMoves.push_back(Move::moveTo("e8", "g8"));
    }
    if(!chessBoard[0][4].hasMoved && !chessBoard[0][0].hasMoved && chessBoard[0][1].side == NONE && chessBoard[0][2].side == NONE && chessBoard[0][3].side == NONE && !isCheck(chessBoard)){
      if(moveIsLegal(Move::moveTo("e8", "c8")))  
        allMoves.push_back(Move::moveTo("e8", "c8"));
    }
  }
}

void Bot::getPawnMove(int i, int j, std::vector<Move*> &allMoves) {
  std::string source, destination;
          source = "";
          destination = "";
          if(getEngineSide() == WHITE) {
            if(chessBoard[i][j - 1].side == BLACK && chessBoard[i][j - 1].didEnPassant) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j - 1) + std::to_string(boardSize - i - 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
                allMoves.push_back(Move::moveTo(source, destination));
            }
            if(chessBoard[i][j + 1].side == BLACK && chessBoard[i][j + 1].didEnPassant) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j + 1) + std::to_string(boardSize - i - 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
                allMoves.push_back(Move::moveTo(source, destination));
            }
            if(i - 1 > 0 && chessBoard[i - 1][j].side == NONE) {
            source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
            destination = std::string(1, 'a' + j) + std::to_string(boardSize - i + 1);
            if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
            if (i == 6 && chessBoard[i - 1][j].side == NONE && chessBoard[i - 2][j].side == NONE) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j) + std::to_string(boardSize - i + 2);
              if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
            if(i - 1 > 0 && j - 1 >= 0 && chessBoard[i - 1][j - 1].side == BLACK) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j - 1) + std::to_string(boardSize - i + 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
            if(i - 1 > 0 && j + 1 < boardSize && chessBoard[i - 1][j + 1].side == BLACK) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j + 1) + std::to_string(boardSize - i + 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
          } else {
            if(chessBoard[i][j - 1].side == WHITE && chessBoard[i][j - 1].didEnPassant) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j - 1) + std::to_string(boardSize - i - 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
                allMoves.push_back(Move::moveTo(source, destination));
            }
            if(chessBoard[i][j + 1].side == WHITE && chessBoard[i][j + 1].didEnPassant) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j + 1) + std::to_string(boardSize - i - 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
                allMoves.push_back(Move::moveTo(source, destination));
            }
            if(i + 1 < boardSize - 1 && chessBoard[i + 1][j].side == NONE) {
            source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
            destination = std::string(1, 'a' + j) + std::to_string(boardSize - i - 1);
            if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
            if (i == 1 && chessBoard[i + 1][j].side == NONE && chessBoard[i + 2][j].side == NONE) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j) + std::to_string(boardSize - i - 2);
              if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
            if(i + 1 < boardSize - 1 && j - 1 >= 0 && chessBoard[i + 1][j - 1].side == WHITE) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j - 1) + std::to_string(boardSize - i - 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
            if(i + 1 < boardSize - 1 && j + 1 < boardSize && chessBoard[i + 1][j + 1].side == WHITE) {
              source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
              destination = std::string(1, 'a' + j + 1) + std::to_string(boardSize - i - 1);
              if(moveIsLegal(Move::moveTo(source, destination)))
              allMoves.push_back(Move::moveTo(source, destination));
            }
          }
}

void Bot::getKnightMove(int i, int j, std::vector<Move*> &allMoves) {
  std::string source, destination;
  source = "";
  destination = "";
  if(i - 1 >=0 && j - 2 >= 0 && chessBoard[i - 1][j - 2].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j - 2) + std::to_string(boardSize - i + 1);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i - 2 >=0 && j - 1 >= 0 && chessBoard[i - 2][j - 1].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j - 1) + std::to_string(boardSize - i + 2);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i - 2 >=0 && j + 1 < boardSize && chessBoard[i - 2][j + 1].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j + 1) + std::to_string(boardSize - i + 2);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i - 1 >=0 && j + 2 < boardSize && chessBoard[i - 1][j + 2].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j + 2) + std::to_string(boardSize - i + 1);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i + 1 < boardSize && j - 2 >= 0 && chessBoard[i + 1][j - 2].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j - 2) + std::to_string(boardSize - i - 1);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i + 2 < boardSize && j - 1 >= 0 && chessBoard[i + 2][j - 1].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j - 1) + std::to_string(boardSize - i - 2);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i + 2 < boardSize && j + 1 < boardSize && chessBoard[i + 2][j + 1].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j + 1) + std::to_string(boardSize - i - 2);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }

  if(i + 1 < boardSize && j + 2 < boardSize && chessBoard[i + 1][j + 2].side != getEngineSide()) {
    source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
    destination = std::string(1, 'a' + j + 2) + std::to_string(boardSize - i - 1);
    if(moveIsLegal(Move::moveTo(source, destination)))
      allMoves.push_back(Move::moveTo(source, destination));
  }
}

void Bot::getRookMove(int i, int j, std::vector<Move*> &allMoves) {
  std::string source, destination;
  source = "";
  destination = "";
  for(int k = i + 1; k < boardSize; k++) {
    if(chessBoard[k][j].side == getEngineSide()) {
      break;
    } else if(chessBoard[k][j].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + j) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + j) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
  for(int k = i - 1; k >= 0; k--) {
    if(chessBoard[k][j].side == getEngineSide()) {
      break;
    } else if(chessBoard[k][j].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + j) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + j) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
  for(int k = j + 1; k < boardSize; k++) {
    if(chessBoard[i][k].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][k].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + k) + std::to_string(boardSize - i);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + k) + std::to_string(boardSize - i);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
  for(int k = j - 1; k >= 0; k--) {
    if(chessBoard[i][k].side == getEngineSide()) {
      break;
    } else if(chessBoard[i][k].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + k) + std::to_string(boardSize - i);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + k) + std::to_string(boardSize - i);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
}

void Bot::getBishopMove(int i, int j, std::vector<Move*> &allMoves) {
  std::string source, destination;
  source = "";
  destination = "";
  for(int k = i + 1, l = j + 1; k < boardSize && l < boardSize; k++, l++) {
    if(chessBoard[k][l].side == getEngineSide()) {
      break;
    } else if(chessBoard[k][l].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
  for(int k = i + 1, l = j - 1; k < boardSize && l >= 0; k++, l--) {
    if(chessBoard[k][l].side == getEngineSide()) {
      break;
    } else if(chessBoard[k][l].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
  for(int k = i - 1, l = j + 1; k >= 0 && l < boardSize; k--, l++) {
    if(chessBoard[k][l].side == getEngineSide()) {
      break;
    } else if(chessBoard[k][l].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
  for(int k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--) {
    if(chessBoard[k][l].side == getEngineSide()) {
      break;
    } else if(chessBoard[k][l].side == NONE) {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
    } else {
      source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
      destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
      if(moveIsLegal(Move::moveTo(source, destination)))
        allMoves.push_back(Move::moveTo(source, destination));
      break;
    }
  }
}

void Bot::getQueenMove(int i, int j, std::vector<Move*> &allMoves) {
  getRookMove(i, j, allMoves);
  getBishopMove(i, j, allMoves);
}

void Bot::getKingMove(int i, int j, std::vector<Move*> &allMoves) {
  std::string source, destination;
  source = "";
  destination = "";
  for(int k = i - 1; k <= i + 1; k++) {
    for(int l = j - 1; l <= j + 1; l++) {
      if(k >= 0 && k < boardSize && l >= 0 && l < boardSize) {
        if(chessBoard[k][l].side == getEngineSide()) {
          continue;
        } else if(chessBoard[k][l].side == NONE) {
          source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
          destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
          if(moveIsLegal(Move::moveTo(source, destination)))
            allMoves.push_back(Move::moveTo(source, destination));
        } else {
          source = std::string(1, 'a' + j) + std::to_string(boardSize - i);
          destination = std::string(1, 'a' + l) + std::to_string(boardSize - k);
          if(moveIsLegal(Move::moveTo(source, destination)))
            allMoves.push_back(Move::moveTo(source, destination));
        }
      }
    }
  }
}

Move* Bot::calculateNextMove() {
  /* Play move for the side the engine is playing (Hint: getEngineSide())
   * Make sure to record your move in custom structures before returning.
   *
   * Return move that you are willing to submit
   * Move is to be constructed via one of the factory methods declared in Move.h */
  std::vector<Move*> allMoves;
  for(int i = 0 ; i < boardSize; i ++){
    for(int j = 0 ; j < boardSize; j++) {
      if(chessBoard[i][j].side == getEngineSide()) {
        if(chessBoard[i][j].type == PAWN) {
          getPawnMove(i, j, allMoves);
        }
        if(chessBoard[i][j].type == KNIGHT) {
          getKnightMove(i, j, allMoves);
        }
        // if(chessBoard[i][j].type == ROOK) {
        //   getRookMove(i, j, allMoves);
        // }
        if(chessBoard[i][j].type == BISHOP) {
          getBishopMove(i, j, allMoves);
        }
        if(chessBoard[i][j].type == QUEEN) {
          getQueenMove(i, j, allMoves);
        }
        // if(chessBoard[i][j].type == KING) {
        //   getKingMove(i, j, allMoves);
        // }
      }
    }
  }
  getCastleMove(allMoves);
  if(allMoves.size()!= 0) {
    return allMoves[rand() % allMoves.size()];
  }
  return Move::resign();
}

bool Bot::isCheck(Pis chessBoard[boardSize][boardSize]) {
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
