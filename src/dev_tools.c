/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:38 by tonted            #+#    #+#             */
/*   Updated: 2022/12/01 09:06:29 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_arguments(t_vars vars)
{
	printf("[%d, %d, %d, %d, %d]\n",
		vars.args[0],
		vars.args[1],
		vars.args[2],
		vars.args[3],
		vars.args[4]
		);
}

void	print_philo(t_philo *philo)
{
	printf("philo: %d", philo->id);
	printf("\n\tleft: %p", (void *)&philo->left_hand);
	printf("\n\tright: %p", (void *)philo->right_hand);
	printf("\n\tvars: %p", (void *)philo->vars);
	printf("\n\n");
}

void	print_philos(t_philo **philos)
{
	int	i;
	int	amount_philo;

	i = 0;
	amount_philo = (*philos)[i].vars->args[AMOUNT_PHILO];
	while (i < amount_philo)
	{
		print_philo((&(*philos)[i]));
		i++;
	}
}
