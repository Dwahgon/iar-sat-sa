#include "parseargs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void parse_args(Args *args, int argc, char **argv)
{
    int i, *p_write_i = NULL;
    unsigned int *p_write_ui = NULL;
    double *p_write_d = NULL;
    char **p_write_s = NULL;

    args->coolingScheduleIndex = 1;
    args->T0 = 100.0;
    args->TN = 0.001;
    args->SAmax = 100;
    args->N = 100;

    for (i = 1; i < argc; i++)
    {
        // Read n ants
        if (p_write_i)
        {
            *p_write_i = atoi(argv[i]);
            p_write_i = NULL;
        }
        if (p_write_ui)
        {
            *p_write_ui = (unsigned int)atol(argv[i]);
            p_write_ui = NULL;
        }
        else if (p_write_d)
        {
            *p_write_d = atof(argv[i]);
            p_write_d = NULL;
        }
        else if (p_write_s)
        {
            if (*p_write_s)
                free(*p_write_s);
            *p_write_s = (char *)malloc(strlen(argv[i]) * sizeof(char));
            strcpy(*p_write_s, argv[i]);
            p_write_s = NULL;
        }

        else if (!strcmp(argv[i], "-z"))
            p_write_d = &args->T0;
        else if (!strcmp(argv[i], "-f"))
            p_write_d = &args->TN;
        else if (!strcmp(argv[i], "-s"))
            p_write_ui = &args->SAmax;
        else if (!strcmp(argv[i], "-n"))
            p_write_ui = &args->N;
        else if (!strcmp(argv[i], "-i"))
            p_write_ui = (unsigned int *)&args->coolingScheduleIndex;
        else
        {
            printf("Argumento desconhecido: %s", argv[i]);
            exit(1);
        }
    }

    // if (!args->filePath)
    // {
    //     args->filePath = calloc(strlen("./input.txt"), sizeof(char));
    //     strcpy(args->filePath, "./input.txt");
    // }
}