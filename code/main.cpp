#include <stdio.h>
#include <string.h>

#include "sb.h"

typedef int bool32;

enum TokenType
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
};

struct Token
{
    TokenType type;
    char *lexeme;
};

struct Tokenizer
{
    char *current;
    char *start;
};

inline bool32 is_num(char c)
{
    if(c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}

inline bool32 is_white_space(char c)
{
    if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
    {
        return true;
    }
    return false;
}

inline void eat_white_space(Tokenizer *tokenizer)
{
    while(is_white_space(*tokenizer->current))
    {
        tokenizer->current++;
    }
}

Token get_next_token(Tokenizer *tokenizer)
{
    Token result = {};

    if(*tokenizer->current == '+')
    {
        result.type = TOKEN_PLUS;
        tokenizer->current++;
    }
    else if(*tokenizer->current == '-')
    {
        result.type = TOKEN_MINUS;
        tokenizer->current++;
    }
    else if(*tokenizer->current == '*')
    {
        result.type = TOKEN_STAR;
        tokenizer->current++;
    }
    else if(*tokenizer->current == '/')
    {
        result.type = TOKEN_SLASH;
        tokenizer->current++;
    }
    else if(is_num(*tokenizer->current))
    {
        while(is_num(*tokenizer->current))
        {
            tokenizer->current++;
        }
        result.type = TOKEN_NUMBER;
    }

    size_t len = tokenizer->current - tokenizer->start;
    char *lexeme = (char *) malloc(len + 1);
    memcpy(lexeme, tokenizer->start, len);
    lexeme[len] = '\0';
    result.lexeme = lexeme;

    return result;
}

Token *tokenize_string(char *string)
{
    Token *tokens = NULL;
    Tokenizer tokenizer = {};
    tokenizer.start = string;
    tokenizer.current = tokenizer.start;
    
    while(*tokenizer.current != '\0')
    {
        Token nextToken = get_next_token(&tokenizer);
        buf_push(tokens, nextToken);
        eat_white_space(&tokenizer);
        tokenizer.start = tokenizer.current;
    }

    return tokens;
}

int evaluate(char *string) {
    Token *tokens = tokenize_string(string);
	return 0;
}

int main(int argc, char **argv) {
	char *test = "3 + 4";
	int solution = evaluate(test);
	printf("Hello, World!");
	return 0;
}
