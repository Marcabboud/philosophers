/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:51:41 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 03:16:03 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_init_philo(struct s_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(struct s_philo) * \
			(unsigned long)table->nb_philo);
	if (table->philo == NULL)
		return ((void)printf("malloc error\n"), 1);
	while (i < table->nb_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].l_fork = &table->forks[i];
		if (table->nb_philo == 1)
			table->philo[i].r_fork = NULL;
		else
			table->philo[i].r_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philo[i].last_meal = table->start_time;
		table->philo[i].total_meal = 0;
		i++;
	}
	return (0);
}

static int	ft_init_forks(struct s_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * (size_t)table->nb_philo);
	if (table->forks == NULL)
		return ((void)printf("malloc error\n"), 1);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			ft_free(table, i - 1);
			return ((void)printf("mutex error\n"), 1);
		}
		i++;
	}
	if (ft_init_philo(table) == 1)
		return ((void)ft_free(table, i - 1), 1);
	return (0);
}

static int	ft_init_fill(struct s_table *table, int argc, char **argv)
{
	table->fail = 0;
	table->argc = argc;
	table->argv = argv;
	table->nb_meals = -1;
	table->died = 0;
	table->start_time = 0;
	table->philo = NULL;
	table->forks = NULL;
	table->nb_philo = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->time_sleep = ft_atol(argv[4]);
	table->lock_init = 0;
	if (table->nb_philo < 1 || table->time_die < 1 || table->time_eat < 1 \
		|| table->time_sleep < 1)
		return ((void)printf("invalid argument\n"), 1);
	if (argc == 6)
	{
		table->nb_meals = ft_atol(argv[5]);
		if (table->nb_meals < 1)
			return ((void)printf("invalid argument\n"), 1);
	}
	return (0);
}

int	ft_init(int argc, char **argv, struct s_table *table)
{
	if (argc < 5 || argc > 6)
	{
		printf("Input should be: ./philo [number_of_philo] [time_to_die]");
		printf(" [time_to_eat] [time_to_sleep] [number_of_sims(optional)]\n");
		return (1);
	}
	if (ft_arg_isnum(argc, argv) == 1)
		return ((void)printf("invalid argument\n"), 1);
	if (ft_init_fill(table, argc, argv) == 1)
		return (1);
	if (pthread_mutex_init(&table->lock, NULL) != 0)
		return ((void)printf("mutex error\n"), 1);
	table->lock_init = 1;
	if (ft_init_forks(table) == 1)
		return (1);
	return (0);
}
