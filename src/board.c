#include "board.h"
#include "moves.h"
#include <stdio.h>
#include <malloc.h>
char number_to_piece(int i) {
  if(i == 0) return '.';
  if(i == 1) return 'P';
  if(i == 2) return 'N';
  if(i == 3) return 'B';
  if(i == 4) return 'R';
  if(i == 5) return 'Q';
  if(i == 6) return 'K';

  if(i == -1) return 'p';
  if(i == -2) return 'n';
  if(i == -3) return 'b';
  if(i == -4) return 'r';
  if(i == -5) return 'q';
  if(i == -6) return 'k';
  return '#';
}

void init_board(board * brd) {
  brd->white_king = 0;
  brd->black_king = 0;
  brd->half_moves = 0;
  for(int i = 0; i < 120; i++) {
    if(i < 20) {
      brd->array[i] = 7;
    }
    else if(! ((i+1) % 10) || !(i%10)) {
      brd->array[i] = 7;
    }
    else if(i > 100) {
      brd->array[i] = 7;
    }
    else brd->array[i] = 0;
  }
  brd->array[21] = 4; // White rook
  brd->array[22] = 2; // White knight
  brd->array[23] = 3; // White bishop
  brd->array[24] = 6; // White king
  brd->array[25] = 5; // White queen
  brd->array[26] = 3;
  brd->array[27] = 2;
  brd->array[28] = 4;

  brd->array[31] = 1; // White pawn
  brd->array[32] = 1;
  brd->array[33] = 1;
  brd->array[34] = 1;
  brd->array[35] = 1;
  brd->array[36] = 1;
  brd->array[37] = 1;
  brd->array[38] = 1;


  brd->array[91] = -4; // White rook
  brd->array[92] = -2; // White knight
  brd->array[93] = -3; // White bishop
  brd->array[94] = -6; // White king
  brd->array[95] = -5; // White queen
  brd->array[96] = -3;
  brd->array[97] = -2;
  brd->array[98] = -4;

  brd->array[81] = -1; // White pawn
  brd->array[82] = -1;
  brd->array[83] = -1;
  brd->array[84] = -1;
  brd->array[85] = -1;
  brd->array[86] = -1;
  brd->array[87] = -1;
  brd->array[88] = -1;
}

/* Function returns 1 if opponent's king is checked
 * c = 1 (white) or -1 (black) */
int is_check(board * brd, int c) {
  move * t = malloc(sizeof(move));
  init_move(&t);
  generate_all_moves(c, brd, &t);
  move * t_ = t;
  while(t_->next != NULL) {
    if( t_->x * c == -6) {
      free_moves(&t);
      return 1;
    }
    t_=t_->next;
  }
  free_moves(&t);
  return 0;
}

/* Returns 1 if player c has valid moves left.
 * c = 1 (white) or -1 (black)
 * If king is in check and no valid moves left, that implies checkmate */
int has_moves(board * brd, int c) {
  move * t = malloc(sizeof(move));
  init_move(&t);
  generate_all_moves(c, brd, &t);
  move * t_ = t;
  while(t_->next != NULL) {
    if(apply_move(brd, &t_, c)) {
      undo_move(brd, &t_);
      free_moves(&t);
      return 1;

    }
    t_ = t_->next;
  }
  free_moves(&t);
  return 0;
}

