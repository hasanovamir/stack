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
    no_el_to_pop = 7,
    scan_num_err = 6,
    scan_oper_err = 5,
    data_ruined = 4,
    allocete_err = 3,
    invalid_value = 2,
    data_trans_err = 1,
    cor_func_oper = 0,
    end_scan = 1
} StackErr_t;

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

StackErr_t StackInit (stack_t* stk, int value);
StackErr_t StackPush (stack_t* stk, stack_val_t value);
StackErr_t StackPop (stack_t* stk, stack_val_t* val_pointer);
StackErr_t StackDestroy (stack_t* stk);
const char* error_code_to_string (StackErr_t status);
void StackDump (stack_t* stk);
StackErr_t verify (stack_t* stk);
StackErr_t scan_input_operation (operation_params* parametrs);
StackErr_t processing_scaned_oper (operation_params* parametrs, stack_t* stk);
StackErr_t scan_and_pocessing (stack_t* stk);
StackErr_t downsize_array (stack_t* stk);
StackErr_t upsize_array (stack_t* stk);
StackErr_t allocete_array (stack_t* stk, int value, int* array_size);
StackErr_t filling_stack (stack_t* stk, int array_size);

#endif

