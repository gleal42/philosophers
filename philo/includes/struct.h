/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:26 by gleal             #+#    #+#             */
/*   Updated: 2022/03/23 15:59:09 by gleal            ###   ########.fr       */
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
	int		satisfied;
	int		locked_right;
	int		locked_left;
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
	pthread_mutex_t		right;
	pthread_mutex_t		died;
	pthread_mutex_t		lastmeal;
	pthread_mutex_t		checkfork;
	pthread_mutex_t		*left;
	pthread_mutex_t		*satisfied;
}			t_philo;

typedef struct s_all
{
	t_gen			gen;
	t_philo			*philos;
	pthread_t		check_ate;
	pthread_t		check_dead;
	pthread_mutex_t	satisfied;
	pthread_mutex_t	finishtype;
	int				simfinished;
}			t_all;

#endif
