#include "philo.h"

int ft_is_number(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] <= '0' || str[i] >= '9')
            return(0);
        i++;
    }
    return(1);
}

int check_args_number(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
   if(argc != 6)
    {
        write(2, "Wrong arguments number", 23);
        return(0);
    }
    while(i < argc)
    {
        if((atoi(argv[i]) < 0 || atoi(argv[i]) >= INT_MAX || !ft_is_number(argv[i])))
        {
            write(1, "Input is not numbers", 21) ;
            return(0);
        }
        i++;
    }
    return(1);
}