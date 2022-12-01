/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:47:30 by tonted            #+#    #+#             */
/*   Updated: 2022/12/01 17:50:06 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_meals(t_philo *philos, t_vars *vars)
{
	int	i;
	int	meals;

	if (vars->args[MUST_EAT] == -1)
		return (0);
	i = 0;
	while (i < vars->args[AMOUNT_PHILO])
	{
		pthread_mutex_lock(&philos[i].m_meals);
		meals = philos[i].meals;
		pthread_mutex_unlock(&philos[i].m_meals);
		if (meals < vars->args[MUST_EAT])
			return (0);
		i++;
	}
	pthread_mutex_lock(&vars->mutexs[PRINT]);
	vars->print = OFF;
	pthread_mutex_unlock(&vars->mutexs[PRINT]);
	return (1);
}

void	monitoring(t_vars *vars, t_philo **philos)
{
	int			i;
	int			amount_philos;
	u_int64_t	time;

	amount_philos = vars->args[AMOUNT_PHILO];
	i = 0;
	while (42)
	{
		if (i == amount_philos)
			i = 0;
		pthread_mutex_lock(&(*philos)[i].m_next_eat);
		time = (*philos)[i].next_eat;
		pthread_mutex_unlock(&(*philos)[i].m_next_eat);
		if (time < get_time())
		{
			print_die(&(*philos)[i]);
			return ;
		}
		if (check_meals(&(**philos), vars))
			return ;
		i++;
	}
}
