#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

typedef struct _args
{
    unsigned char coolingScheduleIndex;
    double T0;
    double TN;
    unsigned int SAmax;
    unsigned int N;
} Args;

void parse_args(Args *args, int argc, char **argv);

#endif