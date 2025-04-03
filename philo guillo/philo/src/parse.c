/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:01:08 by gmassin           #+#    #+#             */
/*   Updated: 2025/04/02 14:01:25 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(t_all *all, int argc, char **argv)
{
	all->data.num_philos = ft_atoi(argv[1]);
	all->data.time_to_die = ft_atoi(argv[2]);
	all->data.time_to_eat = ft_atoi(argv[3]);
	all->data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		all->data.meals_required = ft_atoi(argv[5]);
	}
	else
	{
		all->data.meals_required = -1;
	}
	if (all->data.num_philos <= 0 || all->data.time_to_die <= 0
		|| all->data.time_to_eat <= 0 || all->data.time_to_sleep <= 0)
	{
		printf("Invalid arguments.\n");
		return (1);
	}
	if (argc == 6 && all->data.meals_required <= 0)
	{
		printf("meals_required must be > 0 (or omitted).\n");
		return (1);
	}
	return (0);
}
