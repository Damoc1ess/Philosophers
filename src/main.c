#include "../include/philosophers.h"

t_table *pars_args(t_table *table,int argc, char **argv)
{
    table->philo_nbr = valid_input(argv[1], 200);
    if (table->philo_nbr == -1)
        return (NULL); 
    table->time_to_die = valid_input(argv[2], 1000000);
    if (table->time_to_die == -1)
        return (NULL);
    table->time_to_eat = valid_input(argv[3], 1000000);
    if (table->time_to_eat == -1)
        return (NULL);
    table->time_to_sleep = valid_input(argv[4], 1000000);
    if (table->time_to_sleep == -1)
        return (NULL);
    if(argc == 6)
    {
        table->nbr_limit_meals = valid_input(argv[5], 1000000);
        if (table->nbr_limit_meals == -1)
            return (NULL);
    }
    else
        table->nbr_limit_meals = -1; // -1 mean no limit set;
    return (table);
}

int main(int argc, char **argv)
{
    if (argc == 5 || argc == 6)
    {
        t_table *table;
        table = ft_safe_malloc(sizeof(t_table));
        if (!pars_args(table,argc, argv))
        {
            free_table(table);
            return (1);
        }
        print_table(*table);
    }
    else
    {
        ft_printf("Erro\nWrong number of arguments\n");
        ft_printf("Correct is ./philo 5 800 200 200 [5]\n");
    }
}
