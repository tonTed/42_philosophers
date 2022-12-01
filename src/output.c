/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:23:25 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/01 10:01:23 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->vars->mutexs[PRINT]);
	printf("%llu %d %s\n", get_time_from_beginning(philo->vars->start_time),
		philo->id, s);
	pthread_mutex_unlock(&philo->vars->mutexs[PRINT]);
}

void	print_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->mutexs[PRINT]);
	printf("%llu %d %s\n", get_time_from_beginning(philo->vars->start_time),
		philo->id, PUTS_DIE);
}
