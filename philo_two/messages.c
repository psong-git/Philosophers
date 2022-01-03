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
    return (" unexpected result\n");
}

void display_message(t_philo *philo, int type)
{
    static int flag = MESSAGE_GO;
    char *message;
    int message_length;

    pthread_sem_lock(philo->all->write_sem);
    message = get_message(type);
    message_length = ft_strlen(message);
    if (flag)
    {
        if (type == END || type == DEAD)
            flag = MESSAGE_STOP;
        if (type != END)
        {
            ft_putnbr_fd(get_time() - philo->all->time_to_start, 1);
            write(1, " in_ms ", 7);
            ft_putnbr_fd(philo->position + 1, 1);
            write(1, message, message_length);
        }
    }
    pthread_sem_unlock(philo->all->write_sem);
}