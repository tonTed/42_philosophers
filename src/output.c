/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:23:25 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/01 08:56:30 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *s)
{
	printf("%llu %d %s\n", get_time_from_beginning(philo->vars->start_time), philo->id, s);
}

void	manage_print_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->mutexs[PRINT]);
	if (philo->status == EATING)
		print_status(philo, PUTS_EAT);
	else if (philo->status == SLEEPING)
		print_status(philo, PUTS_SLEEP);
	else if (philo->status == THINKING)
		print_status(philo, PUTS_THINK);
	else if (philo->status == DIE)
		print_status(philo, PUTS_DIE);
	pthread_mutex_unlock(&philo->vars->mutexs[PRINT]);
}
