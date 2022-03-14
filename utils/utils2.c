/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:20:46 by gleal             #+#    #+#             */
/*   Updated: 2022/03/13 19:57:27 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*set_color(int	clr)
{
	colors newcolor;
	newcolor = clr % 11;
	if (newcolor == red)
		return (RED);
	else if (newcolor == grn)
		return (GRN);
	else if (newcolor == blu)
		return (BLU);
	else if (newcolor == mag)
		return (MAG);
	else if (newcolor == cyn)
		return (CYN);
	else if (newcolor == lred)
		return (LRED);
	else if (newcolor == lgrn)
		return (LGRN);
	else if (newcolor == yel)
		return (YEL);
	else if (newcolor == lblu)
		return (LBLU);
	else if (newcolor == lmag)
		return (LMAG);
	else
		return (LCYN);
}
