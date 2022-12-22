/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:03:00 by tonted            #+#    #+#             */
/*   Updated: 2022/12/21 23:22:41 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	clean_child(t_vars *vars)
{
	sem_close(vars->sems[FORKS]);
	sem_close(vars->sems[PRINT]);
	sem_close(vars->sems[DIE]);
	sem_close(vars->sems[FINISH]);
}

void	clean_exit(t_vars *vars)
{
	clean_child(vars);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_FINISH);
}