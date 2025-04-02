/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:41:34 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 03:20:49 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_meal_quota(struct s_table *table)
{
	int	i;

	i = 0;
	if (table->nb_meals == -1)
		return (0);
	while (i < table->nb_philo)
	{
		if (table->philo[i].total_meal < table->nb_meals)
			return (0);
		i++;
	}
	table->died = 1;
	printf("All philosophers have eaten %d time\n", table->nb_meals);
	pthread_mutex_unlock(&table->lock);
	return (1);
}

static void	ft_routine(struct s_philo *philo)
{
	while (42)
	{
		if (ft_death_status(philo) == 1)
			return ;
		if (ft_philo_forks(philo) == 1)
			return ;
		if (ft_philo_eat(philo) == 1)
			return ;
		ft_event_log(philo, "is sleeping");
		ft_sleep(philo, philo->table->time_sleep);
		if (ft_death_status(philo) == 1)
			return ;
		ft_event_log(philo, "is thinking");
	}
}

static void	*ft_philosopher_thread(void *ptr)
{
	struct s_philo	*philo;
	int				fail_status;

	philo = (struct s_philo *)ptr;
	pthread_mutex_lock(&philo->table->lock);
	fail_status = philo->table->fail;
	pthread_mutex_unlock(&philo->table->lock);
	if (fail_status == 1)
		return (0);
	if (philo->id % 2 == 0)
		ft_sleep(philo, philo->table->time_eat);
	ft_routine(philo);
	return (0);
}

void	ft_monitoring(struct s_table *table)
{
	int	i;

	if (table->fail == 1)
		return ;
	while (1)
	{
		pthread_mutex_lock(&table->lock);
		i = 0;
		while (i < table->nb_philo)
		{
			if (ft_time() - table->philo[i].last_meal > table->time_die)
			{
				table->died = 1;
				printf("%d %d died\n", ft_time() - table->start_time, i + 1);
				pthread_mutex_unlock(&table->lock);
				return ;
			}
			i++;
		}
		if (ft_meal_quota(table) == 1)
			return ;
		pthread_mutex_unlock(&table->lock);
		usleep(5000);
	}
}

void	ft_create_threads(struct s_table *table, int i, int j)
{
	pthread_mutex_lock(&table->lock);
	while (i < table->nb_philo)
	{
		table->start_time = ft_time();
		table->philo[i].last_meal = table->start_time;
		if (pthread_create(&table->philo[i].thread, NULL, \
			&ft_philosopher_thread, &table->philo[i]) != 0)
		{
			table->fail = 1;
			printf("philo: Error insufficient resources to create thread\n");
			pthread_mutex_unlock(&table->lock);
			while (--i >= 0)
				pthread_join(table->philo[i].thread, NULL);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->lock);
	ft_monitoring(table);
	while (j < i)
	{
		if (pthread_join(table->philo[j].thread, NULL) != 0)
			printf("philo: Error failed to join thread\n");
		j++;
	}
}
