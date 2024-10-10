#include "../include/philosophers.h"

void    print_table(t_table table)
{
    ft_printf("nbr de philo : %d\n", table.philo_nbr);
    ft_printf("time_to_die : %d\n", table.time_to_die);
    ft_printf("time_to_eat : %d\n", table.time_to_eat);
    ft_printf("time_to_sleep : %d\n", table.time_to_sleep);
    ft_printf("nbr_limit_meals : %d\n", table.nbr_limit_meals);
    ft_printf("start_simultaion : %d\n", table.start_simultaion);
    ft_printf("end_simulation : %d\n", table.end_simulation);
}