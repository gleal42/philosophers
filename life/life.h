/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:57 by gleal             #+#    #+#             */
/*   Updated: 2022/03/11 19:16:05 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "philo.h"

void	*philolife(t_philo *philo);
void	philopickforks(t_philo *philo);
void	philoeat(t_philo *philo, t_fork *forkone, t_fork *forktwo);
void	philosleep(t_philo *philo);
void	philothink(t_philo *philo);

#endif
