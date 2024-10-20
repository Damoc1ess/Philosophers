#include "../include/philosophers.h"

t_table *init_data(t_table *table)
{
    long i;
    table->fork = ft_safe_malloc(sizeof(t_fork) * table->philo_nbr);
    table->philo = ft_safe_malloc(sizeof(t_philo) * table->philo_nbr);

    i = 0;
    while (i < table->philo_nbr)
    {
        table->philo[i].philo_id = i + 1;
        table->philo[i].meals_count = 0;
        table->philo[i].full = false;
        table->philo[i].last_meal_time = get_current_time();
        table->philo[i].left_fork = &table->fork[i];
        table->philo[i].right_fork = &table->fork[(i + 1) % table->philo_nbr];
        pthread_mutex_init(&table->fork[i].mutex, NULL);
        table->fork[i].fork_id = i;
        i++;
    }
    table->end_simulation = false;
    return (table);
}

// void *monitor_routine(void *arg)
// {
//     t_table *table = (t_table *)arg;
//     long current_time;
//     int i;

//     while (!table->end_simulation)
//     {
//         i = 0;
//         while (i < table->philo_nbr)
//         {
//             current_time = get_current_time();
//             if (current_time - table->philo[i].last_meal_time >= table->time_to_die)
//             {
//                 printf("\033[1;31mThe philosopher %zu is fucking dead\033[0m\n", table->philo[i].philo_id);
//                 table->end_simulation = true;
//                 break;
//             }
//             i++;
//         }
//         usleep(1000);
//     }
//     return NULL;
// }
void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    long current_time;
    int i;
    int full_philos;

    while (!table->end_simulation)
    {
        i = 0;
        full_philos = 0;
        while (i < table->philo_nbr)
        {
            current_time = get_current_time();

            // Vérification si un philosophe est mort
            if (current_time - table->philo[i].last_meal_time >= table->time_to_die)
            {
                printf("\033[1;31mThe philosopher %zu is fucking dead\033[0m\n", table->philo[i].philo_id);
                table->end_simulation = true;
                break;
            }

            // Vérification si tous les philosophes ont mangé le nombre limite de repas
            if (table->nbr_limit_meals != -1 && table->philo[i].meals_count >= table->nbr_limit_meals)
                full_philos++;

            i++;
        }

        // Si tous les philosophes ont atteint la limite de repas, on termine la simulation
        if (full_philos == table->philo_nbr)
        {
            printf("\033[1;32mAll philosophers have eaten the required number of meals\033[0m\n");
            table->end_simulation = true;
        }

        usleep(1000);
    }
    return NULL;
}


void create_thread(t_table *table)
{
    int i;
    pthread_t monitor_thread;
    t_philo_arg *philo_arg;

    i = 0;
    while (i < table->philo_nbr)
    {
        philo_arg = malloc(sizeof(t_philo_arg));
        philo_arg->philo = &table->philo[i];
        philo_arg->table = table;
        pthread_create(&table->philo[i].thread_id, NULL, philo_routine, philo_arg);
        i++;
    }
    pthread_create(&monitor_thread, NULL, monitor_routine, table);
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(table->philo[i].thread_id, NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
}

// void *philo_routine(void *arg)
// {
//     t_philo_arg *philo_arg = (t_philo_arg *)arg;
//     t_philo *philo = philo_arg->philo;
//     t_table *table = philo_arg->table;

//     if (table->philo_nbr == 1)
//     {
//         handle_one_philo(philo, table);
//         free(philo_arg);
//         return NULL;
//     }
//     while (!table->end_simulation)
//     {
//         take_forks(philo);  // Les fourchettes sont prises ici
//         if (table->end_simulation)
//             break;
//         printf("Philo %zu is eating\n", philo->philo_id);
//         philo->meals_count++;
//         philo->last_meal_time = get_current_time();
//         usleep(table->time_to_eat * 1000);
//         release_forks(philo);  // Les fourchettes sont relâchées ici
//         if (table->end_simulation)
//             break;
//         printf("Philo %zu is sleeping\n", philo->philo_id);
//         usleep(table->time_to_sleep * 1000);
//         printf("Philo %zu is thinking\n", philo->philo_id);
//         usleep(1000);
//     }
//     free(philo_arg);  // Libérer la mémoire allouée
//     return NULL;
// }
void *philo_routine(void *arg)
{
    t_philo_arg *philo_arg = (t_philo_arg *)arg;
    t_philo *philo = philo_arg->philo;
    t_table *table = philo_arg->table;

    while (!table->end_simulation)
    {
        take_forks(philo);  // Les fourchettes sont prises ici
        if (table->end_simulation)
            break;

        printf("Philo %zu is eating\n", philo->philo_id);
        philo->meals_count++;
        philo->last_meal_time = get_current_time();
        usleep(table->time_to_eat * 1000);

        release_forks(philo);  // Les fourchettes sont relâchées ici

        // Vérification du nombre de repas
        if (table->nbr_limit_meals != -1 && philo->meals_count >= table->nbr_limit_meals)
        {
            philo->full = true;  // Philosophe a terminé ses repas
            break;  // Sort de la boucle, le philosophe a atteint la limite
        }

        printf("Philo %zu is sleeping\n", philo->philo_id);
        usleep(table->time_to_sleep * 1000);
        printf("Philo %zu is thinking\n", philo->philo_id);
        usleep(1000);
    }

    free(philo_arg);  // Libérer la mémoire allouée
    return NULL;
}


void take_forks(t_philo *philo)
{
    if (philo->philo_id % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->mutex);
        printf("Philo %zu has taken right fork %d\n", philo->philo_id, philo->right_fork->fork_id);
        pthread_mutex_lock(&philo->left_fork->mutex);
        printf("Philo %zu has taken left fork %d\n", philo->philo_id, philo->left_fork->fork_id);
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->mutex);
        printf("Philo %zu has taken left fork %d\n", philo->philo_id, philo->left_fork->fork_id);
        pthread_mutex_lock(&philo->right_fork->mutex);
        printf("Philo %zu has taken right fork %d\n", philo->philo_id, philo->right_fork->fork_id);
    }
}

void release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->right_fork->mutex);
    pthread_mutex_unlock(&philo->left_fork->mutex);
    printf("Philo %zu has put down both forks\n", philo->philo_id);
}
void cleanup_table(t_table *table)
{
    long i = 0;

    while (i < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->fork[i].mutex);
        i++;
    }
    free(table->fork);
    free(table->philo);
}
