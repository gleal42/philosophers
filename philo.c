/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:23:07 by gleal             #+#    #+#             */
/*   Updated: 2022/03/11 01:29:06 by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
		printf("Forgot arguments\n");
	else if (argc >= 5 && argc <= 6)
		philosophers(argc, argv);
	else
		printf("Too many arguments\n");
}

void	philosophers(int argc, char **argv)
{
	t_all	all;

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	ft_memset(&all.philos.stat, '\0', sizeof(t_stats));
	pthread_create(&all.philos.philo, NULL, (void *)&philolife, &all.philos);
	while (1)
	{
		if (all.philos.stat.dead
			|| (all.gen.eat_freq && all.philos.stat.ate == all.gen.eat_freq))
		{
			all.gen.endlife = 1;
			break ;
		}
	}
	pthread_join(all.philos.philo, NULL);
}
