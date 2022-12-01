/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/01 13:59:25 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_meal(t_philo *philo)
{
	if (philo->vars->args[MUST_EAT] == -1)
		return ;
	pthread_mutex_lock(&philo->m_meals);
	philo->meals++;
	pthread_mutex_unlock(&philo->m_meals);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
		usleep((philo->vars->args[TIME_TO_EAT] / 2) * 1000);
	while (42)
	{
		pthread_mutex_lock(&philo->left_hand);
		print_status(philo, PUTS_FORK);
		pthread_mutex_lock(philo->right_hand);
		print_status(philo, PUTS_FORK);
		print_status(philo, PUTS_EAT);
		pthread_mutex_lock(&philo->m_next_eat);
		philo->next_eat = get_time()
			+ (u_int64_t)philo->vars->args[TIME_TO_DIE];
		pthread_mutex_unlock(&philo->m_next_eat);
		ft_usleep(philo->vars->args[TIME_TO_EAT]);
		pthread_mutex_unlock(&philo->left_hand);
		pthread_mutex_unlock(philo->right_hand);
		print_status(philo, PUTS_SLEEP);
		ft_usleep(philo->vars->args[TIME_TO_SLEEP]);
		add_meal(philo);
		print_status(philo, PUTS_THINK);
	}
	return (NULL);
}

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
		{
			pthread_mutex_lock(&vars->mutexs[PRINT]);
			return ;
		}	
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
	i = 0;
	while (i < vars.args[AMOUNT_PHILO])
	{
		pthread_create(&philos[i].thd, NULL, routine, &philos[i]);
		i++;
	}
	monitoring(&vars, &philos);
	clean_exit(&vars, &philos);
	pthread_mutex_unlock(&vars.mutexs[PRINT]);
	pthread_mutex_destroy(&vars.mutexs[PRINT]);
	return (EXIT_SUCCESS);
}
