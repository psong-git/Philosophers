/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:20 by psong             #+#    #+#             */
/*   Updated: 2022/01/04 18:45:33 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*must_eat_monitor(t_status *all)
{
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	while (i < all->nums)
	{
		if (all->philos[i].eat_count < all->must_eat_count)
			flag += 1;
		i++;
	}
	if (flag == 0)
	{
		display_message(&(all->philos[0]), END);
		pthread_mutex_unlock(&(all->end_metex));
		return ((void *)SUCCESS);
	}
	return ((void *)FAIL);
}

void	*philo_monitor(void *philo_void)
{
	t_philo		*philo;

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

void	*dining(void *philo_void)
{
	t_philo		*philo;
	pthread_t	pthread;

	philo = (t_philo *)philo_void;
	philo->time_limit = get_time() + philo->all->time_to_die;
	if (pthread_create(&pthread, NULL, &philo_monitor, (void *)philo))
		return ((void *)FAIL);
	pthread_detach(pthread);
	while (42)
	{
		if (philo->all->must_eat_count > 0)
			if (philo->eat_count >= philo->all->must_eat_count)
				break ;
		get_forks(philo);
		eating(philo);
		put_down_forks(philo);
		display_message(philo, THINK);
	}
	return (NULL);
}

int	multi_threads(t_status *all)
{
	int			i;
	pthread_t	th;

	all->time_to_start = get_time();
	i = 0;
	while (i < all->nums)
	{
		if (pthread_create(&th, NULL, &dining, (void *)&all->philos[i]))
			return (FAIL);
		pthread_detach(th);
		i++;
		usleep(100);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_status	all;

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
