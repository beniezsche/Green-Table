#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


enum OPERATIONS{
    SUM,
    AVG
} ;

typedef enum {
    FUNCTION_START,
    CELL_REFERENCE,
    FUNCTION,
    SYMBOL,
    RANGE_SEPARATOR,
    END_OF_FORMULA
} TokenType;

typedef struct {
    char* value;
    TokenType type;
} Token;

char* getTokenType(int tt) {

    char* token_type;

    switch(tt) {
        case CELL_REFERENCE:
            token_type = "CELL_REFERENCE";
            break;
        case FUNCTION:
            token_type = "FUNCTION";
            break;
        case SYMBOL:
            token_type = "SYMBOL";
            break;
        case RANGE_SEPARATOR:
            token_type = "RANGE_SEPARATOR";
            break;
        case END_OF_FORMULA:
            token_type = "END_OF_FORMULA";
            break;
        default:
            break;
    }

    return token_type;
}

Token* tokenize_visicalc_formula(const char* formula) {
    // List of tokens
    Token* tokens = malloc(sizeof(Token) * 100); // Assuming a maximum of 100 tokens
    int token_count = 0;

    // Tokenization logic
    while (*formula != '\0') {
        if (isalpha(*formula)) {
            // Cell reference or function
            int isCellRef = 0;
            int length = 0;
            while (isalnum(*formula) || *formula == '_') {
                length++;
                formula++;

                if(isdigit(*formula))
                    isCellRef = 1;

                if(length > 0) {

                    if(isdigit(*formula) && isalpha(*(formula + 1)))
                        isCellRef = 0;
                }

            }
            char* identifier = malloc(length + 1);
            strncpy(identifier, formula - length, length);
            identifier[length] = '\0';

            // Check if it's a function or cell reference (for simplicity, assume any alphabetical token is a function)
            tokens[token_count].value = identifier;
            if(!isCellRef)
                tokens[token_count].type = FUNCTION;
            else 
                tokens[token_count].type = CELL_REFERENCE;
        } else if (*formula == '+' || *formula == '-' || *formula == '*' || *formula == '/') {
            // Operator
            tokens[token_count].value = malloc(2);
            tokens[token_count].value[0] = *formula;
            tokens[token_count].value[1] = '\0';
            tokens[token_count].type = SYMBOL;
            formula++;
        } else if (*formula == '.') {
            // Colon (range)

            int length = 0;

            while (*formula == '.') {
                length++;
                formula++;
            }

            if (length == 3) {
                tokens[token_count].value = malloc(4);
                tokens[token_count].value[0] = '.';
                tokens[token_count].value[1] = '.';
                tokens[token_count].value[2] = '.';
                tokens[token_count].value[3] = '\0';
                tokens[token_count].type = RANGE_SEPARATOR;
            }
            else {
                fprintf(stderr, "Invalid character in formula: %c\n", *formula);
                exit(EXIT_FAILURE);
            }

        } else if (*formula == '(' || *formula == ')') {
            // Parentheses (for simplicity, treat them as separate tokens)
            tokens[token_count].value = malloc(2);
            tokens[token_count].value[0] = *formula;
            tokens[token_count].value[1] = '\0';
            tokens[token_count].type = *formula == '(' ? SYMBOL : END_OF_FORMULA;
            formula++;
        } 
        else if(*formula == '@') {
            tokens[token_count].value = malloc(2);
            tokens[token_count].value[0] = *formula;
            tokens[token_count].value[1] = '\0';
            tokens[token_count].type = FUNCTION_START;
            formula++;
            
        } else if (*formula == ' ' || *formula == '\n') {
            // Ignore whitespace
            formula++;
            continue;
        } else {
            // Invalid character
            fprintf(stderr, "Invalid character in formula: %c\n", *formula);
            exit(EXIT_FAILURE);
        }

        token_count++;
    }

    // Add an END_OF_FORMULA token at the end
    tokens[token_count].value = NULL;
    tokens[token_count].type = END_OF_FORMULA;

    return tokens;
}

void free_tokens(Token* tokens) {
    for (int i = 0; tokens[i].value != NULL; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}

void print_tokens(Token* tokens) {
    for (int i = 0; tokens[i].value != NULL; i++) {
        printf("Token %d: Type=%s, Value=%s\n", i + 1, getTokenType(tokens[i].type), tokens[i].value);
    }
}

int validate_tokens(Token* tokens) {
    if( tokens[0].type == FUNCTION_START &&
        tokens[1].type == FUNCTION &&
        tokens[2].type == SYMBOL &&
        tokens[3].type == CELL_REFERENCE &&
        tokens[4].type == RANGE_SEPARATOR &&
        tokens[5].type == CELL_REFERENCE &&
        tokens[6].type == END_OF_FORMULA)
        return 1;
    else 
        return 0;
}

void process_function(char* input) {

    Token* tokens = tokenize_visicalc_formula(input);
    // print_tokens(tokens);

    if (validate_tokens(tokens) == 1)
        printf("\nTokens validated\n");
    else 
        printf("\nTokens not validated! Write the function correctly\n");


    free_tokens(tokens);
}



// int main() {
//     char visicalc_formula[20] ;

//     // scanf("%s" ,visicalc_formula);

//     fgets(visicalc_formula, sizeof(visicalc_formula), stdin);

//     Token* tokens = tokenize_visicalc_formula(visicalc_formula);
//     print_tokens(tokens);

//     if (validate_tokens(tokens) == 1)
//         printf("\nTokens validated\n");
//     else 
//         printf("\nTokens not validated! Write the function correctly\n");


//     free_tokens(tokens);

//     return 0;
// }
