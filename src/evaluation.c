#include "board.h"
#include "evaluation.h"
#include "moves.h"
#include <malloc.h>

/* Evaluates the board state, the bigger value the better for white
 * and vice versa. */
double evaluation_function(board * brd) {
  return material_difference(brd) + 0.05*mobility_difference(brd) +
    0.33*development_function(brd) + 0.15*soldier_development(brd);
}

/* Calculates the material difference */
double material_difference(board * brd) {
  double total = 0;
  int c= 0;
  for(int i = 0; i < 120; i++) {
    if(brd->array[i] < 0) c = -1;
    else c = 1;
    if(brd->array[i] * c == 1) {
      total += PAWN_VALUE*c;
    } else if(brd->array[i] * c == 2) {
      total += KNIGHT_VALUE*c;
    } else if(brd->array[i] *c == 3) {
      total += BISHOP_VALUE*c;
    } else if(brd->array[i] * c == 4) {
      total += ROOK_VALUE*c;
    } else if(brd->array[i] * c == 5) {
      total += QUEEN_VALUE*c;
    } else if(brd->array[i] * c == 6) {
      total += KING_VALUE*c;
    }
  }
  return total;
}

/* Calculates mobility difference of black and white */
double mobility_difference(board * brd) {

  move * m = malloc(sizeof(move));
  init_move(&m);
  generate_all_moves(1, brd, &m);
  int a = count_moves(&m);
  free_moves(&m);
  m=malloc(sizeof(move));
  init_move(&m);
  generate_all_moves(-1, brd, &m);
  int b = count_moves(&m);
  free_moves(&m);
  return (double)(a-b);
}

double development_function(board * brd) {
  int white_dev = 0; int black_dev = 0;
  if(brd->array[27] != 2) white_dev++;
  if(brd->array[22] != 2) white_dev++;
  if(brd->array[28] != 4) white_dev++;
  if(brd->array[21] != 4) white_dev++;
  if(brd->array[23] != 3) white_dev++;
  if(brd->array[26] != 3) white_dev++;

  if(brd->array[97] != -2) black_dev++;
  if(brd->array[92] != -2) black_dev++;
  if(brd->array[98] != -4) black_dev++;
  if(brd->array[91] != -4) black_dev++;
  if(brd->array[93] != -3) black_dev++;
  if(brd->array[96] != -3) black_dev++;

  if(brd->half_moves < 20 && brd->array[25] != 5) white_dev -= 2;
  if(brd->half_moves < 20 && brd->array[95] != -5) black_dev -= 2;

  return (double)((white_dev-black_dev));
}

double soldier_development(board * brd) {
  int white_dev =0 , black_dev = 0;
  for(int i = 0; i < 120; i++) {
    if(brd->array[i] == 1) {
      white_dev += (i - (30 + i%10))/10;
    }
    if(brd->array[i] == -1) {
      black_dev += 6 - ((i- (30 + i%10))/10);
    }
  }
  return (double)(white_dev-black_dev);
}

