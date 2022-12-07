/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/01 16:31:43 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo **philos, t_vars *vars)
{
	int	i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * vars->args[AMOUNT_PHILO]);
	i = 0;
	while (i < vars->args[AMOUNT_PHILO])
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].vars = vars;
		(*philos)[i].meals = 0;
		pthread_mutex_init(&(*philos)[i].m_next_eat, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&(*philos)[i].left_hand, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&(*philos)[i].m_meals, PTHREAD_MUTEX_NORMAL);
		if (i)
			(*philos)[i].right_hand = &(*philos)[i - 1].left_hand;
		i++;
	}
	if (i > 1)
		(*philos)[0].right_hand = &(*philos)[i - 1].left_hand;
	else
		(*philos)[0].right_hand = &(*philos)[0].left_hand;
}

int	init_vars(t_vars *vars, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		vars->args[i] = ft_atoi(*(argv)++);
		if (vars->args[i++] <= 0)
			return (EXIT_FAILURE);
	}
	if (argc == 5)
		vars->args[MUST_EAT] = -1;
	pthread_mutex_init(&vars->mutexs[PRINT], PTHREAD_MUTEX_NORMAL);
	vars->print = ON;
	return (EXIT_SUCCESS);
}

int	init(int argc, char **argv, t_vars *vars, t_philo **philos)
{
	int	i;

	if (!ft_isnumberstab(argv))
		return (EXIT_FAILURE);
	if (init_vars(vars, argc, argv))
		return (EXIT_FAILURE);
	init_philo(philos, vars);
	vars->start_time = get_time();
	i = 0;
	while (i < vars->args[AMOUNT_PHILO])
	{
		(*philos)[i].next_eat = vars->start_time + vars->args[TIME_TO_DIE];
		i++;
	}
	return (EXIT_SUCCESS);
}
