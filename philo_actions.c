/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:12:29 by djareno           #+#    #+#             */
/*   Updated: 2025/11/17 10:54:53 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philosopher *philo)
{
	if (is_dead(philo->data))
		return ;
	if (!is_dead(philo->data))
		printf("[%d] %d is sleeping\n", get_time(philo->data), philo->id);
	ft_usleep(philo->data->time_to_sleep, philo);
	if (is_dead(philo->data))
		return ;
	if (!is_dead(philo->data))
		printf("[%d] %d is thinking\n", get_time(philo->data), philo->id);
}

void	getfork(t_philosopher *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		if (!is_dead(p->data))
			printf("[%d] %d has taken a fork\n", get_time(p->data), p->id);
		pthread_mutex_lock(p->left_fork);
		if (!is_dead(p->data))
			printf("[%d] %d has taken a fork\n", get_time(p->data), p->id);
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		if (!is_dead(p->data))
			printf("[%d] %d has taken a fork\n", get_time(p->data), p->id);
		pthread_mutex_lock(p->right_fork);
		if (!is_dead(p->data))
			printf("[%d] %d has taken a fork\n", get_time(p->data), p->id);
	}
}

void	eat1philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!is_dead(philo->data))
		printf("[%d] %d has taken a fork\n", get_time(philo->data), philo->id);
	ft_usleep(philo->data->time_to_die, philo);
	pthread_mutex_lock(philo->data->monitormx);
	philo->data->deadphilo = 1;
	pthread_mutex_unlock(philo->data->monitormx);
	pthread_mutex_unlock(philo->left_fork);
	return ;
}

void	eat(t_philosopher *philo)
{
	if (is_dead(philo->data))
		return ;
	if (philo->data->philo_num == 1)
	{
		eat1philo(philo);
		return ;
	}
	getfork(philo);
	pthread_mutex_lock(philo->data->monitormx);
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(philo->data->monitormx);
	if (!is_dead(philo->data))
		printf("[%ld] %d is eating\n", philo->last_meal, philo->id);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (is_dead(philo->data))
		return ;
	pthread_mutex_lock(philo->data->monitormx);
	philo->times_eat++;
	philo->data->total_times_eat++;
	if (philo->data->total_times_eat
		== philo->data->philo_num * philo->data->times_eat)
		philo->data->finished = 1;
	pthread_mutex_unlock(philo->data->monitormx);
}

void	amidead(t_philosopher *philo)
{
	pthread_mutex_lock(philo->data->monitormx);
	if (get_time(philo->data) - philo->last_meal >= philo->data->time_to_die)
		philo->data->deadphilo = 1;
	pthread_mutex_unlock(philo->data->monitormx);
}
