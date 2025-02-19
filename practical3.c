#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IDENTIFIERS 100

// Define keywords
const char *keywords[] = {"int", "char", "return", "void", "long", "float", "struct"};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

// Symbol table for identifiers
char symbol_table[MAX_IDENTIFIERS][50];
int symbol_table_count = 0;

// Function to check if a word is a keyword
int isKeyword(char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to add identifier to symbol table
void addToSymbolTable(char *identifier) {
    for (int i = 0; i < symbol_table_count; i++) {
        if (strcmp(symbol_table[i], identifier) == 0) {
            return;
        }
    }
    strcpy(symbol_table[symbol_table_count++], identifier);
}

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    return (ch == ' ' || ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}');
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>');
}

// Lexical analysis function
void lexicalAnalyzer(char *code) {
    char token[50];
    int tokenIndex = 0;
    
    printf("TOKENS:\n");
    
    for (int i = 0; code[i] != '\0'; i++) {
        if (isalpha(code[i])) {
            token[tokenIndex++] = code[i];
            while (isalnum(code[i + 1])) {
                token[tokenIndex++] = code[++i];
            }
            token[tokenIndex] = '\0';
            if (isKeyword(token)) {
                printf("Keyword: %s\n", token);
            } else {
                printf("Identifier: %s\n", token);
                addToSymbolTable(token);
            }
            tokenIndex = 0;
        } else if (isdigit(code[i])) {
            token[tokenIndex++] = code[i];
            while (isdigit(code[i + 1])) {
                token[tokenIndex++] = code[++i];
            }
            token[tokenIndex] = '\0';
            printf("Constant: %s\n", token);
            tokenIndex = 0;
        } else if (isOperator(code[i])) {
            printf("Operator: %c\n", code[i]);
        } else if (isDelimiter(code[i])) {
            if (code[i] != ' ') {
                printf("Punctuation: %c\n", code[i]);
            }
        } else if (code[i] == '\"') {
            i++;
            while (code[i] != '\"' && code[i] != '\0') {
                token[tokenIndex++] = code[i++];
            }
            token[tokenIndex] = '\0';
            printf("String: \"%s\"\n", token);
            tokenIndex = 0;
        }
    }
    
    printf("\nSYMBOL TABLE:\n");
    for (int i = 0; i < symbol_table_count; i++) {
        printf("%d) %s\n", i + 1, symbol_table[i]);
    }
}

int main() {
    char code[] = "int main() { int a = 5 ,7H; char b = 'x'; return a + b; }";
    lexicalAnalyzer(code);
    return 0;
}
