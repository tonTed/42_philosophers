/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/01 08:49:24 by tonted           ###   ########.fr       */
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!(philo->id % 2))
		usleep((philo->vars->args[TIME_TO_EAT] / 2) * 1000);
	while (42)
	{
		ph_take_fork(philo);
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;
	
	if ((argc < 5 || argc > 6) || init(argc, &argv[1], &vars, &philos))
		return(exit_mess());
	i = 0;
	free(philos);
	return 0;
}
