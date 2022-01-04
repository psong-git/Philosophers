/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:11:41 by psong             #+#    #+#             */
/*   Updated: 2022/01/04 16:11:44 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_status *all)
{
	int	i;

	i = 0;
	all->forks_mutex = malloc(sizeof(pthread_mutex_t) * all->nums);
	if (!all->forks_mutex)
		return (FAIL);
	while (i < all->nums)
	{
		pthread_mutex_init(&(all->forks_mutex[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(all->write_mutex), NULL);
	pthread_mutex_init(&(all->end_metex), NULL);
	if (pthread_mutex_lock(&(all->end_metex)) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	init_philos(t_status *all)
{
	int	i;

	i = 0;
	all->philos = malloc(sizeof(t_philo) * all->nums);
	if (!all->philos)
		return (FAIL);
	while (i < all->nums)
	{
		all->philos[i].position = i;
		all->philos[i].lfork = i;
		all->philos[i].rfork = (i + 1) % all->nums;
		all->philos[i].eat_count = 0;
		all->philos[i].time_limit = 0;
		all->philos[i].all = all;
		pthread_mutex_init(&(all->philos[i].dining_mutex), NULL);
		i++;
	}
	return (SUCCESS);
}

int	init_all(t_status *all, int ac, char **av)
{
	all->nums = ft_atoi(av[1]);
	all->time_to_die = ft_atoi(av[2]);
	all->time_to_eat = ft_atoi(av[3]);
	all->time_to_sleep = ft_atoi(av[4]);
	all->time_to_start = 0;
	all->must_eat_count = 0;
	all->flag = MESSAGE_GO;
	if (ac == 6)
		all->must_eat_count = ft_atoi(av[5]);
	all->philos = NULL;
	all->forks_mutex = NULL;
	if (init_mutexes(all) != SUCCESS)
		return (FAIL);
	if (init_philos(all) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	parse_argv(char **av)
{
	int	nums;
	int	die;
	int	eat;
	int	sleep;

	nums = ft_atoi(av[1]);
	die = ft_atoi(av[2]);
	eat = ft_atoi(av[3]);
	sleep = ft_atoi(av[4]);
	if (nums < 1 || nums > 200 || die < 0 || eat < 0 || sleep < 0)
		return (FAIL);
	return (SUCCESS);
}
