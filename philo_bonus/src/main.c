/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/22 00:29:04 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <stdlib.h>

sem_t	*open_sem(char *file, int n);

bool	is_died(t_philo philo, t_vars *vars)
{	
	sem_wait(vars->sems[DIE]);
	if (get_time() > philo.next_eat || vars->die)
	{
		print_die(&philo);
		vars->die = 1;
		sem_post(vars->sems[DIE]);
		return true;
	}
	sem_post(vars->sems[DIE]);
	return false;
}

void	take_forks(t_vars *vars, t_philo *philo)
{
	sem_wait(vars->sems[FORKS]);
	print_status(philo, PUTS_FORK);
	sem_wait(vars->sems[FORKS]);
	print_status(philo, PUTS_FORK);
}

int	eat(t_vars *vars, t_philo *philo)
{
	print_status(philo, PUTS_EAT);
	if (get_time() + vars->args[TIME_TO_EAT] > philo->next_eat)
	{
		ft_usleep(philo->next_eat - get_time());
		print_die(philo);
		return (EXIT_FAILURE);
	}
	else
	{
		philo->next_eat = get_time() + vars->args[TIME_TO_DIE];
		ft_usleep(vars->args[TIME_TO_EAT]);
	}
	sem_post(vars->sems[FORKS]);
	sem_post(vars->sems[FORKS]);
	return (EXIT_SUCCESS);
}

int	dodo(t_vars *vars, t_philo *philo)
{
	print_status(philo, PUTS_SLEEP);
	if (get_time() + vars->args[TIME_TO_SLEEP] > philo->next_eat)
	{
		ft_usleep(philo->next_eat - get_time());
		print_die(philo);
		return (EXIT_FAILURE);
	}
	else
		ft_usleep(vars->args[TIME_TO_SLEEP]);
	return (EXIT_SUCCESS);
}

void	think(t_vars *vars, t_philo *philo)
{
	(void) vars;
	
	print_status(philo, PUTS_THINK);
	if (philo->meals > 0)
		philo->meals--;
}

int	philo_process(t_vars *vars, int i)
{	
	t_philo	philo;

	init_philo(&philo, vars, i);
	while (philo.meals)
	{
		take_forks(vars, &philo);
		if (eat(vars, &philo))
			return (1);
		if (dodo(vars, &philo))
			return (1);
		think(vars, &philo);
	}
	sem_post(vars->sems[FINISH]);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	pid_t	*pids;
	int		i;
	int		status;

	if ((argc < 5 || argc > 6) || init(argc, &argv[1], &vars))
		return (exit_mess());
	pids = (pid_t *)malloc(sizeof(pid_t) * vars.args[AMOUNT_PHILO]);
	i = 0;
	while (i < vars.args[AMOUNT_PHILO])
	{
		pids[i] = fork();
		if (!pids[i])
		{
			status = philo_process(&vars, i);
			clean_child(&vars);
			exit(status);
		}
		i++;
	}
	i = 0;
	int	count = 0;
	while (count < vars.args[AMOUNT_PHILO])
	{
		waitpid(0, &status, 0);
		if (status)
		{
			while(i < vars.args[AMOUNT_PHILO])
			{
				kill(pids[i], SIGKILL);
				i++;
			}
			break;
		}
		sem_wait(vars.sems[FINISH]);
		count++;		
	}
	clean_exit(&vars);
	free_null(pids);
	return (EXIT_SUCCESS);
}
