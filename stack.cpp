#include "stack.h"

stack_err_t stack_init (stack_t* stk, int user_size)
{
    DEBUG_ASSERT (stk != NULL);
    if (user_size < 1)
        return invalid_value;
    
    int array_size = 0;
    int array_min_size = 64;
    
    if (user_size > array_min_size)
        array_size = user_size + 2;
    else
        array_size = array_min_size;

    stk->data = (stack_val_t*)calloc (array_size, sizeof (stack_val_t));
    if (stk->data == NULL)
        return allocete_err;

    RETURN_IF_ERR (stack_fill (stk, array_size)); //memset

    STACK_OK (stk);

    return success;
}


stack_err_t stack_push (stack_t* stk, stack_val_t value)
{
    STACK_OK (stk);

    if (stk->size == stk->capasity - 1)
    {
        stk->data = (stack_val_t*)realloc (stk->data, stk->capasity * 2);
        stk->capasity = 2 * stk->capasity - 2;
        if (stk->data == NULL) 
            return allocete_err;
    }

    stk->data[++stk->size] = value;

    STACK_OK (stk);

    return success;
}


stack_err_t stack_pop (stack_t* stk, stack_val_t* val_pointer)
{
    STACK_OK (stk);
    if (stk->size == 0)
        return no_el_to_pop;

    int array_min_size = 64;
    if (stk->size <= stk->capasity / 4 && stk->capasity > array_min_size * 2)
    {
        stk->data = (stack_val_t*)realloc (stk->data, stk->capasity / 2);
        stk->capasity = stk->capasity / 2 - 2;
        if (stk->data == NULL) 
            return allocete_err;
    }

    *val_pointer = stk->data[stk->size];
    stk->data[stk->size--] = POIZON;

    STACK_OK (stk);
    
    return success;
}


stack_err_t stack_destroy (stack_t* stk)
{
    STACK_OK (stk);

    free (stk->data);

    return success;
}


const char* error_code_to_string (stack_err_t status)
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
        case scan_num_err:
            return "scan num err";
            break;
        case scan_oper_err:
            return "scan operation err";
            break;
        case no_el_to_pop:
            return "no elements to pop";
            break;
        case success:
            return "correct function operation";
            break;
        case finish_scan:
            return "end scan";
            break;
        default:
            return "correct function operation";
            break;
    }
}


void stack_dump (stack_t* stk)
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
            printf ("\t\t*[%d] = %d\n", i, stk->data[i]);
    }

    if (stk->data[stk->capasity + 1] == KANAREIKA)
        printf ("\t\t[%d] = KANAREIKA\n", stk->capasity - 1);
    else    
        printf ("\t\t[%d] = %d (not KANAREIKA)\n", stk->capasity + 1, stk->data[stk->capasity + 1]);

    printf ("\t}\n}\n");
}


stack_err_t stack_verify (stack_t* stk)
{
    DEBUG_ASSERT (stk != 0);
    DEBUG_ASSERT (stk->data != 0);

    if (stk->data[stk->capasity + 1] != KANAREIKA || stk->data[0] != KANAREIKA)
        return data_ruined;

    return success;
}


stack_err_t stack_fill (stack_t* stk, int array_size)
{
    DEBUG_ASSERT (stk != 0);
    DEBUG_ASSERT (stk->data != 0);

    stk->capasity = array_size - 2;

    stk->size = 0;

    stk->data[0] = KANAREIKA;
    stk->data[array_size - 1] = KANAREIKA;

    for (int i = 1; i < array_size - 1; i++)
        stk->data[i] = POIZON;

    STACK_OK (stk);

    return success;
}