/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/11/30 13:52:44 by tblanco          ###   ########.fr       */
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
	// manage_print_status(philo);
	while (42)
	{
		ph_take_fork(philo);
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

void print_bin(unsigned char value)
{
    for (int i = sizeof(char) * 7; i >= 0; i--)
        printf("%d", (value & (1 << i)) >> i );
    putc('\n', stdout);
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
		i++;
	}
	i = 0;
	while (i < vars.args[AMOUNT_PHILO])
	{
		pthread_join(philos[i].thd, NULL);
		i++;
	}
	free(philos);
	pthread_mutex_destroy(&vars.m_die);
	printf(RED "Bye Philosophers %llu!!!\n" RESET, get_time() - vars.start_time);
	return 0;
}
