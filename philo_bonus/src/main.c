/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/21 15:10:47 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <stdlib.h>
#include <sys/semaphore.h>

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;

	if ((argc < 5 || argc > 6) || init(argc, &argv[1], &vars, &philos))
		return (exit_mess());
	
	print_arguments(vars);
	// i = 0;
	// while (i < vars.args[AMOUNT_PHILO])
	// {
	// 	pthread_create(&philos[i].thd, NULL, routine, &philos[i]);
	// 	i++;
	// }
	// monitoring(&vars, &philos);
	// i = 0;
	// while (i < vars.args[AMOUNT_PHILO])
	// {
	// 	pthread_join(philos[i].thd, NULL);
	// 	i++;
	// }
	clean_exit(&vars, &philos);
	return (EXIT_SUCCESS);
}
