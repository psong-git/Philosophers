#include "philosophers.h"

void get_forks(t_philo *philo)
{
    pthread_mutex_t *lforks_mutex;
    pthread_mutex_t *rforks_mutex;

    lforks_mutex = &(philo->all->forks_mutex[philo->lfork]);
    rforks_mutex = &(philo->all->forks_mutex[philo->rfork]);

    pthread_mutex_lock(lforks_mutex);
    display_message(philo, FORK);
    pthread_mutex_lock(rforks_mutex);
    display_message(philo, FORK);
}

void exceptional(t_philo *philo)
{
    pthread_mutex_t *lforks_mutex;
    pthread_mutex_t *rforks_mutex;

    lforks_mutex = &(philo->all->forks_mutex[philo->lfork]);
    rforks_mutex = &(philo->all->forks_mutex[philo->rfork]);

    pthread_mutex_lock(rforks_mutex);
    display_message(philo, FORK);
    pthread_mutex_lock(lforks_mutex);
    display_message(philo, FORK);
}

void put_down_forks(t_philo *philo)
{
    pthread_mutex_t *lforks_mutex;
    pthread_mutex_t *rforks_mutex;

    lforks_mutex = &(philo->all->forks_mutex[philo->lfork]);
    rforks_mutex = &(philo->all->forks_mutex[philo->rfork]);
    display_message(philo, SLEEP);
    pthread_mutex_unlock(lforks_mutex);
    pthread_mutex_unlock(rforks_mutex);
    usleep(philo->all->time_to_sleep * 1000);
}

void eating(t_philo *philo)
{
    pthread_mutex_t *dining_mutex;
    pthread_mutex_t *must_eat_mutex;

    dining_mutex = &(philo->dining_mutex);
    must_eat_mutex = &(philo->must_eat_mutex);
    pthread_mutex_lock(dining_mutex);
    philo->time_limit = get_time() + philo->all->time_to_die;
    display_message(philo, EAT);
    usleep(philo->all->time_to_eat * 1000);
    pthread_mutex_unlock(dining_mutex);
    pthread_mutex_unlock(must_eat_mutex);
}