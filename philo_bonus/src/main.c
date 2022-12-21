/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/21 18:26:21 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	open_sems(t_vars *vars);
void	close_sems(t_vars *vars);

void	add_meal(t_philo *philo)
{
	if (philo->vars->args[MUST_EAT] == -1)
		return ;
	philo->meals++;
}

void	child(t_vars *vars, t_philo *philo){

	open_sems(vars);
	int i = 0;
	while (i < 5)
	{
		sem_wait(vars->sems[FORKS]);
		print_status(philo, PUTS_FORK);
		sem_wait(vars->sems[FORKS]);
		print_status(philo, PUTS_FORK);
		print_status(philo, PUTS_EAT);
		ft_usleep(vars->args[TIME_TO_EAT]);
		sem_post(vars->sems[FORKS]);
		sem_post(vars->sems[FORKS]);
		print_status(philo, PUTS_SLEEP);
		ft_usleep(vars->args[TIME_TO_SLEEP]);
		add_meal(philo);
		print_status(philo, PUTS_THINK);
		i++;
	}

}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;


	if ((argc < 5 || argc > 6) || init(argc, &argv[1], &vars, &philos))
		return (exit_mess());
	
	pid_t	pid[vars.args[AMOUNT_PHILO]];
	print_arguments(vars);
	i = 0;
	while (i < vars.args[AMOUNT_PHILO])
	{
		pid[i] = fork();
		if (!pid[i])
		{
			child(&vars, &philos[i]);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i++ < vars.args[AMOUNT_PHILO]){
		waitpid(pid[i - 1], NULL, 0);
	}
	
	// monitoring(&vars, &philos);
	// i = 0;
	// while (i < vars.args[AMOUNT_PHILO])
	// {
	// 	pthread_join(philos[i].thd, NULL);
	// 	i++;
	// }
	clean_exit(&vars, &philos);
	return (EXIT_SUCCESS);
}
