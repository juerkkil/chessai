#include <malloc.h>
#include "board.h"
#include "moves.h"
#include "ai.h"
#include "evaluation.h"

void make_ai_move(board * brd, int c) {

  move * m = malloc(sizeof(move));
  init_move(&m);
  alpha_beta(brd, DEPTH, -1000, 1000, c, 0, &m);
  apply_move(brd, &m, c);

  /* Convert array item number to chess board row/column */
  char f[2], t[2];
  f[2] = '\0';
  t[2] ='\0';
  f[0] = 'h' - (m->from % 10) + 1;
  f[1] = '0' + (m->from - (m->from % 10))/10 - 1;
  t[0] = 'h' - (m->where % 10) + 1;
  t[1] = '0' + (m->where - (m->where % 10))/10 - 1;
  if(m->x == 0)
    printf("My move is %s to %s\n", f,t);
  else
    printf("My move is %sx%s\n", f,t);
  brd->half_moves++;
  free_moves(&m);
  
}

/* Minimax algorithm with alpha beta pruning. This is implemented so that 
 * every iteration we swap alpha and beta and multiply them by -1 which
 * makes our implementation shorter and marginally faster as we need
 * one comparision less */
double alpha_beta(board * brd, int depth, double alpha, double beta, int c, int debug, move ** best) {
  if(depth == 0) {
    if(DEPTH % 2 == 0)
      return evaluation_function(brd);
    else
      return (-1)*evaluation_function(brd);
  }
  double value = 0;
  int moves = 0;
  move * m = malloc(sizeof(move));
  init_move(&m);
  generate_all_moves(c, brd, &m);
  move *mv;
  int a = count_moves(&m);
  for(int i = 0; i<a;i++) {
    mv = get_move(&m, i);
    if(apply_move(brd, &mv, c)) {
      moves++;
      value = alpha_beta(brd, depth-1, beta * (-1), alpha*(-1), c*(-1), debug, best)*(-1);
      undo_move(brd, &mv);
      if(value >= beta) { // alpha (or beta) cut-off
        free_moves(&m);
        return beta;
      }
      if(value > alpha) {
        alpha = value;
        if(depth == DEPTH) {
          (*best)->from = mv->from;
          (*best)->where = mv->where;
          (*best)->x = mv->x;
          (*best)->promotion = mv->promotion;
          (*best)->castle = mv->castle;
          (*best)->next = NULL;
        }
      }

    }
  }
  free_moves(&m);
  if(moves == 0) {
    if(c == -1) {
      if(is_check(brd, 1)) {
        return -999;
      } else {
        return 0;
      }
    } else if(c == 1) {
      if(is_check(brd, -1)) {
          return 999;
      } else {
        return 0;
      }
    }
  }
          


  return alpha;

}

