/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:38:59 by gmassin           #+#    #+#             */
/*   Updated: 2025/04/02 14:22:51 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_death(t_all *all, int i)
{
	long	now;
	long	lm;

	now = get_time_in_ms();
	lm = get_last_meal(&all->philos[i]);
	if ((now - lm) > all->data.time_to_die)
	{
		pthread_mutex_lock(&all->mutex_print);
		if (!get_stop(all))
		{
			printf("%ld %d %s\n", now - all->start_time,
				all->philos[i].id, DIE);
		}
		pthread_mutex_unlock(&all->mutex_print);
		set_stop(all, 1);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_all	*all;
	int		i;

	all = (t_all *)arg;
	while (!get_stop(all))
	{
		i = 0;
		while (i < all->data.num_philos && !get_stop(all))
		{
			if (check_death(all, i))
				break ;
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
