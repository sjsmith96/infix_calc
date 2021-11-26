#include <stdio.h>
#include <assert.h>
#include "tokenizer.cpp"


/*
  TODO: Implement myself:
        - strtod
        - strlen
        - memmove
        - memcopy
        - malloc
        - free

 */

inline void enqueue(Token **queue, Token value)
{
    buf_push(*queue, value);
}

Token *shunting_yard(Token *tokens)
{    
    Token *output_queue = NULL;
    Token *operator_stack = NULL;
    
    for(int i = 0; i < buf_count(tokens); i++)
    {
        Token current = tokens[i];
        switch(current.type)
        {
            case TOKEN_NUMBER:
            {
                enqueue(&output_queue, current);
                break;
            }
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_STAR:
            case TOKEN_SLASH:
            {
                if(operator_stack != NULL)
                {
                    Token *stack_top = &buf_last(operator_stack);
                    while(OPERATOR(stack_top->type) &&
                          stack_top->type != TOKEN_LEFT_PAREN &&
                          stack_top->type >= current.type)
                    {
                        enqueue(&output_queue, buf_pop(operator_stack));
                        stack_top = &buf_last(operator_stack);
                    }
                }
                buf_push(operator_stack, current);
                break;
            }
            case TOKEN_LEFT_PAREN:
            {
                buf_push(operator_stack, current);
                break;
            }
            case TOKEN_RIGHT_PAREN:
            {
                while(buf_last(operator_stack).type != TOKEN_LEFT_PAREN)
                {
                    assert(buf_count(operator_stack) > 0);
                    enqueue(&output_queue, buf_pop(operator_stack));
                }
                assert(buf_last(operator_stack).type == TOKEN_LEFT_PAREN);
                buf_pop(operator_stack);
            }
        }
    }
    while(buf_count(operator_stack) > 0)
    {
        enqueue(&output_queue, buf_pop(operator_stack));
    }

    buf_free(operator_stack);
    buf_free(tokens);
    return output_queue;
}

int evaluate(char *string) {
    
    Token *tokens = tokenize_string(string);
    tokens = shunting_yard(tokens);

    double *value_stack = NULL;
    for(int i = 0; i < buf_count(tokens); i++)
    {
        Token current = tokens[i];
        switch(current.type)
        {
            case TOKEN_NUMBER:
            {
                buf_push(value_stack, current.value);
                break;
            }
            case TOKEN_PLUS:
            {
                double a = buf_pop(value_stack);
                double b = buf_pop(value_stack);
                double result = b + a;
                buf_push(value_stack, result);
                break;
            }
            case TOKEN_MINUS:
            {
             
                double a = buf_pop(value_stack);
                double b = buf_pop(value_stack);
                double result = b - a;
                buf_push(value_stack, result);
                break;
            }
            case TOKEN_STAR:
            {
             
                double a = buf_pop(value_stack);
                double b = buf_pop(value_stack);
                double result = b * a;
                buf_push(value_stack, result);
                break;
            }
            case TOKEN_SLASH:
            {
             
                double a = buf_pop(value_stack);
                double b = buf_pop(value_stack);
                double result = b * a;
                buf_push(value_stack, result);
                break;
            }
        }
        
    }

    buf_free(tokens);
	return (int) buf_pop(value_stack);
}

int main(int argc, char **argv) {
    
    char *expression = NULL;
    if(argc > 1)
    {
        expression = argv[1];
    }
    else
    {
        printf("Did not enter an expression!\n");
        exit(1);
    }
	int solution = evaluate(expression);
	printf("Solution: %d\n", solution);
	return 0;
}
