/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:12:29 by djareno           #+#    #+#             */
/*   Updated: 2025/11/10 12:48:33 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philosopher *philo)
{
	printf("[%d] %d is sleeping\n", get_time(philo->data), philo->id);
	usleep(philo->data->time_to_sleep);
}

void	eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("[%d] %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("[%d] %d has taken a fork\n", get_time(philo->data), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("[%d] %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("[%d] %d has taken a fork\n", get_time(philo->data), philo->id);
	}
	printf("[%d] %d is eating\n", get_time(philo->data), philo->id);
	usleep(philo->data->time_to_eat);
	philo->last_meal = get_time(philo->data);
	philo->times_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	amidead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->data->monitormx);
	if (get_time(philo->data) - philo->last_meal >= philo->data->time_to_die)
	{
		printf("[%d] %d has died\n", get_time(philo->data), philo->id);
		philo->data->deadphilo = 1;
	}
	pthread_mutex_unlock(philo->data->monitormx);
}
