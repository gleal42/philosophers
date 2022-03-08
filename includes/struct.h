/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:26 by gleal             #+#    #+#             */
/*   Updated: 2022/03/08 18:11:57 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <sys/time.h>
#include <pthread.h>

typedef struct s_gen
{
	struct timeval st_t;
	int		nbr;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		eat_freq;
}			t_gen;

typedef struct s_philo
{
	const t_gen gen;
	struct timeval cur_t;
	pthread_t t;
	int	nbr;
}			t_philo;

typedef struct s_all
{
	t_gen	gen;
	t_philo philos;
}			t_all;

#endif
