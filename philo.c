/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:44:32 by djareno           #+#    #+#             */
/*   Updated: 2025/11/04 13:15:47 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *arg)
{
	int				x;
	t_philosopher	*philo;

	philo = (t_philosopher *) arg;
	x = 0;
	if (philo->id % 2 == 0)
		sleep (5);
	pthread_mutex_lock(philo->data->monitormx);
	if (philo->data->ready == 0)
	{
		pthread_mutex_unlock(philo->data->monitormx);
		pthread_mutex_lock(philo->data->monitormx);
		printf("[%d] %d has started\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(philo->data->monitormx);
	}
	return (0);
}

void	create_philos(t_data *data)
{
	t_philosopher	*p;
	pthread_mutex_t	*forks;
	int				x;

	p = malloc(sizeof(t_philosopher) * data->philo_num);
	forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	x = 0;
	while (x < data->philo_num)
	{
		pthread_mutex_init(&forks[x], NULL);
		x++;
	}
	x = 0;
	while (x < data->philo_num)
	{
		p[x].data = data;
		p[x].id = x;
		p[x].times_eat = 0;
		p[x].last_meal = 0;
		p[x].left_fork = forks[x];
		if (x < data->philo_num - 1)
			p[x].right_fork = forks[x + 1];
		else
			p[x].right_fork = forks[0];
		pthread_create(&p[x].thread, NULL, philo_loop, (void *)&p[x]);
		printf("%d is created\n", p[x].id);
		x++;
	}
	data->philosophers = p;
	data->forks = forks;
}

int	parse_args(t_data *data, int argc, char **argv)
{
	pthread_mutex_t	mutex;
	int				x;
	struct timeval	tv;

	if (argc < 5 || argc > 6)
		return (-1);
	pthread_mutex_init(&mutex, NULL);
	data->start_time = 0;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->monitormx = &mutex;
	if (argc == 6)
		data->time_to_eat = ft_atoi(argv[5]);
	else
		data->time_to_eat = -1;
	pthread_mutex_lock(data->monitormx);
	data->ready = -1;
	create_philos(data);
	data->ready = 0;
	pthread_mutex_unlock(data->monitormx);
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_usec;
	x = 0;
	while (x < data->philo_num)
	{
		pthread_join(data->philosophers[x].thread, NULL);
		pthread_mutex_lock(data->monitormx);
		printf("[%d] %d has stopped\n", get_time(data) , data->philosophers[x].id);
		pthread_mutex_unlock(data->monitormx);
		x++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			*data;

	data = malloc (sizeof(t_data));
	parse_args(data, argc, argv);
	return (0);
}
