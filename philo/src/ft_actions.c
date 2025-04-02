/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 03:14:51 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 03:20:49 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_philo_eat(struct s_philo *philo)
{
	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->died)
	{
		pthread_mutex_unlock(&philo->table->lock);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	philo->last_meal = ft_time();
	philo->total_meal++;
	pthread_mutex_unlock(&philo->table->lock);
	ft_event_log(philo, "is eating");
	ft_sleep(philo, philo->table->time_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (ft_death_status(philo));
}

int	ft_philo_forks(struct s_philo *philo)
{
	if (ft_death_status(philo) == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		ft_event_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		ft_event_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		ft_event_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		ft_event_log(philo, "has taken a fork");
	}
	if (ft_death_status(philo) == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	return (0);
}

int	ft_death_status(struct s_philo *philo)
{
	int	died;

	died = 0;
	pthread_mutex_lock(&philo->table->lock);
	died = philo->table->died;
	pthread_mutex_unlock(&philo->table->lock);
	return (died);
}

void	*ft_single_philo(void *ptr)
{
	struct s_philo	*philo;

	philo = (struct s_philo *)ptr;
	pthread_mutex_lock(philo->l_fork);
	ft_event_log(philo, "has taken a fork");
	ft_sleep(philo, philo->table->time_die * 2);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}
