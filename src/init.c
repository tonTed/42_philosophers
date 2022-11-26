/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/11/26 17:00:03 by tblanco          ###   ########.fr       */
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
		(*philos)[i].id = i;
		(*philos)[i].status = THINKING;
		(*philos)[i].vars = vars;
		i++;
	}
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
	return(EXIT_SUCCESS);
}
