#include "../include/philosophers.h"

// t_table *init_data(t_table *table)
// {
//     long i;
//     table->fork = ft_safe_malloc(sizeof(t_fork) * table->philo_nbr);
//     table->philo = ft_safe_malloc(sizeof(t_philo) * table->philo_nbr);

//     i = 0;
//     while (i < table->philo_nbr)
//     {
//         table->philo[i].philo_id = i + 1;
//         table->philo[i].meals_count = 0;
//         table->philo[i].full = false;
//         table->philo[i].last_meal_time = 0;
//         table->philo[i].left_fork = &table->fork[i];
//         table->philo[i].right_fork = &table->fork[(i + 1) % table->philo_nbr];
//         pthread_mutex_init(&table->fork[i].mutex, NULL);
//         table->fork[i].fork_id = i;
//         i++;
//     }
//     table->end_simulation = false;
//     return (table);
// }

// void    create_thread(t_table *table)
// {
//     int i;

//     i = 0;
//     while(i < table->philo_nbr)
//     {
//         pthread_create(&table->philo[i].thread_id, NULL, philo_routine, &table->philo[i]);
//         i++;
//     }
//     i = 0;
//     while(i < table->philo_nbr)
//     {
//          pthread_join(table->philo[i].thread_id, NULL);
//          i++;
//     }
// }

// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;
//     t_table *table = /* Obtenir la table à partir de l'argument ou d'une variable globale */;

//     while (!table->end_simulation) // Boucle jusqu'à la fin de la simulation
//     {
//         // Prendre la fourchette gauche
//         pthread_mutex_lock(&philo->left_fork->mutex);
//         printf("Philosopher %zu has taken left fork %d\n", philo->philo_id, philo->left_fork->fork_id);

//         // Prendre la fourchette droite
//         pthread_mutex_lock(&philo->right_fork->mutex);
//         printf("Philosopher %zu has taken right fork %d\n", philo->philo_id, philo->right_fork->fork_id);

//         // Manger
//         printf("Philosopher %zu is eating\n", philo->philo_id);
//         philo->meals_count++;
//         philo->last_meal_time = get_current_time;
//         usleep(table->time_to_eat * 1000); // Convertir en microsecondes

//         // Libérer la fourchette droite
//         pthread_mutex_unlock(&philo->right_fork->mutex);
//         printf("Philosopher %zu has put down right fork %d\n", philo->philo_id, philo->right_fork->fork_id);

//         // Libérer la fourchette gauche
//         pthread_mutex_unlock(&philo->left_fork->mutex);
//         printf("Philosopher %zu has put down left fork %d\n", philo->philo_id, philo->left_fork->fork_id);

//         // Dormir
//         printf("Philosopher %zu is sleeping\n", philo->philo_id);
//         usleep(table->time_to_sleep * 1000); // Convertir en microsecondes

//         // Réfléchir
//         printf("Philosopher %zu is thinking\n", philo->philo_id);
//         usleep(1000); // Temps de réflexion, à ajuster selon les besoins
//     }
//     return NULL;
// }

// Structure pour passer à la routine du philosophe
typedef struct s_philo_arg {
    t_philo *philo;
    t_table *table;
} t_philo_arg;

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
        table->philo[i].last_meal_time = 0;
        table->philo[i].left_fork = &table->fork[i];
        table->philo[i].right_fork = &table->fork[(i + 1) % table->philo_nbr];
        pthread_mutex_init(&table->fork[i].mutex, NULL);
        table->fork[i].fork_id = i;
        i++;
    }
    table->end_simulation = false;
    return (table);
}

// void    create_thread(t_table *table)
// {
//     int i;
//     t_philo_arg *philo_arg;

//     i = 0;
//     while (i < table->philo_nbr)
//     {
//         philo_arg = malloc(sizeof(t_philo_arg));  // Alloue mémoire pour chaque philosophe
//         philo_arg->philo = &table->philo[i];      // Associe le philosophe
//         philo_arg->table = table;                 // Associe la table

