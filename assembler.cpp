#include "assembler.h"

int main (int argc, char* argv[])
{
    (void)argc;
    parametrs data = {};

    RETURN_IF_ERR (allocation_el_arr (&data, argv[1]));
    RETURN_IF_ERR (read_commands (&data, argv[1]));
    RETURN_IF_ERR (allocation_line_com_arr (&data));
    RETURN_IF_ERR (transator (&data));
    RETURN_IF_ERR (write_commands (&data, argv[2]));
    RETURN_IF_ERR (destroy_arrays (&data));

    return 0;
}


error_t read_commands (parametrs* data, const char* title)
{
    DEBUG_ASSERT (data != NULL);
    DEBUG_ASSERT (data->el_array != NULL);
    DEBUG_ASSERT (title != NULL);

    FILE* file = fopen (title, "r");
    if (file == NULL)
        return ERR_OPEN_READ_FILE;

    data->num_el = (int)fread (data->el_array, sizeof (char), data->num_el, file);
    if (data->num_el == 0)
        return ERR_FREAD;

    fclose (file);

    return SUCCESS;
}


error_t transator (parametrs* data)
{
    DEBUG_ASSERT (data != 0);
    DEBUG_ASSERT (data->line_array != 0);
    DEBUG_ASSERT (data->com_array != 0);

    char tmp[10] = "";
    int pos = 0;

    for (int i = 0; i < data->num_lines; i++)
    {
        sscanf (data->line_array[i], "%s", tmp);

        if (strcmp (tmp, "PUSH") == 0)
        {
            int value = 0;
            sscanf (data->line_array[i] + 4, "%d", &value);
            data->com_array[pos++] = '1';
            data->com_array[pos++] = ' ';
            sprintf (data->com_array + pos, "%d", value);
            int count = 0;
            while (value != 0)
            {
            count++;
            value /= 10;
            }
            pos += count;
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "OUT") == 0)
        {
            data->com_array[pos++] = '2';
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "ADD") == 0)
        {
            data->com_array[pos++] = '3';
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "SUB") == 0)
        {
            data->com_array[pos++] = '4';
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "MUL") == 0)
        {
            data->com_array[pos++] = '5';
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "DIV") == 0)
        {
            data->com_array[pos++] = '6';
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "SQRT") == 0)
        {
            data->com_array[pos++] = '7';
            data->com_array[pos++] = '\n';
        }
        else if (strcmp (tmp, "HLT") == 0)
        {
            data->com_array[pos++] = '8';
            data->com_array[pos++] = '\n';
        }
        else
        {
            printf ("hueta\n");
            return ERR_INVAID_SCAN_SYM;
        }
    }
    data->num_com = --pos;

    return SUCCESS;
}


error_t write_commands (parametrs* data, const char* title)
{
    DEBUG_ASSERT (data != 0);
    DEBUG_ASSERT (title != 0);
    
    FILE* file = fopen (title, "w");
    if (file == NULL)
        return ERR_OPEN_WRITE_FILE;

    fwrite (data->com_array, sizeof (char), data->num_com, file);

    fclose (file);

    return SUCCESS;
}


error_t destroy_arrays (parametrs* data)
{
    DEBUG_ASSERT (data != NULL);
    DEBUG_ASSERT (data->el_array != NULL);
    DEBUG_ASSERT (data->line_array != NULL);
    DEBUG_ASSERT (data->com_array != NULL);

    free (data.com_array);
    free (data.line_array);
    free (data.el_array);

    return SUCCESS;
}