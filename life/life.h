/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/10 22:26:48 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

int		initlife(int argc, char **argv, t_all *philo);
void	*philolife(t_philo *philo);
void	philoeat(t_philo *philo);
void	philosleep(t_philo *philo);
void	philothink(t_philo *philo);

#endif
