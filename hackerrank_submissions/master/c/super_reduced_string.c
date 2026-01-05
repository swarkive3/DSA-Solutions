/*
 * Contest: Master
 * Challenge: Super Reduced String
 * Language: c
 * Score: 0.0
 */

char* superReducedString(char* s) {
    int len = strlen(s);
    
    // Allocate memory for the result. 
    // In the worst case (no deletions), it will be the same length as s.
    // We add +1 for the null terminator.
    char* stack = (char*)malloc((len + 1) * sizeof(char));
    
    int top = -1; // Represents the index of the last character in our stack

    for (int i = 0; i < len; i++) {
        // If stack is not empty AND top element matches current char
        if (top > -1 && stack[top] == s[i]) {
            top--; // "Pop" the element (remove the pair)
        } else {
            top++; // Move index up
            stack[top] = s[i]; // "Push" current char
        }
    }

    // Check if the resulting string is empty
    if (top == -1) {
        // Depending on the platform's requirements, we might need to free 'stack' 
        // before returning a literal, but strict memory management 
        // is often skipped in simple CP snippets.
        return "Empty String";
    }

    // Null-terminate the string
    stack[top + 1] = '\0';

    return stack;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = superReducedString(s);

    fprintf(fptr, "%s\n", result);

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
