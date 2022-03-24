/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:26 by gleal             #+#    #+#             */
/*   Updated: 2022/03/24 20:45:00 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/time.h>
# include <pthread.h>

typedef struct s_stats
{
	double	lastmeal;
	int		ate;
	int		satisfied;
}			t_stats;

typedef struct s_gen
{
	double			tstlife;
	int				philonbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_freq;
	int				endlife;
}			t_gen;

typedef struct s_philo
{
	t_gen const			*gen;
	t_stats				stat;
	int					nbr;
	char				*clr;
	pthread_t			philo;
	pthread_mutex_t		right;
	pthread_mutex_t		*left;
	pthread_mutex_t		*satisfied;
	pthread_mutex_t		*finishsim;
	pthread_mutex_t		*lastmeal;
}			t_philo;

typedef struct s_all
{
	t_gen			gen;
	t_philo			*philos;
	pthread_mutex_t	satisfied;
	pthread_mutex_t	finishsim;
	pthread_mutex_t	lastmeal;
}			t_all;

#endif
