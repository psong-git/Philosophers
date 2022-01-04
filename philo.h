/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:12:36 by psong             #+#    #+#             */
/*   Updated: 2022/01/04 16:13:28 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

# define SUCCESS 0
# define FAIL 1
# define TRUE 1
# define FALSE 0
# define EAT 0
# define SLEEP 1
# define FORK 2
# define THINK 3
# define END 4
# define DEAD 5
# define MESSAGE_STOP 0
# define MESSAGE_GO 1
# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

typedef struct s_philo
{
	int					position;
	int					lfork;
	int					rfork;
	int					eat_count;
	size_t				time_limit;
	struct s_status		*all;
	pthread_mutex_t		dining_mutex;
}						t_philo;

typedef struct s_status
{
	int					nums;
	int					must_eat_count;
	int					flag;

	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				time_to_start;

	t_philo				*philos;
	pthread_mutex_t		*forks_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		end_metex;
}						t_status;

int			long_value(int sign);
int			ft_atoi(const char *str);
size_t		get_time(void);
void		ft_putnbr_fd(int nb, int fd);
size_t		ft_strlen(const char *str);
void		ft_putchar_fd(char c, int fd);
int			error_message(void);
int			clean_all(t_status *all);

int			init_mutexes(t_status *all);
int			init_philos(t_status *all);
int			init_all(t_status *all, int ac, char **av);
int			parse_argv(char **av);

void		exceptional(t_philo *philo);
void		get_forks(t_philo *philo);
void		put_down_forks(t_philo *philo);
void		eating(t_philo *philo);

char		*get_message(int type);
void		display_message(t_philo *philo, int type);
void		*must_eat_monitor(t_status *all);
#endif
