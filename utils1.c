/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:44 by psong             #+#    #+#             */
/*   Updated: 2022/01/04 16:12:45 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	clean_all(t_status *all)
{
	int	i;

	if (all->forks_mutex)
	{
		i = 0;
		while (i < all->nums)
			pthread_mutex_destroy(&(all->forks_mutex[i++]));
		free(all->forks_mutex);
		all->forks_mutex = NULL;
	}
	if (all->philos)
	{
		i = 0;
		while (i < all->nums)
		{
			pthread_mutex_destroy(&(all->philos[i].dining_mutex));
			i++;
		}
		free(all->philos);
	}
	pthread_mutex_destroy(&(all->write_mutex));
	pthread_mutex_destroy(&(all->end_metex));
	return (FAIL);
}

int	error_message(void)
{
	write(STD_ERR, "ERROR\n", 6);
	return (FAIL);
}
