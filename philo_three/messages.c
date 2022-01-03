#include "philosophers.h"

char *get_message(int type)
{
    if (type == EAT)
        return (" is eating\n");
    else if (type == SLEEP)
        return (" is sleeping\n");
    else if (type == FORK)
        return (" has taken a fork\n");
    else if (type == THINK)
        return (" is thingking\n");
    else if (type == DEAD)
        return (" died\n");
    printf("%d", type);
    return (" unexpected result\n");
}

void display_message(t_philo *philo, int type)
{
    char *message;
    int message_length;

    pthread_sem_lock(philo->all->write_sem);
    pthread_sem_lock(philo->all->dead_write_m);
    message = get_message(type);
    message_length = ft_strlen(message);
    ft_putnbr_fd(get_time() - philo->all->time_to_start, 1);
    write(1, " in_ms ", 7);
    ft_putnbr_fd(philo->position + 1, 1);
    write(1, message, message_length);
    if (type < DEAD)
    {
        pthread_sem_unlock(philo->all->dead_write_m);
    }
    pthread_sem_unlock(philo->all->write_sem);
}