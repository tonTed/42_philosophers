/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:31:06 by tblanco           #+#    #+#             */
/*   Updated: 2022/11/30 14:22:08 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

# define LOCK 0x1
# define UNLOCK 0x2

static	void	forks(t_philo *philo, char todo)
{
	if (todo == LOCK)
	{
		pthread_mutex_lock(&philo->left_hand);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_hand);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->left_hand);
		pthread_mutex_unlock(philo->right_hand);
	}
}

void	set_die(t_philo *philo)
{
	philo->status = DIE;
	manage_print_status(philo);
}

void	is_die(t_philo *philo)
{
	if (philo->next_eat <= get_time())
	{
		set_die(philo);
		exit(EXIT_SUCCESS);
	}
}

void	ph_usleep(u_int64_t time)
{
	u_int64_t	times;

	times = time / 50;
	while (times)
	{
		usleep(50);
		times--;
	}
	if (time % 50)
		usleep(time % 50);
}

void	ph_take_fork(t_philo *philo)
{
	is_die(philo);
	forks(philo, LOCK);
}

void	ph_eat(t_philo *philo)
{
	philo->status = EATING;
	philo->next_eat = get_time() + (u_int64_t)philo->vars->args[TIME_TO_DIE];
	manage_print_status(philo);
	usleep(philo->vars->args[TIME_TO_EAT] * 1000);
	forks(philo, UNLOCK);
}

void	ph_sleep(t_philo *philo)
{
	philo->status = SLEEPING;
	manage_print_status(philo);
	usleep(philo->vars->args[TIME_TO_SLEEP] * 1000);
}

void	ph_think(t_philo *philo)
{
	philo->status = THINKING;
	manage_print_status(philo);
}