/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassin <gmassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:24:37 by eden              #+#    #+#             */
/*   Updated: 2025/04/03 15:00:16 by gmassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_required; // Si -1 illimité
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	meal_mutex;
	struct s_all	*all;
}	t_philo;

typedef struct s_all
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	long			start_time;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_stop;
	int				simulation_stop;
}	t_all;

/* ----------------------------- init_ressource ----------------------------- */
int		allocate_resources(t_all *all);
int		init_resources(t_all *all);

/* --------------- Parsing & Main --------------- */
int		parse_args(t_all *all, int argc, char **argv);

/* ----------------- Routine -------------------- */
void	*philosopher_routine(void *arg);

/* ----------------- Monitoring ----------------- */
void	*monitor_death(void *arg);

/* ----------------- Actions -------------------- */
void	set_last_meal(t_philo *philo, long time);
long	get_last_meal(t_philo *philo);
int		increment_meal(t_philo *philo);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

/* ---------------------------------- UTILS --------------------------------- */
long	get_time_in_ms(void);
int		get_stop(t_all *all);
void	set_stop(t_all *all, int val);
void	print_status(t_all *all, int id, const char *status);

/* --------------------------------- ft_atoi -------------------------------- */
int		ft_atoi(const char *str);

#endif