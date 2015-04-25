#ifndef MOVES_H
#define MOVES_H

#include "chess.h"
#include "board.h"

struct move_list {
  struct move_list *next;
  int from;
  int where;
  int x; // capture
  int castle;
  int promotion;
};
typedef struct move_list move;


void init_move(move ** mv);
void generate_bishop_moves(int a, board * brd, int c, move ** moves);
void generate_queen_moves(int a, board * brd, int c, move ** moves);
void generate_rook_moves(int a, board * brd, int c, move ** moves);
void generate_knight_moves(int a, board * brd, int c, move ** moves);
void generate_pawn_moves(int a, board * brd, int c, move ** moves);
void generate_king_moves(int a, board * brd, int c, move ** moves);
//int generate_all_moves(int c, board * brd, move ** moves);
void generate_all_moves(int c, board * brd, move ** moves);

int apply_move(board * brd, move ** m, int c);
int undo_move(board * brd, move ** m);
int count_moves(move ** moves);
move * get_move(move ** moves, int i);
void make_random_move(int c, board * brd);
void free_moves(move ** m);

#endif
