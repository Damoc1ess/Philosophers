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

int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        ft_printf("Erro\nWrong number of arguments\n");
    t_table *table;
    table = ft_safe_malloc(sizeof(t_table));
    if (!pars_args(table,argc, argv))
        return (free_table(table));
    if (!init_data(table))
        return (free_table(table));
    create_thread(table);
    free_table(table);
    // debug_print_all(table);
}
