/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:25:44 by djareno           #+#    #+#             */
/*   Updated: 2025/11/14 10:46:35 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_data *data, pthread_mutex_t *forks)
{
	t_philosopher	*p;
	int				x;

	x = 0;
	p = malloc(sizeof(t_philosopher) * data->philo_num);
	while (x < data->philo_num)
	{
		p[x].data = data;
		p[x].id = x + 1;
		p[x].times_eat = 0;
		p[x].last_meal = get_time(data);
		p[x].left_fork = &forks[x];
		if (x < data->philo_num - 1)
			p[x].right_fork = &forks[x + 1];
		else
			p[x].right_fork = &forks[0];
		pthread_create(&p[x].thread, NULL, philo_loop, (void *)&p[x]);
		x++;
	}
	data->p = p;
}

void	create_philosophers(t_data *data)
{
	pthread_mutex_t	*forks;
	int				x;

	forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	x = 0;
	while (x < data->philo_num)
	{
		pthread_mutex_init(&forks[x], NULL);
		x++;
	}
	create_philo(data, forks);
	data->forks = forks;
}

int	is_dead(t_data *data)
{
	int	ret;

	pthread_mutex_lock(data->monitormx);
	ret = data->deadphilo;
	pthread_mutex_unlock(data->monitormx);
	return (ret);
}
