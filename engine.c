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

#define U64 uint64_t

U64 get_pieces(U64 * board, int colour, int piece);
void print_bitboard(U64 bitboard);

int main() {
    U64 board = 0ULL;

    print_bitboard(board);
    
    return 0;
}

// HELPER FUNCTIONS

U64 get_pieces(U64 * board, int colour, int piece) {
    return board[colour] & board[piece];
}

void print_bitboard(U64 bitboard) {
    printf("\n");
    
    for (int r = 7; r >=0; r--) {
        for (int f = 7; f >= 0; f--) {
            unsigned int bit = (bitboard >> r + 8*f) & 1ULL;
            
            if (bit == 1) {
                printf("1");
            }
            else {
                printf(".");
            }
        }
    }
}