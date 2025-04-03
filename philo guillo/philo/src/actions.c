/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:03:34 by gmassin           #+#    #+#             */
/*   Updated: 2025/04/02 14:03:58 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_last_meal(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->meal_mutex);
}

long	get_last_meal(t_philo *philo)
{
	long	val;

	pthread_mutex_lock(&philo->meal_mutex);
	val = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (val);
}

int	increment_meal(t_philo *philo)
{
	int	val;

	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	val = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (val);
}

void	take_forks(t_philo *philo)
{
	t_all	*all;
	int		low;
	int		high;

	all = philo->all;
	if (philo->left_fork < philo->right_fork)
	{
		low = philo->left_fork;
		high = philo->right_fork;
	}
	else
	{
		low = philo->right_fork;
		high = philo->left_fork;
	}
	pthread_mutex_lock(&all->forks[low]);
	if (!get_stop(all))
		print_status(all, philo->id, FORK);
	pthread_mutex_lock(&all->forks[high]);
	if (!get_stop(all))
		print_status(all, philo->id, FORK);
}

void	release_forks(t_philo *philo)
{
	t_all	*all;
	int		low;
	int		high;

	all = philo->all;
	if (philo->left_fork < philo->right_fork)
	{
		low = philo->left_fork;
		high = philo->right_fork;
	}
	else
	{
		low = philo->right_fork;
		high = philo->left_fork;
	}
	pthread_mutex_unlock(&all->forks[low]);
	pthread_mutex_unlock(&all->forks[high]);
}
