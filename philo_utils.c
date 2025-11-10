/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:50:26 by djareno           #+#    #+#             */
/*   Updated: 2025/11/10 12:52:48 by djareno          ###   ########.fr       */
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
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
}
