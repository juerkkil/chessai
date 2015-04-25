#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int array[120];
    int half_moves;
    int white_king;
    int black_king;

} board;

void init_board(board * brd);
char number_to_piece(int i);
int is_check(board * brd, int c);
int has_moves(board * brd, int c);

#endif
