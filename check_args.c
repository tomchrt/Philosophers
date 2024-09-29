#include "philo.h"

int ft_is_number(char *str)
{
    int i;

    i = 0;
    if(!str || str[i] == '\0')
        return(0);
    while(str[i])
    {
        if(str[i] < '0' || str[i] > '9')
            return(0);
        i++;
    }
    return(1);
}

int check_args_number(int argc, char **argv)
{
    int i;

    i = 1;
   if(argc != 5)
    {
        printf("%d\n", i);
        write(2, "Wrong arguments number", 23);
        exit(EXIT_FAILURE);
    }
    while(i < argc)
    {
        if((atoi(argv[i]) < 0 ) || (atoi(argv[i]) >= INT_MAX ) || !(ft_is_number(argv[i])))
        {
            write(2, "Input is not numbers", 21) ;
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return(1);
}

