/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:13:42 by eden              #+#    #+#             */
/*   Updated: 2025/04/02 14:03:09 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	allocate_resources(t_all *all)
{
	pthread_mutex_t	*tmp_forks;
	t_philo			*tmp_philos;

	tmp_forks = malloc(sizeof(pthread_mutex_t) * all->data.num_philos);
	if (!tmp_forks)
		return (1);
	tmp_philos = malloc(sizeof(t_philo) * all->data.num_philos);
	if (!tmp_philos)
	{
		free(tmp_forks);
		return (1);
	}
	all->forks = tmp_forks;
	all->philos = tmp_philos;
	return (0);
}

static int	init_mutexes(t_all *all)
{
	int	i;
	int	ret;

	i = 0;
	while (i < all->data.num_philos)
	{
		ret = pthread_mutex_init(&all->forks[i], NULL);
		if (ret != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&all->mutex_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&all->mutex_stop, NULL) != 0)
		return (1);
	return (0);
}

static int	init_philosophers(t_all *all)
{
	int	i;
	int	ret;

	i = 0;
	while (i < all->data.num_philos)
	{
		all->philos[i].id = i + 1;
		all->philos[i].left_fork = i;
		all->philos[i].right_fork = (i + 1) % all->data.num_philos;
		all->philos[i].last_meal = 0;
		all->philos[i].meals_eaten = 0;
		ret = pthread_mutex_init(&all->philos[i].meal_mutex, NULL);
		if (ret != 0)
			return (1);
		all->philos[i].all = all;
		i++;
	}
	return (0);
}

int	init_resources(t_all *all)
{
	int	res;

	res = init_mutexes(all);
	if (res != 0)
		return (1);
	res = init_philosophers(all);
	if (res != 0)
		return (1);
	return (0);
}
