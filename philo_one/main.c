#include "philosophers.h"

void *must_eat_monitor(void *all_void)
{
    t_status *all;
    int i;
    int j;

    all = (t_status *)all_void;
    i = 0;
    j = 0;
    while (j < all->must_eat_count)
    {
        i = 0;
        while (i < all->number_of_philosophers)
        {
            pthread_mutex_lock(&(all->philos[i].must_eat_mutex));
            i++;
        }
        j++;
    }
    display_message(&(all->philos[0]), END);
    pthread_mutex_unlock(&(all->end_metex));
    return ((void *)SUCCESS);
}

void *philo_monitor(void *philo_void)
{
    t_philo *philo;

    philo = (t_philo *)philo_void;
    while (42)
    {
        pthread_mutex_lock(&(philo->dining_mutex));
        if (get_time() > philo->time_limit)
        {
            display_message(philo, DEAD);
            pthread_mutex_unlock(&(philo->dining_mutex));
            pthread_mutex_unlock(&(philo->all->end_metex));
            return ((void *)SUCCESS);
        }
        pthread_mutex_unlock(&(philo->dining_mutex));
        usleep(1000);
    }
    return ((void *)FAIL);
}

void *dining_philo(void *philo_void)
{
    t_philo *philo;
    pthread_t pthread;

    philo = (t_philo *)philo_void;
    philo->time_limit = get_time() + philo->all->time_to_die;
    if (pthread_create(&pthread, NULL, &philo_monitor, (void *)philo) != SUCCESS)
        return ((void *)FAIL);
    pthread_detach(pthread);
    while (42)
    {
        get_forks(philo);
        eating(philo);
        put_down_forks(philo);
        display_message(philo, THINK);
    }
    return (NULL);
}

int multi_threads(t_status *all)
{
    int i;
    pthread_t pthread;

    all->time_to_start = get_time();
    if (all->must_eat_count > 0)
    {
        if (pthread_create(&pthread, NULL, &must_eat_monitor, (void *)all) != SUCCESS)
            return (FAIL);
        pthread_detach(pthread);
    }
    i = 0;
    while (i < all->number_of_philosophers)
    {
        if (pthread_create(&pthread, NULL, &dining_philo, (void *)(&(all->philos[i]))) != SUCCESS)
            return (FAIL);
        pthread_detach(pthread);
        i++;
        usleep(100);
    }
    return (SUCCESS);
}

int main(int ac, char **av)
{
    t_status all;

    if (ac < 5 || ac > 6)
        return (error_message());
    if (parse_argv(av) != SUCCESS)
        return (error_message());
    if (init_all(&all, ac, av) != SUCCESS)
        return (clean_all(&all) && error_message());
    if (multi_threads(&all) != SUCCESS)
        return (clean_all(&all) && clean_all(&all));
    pthread_mutex_lock(&(all.end_metex));
    clean_all(&all);
    return (SUCCESS);
}