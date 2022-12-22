/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/21 20:11:31 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

sem_t	*open_sem(char *file, int n)
{
	sem_t	*ret;

	ret = sem_open(file, O_CREAT, S_IRWXU, n);
	if (ret == SEM_FAILED)
		printf("Open Failed: %s\n", strerror(errno));
	return (ret);
}

void	open_sems(t_vars *vars)
{
	vars->sems[PRINT] = open_sem(SEM_PRINT, 1);
	vars->sems[FORKS] = open_sem(SEM_FORKS, vars->args[AMOUNT_PHILO]);
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
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	open_sems(vars);
	vars->print = ON;
	return (EXIT_SUCCESS);
}

int	init(int argc, char **argv, t_vars *vars)
{
	if (!ft_isnumberstab(argv))
		return (EXIT_FAILURE);
	if (init_vars(vars, argc, argv))
		return (EXIT_FAILURE);
	vars->start_time = get_time();
	return (EXIT_SUCCESS);
}
