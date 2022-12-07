/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/01 17:48:03 by tonted           ###   ########.fr       */
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

bool	ft_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->mutexs[PRINT]);
	if (philo->vars->print)
	{
		pthread_mutex_unlock(&philo->vars->mutexs[PRINT]);
		return (true);
	}
	pthread_mutex_unlock(&philo->vars->mutexs[PRINT]);
	return (false);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
		usleep((philo->vars->args[TIME_TO_EAT] / 2) * 1000);
	while (ft_continue(philo))
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
	i = 0;
	while (i < vars.args[AMOUNT_PHILO])
	{
		pthread_join(philos[i].thd, NULL);
		i++;
	}
	clean_exit(&vars, &philos);
	return (pthread_mutex_unlock(&vars.mutexs[PRINT]));
}
