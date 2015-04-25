#ifndef AI_H
#define AI_H

#define DEPTH 4

void make_ai_move(board * brd, int c);
double alpha_beta(board * brd, int depth, double alpha, double beta, int c, int debug, move ** best);

#endif
