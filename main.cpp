#include "stack.h"

int main (void)
{
    stack_t stk = {};

    RETURN_IF_ERR (stack_init (&stk, 10));
    RETURN_IF_ERR (scan_and_pocessing (&stk));
    RETURN_IF_ERR (stack_destroy (&stk));

    return 0;
}