/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eden <eden@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:24:16 by eden              #+#    #+#             */
/*   Updated: 2025/02/27 20:48:21 by eden             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	skip_spaces(const char *str, int i)
{
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

static int	check_sign(const char *str, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			return (-1);
		*i = *i + 1;
	}
	return (1);
}

static int	parse_digits(const char *str, int *i, long *result)
{
	int	digit;

	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (*result > (LONG_MAX - digit) / 10)
			return (-1);
		*result = *result * 10 + digit;
		*i = *i + 1;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		sign;

	result = 0;
	i = 0;
	i = skip_spaces(str, i);
	sign = check_sign(str, &i);
	if (sign == -1)
		return (-1);
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	if (parse_digits(str, &i, &result) == -1)
		return (-1);
	i = skip_spaces(str, i);
	if (str[i] != '\0' || result <= 0)
		return (-1);
	return ((int)result);
}
