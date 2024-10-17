#include "../include/philosophers.h"

void debug_print_all(t_table *table)
{
    long i;

    printf("=== DEBUG: Table Information ===\n");
    printf("Number of Philosophers: %ld\n", table->philo_nbr);
    printf("Time to Die: %ld\n", table->time_to_die);
    printf("Time to Eat: %ld\n", table->time_to_eat);
    printf("Time to Sleep: %ld\n", table->time_to_sleep);
    if (table->nbr_limit_meals != -1)
        printf("Meal Limit: %ld\n", table->nbr_limit_meals);
    else
        printf("Meal Limit: No limit\n");
    printf("Simulation Start Time: %ld\n", table->start_simultaion);
    printf("Simulation Ended: %s\n\n", table->end_simulation ? "Yes" : "No");

    printf("=== DEBUG: Philosopher Information ===\n");
    for (i = 0; i < table->philo_nbr; i++)
    {
        printf("Philosopher %ld\n", i + 1);
        printf("  Philosopher ID: %zu\n", table->philo[i].philo_id);
        printf("  Meals Count: %ld\n", table->philo[i].meals_count);
        printf("  Full: %s\n", table->philo[i].full ? "Yes" : "No");
        printf("  Last Meal Time: %ld\n", table->philo[i].last_meal_time);
        printf("  Left Fork ID: %d\n", table->philo[i].left_fork->fork_id);
        printf("  Right Fork ID: %d\n", table->philo[i].right_fork->fork_id);
        printf("  Thread ID: %lu\n\n", (unsigned long)table->philo[i].thread_id);
    }

    printf("=== DEBUG: Fork Information ===\n");
    for (i = 0; i < table->philo_nbr; i++)
    {
        printf("Fork %ld\n", i + 1);
        printf("  Fork ID: %d\n", table->fork[i].fork_id);
        printf("  Mutex Address: %p\n", (void*)&table->fork[i].mutex);
    }

    printf("=== END DEBUG ===\n\n");
}

