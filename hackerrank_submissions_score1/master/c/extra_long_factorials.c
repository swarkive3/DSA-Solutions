/*
 * Contest: Master
 * Challenge: Extra Long Factorials
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

int parse_int(char*);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

void extraLongFactorials(int n) {
    // 1. Define storage for the Big Integer.
    // 100! has 158 digits. An array of size 200 is sufficient.
    // We store digits in reverse order: index 0 is the ones place.
    int digits[500];
    int len = 1;

    // 2. Initialize the number to 1 (representing 0! or 1!)
    digits[0] = 1;

    // 3. Iterate from 2 up to n to compute the factorial
    for (int i = 2; i <= n; i++) {
        int carry = 0;

        // Multiply the current Big Int by the scalar i
        for (int j = 0; j < len; j++) {
            // Standard multiplication: digit * number + carry
            int product = digits[j] * i + carry;

            // Update the current digit (keep only the last digit of the product)
            digits[j] = product % 10;

            // Calculate the new carry
            carry = product / 10;
        }

        // 4. Handle remaining carry
        // If there is still a carry after the last digit, add new digits
        while (carry > 0) {
            digits[len] = carry % 10;
            carry = carry / 10;
            len++;
        }
    }

    // 5. Print the result
    // Since we stored digits in reverse order, print from len-1 down to 0.
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", digits[i]);
    }
    printf("\n");
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    extraLongFactorials(n);

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
