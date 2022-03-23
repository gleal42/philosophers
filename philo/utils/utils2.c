/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:20:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 21:49:50 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*set_color(int clr)
{
	t_colors	newcolor;

	newcolor = clr % 4;
	if (newcolor == lred)
		return (LRED);
	else if (newcolor == lgrn)
		return (LGRN);
	else if (newcolor == yel)
		return (YEL);
	else
		return (LBLU);
}

int	is_input_uint(char **stack_a_args, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (!is_unsigned_integer(stack_a_args[i]))
		{
			ft_putstr_fd("Error: Input not numeric\n", 1);
			return (0);
		}
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
		return (0);
	if (!is_within_lims(str))
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
	if (nbr < 0)
		return (0);
	return (1);
}
