/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/08 17:39:11 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

int		initlife(int argc, char **argv, t_all *philo);
void	philoeat(t_all *philo);
void	philosleep(t_all *philo);
void	philothink(t_all *philo);

#endif
