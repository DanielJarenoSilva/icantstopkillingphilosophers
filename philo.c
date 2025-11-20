/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:44:32 by djareno           #+#    #+#             */
/*   Updated: 2025/11/20 11:10:27 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_data			*data;
	int				i;

	data = (t_data *)arg;
	pthread_mutex_lock(data->monitormx);
	while (!data->deadphilo && data->finished != 1)
	{
		i = 0;
		while (i < data->philo_num && data->deadphilo != 1)
		{
			if (get_time(data) - data->p[i].last_meal >= data->time_to_die
				&& data->p[i].times_eat != data->times_eat)
			{
				printf("%d %d died\n", get_time(data), data->p[i].id);
				data->deadphilo = 1;
				return (pthread_mutex_unlock(data->monitormx), NULL);
			}
			i++;
		}
		if (data->deadphilo == 1)
			break ;
		pthread_mutex_unlock(data->monitormx);
		usleep(3000);
		pthread_mutex_lock(data->monitormx);
	}
	pthread_mutex_unlock(data->monitormx);
	return (NULL);
}

void	start_monitor(t_data *data)
{
	int				x;
	pthread_t		monitor_thread;

	x = 0;
	data->ready = -1;
	create_philosophers(data);
	pthread_mutex_lock(data->monitormx);
	data->ready = 0;
	pthread_mutex_unlock(data->monitormx);
	pthread_create(&monitor_thread, NULL, monitor, (void *)data);
	pthread_join(monitor_thread, NULL);
	x = 0;
	while (x < data->philo_num)
	{
		pthread_join(data->p[x].thread, NULL);
		x++;
	}
	pthread_mutex_destroy(data->monitormx);
	x = 0;
	while (x < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[x]);
		x++;
	}
}

int	parse_args(t_data *data, int argc, char **argv)
{
	pthread_mutex_t	mutex;
	struct timeval	tv;

	if (argc < 5 || argc > 6)
		return (-1);
	if (valid_args(argc, argv) == -1)
		return (-1);
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->finished = 0;
	data->total_times_eat = 0;
	data->monitormx = &mutex;
	data->deadphilo = 0;
	if (argc == 6)
		data->times_eat = ft_atoi(argv[5]);
	else
		data->times_eat = -1;
	start_monitor(data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			*data;

	data = malloc (sizeof(t_data));
	if (parse_args(data, argc, argv) == -1)
	{
		free(data);
		return (-1);
	}
	free (data->forks);
	free(data->p);
	free (data);
	return (0);
}
