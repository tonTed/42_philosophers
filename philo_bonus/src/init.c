/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/21 18:26:15 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <errno.h>
#include <string.h>

void	open_sems(t_vars *vars)
{
	vars->sems[PRINT] = sem_open(SEM_PRINT, O_CREAT, S_IRWXU, 1);
	vars->sems[FORKS] = sem_open(SEM_FORKS, O_CREAT, S_IRWXU,
		vars->args[AMOUNT_PHILO]);
	if (vars->sems[FORKS] == SEM_FAILED)
		printf("Open Failed: %s\n", strerror(errno));
	if (vars->sems[PRINT] == SEM_FAILED)
		printf("Open Failed: %s\n", strerror(errno));
}

void	close_sems(t_vars *vars)
{
	sem_close(vars->sems[PRINT]);
	sem_close(vars->sems[FORKS]);
}

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
		i++;
	}
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
	open_sems(vars);
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
	init_philo(philos, vars);
	vars->start_time = get_time();
	return (EXIT_SUCCESS);
}
