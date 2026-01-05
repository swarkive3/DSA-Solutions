/*
 * Contest: Master
 * Challenge: Simplified Chess Engine
 * Language: c
 * Score: 0.0
 */

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -- Helper Structures and Definitions -- */

typedef struct {
    char type;    // 'Q', 'N', 'B', 'R'
    int r, c;     // Row and Column (0-3)
    int is_dead;  // 1 if captured, 0 otherwise
} Piece;

// Direction arrays for Knight
int knight_dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int knight_dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// Directions for sliding pieces (Queen, Rook, Bishop)
// Indices 0-3: Orthogonal (Rook)
// Indices 4-7: Diagonal (Bishop)
int slide_dr[] = {0, 0, 1, -1, 1, 1, -1, -1};
int slide_dc[] = {1, -1, 0, 0, 1, -1, 1, -1};

/* -- Helper Functions -- */

// Check if a square contains a piece. Returns index in array or -1.
int get_piece_index(int r, int c, Piece* pieces, int count) {
    for(int i = 0; i < count; i++) {
        if (!pieces[i].is_dead && pieces[i].r == r && pieces[i].c == c) {
            return i;
        }
    }
    return -1;
}

// Recursive Minimax Solver
// turn: 1 = White, 0 = Black
// moves_left: Number of full moves White has left to win
bool can_win(Piece* w_pieces, int w_count, Piece* b_pieces, int b_count, int turn, int moves_left) {
    
    // Base Case: If it's White's turn and no moves are left, White failed to win in time.
    if (turn == 1 && moves_left == 0) return false;

    // Set up pointers for current player and opponent
    Piece* my_pieces = turn ? w_pieces : b_pieces;
    int my_count = turn ? w_count : b_count;
    Piece* opp_pieces = turn ? b_pieces : w_pieces;
    int opp_count = turn ? b_count : w_count;

    // Try all pieces for the current player
    for (int i = 0; i < my_count; i++) {
        if (my_pieces[i].is_dead) continue;

        Piece p = my_pieces[i];
        
        // Determine move characteristics
        bool is_knight = (p.type == 'N');
        bool is_rook = (p.type == 'R');
        bool is_bishop = (p.type == 'B');
        
        // Iterate through directions
        // Knight: 8 dirs (custom array)
        // Rook: 4 dirs (0-3 of slide array)
        // Bishop: 4 dirs (4-7 of slide array)
        // Queen: 8 dirs (0-7 of slide array)
        
        int start_dir = is_bishop ? 4 : 0;
        int end_dir = is_rook ? 4 : 8;
        if (is_knight) end_dir = 8; // Iterate 0-7 for knight array

        for (int d = start_dir; d < end_dir; d++) {
            int dr = is_knight ? knight_dr[d] : slide_dr[d];
            int dc = is_knight ? knight_dc[d] : slide_dc[d];
            
            int nr = p.r + dr;
            int nc = p.c + dc;

            // Loop for sliding (runs once for Knight)
            while (nr >= 0 && nr <= 3 && nc >= 0 && nc <= 3) {
                // Check if blocked by own piece
                int my_block = get_piece_index(nr, nc, my_pieces, my_count);
                if (my_block != -1) break; 

                // Check if opponent piece is here (Capture)
                int opp_idx = get_piece_index(nr, nc, opp_pieces, opp_count);
                
                // --- WIN/LOSS CHECK ---
                if (opp_idx != -1 && opp_pieces[opp_idx].type == 'Q') {
                    // If we captured the Queen:
                    // White wins (return true)
                    // Black wins (White loses -> return false)
                    return turn ? true : false;
                }
                
                // --- MAKE MOVE ---
                // Save state to backtrack
                int prev_r = my_pieces[i].r;
                int prev_c = my_pieces[i].c;
                
                my_pieces[i].r = nr;
                my_pieces[i].c = nc;
                if (opp_idx != -1) opp_pieces[opp_idx].is_dead = 1;

                // --- RECURSE ---
                // If current is White (1), next is Black (0). Pass same moves_left.
                // If current is Black (0), next is White (1). Decrement moves_left.
                int next_moves = (turn == 1) ? moves_left : moves_left - 1;
                
                bool result = can_win(w_pieces, w_count, b_pieces, b_count, !turn, next_moves);

                // --- BACKTRACK ---
                my_pieces[i].r = prev_r;
                my_pieces[i].c = prev_c;
                if (opp_idx != -1) opp_pieces[opp_idx].is_dead = 0;

                // --- EVALUATE ---
                if (turn == 1) {
                    // White needs just ONE winning move
                    if (result == true) return true;
                } else {
                    // Black needs just ONE move to prevent White win (return false)
                    if (result == false) return false;
                }

                // If captured or is Knight, stop sliding
                if (opp_idx != -1 || is_knight) break;

                // Continue sliding
                nr += dr;
                nc += dc;
            }
        }
    }

    // If we exhausted all moves:
    // If White: Found no winning move -> return false.
    // If Black: Found no escape move (or no moves at all) -> return true (White wins).
    return turn ? false : true;
}

