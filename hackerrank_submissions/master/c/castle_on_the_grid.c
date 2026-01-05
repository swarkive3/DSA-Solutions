/*
 * Contest: Master
 * Challenge: Castle on the Grid
 * Language: c
 * Score: 1.0
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
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 * 1. STRING_ARRAY grid
 * 2. INTEGER startX
 * 3. INTEGER startY
 * 4. INTEGER goalX
 * 5. INTEGER goalY
 */

typedef struct {
    int r;
    int c;
} Point;

int minimumMoves(int grid_count, char** grid, int startX, int startY, int goalX, int goalY) {
    int n = grid_count;
    
    // Allocate memory for the distance array and initialize to -1
    // Flattened 2D array logic: index = r * n + c
    int* dist = malloc(sizeof(int) * n * n);
    for (int i = 0; i < n * n; i++) {
        dist[i] = -1;
    }

    // Allocate memory for the queue (max size needed is n*n)
    Point* queue = malloc(sizeof(Point) * (n * n + 1));
    int head = 0;
    int tail = 0;

    // Push starting position
    dist[startX * n + startY] = 0;
    queue[tail++] = (Point){startX, startY};

    // Directions: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (head < tail) {
        Point cur = queue[head++];
        int current_dist = dist[cur.r * n + cur.c];

        // Check if we reached the goal
        if (cur.r == goalX && cur.c == goalY) {
            free(dist);
            free(queue);
            return current_dist;
        }

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            // Slide in the current direction until blocked
            for (int k = 1; k < n; k++) {
                int nr = cur.r + dr[i] * k;
                int nc = cur.c + dc[i] * k;

                // 1. Check bounds
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                    break;
                }

                // 2. Check for obstacle
                if (grid[nr][nc] == 'X') {
                    break;
                }

                int neighbor_idx = nr * n + nc;

                // 3. Process the cell
                if (dist[neighbor_idx] == -1) {
                    // Unvisited: Mark distance and enqueue
                    dist[neighbor_idx] = current_dist + 1;
                    queue[tail++] = (Point){nr, nc};
                } else if (dist[neighbor_idx] < current_dist + 1) {
                    // Optimization: If we hit a cell visited by a shorter path, 
                    // we can stop sliding. The path extending from here was 
                    // already covered more efficiently.
                    break;
                }
                // If dist == current_dist + 1, we continue sliding to find 
                // new unvisited cells further down the line, but we don't enqueue.
            }
        }
    }

    free(dist);
    free(queue);
    return -1; // Should not be reached given constraints
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** grid = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    char** first_multiple_input = split_string(rtrim(readline()));

    int startX = parse_int(*(first_multiple_input + 0));

    int startY = parse_int(*(first_multiple_input + 1));

    int goalX = parse_int(*(first_multiple_input + 2));

    int goalY = parse_int(*(first_multiple_input + 3));

    int result = minimumMoves(n, grid, startX, startY, goalX, goalY);

    fprintf(fptr, "%d\n", result);

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
