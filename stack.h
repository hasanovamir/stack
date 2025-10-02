#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define POIZON 0x11223344
#define KANAREIKA 0x55667788

typedef int stack_val_t;

typedef enum
{
    PUSH = 1,
    OUT = 2,
    ADD = 3,
    SUB = 4,
    DIV = 5,
    MUL = 6,
    HLT = 7,
    sqvRT = 8
} operation_t;

typedef enum
{
    finish_scan = 8,
    no_el_to_pop = 7,
    scan_num_err = 6,
    scan_oper_err = 5,
    data_ruined = 4,
    allocete_err = 3,
    invalid_value = 2,
    success = 0
} stack_err_t;

typedef struct
{
    stack_val_t* data;
    int size;
    int capasity;
} stack_t;

typedef struct
{
    stack_val_t value;
    operation_t operation;
} operation_params;

stack_err_t stack_init (stack_t* stk, int user_size);
stack_err_t stack_push (stack_t* stk, stack_val_t value);
stack_err_t stack_pop (stack_t* stk, stack_val_t* val_pointer);
stack_err_t stack_destroy (stack_t* stk);
const char* error_code_to_string (stack_err_t status);
void stack_dump (stack_t* stk);
stack_err_t stack_verify (stack_t* stk);
stack_err_t scan_input_operation (operation_params* parametrs);
stack_err_t processing_scaned_oper (operation_params* parametrs, stack_t* stk);
stack_err_t scan_and_pocessing (stack_t* stk);
stack_err_t stack_fill (stack_t* stk, int array_size);



#ifndef N_DEBUG
#define DEBUG_ASSERT(cond)\
if (!cond)\
{\
    fprintf(stderr, "%s in %s: %d func:%s\n", #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    exit(1);\
}
#else
#define DEBUG_ASSERT() 
#endif



#define RETURN_IF_ERR(status) do \
{\
    stack_err_t _status_val_ = status;\
    if (_status_val_)\
    {\
        fprintf(stderr, "%s in %s: %d func:%s\n", error_code_to_string (_status_val_), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        return _status_val_;\
    }\
} while (0)



#define STACK_OK(stack) do\
{\
    stack_err_t _status_ = stack_verify (stack);\
    if (_status_)\
    {\
        printf ("StackDump colled from %s: %d\n", __FILE__, __LINE__);\
        stack_dump (stack);\
        return _status_;\
    }\
}while (0);



#endif