/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 02:32:45 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 16:39:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	is_input_uint(char **stack_a_args, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!is_unsigned_integer(stack_a_args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_unsigned_integer(char *str)
{
	char	*strg;

	if (!str || !(*str))
		return (0);
	strg = str;
	if (*strg == '+' || *strg == '-')
		strg++;
	if (!is_all_digits(strg))
	{
		ft_putstr_fd("Error: Input not numeric\n", 2);
		return (0);
	}
	if (!is_within_lims(str))
	{
		ft_putstr_fd("Error: Input not within limits\n", 2);
		return (0);
	}
	return (1);
}

int	is_all_digits(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	is_within_lims(char *strg)
{
	long	nbr;

	while (*strg && *strg == '0')
		strg++;
	nbr = ft_atol(strg);
	if (nbr > INT32_MAX)
		return (0);
	if (nbr < 0)
		return (0);
	return (1);
}
