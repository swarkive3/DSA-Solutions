/*
 * Contest: Master
 * Challenge: Kruskal (MST): Really Special Subtree
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

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

// 1. Define a structure to represent an edge
typedef struct {
    int u, v, w;
} Edge;

// 2. Comparator function for qsort
// Primary Sort Key: Weight (ascending)
// Secondary Sort Key: Sum of u + v + w (ascending) as per problem rules
int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;

    if (e1->w != e2->w) {
        return e1->w - e2->w;
    }
    
    // Tie-breaker rule from problem description
    int sum1 = e1->u + e1->v + e1->w;
    int sum2 = e2->u + e2->v + e2->w;
    return sum1 - sum2;
}

// 3. Find Function for Disjoint Set Union (DSU) with Path Compression
int find_set(int i, int* parent) {
    if (i == parent[i])
        return i;
    // Path compression: Point directly to the root
    return parent[i] = find_set(parent[i], parent);
}

// 4. Union Function for DSU
void union_sets(int i, int j, int* parent) {
    int root_i = find_set(i, parent);
    int root_j = find_set(j, parent);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int kruskals(int g_nodes, int g_edges, int* g_from, int* g_to, int* g_weight) {
    // A. Convert input arrays into a unified array of Edge structs
    Edge* edges = malloc(g_edges * sizeof(Edge));
    for (int i = 0; i < g_edges; i++) {
        edges[i].u = g_from[i];
        edges[i].v = g_to[i];
        edges[i].w = g_weight[i];
    }

    // B. Sort the edges based on weight and the tie-breaker rule
    qsort(edges, g_edges, sizeof(Edge), compareEdges);

    // C. Initialize the DSU 'parent' array
    // We use 1-based indexing as per constraints (nodes are 1 to g_nodes)
    int* parent = malloc((g_nodes + 1) * sizeof(int));
    for (int i = 1; i <= g_nodes; i++) {
        parent[i] = i;
    }

    int mst_weight = 0;
    
    // D. Iterate through sorted edges and build the MST
    for (int i = 0; i < g_edges; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        // Find the roots of the sets that u and v belong to
        int root_u = find_set(u, parent);
        int root_v = find_set(v, parent);

        // If they are in different sets, adding this edge won't form a cycle
        if (root_u != root_v) {
            mst_weight += w;          // Add weight to total
            union_sets(root_u, root_v, parent); // Merge the sets
        }
    }

    // E. Cleanup and Return
    free(edges);
    free(parent);
    
    return mst_weight;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** g_nodes_edges = split_string(rtrim(readline()));

    int g_nodes = parse_int(*(g_nodes_edges + 0));
    int g_edges = parse_int(*(g_nodes_edges + 1));

    int* g_from = malloc(g_edges * sizeof(int));
    int* g_to = malloc(g_edges * sizeof(int));
    int* g_weight = malloc(g_edges * sizeof(int));

    for (int i = 0; i < g_edges; i++) {
        char** g_from_to_weight = split_string(ltrim(readline()));

        int g_from_temp = parse_int(*(g_from_to_weight + 0));
        int g_to_temp = parse_int(*(g_from_to_weight + 1));
        int g_weight_temp = parse_int(*(g_from_to_weight + 2));

        *(g_from + i) = g_from_temp;
        *(g_to + i) = g_to_temp;
        *(g_weight + i) = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_edges, g_from, g_to, g_weight);

    // Write your code here.

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
