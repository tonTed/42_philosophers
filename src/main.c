/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/11/26 20:18:04 by tonted           ###   ########.fr       */
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

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("philo: %d - %p\n", philo->id, &philo->vars->die);
	if (philo->id == 3)
		sleep(3);
	pthread_mutex_lock(&philo->vars->m_die);
	philo->vars->die = 0x1;
	pthread_mutex_unlock(&philo->vars->m_die);
	printf("philo: %d\n", philo->id);
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
	// pthread_detach(philos[3].thd);
	while (!vars.die)
		;
	// sleep(6);
	free(philos);
	pthread_mutex_destroy(&vars.m_die);
	printf(RED "Bye Philosophers %llu!!!\n" RESET, get_time() - vars.start_time);
	return 0;
}
