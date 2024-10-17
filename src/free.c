#include "../include/philosophers.h"

int free_table(t_table *table)
{
    if (table->fork)
        free(table->fork);
    if (table->philo)
        free(table->philo);
    free(table);
    return (-1);
}