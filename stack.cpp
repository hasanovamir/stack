#include "stack.h"
#include "macros.h"


StackErr_t StackInit (stack_t* stk, int value)
{
    ASSERT (stk != NULL);
    
    int array_size = 0;
    RETURN_IF_ERR (allocete_array (stk, value, &array_size));
    RETURN_IF_ERR (filling_stack (stk, array_size));

    STACK_OK (stk);

    return cor_func_oper;
}


StackErr_t StackPush (stack_t* stk, stack_val_t value)
{
    STACK_OK (stk);

    RETURN_IF_ERR (upsize_array (stk));
    RETURN_IF_ERR (downsize_array (stk));  

    stk->data[++stk->size] = value;

    return cor_func_oper;
}


StackErr_t StackPop (stack_t* stk, stack_val_t* val_pointer)
{
    STACK_OK (stk);
    if (stk->size == 0)
        return no_el_to_pop;

    *val_pointer = stk->data[stk->size];
    stk->data[stk->size--] = POIZON;

    return cor_func_oper;
}


StackErr_t StackDestroy (stack_t* stk)
{
    STACK_OK (stk);

    free (stk->data);

    return cor_func_oper;
}


const char* error_code_to_string (StackErr_t status)
{
    switch (status)
    {
        case data_ruined:
            return "data ruined";
            break;
        case allocete_err:
            return "allocete error";
            break;
        case invalid_value:
            return "invalid value";
            break;
        case data_trans_err:
            return "data transmition error";
            break;
        case scan_num_err:
            return "scan num err";
            break;
        case scan_oper_err:
            return "scan operation err";
            break;
        case no_el_to_pop:
            return "no elements to pop";
            break;
        case cor_func_oper:
            return "correct function operation";
            break;
        default:
            return "correct function operation";
            break;
    }
}


void StackDump (stack_t* stk)
{
    printf ("Stack [%p]\n{\n", stk);

    int tmp = 0;
    if (stk->capasity < 20)
        tmp = stk->capasity;
    else   
        tmp = 20;

    printf ("\tsize = %d\n", stk->size);
    printf ("\tcapasity = %d\n", stk->capasity);
    printf ("\tdata[%p]\n\t{\n", stk->data);

    if (stk->data[0] == KANAREIKA)
        printf ("\t\t[0] = KANAREIKA\n");
    else    
        printf ("\t\t[0] = %d (not KANAREIKA)\n", stk->data[0]);

    for (int i = 1; i < tmp + 1; i++)
    {
        if (stk->data[i] == POIZON)
            printf ("\t\t[%d] = POIZON\n", i);
        else    
            printf ("\t\t*[%d] = %d\n", i, stk->data[0]);
    }

    if (stk->data[stk->capasity + 1] == KANAREIKA)
        printf ("\t\t[%d] = KANAREIKA\n", stk->capasity - 1);
    else    
        printf ("\t\t[%d] = %d (not KANAREIKA)\n", stk->capasity + 1, stk->data[stk->capasity + 1]);

    printf ("\t}\n}\n");
}


StackErr_t verify (stack_t* stk)
{
    ASSERT (stk != 0);
    ASSERT (stk->data != 0);

    if (stk->data[stk->capasity + 1] != KANAREIKA || stk->data[0] != KANAREIKA)
    {
        return data_ruined;
    }

    return cor_func_oper;
}


StackErr_t upsize_array (stack_t* stk)
{
    STACK_OK (stk);

    if (stk->size == stk->capasity - 1)
    {
        stk->data = (stack_val_t*)realloc (stk->data, stk->capasity * 2);
        stk->capasity = 2 * stk->capasity - 2;
        if (stk->data == NULL) 
            return allocete_err;
    }

    STACK_OK (stk);

    return cor_func_oper;
}


StackErr_t downsize_array (stack_t* stk)
{
    STACK_OK (stk);

    int array_min_size = 64;
    if (stk->size <= 0.25 * stk->capasity && stk->capasity > array_min_size * 2)
    {
        stk->data = (stack_val_t*)realloc (stk->data, stk->capasity / 2);
        stk->capasity = stk->capasity / 2 - 2;
        if (stk->data == NULL) 
            return allocete_err;
    }

    STACK_OK (stk);

    return cor_func_oper;
}


StackErr_t allocete_array (stack_t* stk, int value, int* array_size)
{
    ASSERT (stk != 0);
    if (value < 1)
        return invalid_value;

    int array_min_size = 64;

    if (value > array_min_size)
        *array_size = value + 2;
    else
        *array_size = array_min_size;

    stk->data = (stack_val_t*)calloc (*array_size, sizeof (stack_val_t));
    if (stk->data == NULL) 
        return allocete_err;

    return cor_func_oper;
}


StackErr_t filling_stack (stack_t* stk, int array_size)
{
    ASSERT (stk != 0);
    ASSERT (stk->data != 0);

    stk->capasity = array_size - 2;

    stk->size = 0;

    stk->data[0] = KANAREIKA;
    stk->data[array_size - 1] = KANAREIKA;

    for (int i = 1; i < array_size - 1; i++)
        stk->data[i] = POIZON;

    STACK_OK (stk);

    return cor_func_oper;
}