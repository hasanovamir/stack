#include "stack.h"
#include "macros.h"

int main (void)
{
    stack_t stk = {};

    RETURN_IF_ERR (StackInit (&stk, 10));
    RETURN_IF_ERR (scan_and_pocessing (&stk));

    return 0;
}