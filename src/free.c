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

void handle_one_philo(t_philo *philo, t_table *table)
{
    pthread_mutex_lock(&philo->left_fork->mutex);
    printf("Philo %zu has taken left fork %d\n", philo->philo_id, philo->left_fork->fork_id);
    usleep(table->time_to_die * 1000);
    pthread_mutex_unlock(&philo->left_fork->mutex);
    table->end_simulation = true;
}
