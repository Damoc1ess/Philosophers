#include "../include/philosophers.h"

void free_table(t_table *table)
{
    if (table->fork)
        free(table->fork);
    if (table->philo)
        free(table->philo);
    free(table);
}