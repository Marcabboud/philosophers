/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:20:58 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 03:17:06 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	struct s_table	table;

	if (ft_init(argc, argv, &table) == 1)
		return (1);
	if (table.nb_philo == 1)
	{
		pthread_mutex_lock(&table.lock);
		table.start_time = ft_time();
		table.philo[0].last_meal = table.start_time;
		if (pthread_create(&table.philo[0].thread, NULL, \
			&ft_single_philo, &table.philo[0]) != 0)
			return ((void)printf("pthread error"), \
				(void)ft_free(&table, table.nb_philo - 1), 1);
		pthread_mutex_unlock(&table.lock);
		ft_monitoring(&table);
		pthread_join(table.philo[0].thread, NULL);
	}
	else
		ft_create_threads(&table, 0, 0);
	ft_free(&table, table.nb_philo - 1);
	if (table.fail == 1)
		return (1);
	return (0);
}