/* -- Main Function -- */

char* simplifiedChessEngine(int whites_rows, int whites_columns, char** whites, int blacks_rows, int blacks_columns, char** blacks, int moves) {
    
    // 1. Parse Input
    Piece w_pieces[5];
    Piece b_pieces[5];

    for (int i = 0; i < whites_rows; i++) {
        // Format "T C R" e.g., "Q A 1"
        w_pieces[i].type = whites[i][0];
        w_pieces[i].c = whites[i][2] - 'A';
        w_pieces[i].r = whites[i][4] - '1'; // Convert 1-based char to 0-based int
        w_pieces[i].is_dead = 0;
    }

    for (int i = 0; i < blacks_rows; i++) {
        b_pieces[i].type = blacks[i][0];
        b_pieces[i].c = blacks[i][2] - 'A';
        b_pieces[i].r = blacks[i][4] - '1';
        b_pieces[i].is_dead = 0;
    }

    // 2. Solve
    // Start with White's turn (1)
    bool result = can_win(w_pieces, whites_rows, b_pieces, blacks_rows, 1, moves);

    // 3. Return Output
    char* output = (char*)malloc(4 * sizeof(char));
    if (result) {
        strcpy(output, "YES");
    } else {
        strcpy(output, "NO");
    }
    return output;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* g_endptr;
    char* g_str = readline();
    int g = strtol(g_str, &g_endptr, 10);

    if (g_endptr == g_str || *g_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int g_itr = 0; g_itr < g; g_itr++) {
        char** wbm = split_string(readline());

        char* w_endptr;
        char* w_str = wbm[0];
        int w = strtol(w_str, &w_endptr, 10);

        if (w_endptr == w_str || *w_endptr != '\0') { exit(EXIT_FAILURE); }

        char* b_endptr;
        char* b_str = wbm[1];
        int b = strtol(b_str, &b_endptr, 10);

        if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

        char* m_endptr;
        char* m_str = wbm[2];
        int m = strtol(m_str, &m_endptr, 10);

        if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

        char** whites = malloc(w * sizeof(char*));

        for (int whites_row_itr = 0; whites_row_itr < w; whites_row_itr++) {
            whites[whites_row_itr] = malloc(3 * (sizeof(char)));

            char** whites_item_temp = split_string(readline());

            for (int whites_column_itr = 0; whites_column_itr < 3; whites_column_itr++) {
                char* whites_item_str = whites_item_temp[whites_column_itr];
                char whites_item = *whites_item_str;

                whites[whites_row_itr][whites_column_itr] = whites_item;
            }
        }

        char** blacks = malloc(b * sizeof(char*));

        for (int blacks_row_itr = 0; blacks_row_itr < b; blacks_row_itr++) {
            blacks[blacks_row_itr] = malloc(3 * (sizeof(char)));

            char** blacks_item_temp = split_string(readline());

            for (int blacks_column_itr = 0; blacks_column_itr < 3; blacks_column_itr++) {
                char* blacks_item_str = blacks_item_temp[blacks_column_itr];
                char blacks_item = *blacks_item_str;

                blacks[blacks_row_itr][blacks_column_itr] = blacks_item;
            }
        }

        int result_count;
        char** result = simplifiedChessEngine(whites_rows, whites_columns, whites, blacks_rows, blacks_columns, blacks, m, &result_count);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