//         pthread_create(&table->philo[i].thread_id, NULL, philo_routine, philo_arg);
//         i++;
//     }

//     i = 0;
//     while (i < table->philo_nbr)
//     {
//         pthread_join(table->philo[i].thread_id, NULL);
//         i++;
//     }
// }
void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    long current_time;
    int i;

    while (!table->end_simulation)
    {
        i = 0;
        while (i < table->philo_nbr)
        {
            current_time = get_current_time(); // Fonction pour obtenir le temps actuel en millisecondes
            if (current_time - table->philo[i].last_meal_time >= table->time_to_die)
            {
                printf("Philosopher %zu has died\n", table->philo[i].philo_id);
                table->end_simulation = true;  // Met fin à la simulation
                break;
            }
            i++;
        }
        usleep(1000);  // Petit délai pour éviter une boucle infinie rapide
    }
    return NULL;
}

void create_thread(t_table *table)
{
    int i;
    pthread_t monitor_thread; // Thread pour surveiller la mort des philosophes
    t_philo_arg *philo_arg;

    i = 0;
    while (i < table->philo_nbr)
    {
        philo_arg = malloc(sizeof(t_philo_arg));  // Alloue mémoire pour chaque philosophe
        philo_arg->philo = &table->philo[i];      // Associe le philosophe
        philo_arg->table = table;                 // Associe la table

        pthread_create(&table->philo[i].thread_id, NULL, philo_routine, philo_arg);
        i++;
    }

    // Lancer le thread de surveillance
    pthread_create(&monitor_thread, NULL, monitor_routine, table);

    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(table->philo[i].thread_id, NULL);
        i++;
    }

    // Attendre la fin du thread de surveillance
    pthread_join(monitor_thread, NULL);
}

void *philo_routine(void *arg)
{
    t_philo_arg *philo_arg = (t_philo_arg *)arg;
    t_philo *philo = philo_arg->philo;
    t_table *table = philo_arg->table;

    while (!table->end_simulation) // Boucle jusqu'à la fin de la simulation
    {
        // Philosophe pair prend la fourchette droite en premier
        if (philo->philo_id % 2 == 0)
        {
            // Prendre la fourchette droite
            pthread_mutex_lock(&philo->right_fork->mutex);
            printf("Philosopher %zu has taken right fork %d\n", philo->philo_id, philo->right_fork->fork_id);

            // Prendre la fourchette gauche
            pthread_mutex_lock(&philo->left_fork->mutex);
            printf("Philosopher %zu has taken left fork %d\n", philo->philo_id, philo->left_fork->fork_id);
        }
        else
        {
            // Philosophe impair prend la fourchette gauche en premier
            pthread_mutex_lock(&philo->left_fork->mutex);
            printf("Philosopher %zu has taken left fork %d\n", philo->philo_id, philo->left_fork->fork_id);

            pthread_mutex_lock(&philo->right_fork->mutex);
            printf("Philosopher %zu has taken right fork %d\n", philo->philo_id, philo->right_fork->fork_id);
        }

        // Manger
        printf("Philosopher %zu is eating\n", philo->philo_id);
        philo->meals_count++;
        philo->last_meal_time = get_current_time();
        usleep(table->time_to_eat * 1000); // Convertir en microsecondes

        // Libérer les fourchettes
        pthread_mutex_unlock(&philo->right_fork->mutex);
        pthread_mutex_unlock(&philo->left_fork->mutex);
        printf("Philosopher %zu has put down both forks\n", philo->philo_id);

        // Dormir
        printf("Philosopher %zu is sleeping\n", philo->philo_id);
        usleep(table->time_to_sleep * 1000); // Convertir en microsecondes

        // Réfléchir
        printf("Philosopher %zu is thinking\n", philo->philo_id);
        usleep(1000); // Temps de réflexion, à ajuster selon les besoins
    }

    free(philo_arg); // Libère la mémoire allouée pour les arguments
    return NULL;
}
