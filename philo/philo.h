/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:42:00 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 03:20:49 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "struct.h"

int					ft_init(int argc, char **argv, struct s_table *table);
void				ft_create_threads(struct s_table *table, int i, int j);
void				ft_monitoring(struct s_table *table);

void				*ft_single_philo(void *ptr);
int					ft_philo_forks(struct s_philo *philo);
int					ft_philo_eat(struct s_philo *philo);
void				ft_sleep(struct s_philo *philo, int delay);

int					ft_arg_isnum(int argc, char **argv);
int					ft_atol(char *str);
int					ft_time(void);
void				ft_event_log(struct s_philo *philo, char *str);
int					ft_death_status(struct s_philo *philo);
void				ft_free(struct s_table *table, int i);

#endif
