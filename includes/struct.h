/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:26 by gleal             #+#    #+#             */
/*   Updated: 2022/03/13 18:17:57 by gleal            ###   ########.fr       */
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


typedef struct s_fork
{
	pthread_mutex_t fork;
	int 			using;
}			t_fork;

typedef struct s_philo
{
	t_gen const		*gen;
	struct timeval	tval;
	pthread_t		philo;
	t_stats			stat;
	int				nbr;
	char 			*clr;
	t_fork			*left;
	t_fork			own;
	t_fork			*right;
}			t_philo;

typedef struct s_all
{
	t_gen	gen;
	t_philo	*philos;
}			t_all;

#endif
