/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:23:53 by eden              #+#    #+#             */
/*   Updated: 2025/04/02 14:10:14 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_all(t_all *all, int argc, char **argv)
{
	int	res;

	all->simulation_stop = 0;
	res = parse_args(all, argc, argv);
	if (res != 0)
		return (1);
	res = allocate_resources(all);
	if (res != 0)
		return (1);
	res = init_resources(all);
	if (res != 0)
		return (1);
	all->start_time = get_time_in_ms();
	return (0);
}

static int	create_threads(t_all *all, pthread_t *monitor, pthread_t *threads)
{
	int	i;
	int	ret;

	i = 0;
	while (i < all->data.num_philos)
	{
		ret = pthread_create(&threads[i], NULL, philosopher_routine,
				(void *)&all->philos[i]);
		if (ret != 0)
			return (1);
		i++;
	}
	ret = pthread_create(monitor, NULL, monitor_death, all);
	if (ret != 0)
		return (1);
	return (0);
}

static void	join_threads(t_all *all, pthread_t monitor, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < all->data.num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

static void	cleanup(t_all *all, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < all->data.num_philos)
	{
		pthread_mutex_destroy(&all->forks[i]);
		pthread_mutex_destroy(&all->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&all->mutex_print);
	pthread_mutex_destroy(&all->mutex_stop);
	free(all->forks);
	free(all->philos);
	free(threads);
}

int	main(int argc, char **argv)
{
	t_all		all;
	pthread_t	monitor;
	pthread_t	*threads;
	int			res;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo n_philos t_die t_eat t_sleep [meals]\n");
		return (1);
	}
	res = init_all(&all, argc, argv);
	if (res != 0)
		return (1);
	threads = malloc(sizeof(pthread_t) * all.data.num_philos);
	if (!threads)
		return (1);
	res = create_threads(&all, &monitor, threads);
	if (res != 0)
	{
		free(threads);
		return (1);
	}
	join_threads(&all, monitor, threads);
	cleanup(&all, threads);
	return (0);
}
