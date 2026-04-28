#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define WHITE 0
#define BLACK 1
#define KING 2
#define QUEEN 3
#define ROOK 4
#define BISHOP 5
#define KNIGHT 6
#define PAWN 7

#define NOT_A_FILE 0xfefefefefefefefeULL
#define NOT_H_FILE 0x7f7f7f7f7f7f7f7fULL
#define NOT_B_FILE 0xfdfdfdfdfdfdfdfdULL
#define NOT_G_FILE 0xbfbfbfbfbfbfbfbfULL

#define U64 uint64_t // Bitboard

// Move components
#define MOVE_FROM(m) ((m) & 0x3F)
#define MOVE_TO(m) (((m) >> 6) & 0x3F)
#define MOVE_FLAGS(m) (((m) >> 12) & 0xF)
#define MOVE_PROMO(m) (((m) >> 16) & 0xF)

// Flags
#define FLAG_QUIET        0x0
#define FLAG_CAPTURE      0x1
#define FLAG_EP           0x2
#define FLAG_CASTLE_K     0x3
#define FLAG_CASTLE_Q     0x4
#define FLAG_PROMO        0x8

// ====================|
// FUNCTION PROTOTYPES |
// ====================|


void print_bitboard (U64 bitboard);

void generate_moves (const Board *b, MoveList *ml);

// ===========|
// STRUCTURES |
// ===========|

typedef struct {
    U64 pieces[8];
    int side_to_move;
    int castling_rights;
    int en_passant_sq;
} Board;

typedef struct {
    Move moves[256];
    int count;
} MoveList;

typedef uint32_t Move; // Move

// ==========|
// MAIN LOOP |
// ==========|


int main() {
    return 0;
}

// =====================|
// BOARD REPRESENTATION |
// =====================|




void generate_moves (const Board *b, MoveList *ml) {

}




// =================|
// HELPER FUNCTIONS |
// =================|


void print_bitboard (U64 bitboard) {
    printf("\n");
    
    for (int rank = 7; rank >=0; rank--) {
        for (int file = 0; file < 8; file++) {
            unsigned int bit = (bitboard >> (8 * rank + file)) & 1ULL;
            
            if (bit == 1) {
                printf("1 ");
            }
            else {
                printf(". ");
            }
        }
        
        printf("\n");
    }
}

// Finds the position of the lowest piece on the board
static inline int pop_lsb(bb) {
    // Counts the trailing zeros (position of least significant bit)
    int index = __builtin_ctzll(bb); 
    
    // Clears the lowest bit
    bb = bb & (bb - 1); 
    return index;
}

// Takes in current position of piece and places it can move to
// then converts these to individual moves
void extract_moves (int from_index, int targets, int flags, MoveList movelist) {
    int count = 0;
    
    while (targets != 0) {
        count++;
        int to_index = pop_lsb(targets);
        movelist.moves[count] = encode_move(from_index, to_index, flags);
    }
}

Move encode_move (int from_index, int to_index, int flags) {
    return (flags << 12) & (to_index << 6) & from_index;
}