#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/time.h>
#include <limits.h>
# include "../libft/includes/libft.h"

typedef struct s_fork
{
    int fork_id;
    pthread_mutex_t mutex;
}   t_fork;

typedef struct s_philo
{
    size_t      philo_id;
    long        meals_count;
    bool        full;
    long        last_meal_time;
    t_fork     *left_fork;
    t_fork     *right_fork;
    pthread_t  thread_id;
}   t_philo;

typedef struct s_table
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_limit_meals;
    long    start_simultaion;
    bool    end_simulation;
    t_fork  *fork;
    t_philo *philo;
}   t_table;

typedef struct s_philo_arg {
    t_philo *philo;
    t_table *table;
} t_philo_arg;

void debug_print_all(t_table *table);
void *philo_routine(void *arg);
void    create_thread(t_table *table);
long    get_current_time();
int    free_table(t_table *table);
long    valid_input(const char *str, long i);
t_table *init_data(t_table *table);
#endif