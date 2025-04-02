/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:11:02 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 02:57:49 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

struct				s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	int				id;
	int				start;
	struct s_table	*table;
	int				last_meal;
	int				total_meal;
};

struct				s_table
{
	char			**argv;
	int				argc;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meals;
	struct s_philo	*philo;
	int				start_time;
	int				fail;
	int				died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	int				lock_init;
};

#endif