/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:23:48 by kpires            #+#    #+#             */
/*   Updated: 2025/04/02 03:20:49 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free(struct s_table *table, int i)
{
	if (table->forks)
	{
		while (i >= 0)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i--;
		}
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philo)
		free(table->philo);
	if (table->lock_init)
		pthread_mutex_destroy(&table->lock);
}

int	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("philo: Error ft_timeofday");
		return (0);
	}
	return ((long long)(time.tv_sec * 1000) + (long long)(time.tv_usec / 1000));
}

void	ft_event_log(struct s_philo *philo, char *str)
{
	int	time;

	pthread_mutex_lock(&philo->table->lock);
	if (philo->table->died == 0)
	{
		time = ft_time() - philo->table->start_time;
		printf("%d %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->lock);
}

void	ft_sleep(struct s_philo *philo, int delay)
{
	int	start;

	start = ft_time();
	while (ft_time() - start < delay)
	{
		if (ft_death_status(philo) == 1)
			return ;
		usleep(500);
	}
}
