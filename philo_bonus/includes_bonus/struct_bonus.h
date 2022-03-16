/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 22:10:34 by gleal             #+#    #+#             */
/*   Updated: 2022/03/16 16:38:09 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <sys/time.h>
# include <pthread.h>

typedef struct s_stats
{
	double	lastsleep;
	double	act;
	double	lastmeal;
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
	pthread_t		checker;
}			t_gen;

typedef struct s_philo
{
	t_gen const			*gen;
	struct timeval		tval;
	t_stats				stat;
	int					nbr;
	char				*clr;
}			t_philo;

typedef struct s_all
{
	t_gen	gen;
	t_philo	philos;
}			t_all;

#endif
