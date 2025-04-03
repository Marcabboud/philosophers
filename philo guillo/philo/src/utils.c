/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:20:08 by eden              #+#    #+#             */
/*   Updated: 2025/04/03 15:06:13 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

int	get_stop(t_all *all)
{
	int	val;

	pthread_mutex_lock(&all->mutex_stop);
	val = all->simulation_stop;
	pthread_mutex_unlock(&all->mutex_stop);
	return (val);
}

void	set_stop(t_all *all, int val)
{
	pthread_mutex_lock(&all->mutex_stop);
	all->simulation_stop = val;
	pthread_mutex_unlock(&all->mutex_stop);
}

void	print_status(t_all *all, int id, const char *status)
{
	long	time;

	pthread_mutex_lock(&all->mutex_print);
	if (!get_stop(all))
	{
		time = get_time_in_ms() - all->start_time;
		printf("%ld %d %s\n", time, id, status);
	}
	pthread_mutex_unlock(&all->mutex_print);
}
