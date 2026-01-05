/*
 * Contest: Master
 * Challenge: Build a Palindrome
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

#define MAXLEN 100005

struct State {
    int len, link;
    int next[26];
} st[MAXLEN * 2];

int sz, last;

void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    for(int i=0; i<26; i++) st[0].next[i] = -1;
    sz = 1;
    last = 0;
}

void sam_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    for(int i=0; i<26; i++) st[cur].next[i] = -1;
    
    int p = last;
    int code = c - 'a';
    while (p != -1 && st[p].next[code] == -1) {
        st[p].next[code] = cur;
        p = st[p].link;
    }
    
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[code];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next[0] = -1; 
            for(int i=0; i<26; i++) st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[code] == q) {
                st[p].next[code] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

char* buildPalindrome(char* a, char* b) {
    sam_init();
    int len_a = strlen(a);
    for (int i = 0; i < len_a; i++) {
        sam_extend(a[i]);
    }

    int len_b = strlen(b);
    char *b_rev = malloc((len_b + 1) * sizeof(char));
    for(int i=0; i<len_b; i++) {
        b_rev[i] = b[len_b - 1 - i];
    }
    b_rev[len_b] = '\0';

    int v = 0;
    int l = 0;
    
    char *final_res = malloc((len_a + len_b + 5) * sizeof(char));
    final_res[0] = '\0'; 
    int final_len = 0;

    for (int i = 0; i < len_b; i++) {
        int c = b_rev[i] - 'a';
        
        while (v != 0 && st[v].next[c] == -1) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next[c] != -1) {
            v = st[v].next[c];
            l++;
        }
        
        if (l > 0) {
            int cand_len_even = l * 2;
            int cand_len_odd_a = 0; 
            int cand_len_odd_b = 0; 
            char center_a = 0;
            char center_b = 0;

            for(int k=0; k<26; k++) {
                if(st[v].next[k] != -1) {
                    cand_len_odd_a = l * 2 + 1;
                    center_a = (char)('a' + k);
                    break; 
                }
            }

            if (i + 1 < len_b) {
                cand_len_odd_b = l * 2 + 1;
                center_b = b_rev[i+1];
            }

            int best_local_len = cand_len_even;
            if(cand_len_odd_a > best_local_len) best_local_len = cand_len_odd_a;
            if(cand_len_odd_b > best_local_len) best_local_len = cand_len_odd_b;

            if (best_local_len > final_len || (best_local_len == final_len && final_len > 0)) {
                
                char *temp = malloc((best_local_len + 1) * sizeof(char));
                
                if (cand_len_odd_a == best_local_len) {
                    strncpy(temp, b_rev + (i - l + 1), l);
                    temp[l] = center_a;
                    for(int k=0; k<l; k++) temp[l + 1 + k] = temp[l - 1 - k];
                    temp[best_local_len] = '\0';
                } else if (cand_len_odd_b == best_local_len) {
                    strncpy(temp, b_rev + (i - l + 1), l);
                    temp[l] = center_b;
                    for(int k=0; k<l; k++) temp[l + 1 + k] = temp[l - 1 - k];
                    temp[best_local_len] = '\0';
                } else {
                    strncpy(temp, b_rev + (i - l + 1), l);
                    for(int k=0; k<l; k++) temp[l + k] = temp[l - 1 - k];
                    temp[best_local_len] = '\0';
                }
                
                int update = 0;
                if (best_local_len > final_len) {
                    update = 1;
                } else {
                     if (strcmp(temp, final_res) < 0) update = 1;
                }

                if (update) {
                    final_len = best_local_len;
                    strcpy(final_res, temp);
                }
                free(temp);
            }
        }
    }
    
    free(b_rev);

    if (final_len == 0) {
        strcpy(final_res, "-1");
    }

    return final_res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char* a = readline();

        char* b = readline();

        char* result = buildPalindrome(a, b);

        fprintf(fptr, "%s\n", result);
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
