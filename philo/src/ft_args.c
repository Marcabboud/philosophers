/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:42:19 by mabboud           #+#    #+#             */
/*   Updated: 2025/04/02 02:59:04 by mabboud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_arg_isnum(int argc, char **argv)
{
	int		i;
	char	*j;

	i = 1;
	while (i < argc)
	{
		j = argv[i];
		while (*j)
		{
			if (!((*j >= '0' && *j <= '9') || *j == '+'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atol(char *str)
{
	int				i;
	long long int	res;
	long long int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if ((res > INT_MAX) || (res * sign < INT_MIN))
			return (0);
	}
	return ((int)res * (int)sign);
}
