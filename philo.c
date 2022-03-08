/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:31:43 by gleal             #+#    #+#             */
/*   Updated: 2022/03/07 21:09:07by gleal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*philolife(t_philo *philo)
{
	int i = 0;
	while (i < 5)
	{
		philoeat(philo);
		philosleep(philo);
		philothink(philo);
		i++;
	}
	return ((void *)0);
}

void	all(int argc, char **argv)
{
	t_all all;

	if (initlife(argc, argv, &all) != EXIT_SUCCESS)
		return ;
	pthread_create(&all.philos.t, NULL, (void *)&philolife, &all.philos);
	pthread_join(all.philos.t, NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		printf("Forgot arguments\n");
	else if (argc >= 5 && argc <= 6)
		all(argc, argv);
	else
		printf("Too many arguments\n");
}