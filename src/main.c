/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/11/30 11:59:41 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

number_of_philosophers: Le nombre de philosophes, mais aussi le nombre de
	fourchettes.

time_to_die (en millisecondes): Si un philosophe n’a pas commencé à manger
	time_to_die millisecondes après le début de son précédent repas ou depuis le
	début de la simulation, il meurt.

time_to_eat (en millisecondes): Le temps qu’un philosophe prend à manger.
	Pendant ce temps, un philosophe doit garder ses deux fourchettes.

time_to_sleep (en millisecondes): Le temps qu’un philosophe passe à dormir.

number_of_times_each_philosopher_must_eat (argument optionnel) : Si tous les
	philosophes ont mangé au moins number_of_times_each_philosopher_must_eat
	fois, la simulation prend fin. Si cet argument n’est pas spécifié, alors la
	simulation prend fin à la mort d’un philosophe.

memset, printf, malloc, free, write,
int usleep(useconds_t usec);

int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);

http://manpagesfr.free.fr/man/man3/pthread_create.3.html
int pthread_create(	pthread_t *restrict thread, 
					const pthread_attr_t *restrict attr,
					void *(*start_routine)(void *),
					void *restrict arg);

http://manpagesfr.free.fr/man/man3/pthread_detach.3.html
int pthread_detach(pthread_t thread);

http://manpagesfr.free.fr/man/man3/pthread_join.3.html
int pthread_join(pthread_t th, void **thread_return);  

http://manpagesfr.free.fr/man/man3/pthread_mutex_init.3.html
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex_t *mutex));
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);  pthread_mutex_init,

*/

#include "philosophers.h"

void	test_gettimeofday()
{
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);
	printf("sec: %ld, usec: %d\n", tv.tv_sec, tv.tv_usec);
	usleep(1);
	gettimeofday(&tv, &tz);
	printf("sec: %ld, usec: %d\n", tv.tv_sec, tv.tv_usec);
}

void	set_die(t_philo *philo)
{
		philo->status = DIE;
		manage_print_status(philo);
		pthread_mutex_lock(&philo->vars->m_die);
		philo->vars->die = 0x1;
		pthread_mutex_unlock(&philo->vars->m_die);
}

char	get_is_die(t_vars *vars)
{
	int	is_die;

	pthread_mutex_lock(&vars->m_die);
	is_die = vars->die;
	pthread_mutex_unlock(&vars->m_die);
	return (is_die);
}


# define LOCK 0x1
# define UNLOCK 0x2
void	forks(t_philo *philo, char todo)
{
	if (todo == LOCK)
	{
		pthread_mutex_lock(&philo->left_hand);
		pthread_mutex_lock(philo->right_hand);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_hand);
		pthread_mutex_unlock(philo->right_hand);
	}
}

void	take_fork(t_philo *philo)
{
	forks(philo, LOCK);
	philo->status = FORK;
	manage_print_status(philo);
}

void	eat(t_philo *philo)
{
	if (philo->next_eat <= get_time())
	{
		set_die(philo);
		return ;
	}
	philo->status = EATING;
	manage_print_status(philo);
	usleep(philo->vars->args[TIME_TO_EAT] * 1000);
	forks(philo, UNLOCK);
	philo->next_eat = get_time() + (u_int64_t)philo->vars->args[TIME_TO_DIE];
}

void	sleep_philo(t_philo *philo)
{
	philo->status = SLEEPING;
	manage_print_status(philo);
	usleep(philo->vars->args[TIME_TO_EAT] * 1000);
}

void	think(t_philo *philo)
{
	philo->status = THINKING;
	manage_print_status(philo);
}


void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	manage_print_status(philo);
	while (42)
	{
		take_fork(philo);
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	printf(RED "Hello Philosophers %llu!!!\n" RESET, get_time());
	t_vars	vars;
	t_philo	*philos;
	int		i;
	
	if ((argc < 5 || argc > 6) || init(argc, &argv[1], &vars, &philos))
		return(exit_mess());
	i = 0;
	while (i < vars.args[AMOUNT_PHILO])
	{
		pthread_create(&philos[i].thd, NULL, routine, &philos[i]);
		pthread_detach(philos[i].thd);
		i++;
	}
	while (!get_is_die(&vars))
		;
	free(philos);
	pthread_mutex_destroy(&vars.m_die);
	printf(RED "Bye Philosophers %llu!!!\n" RESET, get_time() - vars.start_time);
	return 0;
}
