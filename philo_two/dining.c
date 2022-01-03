#include "philosophers.h"

void get_forks(t_philo *philo)
{
    pthread_sem_lock(philo->all->forks_sem);
    display_message(philo, FORK);
    pthread_sem_lock(philo->all->forks_sem);
    display_message(philo, FORK);
}

void put_down_forks(t_philo *philo)
{
    display_message(philo, SLEEP);
    pthread_sem_unlock(philo->all->forks_sem);
    pthread_sem_unlock(philo->all->forks_sem);
    usleep(philo->all->time_to_sleep * 1000);
}

void eating(t_philo *philo)
{
    pthread_sem_lock(philo->dining_sem);
    philo->time_limit = get_time() + philo->all->time_to_die;
    display_message(philo, EAT);
    usleep(philo->all->time_to_eat * 1000);
    sem_wait(philo->dining_sem);
    pthread_sem_unlock(philo->dining_sem);
    pthread_sem_unlock(philo->must_eat_sem);
}
