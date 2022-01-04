/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:11 by psong             #+#    #+#             */
/*   Updated: 2022/01/04 18:31:15 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo)
{
	pthread_mutex_t	*lforks_mutex;
	pthread_mutex_t	*rforks_mutex;

	lforks_mutex = &(philo->all->forks_mutex[philo->lfork]);
	rforks_mutex = &(philo->all->forks_mutex[philo->rfork]);
	pthread_mutex_lock(lforks_mutex);
	display_message(philo, FORK);
	pthread_mutex_lock(rforks_mutex);
	display_message(philo, FORK);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_t	*lforks_mutex;
	pthread_mutex_t	*rforks_mutex;

	lforks_mutex = &(philo->all->forks_mutex[philo->lfork]);
	rforks_mutex = &(philo->all->forks_mutex[philo->rfork]);
	display_message(philo, SLEEP);
	pthread_mutex_unlock(rforks_mutex);
	pthread_mutex_unlock(lforks_mutex);
	usleep(philo->all->time_to_sleep * 1000);
}

void	eating(t_philo	*philo)
{
	pthread_mutex_t	*dining_mutex;

	dining_mutex = &(philo->dining_mutex);
	pthread_mutex_lock(dining_mutex);
	philo->time_limit = get_time() + philo->all->time_to_die;
	philo->eat_count++;
	display_message(philo, EAT);
	if (philo->all->must_eat_count > 0)
		must_eat_monitor(philo->all);
	usleep(philo->all->time_to_eat * 1000);
	pthread_mutex_unlock(dining_mutex);
}
