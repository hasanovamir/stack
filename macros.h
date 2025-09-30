#ifndef MACROS
#define MACROS

#ifndef N_DEBUG
#define ASSERT(cond)\
if (!cond)\
{\
    fprintf(stderr, "%s in %s: line :%d func:%s\n", #cond, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
    exit(1);\
}
#else
#define ASSERT() 
#endif



#define RETURN_IF_ERR(status) do \
{\
    StackErr_t _status_val_ = status;\
    if (_status_val_)\
    {\
        fprintf(stderr, "%s in %s: line: %d func:%s\n", error_code_to_string (_status_val_), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        return _status_val_;\
    }\
} while (0)



#define STACK_OK(stack) do\
{\
    StackErr_t _status_ = verify (stack);\
    if (_status_)\
    {\
        printf ("StackDump colled from %s: %d\n", __FILE__, __LINE__);\
        StackDump (stack);\
        return _status_;\
    }\
}while (0);

#endif