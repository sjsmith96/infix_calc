#include "tokenizer.h"

Token get_next_token(Tokenizer *tokenizer)
{
    Token result = {};
    
    if(is_num(*tokenizer->current))
    {
        while(is_num(*tokenizer->current))
        {
            tokenizer->current++;
        }
        result.type = TOKEN_NUMBER;
        result.value = strtod(tokenizer->start, &tokenizer->current);
    }
    else if(*tokenizer->current == '(')
    {
        result.type = TOKEN_LEFT_PAREN;
        tokenizer->current++;
    }
    else if(*tokenizer->current == ')')
    {
        result.type = TOKEN_RIGHT_PAREN;
        tokenizer->current++;
    }
    else if(*tokenizer->current == '+')
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

