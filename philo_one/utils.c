#include "philosophers.h"

int long_value(int sign)
{
    if (sign == -1)
        return (0);
    else
        return (-1);
}

int ft_atoi(const char *str)
{
    int i;
    int nb;
    int sign;

    i = 0;
    nb = 0;
    sign = 1;
    while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while ('0' <= str[i] && str[i] <= '9')
    {
        nb = nb * 10 + sign * (str[i] - '0');
        i++;
    }
    if (i >= 20)
        nb = long_value(sign);
    return (nb);
}

size_t get_time()
{
    struct timeval current;

    gettimeofday(&current, NULL);
    return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void ft_putnbr_fd(int nb, int fd)
{
    unsigned int nbr;

    if (nb < 0)
    {
        ft_putchar_fd('-', fd);
        nbr = (unsigned int)(nb * -1);
    }
    else
        nbr = (unsigned int)nb;
    if (nbr >= 10)
        ft_putnbr_fd(nbr / 10, fd);
    ft_putchar_fd((char)(nbr % 10 + '0'), fd);
}

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

int clean_all(t_status *all)
{
    int i;

    if (all->forks_mutex)
    {
        i = 0;
        while (i < all->number_of_philosophers)
        {
            pthread_mutex_destroy(&(all->forks_mutex[i]));
            i++;
        }
        free(all->forks_mutex);
        all->forks_mutex = NULL;
    }
    if (all->forks_mutex)
    {
        i = 0;
        while (i < all->number_of_philosophers)
        {
            pthread_mutex_destroy(&(all->forks_mutex[i]));
            i++;
        }
        free(all->forks_mutex);
        all->forks_mutex = NULL;
    }
    if (all->philos)
    {
        i = 0;
        while (i < all->number_of_philosophers)
        {
            pthread_mutex_destroy(&(all->philos[i].dining_mutex));
            pthread_mutex_destroy(&(all->philos[i].must_eat_mutex));
            i++;
        }
        free(all->philos);
        all->philos = NULL;
    }
    pthread_mutex_destroy(&(all->write_mutex));
    pthread_mutex_destroy(&(all->end_metex));
    return (FAIL);
}

int error_message()
{
    write(0, "ERROR\n", 6);
    return (FAIL);
}