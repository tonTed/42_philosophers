/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:13:23 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/01 13:15:29 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

uint64_t	get_time_from_beginning(u_int64_t begin)
{
	return (get_time() - begin);
}

void	ft_usleep(u_int64_t time)
{
	int	time_at_beginning;

	time_at_beginning = get_time();
	while (get_time() - time_at_beginning < time)
		usleep(10);
}

int	exit_mess(void)
{
	return (ft_errormess_fd(STDERR_FILENO, "Error\n", EXIT_FAILURE));
}

void	clean_exit(t_vars *vars, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < vars->args[AMOUNT_PHILO])
	{
		pthread_mutex_destroy(&(*philos)[i].m_next_eat);
		pthread_mutex_destroy(&(*philos)[i].left_hand);
		pthread_mutex_destroy(&(*philos)[i].m_meals);
		i++;
	}
	free(*philos);
}
