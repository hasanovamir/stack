#include "stack.h"

stack_err_t scan_and_pocessing (stack_t* stk)
{
    STACK_OK (stk);

    operation_params parametrs = {};

    while (1)
    {
        RETURN_IF_ERR (scan_input_operation (&parametrs));

        stack_err_t status = processing_scaned_oper (&parametrs, stk);

        if (status == finish_scan)
            return success;
        else
            RETURN_IF_ERR (status);
    }
}


stack_err_t scan_input_operation (operation_params* parametrs)
{
    DEBUG_ASSERT (parametrs != NULL);

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

    return success;
}


stack_err_t processing_scaned_oper (operation_params* parametrs, stack_t* stk)
{
    DEBUG_ASSERT (parametrs != NULL);
    STACK_OK (stk);

    stack_val_t a = 0;
    stack_val_t b = 0;

    switch (parametrs->operation)
    {
        case PUSH:
            RETURN_IF_ERR (stack_push (stk, parametrs->value));
            break;
        case OUT:
            RETURN_IF_ERR (stack_pop (stk, &a));
            printf ("%d\n", a);
            break;
        case ADD:
            RETURN_IF_ERR (stack_pop (stk, &a));
            RETURN_IF_ERR (stack_pop (stk, &b));
            RETURN_IF_ERR (stack_push (stk, a + b));
            break;
        case SUB:
            RETURN_IF_ERR (stack_pop (stk, &a));
            RETURN_IF_ERR (stack_pop (stk, &b));
            RETURN_IF_ERR (stack_push (stk, b - a));
            break;
        case DIV:
            RETURN_IF_ERR (stack_pop (stk, &a));
            RETURN_IF_ERR (stack_pop (stk, &b));
            RETURN_IF_ERR (stack_push (stk, b / a));
            break;
        case MUL:
            RETURN_IF_ERR (stack_pop (stk, &a));
            RETURN_IF_ERR (stack_pop (stk, &b));
            RETURN_IF_ERR (stack_push (stk, a * b));
            break;
        case HLT:
            return finish_scan;
            break;
        case sqvRT:
            RETURN_IF_ERR (stack_pop (stk, &a));
            RETURN_IF_ERR (stack_push (stk, (stack_val_t)sqrt (a)));
            break;
        default:
            return scan_oper_err;
    }

    return success;
}