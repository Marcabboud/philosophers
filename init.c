/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [YourName] <youremail@example.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:42:16 by [YourName]        #+#    #+#             */
/*   Updated: 2025/02/XX XX:XX:XX by [YourName]       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialize_philosophers(struct s_table *table)
{
	int i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].total_meal = 0;
		table->philo[i].last_meal = table->start_time;
		table->philo[i].l_fork = &table->forks[i];
		if (table->nb_philo == 1)
			table->philo[i].r_fork = NULL;
		else
			table->philo[i].r_fork = &table->forks[(i + 1) % table->nb_philo];
		i++;
	}
}

static int	initialize_mutex(struct s_table *table)
{
	int i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			return (-3);
		}
		i++;
	}
	if (pthread_mutex_init(&table->lock, NULL) != 0)
	{
		i = table->nb_philo;
		while (--i >= 0)
			pthread_mutex_destroy(&table->forks[i]);
		return (-4);
	}
	return (0);
}

int	ft_init(int argc, char **argv, struct s_table *table)
{
	int ret;
	if (argc < 5 || argc > 6) {
		printf("philo: Usage: ./philo [number_of_philo] [time_to_die]");
		printf("[time_to_eat] [time_to_sleep] <number_of_meals>\n");
		printf("Required:[value] ~ Optional:<value>\n");
		return (1);
	}
	table->nb_philo = ft_atol(argv[1]); table->time_die = ft_atol(argv[2]); 
	table->time_eat = ft_atol(argv[3]); table->time_sleep = ft_atol(argv[4]);
	table->nb_meals = (argc == 6) ? ft_atol(argv[5]) : -1;
	if (table->nb_meals == 0 || table->nb_philo < 1 || table->time_die < 1 ||
	    table->time_eat < 1 || table->time_sleep < 1)
		return (printf("philo: Invalid argument\n"), 1);
	table->fail = table->died = 0; table->start_time = ft_gettime();
	table->philo = malloc(sizeof(struct s_philo) * table->nb_philo);
	if (!table->philo) return (printf("philo: Error malloc\n"), 1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks) return (printf("philo: Error malloc\n"), 1);
	ret = initialize_mutex(table);
	if (ret < 0) return (printf("philo: Error initializing mutexes\n"), 1);
	initialize_philosophers(table);
	return (0);
}
