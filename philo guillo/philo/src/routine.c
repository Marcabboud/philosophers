/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:04:25 by gmassin           #+#    #+#             */
/*   Updated: 2025/04/03 15:06:05 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_meals(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.num_philos)
	{
		pthread_mutex_lock(&all->philos[i].meal_mutex);
		if (all->philos[i].meals_eaten < all->data.meals_required)
		{
			pthread_mutex_unlock(&all->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&all->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

static void	handle_single_philo(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	pthread_mutex_lock(&all->forks[philo->left_fork]);
	print_status(all, philo->id, FORK);
	usleep(all->data.time_to_die * 1000);
	pthread_mutex_lock(&all->mutex_print);
	if (!get_stop(all))
	{
		printf("%ld %d %s\n",
			get_time_in_ms() - all->start_time, philo->id, DIE);
	}
	pthread_mutex_unlock(&all->mutex_print);
	pthread_mutex_unlock(&all->forks[philo->left_fork]);
	set_stop(all, 1);
}

static int	routine_eat(t_philo *philo)
{
	t_all	*all;
	int		meals;

	all = philo->all;
	take_forks(philo);
	if (get_stop(all))
	{
		release_forks(philo);
		return (1);
	}
	print_status(all, philo->id, EAT);
	set_last_meal(philo, get_time_in_ms());
	usleep(all->data.time_to_eat * 1000);
	meals = increment_meal(philo);
	release_forks(philo);
	if (all->data.meals_required != -1 && meals >= all->data.meals_required)
	{
		if (check_meals(all))
		{
			printf("DEBUG: All reached 7 at time %ld\n",
				get_time_in_ms() - all->start_time);
			set_stop(all, 1);
		}
	}
	return (0);
}

static void	routine_loop(t_philo *philo)
{
	t_all	*all;

	all = philo->all;
	while (!get_stop(all))
	{
		if (routine_eat(philo) == 1 || get_stop(all))
			break ;
		print_status(all, philo->id, SLEEP);
		usleep(all->data.time_to_sleep * 1000);
		if (get_stop(all))
			break ;
		print_status(all, philo->id, THINK);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_all	*all;

	philo = (t_philo *)arg;
	all = philo->all;
	set_last_meal(philo, get_time_in_ms());
	if (all->data.num_philos == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if ((philo->id % 2) == 0)
		usleep(1000);
	routine_loop(philo);
	return (NULL);
}
