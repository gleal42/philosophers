/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:09:12 by gleal             #+#    #+#             */
/*   Updated: 2022/03/14 22:09:37 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_BONUS_H
# define COLORS_BONUS_H

# define LRED	"\e[1;31m"
# define LGRN	"\e[1;32m"
# define YEL   "\e[1;33m"
# define LBLU   "\e[1;34m"
# define RESET_COLOR "\e[m"

typedef enum c_colors{
	lred,
	lgrn,
	yel,
	lblu,
}			t_colors;

#endif
