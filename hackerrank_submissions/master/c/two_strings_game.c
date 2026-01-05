/*
 * Contest: Master
 * Challenge: Two Strings Game
 * Language: c
 * Score: 0.0
 */

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Suffix Automaton Node */
typedef struct {
    int len;
    int link;
    int next[26];
    int grundy;
    // For B: count[g] stores number of paths in subtree with Grundy value g
    long long cnt_b[30]; 
    // For A: total_wins stores number of valid pairs (A_ext, B_any) in this subtree
    long long total_wins_a; 
} Node;

/* Automaton State */
typedef struct {
    Node* nodes;
    int sz;
    int last;
    int capacity;
} SAM;

void sam_init(SAM* sam, int maxlen) {
    sam->capacity = maxlen * 2 + 1;
    sam->nodes = (Node*)calloc(sam->capacity, sizeof(Node));
    sam->nodes[0].link = -1;
    // Initialize next arrays to -1 to distinguish from index 0
    for(int i=0; i<sam->capacity; i++) {
        for(int j=0; j<26; j++) sam->nodes[i].next[j] = -1;
    }
    sam->sz = 1;
    sam->last = 0;
}

void sam_extend(SAM* sam, char c) {
    int cur = sam->sz++;
    sam->nodes[cur].len = sam->nodes[sam->last].len + 1;
    int p = sam->last;
    int code = c - 'a';
    while (p != -1 && sam->nodes[p].next[code] == -1) {
        sam->nodes[p].next[code] = cur;
        p = sam->nodes[p].link;
    }
    if (p == -1) {
        sam->nodes[cur].link = 0;
    } else {
        int q = sam->nodes[p].next[code];
        if (sam->nodes[p].len + 1 == sam->nodes[q].len) {
            sam->nodes[cur].link = q;
        } else {
            int clone = sam->sz++;
            sam->nodes[clone].len = sam->nodes[p].len + 1;
            sam->nodes[clone].link = sam->nodes[q].link;
            memcpy(sam->nodes[clone].next, sam->nodes[q].next, sizeof(sam->nodes[q].next));
            
            while (p != -1 && sam->nodes[p].next[code] == q) {
                sam->nodes[p].next[code] = clone;
                p = sam->nodes[p].link;
            }
            sam->nodes[q].link = sam->nodes[cur].link = clone;
        }
    }
    sam->last = cur;
}

void sam_free(SAM* sam) {
    free(sam->nodes);
}

// Global visited arrays for DFS to prevent re-computation
int* vis_grundy;
int* vis_calc;

// Compute Grundy values
void calc_grundy(SAM* sam, int u) {
    if (vis_grundy[u]) return;
    vis_grundy[u] = 1;

    int seen_grundy = 0; // Bitmask for small grundy values (up to 30)
    
    for (int i = 0; i < 26; i++) {
        int v = sam->nodes[u].next[i];
        if (v != -1) {
            calc_grundy(sam, v);
            int g = sam->nodes[v].grundy;
            if (g < 30) seen_grundy |= (1 << g);
        }
    }
    
    int mex = 0;
    while (seen_grundy & (1 << mex)) mex++;
    sam->nodes[u].grundy = mex;
}

// Compute counts for B (how many substrings in subtree have grundy g)
void calc_counts_b(SAM* sam, int u) {
    if (vis_calc[u]) return;
    vis_calc[u] = 1;

    // The substring corresponding to the node itself contributes
    // Note: In trie traversal, the node represents one valid substring ending.
    sam->nodes[u].cnt_b[sam->nodes[u].grundy] = 1;

    for (int i = 0; i < 26; i++) {
        int v = sam->nodes[u].next[i];
        if (v != -1) {
            calc_counts_b(sam, v);
            for (int g = 0; g < 30; g++) {
                sam->nodes[u].cnt_b[g] += sam->nodes[v].cnt_b[g];
            }
        }
    }
}

// Global to hold B's total counts for easy access when processing A
long long b_total_by_grundy[30];
long long b_total_substrings = 0;

// Compute wins for A (how many pairs starting with this prefix win)
void calc_wins_a(SAM* sam, int u) {
    if (vis_calc[u]) return;
    vis_calc[u] = 1;

    // Current substring A' wins against (Total B - B with same Grundy)
    int g = sam->nodes[u].grundy;
    // Winning count = Total B strings - B strings with same grundy
    long long current_wins = b_total_substrings - (g < 30 ? b_total_by_grundy[g] : 0);
    
    sam->nodes[u].total_wins_a = current_wins;

    for (int i = 0; i < 26; i++) {
        int v = sam->nodes[u].next[i];
        if (v != -1) {
            calc_wins_a(sam, v);
            sam->nodes[u].total_wins_a += sam->nodes[v].total_wins_a;
        }
    }
}

char* final_a;
char* final_b;
int found_flag = 0;

