/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:23:25 by tblanco           #+#    #+#             */
/*   Updated: 2022/11/30 13:16:22 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

# define PUTS_FORK "has taken a fork"
# define PUTS_EAT "is eating"
# define PUTS_SLEEP "is sleeping"
# define PUTS_THINK "is thinking"
# define PUTS_DIE "die"

// char	get_is_die(t_vars *vars);

void	print_status(t_philo *philo, char *s)
{
	printf("%llu %d %s\n", get_time_from_beginning(philo->vars->start_time), philo->id, s);
}

void	manage_print_status(t_philo *philo)
{
	// if (get_is_die(philo->vars))
	// 	exit(EXIT_SUCCESS);
	if (philo->status == SLEEPING)
		print_status(philo, PUTS_SLEEP);
	else if (philo->status == THINKING)
		print_status(philo, PUTS_THINK);
	else if (philo->status == EATING)
		print_status(philo, PUTS_EAT);
	else if (philo->status == DIE)
		print_status(philo, PUTS_DIE);
	else if (philo->status == FORK)
		print_status(philo, PUTS_FORK);
}
