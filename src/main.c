/* Chess artificial intelligence 
 * Jussi-Pekka Erkkilä, 2011
 * juerkkil@iki.fi
 *
 * Please apply MIT license if you wish to copypaste something.
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "board.h"
#include "moves.h"
#include "evaluation.h"
#include "ai.h"
#include "io.h"

void init_test(board * brd);

int main() {

  board b;
  init_board(&b);

  move * m = NULL;
  m = malloc(sizeof(move));
  init_move(&m);

  int a = 0;
  while(1) {
    print_board(&b);
    make_ai_move(&b, 1);
    if(is_check(&b, 1)) {
      printf("Check against black!\n");
      if(!has_moves(&b, -1)) {
        print_board(&b);
        printf("Checkmate, white wins!\n");
        break;
      }
    }
    print_board(&b);
    while(!a) a = read_move(&b, -1);
    a = 0;
    if(is_check(&b, -1)) {
      printf("Check against white!\n");
      if(!has_moves(&b, 1)) {
        printf("Checkmate, black wins!\n");
        print_board(&b);
        break;
      }
    }
  }
  return 0;
}

// just for testing
void init_test(board * brd) {
  brd->black_king = 0;
  brd->white_king = 0;
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
  brd->array[38] = -6;
  brd->array[27] = 4;
  brd->array[26] = 5;
  brd->array[78] = 1;
  brd->array[85] = 6;
  brd->array[71] = 1;
  brd->array[73] = 1;
  brd->array[63] = 3;
  brd->array[55] = 3;
}


