/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:01:29 by djareno           #+#    #+#             */
/*   Updated: 2025/11/19 10:55:40 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				times_eat;
	struct s_data	*data;
}					t_philosopher;
typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_num;
	int				start_time;
	int				times_eat;
	int				finished;
	int				total_times_eat;
	t_philosopher	*p;
	pthread_mutex_t	*monitormx;
	int				ready;
	pthread_mutex_t	*forks;
	int				deadphilo;
}		t_data;

int		ft_atoi(const char *n);
int		get_time(t_data *data);
void	eat(t_philosopher *philo);
void	philo_sleep(t_philosopher *philo);
void	amidead(t_philosopher *philo);
void	ft_usleep(int time_in_ms, t_philosopher *philo);
void	create_philosophers(t_data *data);
void	*philo_loop(void *arg);
int		valid_args(int argc, char **argv);
int		is_dead(t_data *data);
void	*philo_loop(void *arg);
#endif