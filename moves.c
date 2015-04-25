/* Chess AI 
 * moves.c
 */
#include "moves.h"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void init_move(move ** mv) {
  (*mv)->next = NULL;
  (*mv)->x= -1;
  (*mv)->where = -1;
  (*mv)->from = -1;
  (*mv)->castle = 0;
  (*mv)->promotion = 0;
}

void generate_all_moves(int c, board * brd, move ** moves) {
  move * tmp;
  tmp = *moves;
  for(int a = 9; a > 1; a--) {
    for(int b = 8; b > 0; b--) {
      if(brd->array[a*10 + b]*c == 1) {
        generate_pawn_moves(a*10+b, brd, c, &tmp);
      }
      if(brd->array[a*10 + b]*c == 2) {
        generate_knight_moves(a*10+b, brd, c, &tmp);
      }
      if(brd->array[a*10 + b]*c == 3) {
        generate_bishop_moves(a*10+b, brd, c, &tmp);
      }
      if(brd->array[a*10 + b]*c == 4) {
        generate_rook_moves(a*10+b, brd, c, &tmp);
      }
      if(brd->array[a*10 + b]*c == 5) {
        generate_queen_moves(a*10+b, brd, c, &tmp);
      }
      if(brd->array[a*10 + b]*c == 6) {
        generate_king_moves(a*10+b, brd, c, &tmp);
      }
      while(tmp->next != NULL) tmp=tmp->next;
    }
  }


}

/* Generate all possible queen moves.
 * Queen moves are actually combination of rook and bishop moves */
void generate_queen_moves(int a, board * brd, int c, move ** moves) {
  generate_bishop_moves(a, brd, c, moves);
  move * t = *moves; while(t->next != NULL) t=t->next;
  generate_rook_moves(a, brd, c, &t);
}

/* Generate all possible king moves
 * a = location on board
 * brd = current state
 * c = color (1 = white, -1 = black)
 */
