#include "../include/philosophers.h"

long valid_input(const char *str, long i)
{
    long nbr;

    nbr = ft_atol(str);
    if (nbr > i)
    {
        printf("Error\n%s exceeds %ld\n", str, i);
        return (-1);
    }
    if (nbr < 1)
    {
        ft_printf("Error\n%s must be a positive number\n", str);
        return (-1);
    }
    return (nbr);
}