// Reconstruct string A
void find_kth_a(SAM* sam, int u, long long* k, char* buffer, int depth) {
    if (found_flag) return;

    int g = sam->nodes[u].grundy;
    long long wins_here = b_total_substrings - (g < 30 ? b_total_by_grundy[g] : 0);

    if (*k <= wins_here) {
        // Found the A string!
        buffer[depth] = '\0';
        final_a = strdup(buffer);
        // Now find B
        found_flag = 1; // Mark A found
        return; 
    }
    
    *k -= wins_here;

    for (int i = 0; i < 26; i++) {
        int v = sam->nodes[u].next[i];
        if (v != -1) {
            if (*k <= sam->nodes[v].total_wins_a) {
                buffer[depth] = 'a' + i;
                find_kth_a(sam, v, k, buffer, depth + 1);
                if (found_flag) return;
            } else {
                *k -= sam->nodes[v].total_wins_a;
            }
        }
    }
}

// Reconstruct string B
void find_kth_b(SAM* sam, int u, long long* k, int target_grundy, char* buffer, int depth) {
    if (found_flag == 2) return;

    int g = sam->nodes[u].grundy;
    
    if (g != target_grundy) {
        if (*k == 1) {
            buffer[depth] = '\0';
            final_b = strdup(buffer);
            found_flag = 2;
            return;
        }
        (*k)--;
    }

    for (int i = 0; i < 26; i++) {
        int v = sam->nodes[u].next[i];
        if (v != -1) {
            // How many valid strings in this branch?
            long long valid_in_branch = 0;
            for(int j=0; j<30; j++) {
                if(j != target_grundy) valid_in_branch += sam->nodes[v].cnt_b[j];
            }
            
            if (*k <= valid_in_branch) {
                buffer[depth] = 'a' + i;
                find_kth_b(sam, v, k, target_grundy, buffer, depth + 1);
                if (found_flag == 2) return;
            } else {
                *k -= valid_in_branch;
            }
        }
    }
}

/*
 * Complete the 'twoStrings' function below.
 */
char** twoStrings(long k_in, char* a, char* b, int* result_count) {
    long long k = (long long)k_in;
    
    SAM sam_a, sam_b;
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    sam_init(&sam_a, len_a);
    for(int i=0; i<len_a; i++) sam_extend(&sam_a, a[i]);
    
    sam_init(&sam_b, len_b);
    for(int i=0; i<len_b; i++) sam_extend(&sam_b, b[i]);

    // 1. Calc Grundy for A
    vis_grundy = (int*)calloc(sam_a.sz, sizeof(int));
    calc_grundy(&sam_a, 0);
    free(vis_grundy);

    // 2. Calc Grundy for B
    vis_grundy = (int*)calloc(sam_b.sz, sizeof(int));
    calc_grundy(&sam_b, 0);
    free(vis_grundy);

    // 3. Calc Subtree Counts for B
    vis_calc = (int*)calloc(sam_b.sz, sizeof(int));
    calc_counts_b(&sam_b, 0);
    free(vis_calc);

    // Store B totals globally
    b_total_substrings = 0;
    for(int i=0; i<30; i++) {
        b_total_by_grundy[i] = sam_b.nodes[0].cnt_b[i];
        b_total_substrings += b_total_by_grundy[i];
    }

    // 4. Calc Total Wins for A
    vis_calc = (int*)calloc(sam_a.sz, sizeof(int));
    calc_wins_a(&sam_a, 0);
    free(vis_calc);

    // Check if solution exists
    if (k > sam_a.nodes[0].total_wins_a) {
        *result_count = 1;
        char** res = malloc(sizeof(char*));
        res[0] = strdup("no solution");
        sam_free(&sam_a);
        sam_free(&sam_b);
        return res;
    }

    // 5. Find A
    found_flag = 0;
    char* buf = malloc((len_a + len_b + 5) * sizeof(char));
    find_kth_a(&sam_a, 0, &k, buf, 0);

    // Calculate Grundy of the found A string
    // To do this properly, we need to trace the path again or store it.
    // However, find_kth_a stopped exactly at the node representing A'.
    // Wait, find_kth_a logic updates k. We need to preserve the state or retrieve the grundy.
    // The traversal in find_kth_a finds A, but to find B we need G(A').
    // Let's re-traverse A to get G(A').
    int curr = 0;
    for(int i=0; final_a[i]; i++) {
        curr = sam_a.nodes[curr].next[final_a[i] - 'a'];
    }
    int ga = sam_a.nodes[curr].grundy;

    // 6. Find B
    // k currently holds the remaining index relative to the specific A' found
    // The logic inside find_kth_a subtracted counts for skipped A's, but when it found the correct A',
    // the variable k was containing exactly the index within the B-list for that A'.
    // BUT find_kth_a checks `if (*k <= wins_here)`. The value of k is correct for the B-search.
    found_flag = 1; // ready for B
    find_kth_b(&sam_b, 0, &k, ga, buf, 0);

    sam_free(&sam_a);
    sam_free(&sam_b);
    free(buf);

    *result_count = 2;
    char** res = malloc(2 * sizeof(char*));
    res[0] = final_a;
    res[1] = final_b;
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    long k = parse_long(*(first_multiple_input + 2));

    char* a = readline();

    char* b = readline();

    int result_count;
    char** result = twoStrings(k, a, b, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

long parse_long(char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
