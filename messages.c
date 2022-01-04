/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:11:52 by psong             #+#    #+#             */
/*   Updated: 2022/01/04 16:13:52 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_message(int type)
{
	if (type == EAT)
		return (" is eating\n");
	else if (type == SLEEP)
		return (" is sleeping\n");
	else if (type == FORK)
		return (" has taken a fork\n");
	else if (type == THINK)
		return (" is thinking\n");
	else if (type == DEAD)
		return (" died\n");
	return (" unexpected result\n");
}

void	display_message(t_philo *philo, int type)
{
	char		*message;
	int			message_length;

	pthread_mutex_lock(&(philo->all->write_mutex));
	message = get_message(type);
	message_length = ft_strlen(message);
	if (type == END || type == DEAD)
		philo->all->flag = MESSAGE_STOP;
	if (type != END)
	{
		ft_putnbr_fd(get_time() - philo->all->time_to_start, 1);
		write(STD_OUT, " in_ms ", 7);
		ft_putnbr_fd(philo->position + 1, 1);
		write(STD_OUT, message, message_length);
	}
	if (philo->all->flag == MESSAGE_GO)
		pthread_mutex_unlock(&(philo->all->write_mutex));
}
