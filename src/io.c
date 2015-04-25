#include "board.h"
#include "moves.h"
#include "io.h"
#include <malloc.h>

void print_board(board * brd) {
  for(int a = 9; a > 0; a--) {
    for(int b = 8; b > 0; b--) {
      if(b == 8 && a > 1) { printf("%d ", (a-1)); }
      if(b == 8 && a == 1) { printf("  ");}
      if(a > 1)
        printf("%c ", number_to_piece(brd->array[a*10 + b]));
      if(a == 1) printf("%c ", 105 - b);
    }
    printf("\n");
  }
  /*
  for(int i = 0; i < 120; i++) {
    if( (i%10) == 0) printf("\n");
    if(i < 10) printf(" %d  ", i);
    else if(i >= 10 && i < 100) printf("%d  ", i);
    else printf("%d ", i);
  }
  */
}

/* Read move from stdin and apply it */

int read_move(board * brd, int c) {
  int s, d;
  char a[2], b[2];
  move * t = malloc(sizeof(move));
  init_move(&t);

  printf("Move from: ");
  scanf("%s", a);
  printf("Move to: ");
  scanf("%s", b);
  /* Convert a1 ... h8 to corresponding values in board array */
  s = (a[1]-48 + 1) * 10 + (105-a[0]);
  d = (b[1]-48 + 1) * 10 + (105-b[0]);

  if(s == 517) {
    t->castle = 3;
  } 
  else if(s == 511) {
    t->castle = 4;
  } else {
    t->from = s;
    t->where = d;
    t->x = brd->array[d];
    if(brd->array[s] == 1 && d > 90)
      t->promotion = 1;
    if(brd->array[s] == -1 && d < 30) {
      t->promotion = 1;
    }
  }
  if(apply_move(brd, &t, c)) {
    free(t);
    brd->half_moves++;
    printf("Move OK\n");
    return 1;
  } else {
    free(t);
    return 0;
  }
}

