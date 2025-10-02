#include "assembler.h"

error_t allocation_el_arr (parametrs* data, const char* title)
{
    DEBUG_ASSERT (data != NULL);
    DEBUG_ASSERT (title != NULL);

    struct stat statistic = {};
    stat (title, &statistic);

    data->num_el = statistic.st_size;

    data->el_array = (char*)calloc (data->num_el + 1, sizeof (char));
    if (data->el_array == NULL)
        return ERR_ALLOCATION;

    return SUCCESS;
}


error_t allocation_line_com_arr (parametrs* data)
{
    data->com_array = (char*)calloc (data->num_lines * 20, sizeof (char));
    if (data->com_array == NULL)
        return ERR_ALLOCATION;

    RETURN_IF_ERR (count_n_lines (data));

    data->line_array = (char**)calloc (data->num_lines, sizeof (char*));
    if (data->com_array == NULL)
        return ERR_ALLOCATION;

    filling_line_array (data);

    data->el_array[data->num_el] = '\0';
    data->com_array[data->num_lines * 20 - 1] = '\0';

    return SUCCESS;
}


error_t count_n_lines (parametrs* data)
{
    DEBUG_ASSERT (data != NULL);
    DEBUG_ASSERT (data->el_array != NULL);

    int i = 0;
    char* tmp = data->el_array;

    while (tmp != NULL)
    {
        tmp = strchr (tmp, '\n');

        if (tmp != NULL)
        {
            i++;
            tmp++;
        }
    }

    data->num_lines = i + 1;

    return SUCCESS;
}


error_t filling_line_array (parametrs* data)
{
    DEBUG_ASSERT (data != 0);
    DEBUG_ASSERT (data->line_array != 0);

    char* tmp = data->el_array;

    for (int i = 0; i < data->num_lines; i++)
    {
        (data->line_array)[i] = tmp;
        tmp = strchr (tmp, '\n');
        if (tmp == NULL)
            return ERR_LINE_ARR_FILL;
        tmp++;
    }

    return SUCCESS;
}


const char* error_code_to_string (error_t status)
{
    switch (status)
    {
        case ERR_ALLOCATION:
            return "ERR_ALLOCATION";
            break;
        case ERR_OPEN_READ_FILE:
            return "ERR_OPEN_READ_FILE";
            break;
        case ERR_FREAD:
            return "ERR_FREAD";
            break;
        case ERR_LINE_ARR_FILL:
            return "ERR_LINE_ARR_FILL";
            break;
        case ERR_INVAID_SCAN_SYM:
            return "ERR_INVAID_SCAN_SYM";
            break;
        case ERR_OPEN_WRITE_FILE:
            return "ERR_OPEN_WRITE_FILE";
            break;
        case SUCCESS:
            return "SUCCESS";
            break;
        default:
            return "SUCCESS";
    }
}