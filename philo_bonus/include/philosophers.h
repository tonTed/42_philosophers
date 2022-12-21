/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:06:02 by tonted            #+#    #+#             */
/*   Updated: 2022/12/21 18:23:06 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include "../libft/include/libft.h"
# include <sys/semaphore.h>
# include <sys/time.h>
# include <pthread.h>


/* status */
# define OFF 0x0
# define ON 0x1

/* outputs */
# define PUTS_FORK "has taken a fork"
# define PUTS_EAT "is eating"
# define PUTS_SLEEP "is sleeping"
# define PUTS_THINK "is thinking"
# define PUTS_DIE "die"

# define SEM_FORKS "sem_forks_5"
# define SEM_PRINT "sem_print_5"

enum {
	AMOUNT_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	MUST_EAT
};

enum {
	PRINT,
	FORKS,
};

typedef pthread_mutex_t	t_mutex;

/* structs */
typedef struct s_vars {
	int			args[5];
	uint64_t	start_time;
	sem_t		*sems[2];
	char		print;
}	t_vars;

typedef struct s_philosophers {
	t_vars		*vars;
	pthread_t	thd;
	uint8_t		id;
	sem_t		*m_next_eat;
	uint64_t	next_eat;
	sem_t		*m_meals;
	int			meals;
}	t_philo;

/* initialization */
int			init(int argc, char **argv, t_vars *vars, t_philo **philos);

/* monitoring */
void		monitoring(t_vars *vars, t_philo **philos);

/* utils */
uint64_t	get_time(void);
uint64_t	get_time_from_beginning(u_int64_t begin);
void		ft_usleep(u_int64_t time);
void		clean_exit(t_vars *vars, t_philo **philos);
int			exit_mess(void);

/* outputs */
void		print_status(t_philo *philo, char *s);
void		print_die(t_philo *philo);

/* Dev tools */
void		print_arguments(t_vars vars);
void		print_philos(t_philo **philos);

#endif
