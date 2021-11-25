#if !defined(TOKENIZER_H)

#define TOKENIZER_H

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

#define OPERATOR(t)     (((t) >= TOKEN_PLUS && (t) <= TOKEN_SLASH) ? 1 : 0) 

struct Token
{
    TokenType type;
    char *lexeme;

    double value;
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

#endif
