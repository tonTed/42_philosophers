/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:12:21 by tblanco           #+#    #+#             */
/*   Updated: 2022/11/18 10:23:05 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init(int argc, char **argv, t_vars *vars)
{
	int	i;

	if (!ft_isnumberstab(argv))
		return (EXIT_FAILURE);
	i = 0;
	while (i < argc - 1)
		vars->args[i++] = ft_atoi(*(argv)++);
	if (argc == 5)
		vars->args[NUMBER_OF_TIMES_EACH_PHILISOPHER_MUST_EAT] = -1;
	vars->start_time = get_time();
	vars->tab_philo = (t_philo *)malloc(sizeof(t_philo) * vars->args[AMOUNT_PHILO]);
	i = 0;
	while(i < vars->args[AMOUNT_PHILO])
	{
		vars->tab_philo[i].status = THINKING;
		i++;
		vars->tab_philo[i].id = i;
	}
	return(EXIT_SUCCESS);
}
