#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Token types
typedef enum {
    KEYWORD,
    OPERATOR,
    LITERAL,
    IDENTIFIER,
    SYMBOL,
    END_OF_INPUT,
    INVALID
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char *value;
} Token;

// Function to tokenize input
Token getNextToken(char **input) {
    while (isspace(**input)) {
        (*input)++;
    }

    if (**input == '\0') {
        return (Token){.type = END_OF_INPUT, .value = NULL};
    }

    // Check for keywords ("int")
    if (isalpha(**input)) {
        char *start = *input;
        while (isalnum(**input)) {
            (*input)++;
        }

        return (Token){.type = KEYWORD, .value = strndup(start, *input - start)};
    }

    // Check for operators ("+", "*", "=")
    if (**input == '+' || **input == '*' || **input == '=') {
        char *operator = malloc(2);
        operator[0] = **input;
        operator[1] = '\0';
        (*input)++;
        return (Token){.type = OPERATOR, .value = operator};
    }

    // Check for literals (numbers)
    if (isdigit(**input)) {
        char *start = *input;
        while (isdigit(**input)) {
            (*input)++;
        }

        return (Token){.type = LITERAL, .value = strndup(start, *input - start)};
    }

    // Check for identifiers
    if (isalnum(**input) || **input == '_') {
        char *start = *input;
        while (isalnum(**input) || **input == '_') {
            (*input)++;
        }

        return (Token){.type = IDENTIFIER, .value = strndup(start, *input - start)};
    }

    // Check for symbols (";", "{", "}")
    char *symbol = malloc(2);
    symbol[0] = **input;
    symbol[1] = '\0';
    (*input)++;
    return (Token){.type = SYMBOL, .value = symbol};
}

// Function to free memory allocated for tokens
void freeToken(Token *token) {
    if (token->value != NULL) {
        free(token->value);
    }
}

int main() {
    char input[] = "@SUM(A1...A3)";
    char *inputPtr = input;

    Token token;
    do {
        token = getNextToken(&inputPtr);

        // Process or print the token
        switch (token.type) {
            case KEYWORD:
                printf("Keyword: %s\n", token.value);
                break;
            case OPERATOR:
                printf("Operator: %s\n", token.value);
                break;
            case LITERAL:
                printf("Literal: %s\n", token.value);
                break;
            case IDENTIFIER:
                printf("Identifier: %s\n", token.value);
                break;
            case SYMBOL:
                printf("Symbol: %s\n", token.value);
                break;
            case END_OF_INPUT:
                printf("End of input\n");
                break;
            case INVALID:
                printf("Invalid token\n");
                break;
        }

        // Free memory allocated for the token
        freeToken(&token);

    } while (token.type != END_OF_INPUT);

    return 0;
}