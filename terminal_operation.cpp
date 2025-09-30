#include "stack.h"
#include "macros.h"

StackErr_t scan_and_pocessing (stack_t* stk)
{
    STACK_OK (stk);

    operation_params parametrs = {};

    while (1)
    {
        RETURN_IF_ERR (scan_input_operation (&parametrs));

        RETURN_IF_ERR (processing_scaned_oper (&parametrs, stk));
    }
}


StackErr_t scan_input_operation (operation_params* parametrs)
{
    ASSERT (parametrs != NULL);

    char tmp[6] = "";
    if (scanf ("%s", tmp) == 0)
        return scan_oper_err;

    if (strcmp (tmp, "PUSH") == 0)
    {
        parametrs->operation = PUSH;
        if (scanf ("%d", &(parametrs->value)) == 0)// че с %d делать
            return scan_num_err;
    }
    else if (strcmp (tmp, "OUT") == 0)
        parametrs->operation = OUT;
    else if (strcmp (tmp, "ADD") == 0)
        parametrs->operation = ADD;
    else if (strcmp (tmp, "SUB") == 0)
        parametrs->operation = SUB;
    else if (strcmp (tmp, "DIV") == 0)
        parametrs->operation = DIV;
    else if (strcmp (tmp, "MUL") == 0)
        parametrs->operation = MUL;
    else if (strcmp (tmp, "HLT") == 0)
        parametrs->operation = HLT;
    else if (strcmp (tmp, "sqvRT") == 0)
        parametrs->operation = sqvRT;
    else
        return scan_oper_err;

    return cor_func_oper;
}


StackErr_t processing_scaned_oper (operation_params* parametrs, stack_t* stk)
{
    ASSERT (parametrs != NULL);
    STACK_OK (stk);

    stack_val_t a = 0;
    stack_val_t b = 0;

    switch (parametrs->operation)
    {
        case PUSH:
            RETURN_IF_ERR (StackPush (stk, parametrs->value));
            break;
        case OUT:
            RETURN_IF_ERR (StackPop (stk, &a));
            printf ("%d\n", a);
            break;
        case ADD:
            RETURN_IF_ERR (StackPop (stk, &a));
            RETURN_IF_ERR (StackPop (stk, &b));
            RETURN_IF_ERR (StackPush (stk, a + b));
            break;
        case SUB:
            RETURN_IF_ERR (StackPop (stk, &a));
            RETURN_IF_ERR (StackPop (stk, &b));
            RETURN_IF_ERR (StackPush (stk, b - a));
            break;
        case DIV:
            RETURN_IF_ERR (StackPop (stk, &a));
            RETURN_IF_ERR (StackPop (stk, &b));
            RETURN_IF_ERR (StackPush (stk, b / a));
            break;
        case MUL:
            RETURN_IF_ERR (StackPop (stk, &a));
            RETURN_IF_ERR (StackPop (stk, &b));
            RETURN_IF_ERR (StackPush (stk, a * b));
            break;
        case HLT:
            RETURN_IF_ERR (StackDestroy (stk));
            exit (1);//X3
            break;
        case sqvRT:
            RETURN_IF_ERR (StackPop (stk, &a));
            RETURN_IF_ERR (StackPush (stk, (stack_val_t)sqrt (a)));
            break;
        default:
            return scan_oper_err;
    }

    return cor_func_oper;
}