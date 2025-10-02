#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct
{
    int num_lines;
    int num_el;
    int num_com;
    char* el_array;
    char* com_array;
    char** line_array;
} parametrs;

typedef enum
{
    SUCCESS = 0,
    ERR_ALLOCATION = 1,
    ERR_OPEN_READ_FILE = 2,
    ERR_FREAD = 3,
    ERR_LINE_ARR_FILL = 4,
    ERR_INVAID_SCAN_SYM = 5,
    ERR_OPEN_WRITE_FILE = 6
}error_t;

#define RETURN_IF_ERR(status) do \
{\
    error_t _status_val_ = status;\
    if (_status_val_)\
    {\
        fprintf(stderr, "%s in %s: %d func:%s\n", error_code_to_string (_status_val_), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        return _status_val_;\
    }\
} while (0)

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

error_t allocation_el_arr (parametrs* data, const char* title);
error_t allocation_line_com_arr (parametrs* data);
error_t read_commands (parametrs* data, const char* title);
error_t count_n_lines (parametrs* data);
error_t filling_line_array (parametrs* data);
error_t transator (parametrs* data);
error_t write_commands (parametrs* data, const char* title);
const char* error_code_to_string (error_t status);
error_t destroy_arrays (parametrs* data);

#endif