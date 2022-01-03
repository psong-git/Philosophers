#include "philosophers.h"

int init_semaphores(t_status *all)
{
    if (pthread_sem_init(all->forks_sem, "forks", 0, all->number_of_philosophers) != SUCCESS)
        return (FAIL);
    if (pthread_sem_init(all->write_sem, "write", 0, 1) != SUCCESS)
        return (FAIL);
    if (pthread_sem_init(all->end_sem, "end", 0, 0) != SUCCESS)
        return (FAIL);
    if (pthread_sem_init(all->dead_write_m, "etc", 0, 1) != SUCCESS)
        return (FAIL);
    return (SUCCESS);
}

int init_philos(t_status *all)
{
    int i;

    i = 0;
    if (!(all->philos = malloc(sizeof(t_philo) * all->number_of_philosophers)))
        return (FAIL);
    while (i < all->number_of_philosophers)
    {
        all->philos[i].is_eating = 0;
        all->philos[i].position = i;
        all->philos[i].time_limit = 0;
        all->philos[i].all = all;
        if (pthread_sem_init(all->philos[i].dining_sem, "dining", i, 1) != SUCCESS)
            return (FAIL);
        if (pthread_sem_init(all->philos[i].must_eat_sem, "must", i, 0) != SUCCESS)
            return (FAIL);
        i++;
    }
    return (SUCCESS);
}

int init_all(t_status *all, int ac, char **av)
{
    all->number_of_philosophers = ft_atoi(av[1]);
    all->time_to_die = ft_atoi(av[2]);
    all->time_to_eat = ft_atoi(av[3]);
    all->time_to_sleep = ft_atoi(av[4]);
    all->time_to_start = 0;
    all->must_eat_count = 0;
    if (ac == 6)
        all->must_eat_count = ft_atoi(av[5]);
    all->philos = NULL;
    all->forks_sem = NULL;
    if (init_semaphores(all) != SUCCESS)
        return (FAIL);
    if (init_philos(all) != SUCCESS)
        return (FAIL);
    return (SUCCESS);
}

int parse_argv(char **av)
{
    int nums;
    int die;
    int eat;
    int sleep;

    nums = ft_atoi(av[1]);
    die = ft_atoi(av[2]);
    eat = ft_atoi(av[3]);
    sleep = ft_atoi(av[4]);
    if (nums < 2 || die < 0 || eat < 0 || sleep < 0)
        return (FAIL);
    return (SUCCESS);
}