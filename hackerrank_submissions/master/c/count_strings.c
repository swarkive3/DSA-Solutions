/*
 * Contest: Master
 * Challenge: Count Strings
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

#define MOD 1000000007
#define MAX_NODES 210

/* -- Data Structures -- */

typedef struct {
    int u, v;
    char type; // 0 for epsilon, 'a', 'b'
} Edge;

typedef struct {
    int start, end;
} NodePair;

// Global storage for the graph to avoid stack overflow or complex passing
Edge edges[MAX_NODES * 4];
int edge_count = 0;
int node_count = 0;

/* -- Helper Functions -- */

void add_edge(int u, int v, char type) {
    edges[edge_count].u = u;
    edges[edge_count].v = v;
    edges[edge_count].type = type;
    edge_count++;
}

// Recursive Descent Parser to build NFA (Thompson's Construction)
NodePair parse(char* r, int i, int j) {
    // Base Case: Single character regex "a" or "b"
    if (i == j) {
        int u = node_count++;
        int v = node_count++;
        add_edge(u, v, r[i]);
        NodePair p = {u, v};
        return p;
    }

    // Recursive Step: Handle "(...)"
    // We assume the input is well-formed according to problem rules.
    if (r[i] == '(' && r[j] == ')') {
        // Find the split point between the two operands
        int balance = 0;
        int split = -1;
        int k = i + 1;

        // The first element starts at i+1. Find where it ends.
        if (r[k] == '(') {
            balance = 1;
            k++;
            while (balance > 0 && k < j) {
                if (r[k] == '(') balance++;
                if (r[k] == ')') balance--;
                k++;
            }
            // k is now the index AFTER the first closed parenthesized group
            split = k - 1; 
        } else {
            // First element is a literal (e.g., 'a' or 'b')
            split = k;
        }

        // Identify the operator located immediately after the first element
        char op = r[split + 1];

        if (op == '*') {
            // Case: Kleene Star (R1*)
            // Parse inner R1
            NodePair inner = parse(r, i + 1, split);
            int s = node_count++;
            int e = node_count++;
            
            // Connect edges for zero or more repetitions
            add_edge(s, inner.start, 0);       // Enter R1
            add_edge(s, e, 0);                 // Skip R1 (zero times)
            add_edge(inner.end, inner.start, 0); // Loop back (more times)
            add_edge(inner.end, e, 0);         // Exit R1
            
            NodePair p = {s, e};
            return p;
        } else if (op == '|') {
            // Case: Union (R1|R2)
            NodePair p1 = parse(r, i + 1, split);
            NodePair p2 = parse(r, split + 2, j - 1); // Skip the '|'
            int s = node_count++;
            int e = node_count++;
            
            // Branch to either R1 or R2
            add_edge(s, p1.start, 0);
            add_edge(s, p2.start, 0);
            add_edge(p1.end, e, 0);
            add_edge(p2.end, e, 0);
            
            NodePair p = {s, e};
            return p;
        } else {
            // Case: Concatenation (R1R2)
            // Note: Concatenation has no explicit operator char in some definitions,
            // but the structure implies we just process the two adjacent parts.
            NodePair p1 = parse(r, i + 1, split);
            NodePair p2 = parse(r, split + 1, j - 1);
            
            // Link end of R1 to start of R2 via epsilon
            add_edge(p1.end, p2.start, 0);
            
            NodePair p = {p1.start, p2.end};
            return p;
        }
    }
    
    NodePair empty = {0, 0};
    return empty;
}

// Standard Matrix Multiplication (A = A * B)
void multiply(long long A[MAX_NODES][MAX_NODES], long long B[MAX_NODES][MAX_NODES], int n) {
    long long C[MAX_NODES][MAX_NODES] = {0};
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (A[i][k]) {
                for (int j = 0; j < n; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = C[i][j];
}

// Matrix Exponentiation (A = A^p)
void power(long long A[MAX_NODES][MAX_NODES], int p, int n) {
    long long res[MAX_NODES][MAX_NODES] = {0};
    for (int i = 0; i < n; i++) res[i][i] = 1;
    while (p > 0) {
        if (p & 1) multiply(res, A, n);
        multiply(A, A, n);
        p >>= 1;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = res[i][j];
}

/* -- Main Logic -- */

int countStrings(char* r, int l) {
    // Reset globals for each test case
    node_count = 0;
    edge_count = 0;

    // 1. Build NFA from Regex
    NodePair root = parse(r, 0, strlen(r) - 1);
    int n = node_count;

    // 2. Compute Epsilon Reachability Matrix (E)
    // E[i][j] = 1 if state i can reach state j using only epsilon moves
    long long eps[MAX_NODES][MAX_NODES] = {0};
    
    // Initialize self-loops
    for (int i = 0; i < n; i++) eps[i][i] = 1;
    
    // Add direct epsilon edges
    for (int i = 0; i < edge_count; i++) {
        if (edges[i].type == 0) {
            eps[edges[i].u][edges[i].v] = 1;
        }
    }

    // Floyd-Warshall to compute transitive closure of epsilon moves
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (eps[i][k]) {
                for (int j = 0; j < n; j++) {
                    if (eps[k][j]) eps[i][j] = 1;
                }
            }
        }
    }

    // 3. Compute Character Transition Matrix (C)
    // C[u][v] = count of direct transitions from u to v consuming 'a' or 'b'
    long long C[MAX_NODES][MAX_NODES] = {0};
    for (int i = 0; i < edge_count; i++) {
        if (edges[i].type != 0) {
            C[edges[i].u][edges[i].v]++;
        }
    }

    // 4. Compute Single-Step Transition Matrix (T)
    // T = E * C
    // T[i][j] represents the number of ways to transition from state i to state j
    // by taking any number of epsilon moves followed by EXACTLY one character move.
    long long T[MAX_NODES][MAX_NODES] = {0};
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (eps[i][k]) { // From i, reach k via epsilon
                for (int j = 0; j < n; j++) {
                    if (C[k][j]) { // From k, consume char to reach j
                        T[i][j] = (T[i][j] + C[k][j]) % MOD;
                    }
                }
            }
        }
    }

    // 5. Exponentiate T to find paths of length L
    power(T, l, n);

    // 6. Aggregate Results
    // The total count is the sum of paths from the Start Node (root.start)
    // to any node 'k', such that 'k' can reach the End Node (root.end) via epsilon.
    long long ans = 0;
    for (int k = 0; k < n; k++) {
        // T[root.start][k] gives ways to reach 'k' consuming L characters
        if (T[root.start][k]) {
            // Check if 'k' is a valid accepting state (can reach end via epsilon)
            if (eps[k][root.end]) {
                ans = (ans + T[root.start][k]) % MOD;
            }
        }
    }

    return (int)ans;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        char* r = *(first_multiple_input + 0);

        int l = parse_int(*(first_multiple_input + 1));

        int result = countStrings(r, l);

        fprintf(fptr, "%d\n", result);
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
