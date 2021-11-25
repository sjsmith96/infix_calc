#include <stdio.h>

#include "tokenizer.cpp"


/*
  TODO: Implement myself:
        - strtod
        - strlen
        - memmove
        - memcopy
        - malloc
        - free

  Stack implementation
 */

#define MAX_STACK 256

struct OperatorStack
{
    Token stack[MAX_STACK];
    Token *stack_top;
};


struct ValueStack
{
    double stack[MAX_STACK];
    double *stack_top;
};


inline void enqueue(Token **queue, Token value)
{
    buf_push(*queue, value);
}

inline Token dequeue(Token **queue)
{
    Token value = *queue[0];
    memmove(queue, &queue[1], sizeof(queue[0]));
    buf_count_raw(queue)--;
    return value;
}

inline Token pop_op(OperatorStack *stack)
{
    stack->stack_top--;
    return *stack->stack_top;
}

inline void push_op(OperatorStack *stack, Token value)
{
    *stack->stack_top = value;
    stack->stack_top++;
}


inline double pop_val(ValueStack *stack)
{
    stack->stack_top--;
    return *stack->stack_top;
}

inline void push_val(ValueStack *stack, double value)
{
    *stack->stack_top = value;
    stack->stack_top++;
}


void init_operator_stack(OperatorStack *stack)
{
    stack->stack_top = stack->stack;
}

void init_value_stack(ValueStack *stack)
{
    stack->stack_top = stack->stack;
}


Token *shunting_yard(Token *tokens)
{    
    Token *output_queue = NULL;
    OperatorStack operator_stack = {};
    init_operator_stack(&operator_stack);
    
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
                Token *stack_top = operator_stack.stack_top;
                while(stack_top &&
                      OPERATOR(stack_top->type) &&
                      stack_top->type > current.type)
                {
                    enqueue(&output_queue, pop_op(&operator_stack));
                }
                push_op(&operator_stack, current);
                break;
            }
        }
    }
    while(operator_stack.stack_top > operator_stack.stack)
    {
        enqueue(&output_queue, pop_op(&operator_stack));
    }

    return output_queue;
}

int evaluate(char *string) {
    
    Token *tokens = tokenize_string(string);
    tokens = shunting_yard(tokens);

    ValueStack value_stack = {};
    init_value_stack(&value_stack);
    for(int i = 0; i < buf_count(tokens); i++)
    {
        Token current = tokens[i];
        switch(current.type)
        {
            case TOKEN_NUMBER:
            {
                push_val(&value_stack, current.value);
                break;
            }
            case TOKEN_PLUS:
            {
                double a = pop_val(&value_stack);
                double b = pop_val(&value_stack);
                double result = a + b;
                push_val(&value_stack, result);
                break;
            }
            case TOKEN_MINUS:
            {
                break;
            }
            case TOKEN_STAR:
            {
                break;
            }
            case TOKEN_SLASH:
            {
                break;
            }
        }
        
    }

	return (int) pop_val(&value_stack);
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
