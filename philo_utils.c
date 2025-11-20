/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:50:26 by djareno           #+#    #+#             */
/*   Updated: 2025/11/17 13:10:18 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *n)
{
	int	x;
	int	signo;
	int	num;

	num = 0;
	x = 0;
	signo = 1;
	while (*n == 32 || (*n >= 9 && *n <= 13))
		n++;
	if (*n == '-')
		signo *= -1;
	if (*n == '+' || *n == '-')
		n++;
	while (*n >= '0' && *n <= '9')
	{
		num = num * 10 + (n[x] - '0');
		n++;
	}
	return (num * signo);
}

int	get_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time);
}

void	ft_usleep(int ms, t_philosopher *philo)
{
	int	start;

	start = get_time(philo->data);
	while (get_time(philo->data) - start < ms)
	{
		pthread_mutex_lock(philo->data->monitormx);
		if (philo->data->deadphilo)
		{
			pthread_mutex_unlock(philo->data->monitormx);
			break ;
		}
		pthread_mutex_unlock(philo->data->monitormx);
		usleep(500);
	}
}

int	valid_num(char	*num)
{
	int	x;

	x = 0;
	while (num[x])
	{
		if (num[x] < 48 || num[x] > 57)
			return (-1);
		x++;
	}
	return (0);
}

int	valid_args(int argc, char **argv)
{
	if (valid_num(argv[1]) == -1 || valid_num(argv[2]) == -1
		|| valid_num(argv[3]) == -1 || valid_num(argv[4]) == -1)
	{
		return (-1);
	}
	if (argc == 6)
	{
		if (valid_num(argv[5]) == -1)
		{
			return (-1);
		}
	}
	if (ft_atoi(argv[1]) == 0)
		return (-1);
	return (0);
}
