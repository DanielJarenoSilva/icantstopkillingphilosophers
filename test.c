/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:00:55 by djareno           #+#    #+#             */
/*   Updated: 2025/10/27 12:20:23 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*increment(void* arg)
{
	threadata *data;
	int		i;

	i = 0;
	data = (threadata*)arg;
	while (i < data->iteraciones)
	{
		pthread_mutex_lock(data->mutex);
		*(data->contador_compartido) += 1;
		sleep(2);
		pthread_mutex_unlock(data->mutex);
		i++;
	}
	printf("Hilo %d termino contador = %d\n", data->id, *(data->contador_compartido));
	pthread_exit(NULL);
}

int	main(void)
{
	pthread_t		hilos[10];
	pthread_mutex_t	mutex;
	int				cont;
	int				i;
	threadata		data[10];

	pthread_mutex_init(&mutex, NULL);
	cont = 0;
	i = 0;
	while (i < 10)
	{
		data[i].id = i;
		data[i].iteraciones = 20;
		data[i].contador_compartido = &cont;
		data[i].mutex  = &mutex;
		pthread_create(&hilos[i], NULL, increment, (void*)&data[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		pthread_join(hilos[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Final cont value: %d\n", cont);
	return (0);
}