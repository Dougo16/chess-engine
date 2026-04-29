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
#define NOT_B_FILE 0xfdfdfdfdfdfdfdfdULL
#define NOT_G_FILE 0xbfbfbfbfbfbfbfbfULL
#define NOT_H_FILE 0x7f7f7f7f7f7f7f7fULL

#define BitBoard uint64_t // Bitboard

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

BitBoard precomp_moves[2][64];

// ====================|
// FUNCTION PROTOTYPES |
// ====================|


void print_bitboard (BitBoard bitboard);

void generate_moves (const Board *b, MoveList *ml);

void init_generate_moves (move_table);

// ===========|
// STRUCTURES |
// ===========|

typedef struct {
    BitBoard pieces[8];
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

// Generate moves for easily precomputable pieces (knight and king)
void init_generate_moves (BitBoard **move_table) {
    BitBoard moves;

    // King moves
    for (int index = 0; index < 63; index++) {
        moves = 0ULL;

        moves = gen_king_moves(index);

        move_table[0][index] = moves;
    }

    // Knight moves
    for (int index = 0; index < 63; index++) {
        moves = 0ULL;

        moves = gen_knight_moves(index);

        move_table[0][index] = moves;
    }
}

void generate_moves (const Board *b, MoveList *ml) {

}


// ================|
// MOVE GENERATORS |
// ================|

BitBoard gen_king_moves (int index) {
    BitBoard moves = 0ULL;
    
    BitBoard bb = index_to_bb(index);

    moves |= bb << 8; // N
    moves |= bb >> 8; // S
    moves |= bb >> 1; // W
    moves |= bb << 1; // E
    moves |= bb << 7; // NW
    moves |= bb << 9; // NE
    moves |= bb >> 9; // SW
    moves |= bb >> 7; // SE

    if (index % 8 == 7) {
        moves &= NOT_A_FILE;
    }
    else if (index % 8 == 0) {
        moves &= NOT_H_FILE;
    }

    return moves;

}

BitBoard gen_knight_moves (int index) {
    BitBoard moves = 0ULL;
    
    BitBoard bb = index_to_bb(index);

    moves |= bb << 17; // NE high
    moves |= bb >> 17; // SW low
    moves |= bb >> 15; // NW high
    moves |= bb << 15; // SE low
    moves |= bb << 6; // NW left
    moves |= bb << 10; // NE right
    moves |= bb >> 6; // SE right
    moves |= bb >> 10; // SW left

    // Mask out wraparound
    if (index % 8 >= 6) {
        moves &= (NOT_A_FILE & NOT_B_FILE);
    }
    else if (index % 8 <= 1) {
        moves &= (NOT_H_FILE & NOT_G_FILE);
    }

    return moves;

}




// =================|
// HELPER FUNCTIONS |
// =================|


void print_bitboard (BitBoard bitboard) {
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

BitBoard index_to_bb (int index) {
    return 1ULL << index;
}