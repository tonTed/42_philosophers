/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/11/30 11:03:23 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo **philos, t_vars *vars)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * vars->args[AMOUNT_PHILO]);
	i = 0;
	while(i < vars->args[AMOUNT_PHILO])
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].status = THINKING;
		(*philos)[i].vars = vars;
		pthread_mutex_init(&(*philos)[i].left_hand, PTHREAD_MUTEX_NORMAL);
		if (i)
			(*philos)[i].right_hand = &(*philos)[i - 1].left_hand;
		i++;
	}
	if (i > 1)
		(*philos)[0].right_hand = &(*philos)[i - 1].left_hand;
}

void	init_vars(t_vars *vars, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc - 1)
		vars->args[i++] = ft_atoi(*(argv)++);
	if (argc == 5)
		vars->args[NUMBER_OF_TIMES_EACH_PHILISOPHER_MUST_EAT] = -1;
	vars->die = 0x0;
	pthread_mutex_init(&vars->m_die, PTHREAD_MUTEX_NORMAL);
}

int	init(int argc, char **argv, t_vars *vars, t_philo **philos)
{
	int	i;

	if (!ft_isnumberstab(argv))
		return (EXIT_FAILURE);
	init_vars(vars, argc, argv);
	init_philo(philos, vars);
	vars->start_time = get_time();
	i = 0;
	while (i < vars->args[AMOUNT_PHILO])
	{
		(*philos)[i].next_eat = vars->start_time + vars->args[TIME_TO_DIE];
		i++;
	}
	return(EXIT_SUCCESS);
}
