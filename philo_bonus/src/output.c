/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:23:25 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/21 14:46:20 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_philo *philo, char *s)
{
	sem_wait(philo->vars->sems[PRINT]);
	if (philo->vars->print == ON)
		printf("%llu %d %s\n",
			get_time_from_beginning(philo->vars->start_time), philo->id, s);
	sem_post(philo->vars->sems[PRINT]);
}

void	print_die(t_philo *philo)
{
	sem_wait(philo->vars->sems[PRINT]);
	if (philo->vars->print == ON)
		printf("%llu %d %s\n",
			get_time_from_beginning(philo->vars->start_time),
			philo->id, PUTS_DIE);
	philo->vars->print = OFF;
	sem_post(philo->vars->sems[PRINT]);
}
