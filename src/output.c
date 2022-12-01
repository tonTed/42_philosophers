/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:23:25 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/01 07:57:42 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

# define PUTS_FORK "has taken a fork"
# define PUTS_EAT "is eating"
# define PUTS_SLEEP "is sleeping"
# define PUTS_THINK "is thinking"
# define PUTS_DIE "die"


void	print_status(t_philo *philo, char *s)
{
	printf("%llu %d %s\n", get_time_from_beginning(philo->vars->start_time), philo->id, s);
}

void	manage_print_status(t_philo *philo)
{
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