void generate_king_moves(int a, board * brd, int c, move ** moves) {
  move * tmp;
  tmp = *moves;
  if(brd->array[a+1]*c <= 0 && brd->array[a+1] != 7) {
    tmp->from = a;
    tmp->where = a+1;
    tmp->x = brd->array[a+1];
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-1]*c <= 0 && brd->array[a-1] != 7) {
    tmp->from = a;
    tmp->where = a-1;
    tmp->x = brd->array[a-1];
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a+10]*c <= 0  && brd->array[a+10] != 7) {
    tmp->from = a;
    tmp->where = a+10;
    tmp->x = brd->array[a+10];
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-10]*c <= 0 && brd->array[a-10] != 7) {
    tmp->from = a;
    tmp->where = a-10;
    tmp->x = brd->array[a-10];
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-9]*c <= 0 && brd->array[a-9] != 7 ) {
    tmp->from = a;
    tmp->where = a-9;
    tmp->x = brd->array[a-9];
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-11]*c <= 0 && brd->array[a-11] != 7 ) {
    tmp->from = a;
    tmp->where = a-11;
    tmp->x = brd->array[a-11];
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a+9]*c <= 0 && brd->array[a+9] != 7) {
    tmp->from = a;
    tmp->where = a+9;
    tmp->x = brd->array[a+9];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a+11]*c <= 0 && brd->array[a+11] != 7 ) {
    tmp->from = a;
    tmp->where = a+11;
    tmp->x = brd->array[a+11];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }

  /* Special case: castling moves */
  if(c == 1) {
    if(brd->white_king == 0 && brd->array[23] == 0 && brd->array[22] == 0) {
      tmp->castle = 1;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
    if(brd->white_king && brd->array[25] == 0 && brd->array[26] == 0 &&
        brd->array[27] == 0) {
      tmp->castle = 2;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
  } else if(c == -1) {
    if(brd->black_king == 0 && brd->array[93] == 0 && brd->array[92] == 0) {
      tmp->castle = 3;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
    if(brd->black_king == 0 && brd->array[95] == 0 && brd->array[96] == 0 &&
        brd->array[97] == 0) {
      tmp->castle = 4;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
  }
}

/* Generate all possible pawn moves
 * a = location on board
 * brd = current state
 * c = color (1 = white, -1 = black)
 */
void generate_pawn_moves(int a, board * brd, int c, move ** moves) {
  move * tmp;
  tmp = *moves;
  if(c == 1) {
    if(brd->array[a+10] == 0) {
      tmp->from = a;
      tmp->where = a+10;
      tmp->x = 0;
      if(tmp->where > 90)
        tmp->promotion = 1;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
      if(a < 40 && brd->array[a+20] == 0) {
        tmp->from = a;
        tmp->where = a+20;
        tmp->x = 0;
        tmp->next = malloc(sizeof(move));
        init_move(&(tmp->next));
        tmp = tmp->next;
      }
    }
    if(brd->array[a+9] < 0) {
      tmp->from = a;
      tmp->where = a+9;
      tmp->x = brd->array[a+9];
      tmp->next = malloc(sizeof(move));
      if(tmp->where > 90)
        tmp->promotion = 1;
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
    if(brd->array[a+11] < 0) {
      tmp->from = a;
      tmp->where = a+11;
      if(tmp->where > 90)
        tmp->promotion = 1;
      tmp->x = brd->array[a+11];
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
  } else if(c == -1) {
    if(brd->array[a-10] == 0) {
      tmp->from = a;
      tmp->where = a-10;
      tmp->x = 0;
      if(tmp->where < 30) 
        tmp->promotion = 1;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
      if(a > 80 && brd->array[a-20] == 0) {
        tmp->from = a;
        tmp->where = a-20;
        tmp->x = 0;
        tmp->next = malloc(sizeof(move));
        init_move( &(tmp->next));
        tmp = tmp->next;
      }
    }
    if(brd->array[a-9] > 0 && brd->array[a-9] != 7) {
      tmp->from = a;
      tmp->where = a-9;
      tmp->x = brd->array[a-9];
      if(tmp->where < 30) 
        tmp->promotion = 1;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
    if(brd->array[a-11] > 0 && brd->array[a-11] != 7) {
      tmp->from = a;
      tmp->where = a-11;
      tmp->x = brd->array[a-11];
      if(tmp->where < 30) 
        tmp->promotion = 1;
      tmp->next = malloc(sizeof(move));
      init_move(&(tmp->next));
      tmp = tmp->next;
    }
  }
}

/* Generate all possible knight moves
 * a = location on board
 * brd = current state
 * c = color (1 = white, -1 = black)
 */
void generate_knight_moves(int a, board * brd, int c, move ** moves) {
  move * tmp;
  tmp = *moves;
  if(brd->array[a-8] != 7 && (brd->array[a-8]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a-8;
    tmp->x = brd->array[a-8];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-12] != 7 && (brd->array[a-12]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a-12;
    tmp->x = brd->array[a-12];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-19] != 7 && (brd->array[a-19]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a-19;
    tmp->x = brd->array[a-19];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a-21] != 7 && (brd->array[a-21]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a-21;
    tmp->x = brd->array[a-21];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }

  if(brd->array[a+8] != 7 && (brd->array[a+8]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a+8;
    tmp->x = brd->array[a+8];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a+12] != 7 && (brd->array[a+12]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a+12;
    tmp->x = brd->array[a+12];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a+19] != 7 && (brd->array[a+19]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a+19;
    tmp->x = brd->array[a+19];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
  if(brd->array[a+21] != 7 && (brd->array[a+21]*c) <= 0 ) {
    tmp->from = a;
    tmp->where = a+21;
    tmp->x = brd->array[a+21];
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
  }
}

/* Generate all possible bishop moves
 * a = location on board
 * brd = current state
 * c = color (1 = white, -1 = black)
 */
void generate_bishop_moves(int a, board * brd, int c, move ** moves) {
  int i = a;
  move * tmp;
  tmp = *moves;
  while(brd->array[i-9] != 7 && (brd->array[i-9] * c) <= 0 ) { 
    tmp->from = a;
    tmp->where = i-9;
    tmp->x = brd->array[i-9]; // capture
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
    if(brd->array[i-9] != 0) 
      break;
    i-=9;
  }

  i = a;
  while(brd->array[i+11] != 7 && (brd->array[i+11] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i+11;
    tmp->x = brd->array[i+11]; // capture
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
    if(brd->array[i+11] != 0) 
      break;
    i += 11;
  }
  i = a;

  while(brd->array[i+9] != 7 && (brd->array[i+9] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i+9;
    tmp->x = brd->array[i+9]; // capture
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));

    tmp = tmp->next;
    if(brd->array[i+9] != 0) 
      break;
    i += 9;
  }
  i = a;

  while(brd->array[i-11] != 7 && (brd->array[i-11] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i-11;
    tmp->x = brd->array[i-11]; // capture
    tmp->next = malloc(sizeof(move));
    init_move(&(tmp->next));
    tmp = tmp->next;
    if(brd->array[i-11] != 0) 
      break;
    i -=11;
  }
}

/* Generate all possible rook moves
 * a = location on board
 * brd = current state
 * c = color (1 = white, -1 = black)
 */
void generate_rook_moves(int a, board * brd, int c, move ** moves) {
  int i = a;
  move * tmp;
  tmp = *moves;
  while(brd->array[i-10] != 7 && (brd->array[i-10] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i-10;
    tmp->x = brd->array[i-10]; // capture
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
    if(brd->array[i-10] != 0)
      break;
    i -= 10;
  }

  i = a;
  while(brd->array[i+10] != 7 && (brd->array[i+10] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i+10;
    tmp->x = brd->array[i+10]; // capture
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
    if(brd->array[i+10] != 0)
      break;
    i += 10;
  }
  i = a;
  while(brd->array[i+1] != 7 && (brd->array[i+1] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i+1;
    tmp->x = brd->array[i+1]; // capture
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
    if(brd->array[i+1] != 0)
      break;
    i++;
  }
  i = a;
  while(brd->array[i-1] != 7 && (brd->array[i-1] * c) <= 0 ) { // if different color pieces 
    tmp->from = a;
    tmp->where = i-1;
    tmp->x = brd->array[i-1]; // capture
    tmp->next = malloc(sizeof(move));
    init_move( &(tmp->next));
    tmp = tmp->next;
    if(brd->array[i-1] != 0)
      break;
    i--;
  }
}


/* Applies move m to board brd. Returns 1 on success and 0 on fail 
 * (if move is illegal) */
int apply_move(board * brd, move ** m, int c) {

  move * mv = *m;
  /* First special case: castling */
  
  if(mv->castle != 0) {
    if(is_check(brd, c*(-1)))
      return 0;
    if(mv->castle == 1 && brd->white_king == 0 ) {
      if(brd->array[23]==0 && brd->array[22] == 0 && brd->array[21] == 4) {
        brd->white_king++;
        brd->array[22] = 6; brd->array[23] = 4;
        brd->array[24] = 0; brd->array[21]=0;
        return 1;
      }
    } else if(mv->castle == 2 && brd->white_king == 0) {
      if(brd->array[25]==0 && brd->array[26] == 0 && 
          brd->array[27] == 0 && brd->array[28] == 4) {
        brd->white_king++;
        brd->array[26] = 6; brd->array[25] = 4;
        brd->array[28] = 0; brd->array[27]=0; brd->array[24] = 0;
        return 1;
      }
    } else if(mv->castle == 3 && brd->black_king == 0) {
      if(brd->array[93]==0 && brd->array[92] == 0 && brd->array[91] == -4) {
        brd->black_king++;
        brd->array[92] = -6; brd->array[93] = -4;
        brd->array[94]= 0; brd->array[91]=0;
        return 1;
      }
    } else if(mv->castle == 4 && brd->black_king == 0) {
      if(brd->array[95]==0 && brd->array[96] == 0 && 
          brd->array[97] == 0 && brd->array[98] == -4) {
        brd->black_king++;
        brd->array[96] = -6; brd->array[95] = -4;
        brd->array[98] = 0; brd->array[97]=0; brd->array[94] = 0;
        return 1;
      }
    }
    return 0;
  }


  move * t = malloc(sizeof(move));
  init_move(&t);
  move * t_ = t;
  int piece = brd->array[mv->from];
  piece *= c;
  if(piece <= 0) {
    printf("Invalid piece, failed\n");
    free_moves(&t);
    return 0;
  }
  if(piece == 1) { /* Generate all possible moves */
    generate_pawn_moves(mv->from, brd, c, &t);
  } else if(piece == 2) {
    generate_knight_moves(mv->from, brd, c, &t);
  } else if(piece == 3) {
    generate_bishop_moves(mv->from, brd, c, &t);
  } else if(piece == 4) {
    generate_rook_moves(mv->from, brd, c, &t);
  } else if(piece == 5) {
    generate_queen_moves(mv->from, brd, c, &t);
  } else if(piece ==6) {
    generate_king_moves(mv->from, brd, c, &t);
  }
  /* Check if our move is among possible moves. If it is, apply it. */
  while(t_->next != NULL) {
    if(t_->where == mv->where) {
      if(brd->array[mv->from] == 6) {
        brd->white_king++;
      }
      if(brd->array[mv->from] == -6) {
        brd->black_king++;
      }
      brd->array[mv->where]= brd->array[mv->from];
      brd->array[mv->from]= 0;
      if(mv->promotion) {
        brd->array[mv->where] = 5*c;
      }
      /* Here we make sure that move is valid (no check for opponent) */
      if(!is_check(brd, c*(-1))) {
        free_moves(&t);
        return 1; // success
      } else {
        undo_move(brd, m);
        free_moves(&t);
        return 0;
      }
    }
    t_ = t_->next;
  }
  free_moves(&t);
  return 0; // fail, illegal move
}

/* Undo move m from board brd */

int undo_move(board * brd, move ** m) {
  if((*m)->castle != 0) {
    if((*m)->castle == 1) {
      brd->white_king--;
      brd->array[21] = 4; brd->array[24] = 6; 
      brd->array[23] = 0; brd->array[22]= 0;
    } else if((*m)->castle == 2) {
      brd->array[28] = 4; brd->array[24] = 6; 
      brd->array[25] = 0; brd->array[26]= 0;
      brd->white_king--;
      brd->array[27] = 0;
    } else if((*m)->castle == 3) {
      brd->array[91] = -4; brd->array[94] = -6; brd->array[93] = 0; 
      brd->array[92]= 0; brd->black_king--;
    } else if((*m)->castle == 4) {
      brd->array[98] = -4; brd->array[94] = -6; brd->array[95] = 0; 
      brd->array[96]= 0; brd->array[97]=0;
      brd->black_king--;
    }
    return 1;
  }
  if(brd->array[(*m)->where] == 6) brd->white_king--;
  if(brd->array[(*m)->where] == -6) brd->black_king--;
  brd->array[(*m)->from] = brd->array[(*m)->where];
  brd->array[(*m)->where] = (*m)->x;
  if((*m)->promotion)
    brd->array[(*m)->from] = brd->array[(*m)->from]/5;
  return 1;
}

/* Return length of move list moves */
int count_moves(move ** moves) {
  move * m = *moves;
  int i = 0;
  while(m->next != NULL) {
    m = m->next;
    i++;
  }
  return i;
}

/*  Returns pointer to move number i of move list moves */
move * get_move(move ** moves, int i) {
  move * m = *moves;
  for(int a = 0; a < i; a++) {
    m = m->next;
  }
  return m;
}

/* Makes and applies a random move for color c
 * This is only for testing */
void make_random_move(int c, board * brd) {
  srand((unsigned)time(NULL));
  move * m = malloc(sizeof(move));
  init_move(&m);
  generate_all_moves(c, brd, &m);
  int i = count_moves(&m);
  int a = rand() % i;
  move * mv;
  do {
    mv = get_move(&m, a);
    a = rand() % i;
  } while(!apply_move(brd, &mv, c));
  free_moves(&m);
}

/* Free the memory allocated for move list */
void free_moves(move ** m) {
  move * mv = *m;
move * tmp;
  int a = count_moves(&mv);
  for(int i = a; i > 0; i--) {
    tmp = get_move(&mv, i);
    free(tmp);
  }
  free(mv);
}
  

