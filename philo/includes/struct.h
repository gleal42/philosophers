/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:26 by gleal             #+#    #+#             */
/*   Updated: 2022/03/21 23:38:32 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/time.h>
# include <pthread.h>

typedef struct s_stats
{
	double	lastsleep;
	double	act;
	double	lastmeal;
	int		dead;
	int		ate;
}			t_stats;

typedef struct s_gen
{
	struct timeval	tval;
	double			tstlife;
	double			tendlife;
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
	struct timeval		tval;
	pthread_t			philo;
	t_stats				stat;
	int					nbr;
	char				*clr;
	pthread_mutex_t		*left;
	pthread_mutex_t		right;
	pthread_mutex_t		*death;
	pthread_mutex_t		*eat;
	pthread_mutex_t		*monitor;
}			t_philo;

typedef struct s_all
{
	t_gen			gen;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
}			t_all;

#endif
