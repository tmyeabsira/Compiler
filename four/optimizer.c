#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPRESSIONS 100
#define MAX_CODE_LENGTH 1024  // Maximum length for user input code

typedef struct {
    char expression[50];
    int value;
} CommonSubexpression;

CommonSubexpression commonExpressions[MAX_EXPRESSIONS];
int commonCount = 0;

// Function to evaluate an expression
int evaluate(const char *expression) {
    // Simple evaluation for the sake of example (only handles + and -)
    int result = 0;
    char op = '+';
    int num = 0;

    for (const char *p = expression; *p; p++) {
        if (isdigit(*p)) {
            num = num * 10 + (*p - '0');
        } else if (*p == '+' || *p == '-') {
            if (op == '+') {
                result += num;
            } else if (op == '-') {
                result -= num;
            }
            op = *p;
            num = 0;
        }
    }
    // Final operation
    if (op == '+') {
        result += num;
    } else if (op == '-') {
        result -= num;
    }

    return result;
}

// Function to check for common subexpressions
int findCommonSubexpression(const char *expression) {
    for (int i = 0; i < commonCount; i++) {
        if (strcmp(commonExpressions[i].expression, expression) == 0) {
            return commonExpressions[i].value;
        }
    }
    return -1; // Not found
}

// Function to add a common subexpression
void addCommonSubexpression(const char *expression, int value) {
    if (commonCount < MAX_EXPRESSIONS) {
        strcpy(commonExpressions[commonCount].expression, expression);
        commonExpressions[commonCount].value = value;
        commonCount++;
    }
}

// Function to optimize and generate code
void optimizeAndGenerateCode(char *code) {
    char *line = strtok(code, "\n");
    while (line != NULL) {
        char *trimmedLine = strtok(line, " ");
        if (trimmedLine != NULL && strcmp(trimmedLine, "x") == 0) {
            // Example: x = a + b
            char *expression = strtok(NULL, "=");
            if (expression != NULL) {
                // Remove leading whitespace
                expression += strspn(expression, " ");
                char *result = malloc(50);
                strcpy(result, expression);

                // Check for common subexpression
                int value = findCommonSubexpression(result);
                if (value != -1) {
                    printf("%s = %d; // Common subexpression eliminated\n", trimmedLine, value);
                } else {
                    // Evaluate the expression
                    value = evaluate(result);
                    addCommonSubexpression(result, value);
                    printf("%s = %d; // Evaluated and stored common subexpression\n", trimmedLine, value);
                }
                free(result);  // Free the allocated memory
            }
        }
        line = strtok(NULL, "\n");
    }
}

int main() {
    char code[MAX_CODE_LENGTH];

    printf("Enter the code (end with an empty line):\n");
    // Read multiple lines of input
    int totalLength = 0;
    while (1) {
        fgets(code + totalLength, MAX_CODE_LENGTH - totalLength, stdin);
        if (strcmp(code + totalLength, "\n") == 0) { // Check for empty line
            break;
        }
        totalLength += strlen(code + totalLength);
        if (totalLength >= MAX_CODE_LENGTH - 1) {
            printf("Code is too long! Truncating input.\n");
            break;
        }
    }

    printf("Original Code:\n%s", code);
    printf("Optimized Code:\n");
    optimizeAndGenerateCode(code);
    return 0;
}

