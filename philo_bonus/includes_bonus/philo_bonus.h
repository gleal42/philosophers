/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:09:56 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 01:34:10 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include "colors_bonus.h"
# include "struct_bonus.h"
# include "utils_bonus.h"
# include "life_bonus.h"

void	philosophers(int argc, char **argv);
void	check_finish(t_all *all);
void	create_philos(t_philo *philo);

#endif
