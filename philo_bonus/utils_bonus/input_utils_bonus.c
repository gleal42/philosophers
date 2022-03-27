/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 02:32:45 by gleal             #+#    #+#             */
/*   Updated: 2022/03/27 02:32:53 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

int	is_input_integer(char **stack_a_args)
{
	int	i;

	i = 0;
	if (!stack_a_args[0])
		return (0);
	while (stack_a_args[i])
	{
		if (!is_integer(stack_a_args[i]))
		{
			ft_putstr_fd("Error: Input not numeric\n", 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_integer(char *str)
{
	char	*strg;

	if (!str || !(*str))
		return (0);
	strg = str;
	if (*strg == '+' || *strg == '-')
		strg++;
	if (!is_all_digits(strg))
		return (0);
	if (!is_within_lims(strg))
		return (0);
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

	if (ft_strlen(strg) > 10)
		return (0);
	nbr = ft_atol(strg);
	if (nbr > INT32_MAX)
		return (0);
	if (nbr < INT32_MIN)
		return (0);
	return (1);
}
