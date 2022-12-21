/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/21 14:54:46 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>

void	init_philo(void)
{
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
	vars->sems[PRINT] = sem_open(SEM_PRINT, O_CREAT, S_IRWXO, 1);
	vars->sems[FORKS] = sem_open(SEM_FORKS, O_CREAT, S_IRWXO,
		vars->args[AMOUNT_PHILO]);
	vars->print = ON;
	return (EXIT_SUCCESS);
}

int	init(int argc, char **argv, t_vars *vars, t_philo **philos)
{
	(void)philos;

	if (!ft_isnumberstab(argv))
		return (EXIT_FAILURE);
	if (init_vars(vars, argc, argv))
		return (EXIT_FAILURE);
	vars->start_time = get_time();
	return (EXIT_SUCCESS);
}
