#ifndef EVALUATION_H
#define EVALUATION_H

#define PAWN_VALUE 1
#define BISHOP_VALUE 3
#define KNIGHT_VALUE 3
#define ROOK_VALUE 5
#define QUEEN_VALUE 9
#define KING_VALUE 200

double evaluation_function(board * brd);
double material_difference(board * brd);
double mobility_difference(board * brd);
double development_function(board * brd);
double soldier_development(board * brd);

#endif
