#ifndef STACK_H
#define STACK_H

//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

//--------------------------------------------------------------------------------

#define POIZON    0x11223344
#define KANAREIKA 0x55667788

//--------------------------------------------------------------------------------

const int array_min_size = 64;

typedef int stack_val_t;

//--------------------------------------------------------------------------------

typedef enum
{
    STACK_SUCCESS        = 0,
    STACK_NO_EL_TO_POP   = 2,
    STACK_DATA_RUINED    = 3,
    STACK_ALLOCATION_ERR = 4,
    STACK_INVALID_VALUE  = 5,
} stack_err_t;

//--------------------------------------------------------------------------------

struct stack_t
{
    stack_val_t* data;
    int size;
    int capacity; // spellchecker
};

//--------------------------------------------------------------------------------

stack_err_t stack_init             (stack_t* stk, int init_size           );
stack_err_t stack_push             (stack_t* stk, stack_val_t value       );
stack_err_t stack_pop              (stack_t* stk, stack_val_t* val_pointer);
stack_err_t stack_destroy          (stack_t* stk                          );
const char* error_code_to_string   (stack_err_t status                    );
void        stack_dump             (stack_t* stk                          );
stack_err_t stack_verify           (stack_t* stk                          );
stack_err_t stack_fill             (stack_t* stk                          );
stack_err_t upsize_array_if_need   (stack_t* stk                          );
stack_err_t downsize_array_if_need (stack_t* stk                          );

//--------------------------------------------------------------------------------

#ifndef N_DEBUG
#define DEBUG_ASSERT(cond)\
if (!cond)\
{\
    fprintf(stderr, "%s in %s:%d func:%s\n", #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    exit(1);\
}
#else
#define DEBUG_ASSERT() 
#endif //N_DEBUG

//--------------------------------------------------------------------------------

#define RETURN_IF_ERR(status) do \
{\
    stack_err_t _status_val_ = status;\
    if (_status_val_)\
    {\
        fprintf(stderr, "%s in %s:%d func:%s\n", error_code_to_string (_status_val_), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        return _status_val_;\
    }\
} while (0)

//--------------------------------------------------------------------------------

#define STACK_OK(stack) do\
{\
    stack_err_t _status_ = stack_verify (stack);\
    if (_status_)\
    {\
        printf ("StackDump called from %s:%d\n", __FILE__, __LINE__);\
        stack_dump (stack);\
        return _status_;\
    }\
}while (0);

//--------------------------------------------------------------------------------

#define ERRCASE(enum)\
    case enum:\
        return #enum;\

//--------------------------------------------------------------------------------

#endif // STACK_H