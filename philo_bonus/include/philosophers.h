/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:06:02 by tonted            #+#    #+#             */
/*   Updated: 2022/12/21 23:52:16 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdint.h>
# include <stdio.h>
# include "../libft/include/libft.h"
# include <sys/_types/_pid_t.h>
# include <sys/semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
 #include <signal.h>


/* status */
# define OFF 0x0
# define ON 0x1

/* outputs */
# define PUTS_FORK "has taken a fork"
# define PUTS_EAT "is eating"
# define PUTS_SLEEP "is sleeping"
# define PUTS_THINK "is thinking"
# define PUTS_DIE "die"

# define SEM_FORKS "sem_forks_6"
# define SEM_PRINT "sem_print_6"
# define SEM_DEAD "sem_dead_6"
# define SEM_FINISH "sem_finish_6"

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
	DIE,
	FINISH,
};

typedef pthread_mutex_t	t_mutex;

/* structs */
typedef struct s_vars {
	int			args[5];
	uint64_t	start_time;
	sem_t		*sems[4];
	char		die;
}	t_vars;

typedef struct s_philosophers {
	int			meals;
	uint64_t	next_eat;
	uint8_t		id;
	t_vars		*vars;
}	t_philo;

/* initialization */
int			init(int argc, char **argv, t_vars *vars);
void		init_philo(t_philo *philo, t_vars *vars, int i);
sem_t		*open_sem(char *file, int n);

/* monitoring */
void		monitoring(t_vars *vars, t_philo **philos);

/* utils */
uint64_t	get_time(void);
uint64_t	get_time_from_beginning(u_int64_t begin);
void		ft_usleep(u_int64_t time);
void		clean_exit(t_vars *vars);
void		clean_child(t_vars *vars);
int			exit_mess(void);
void		free_null(void *ptr);

/* outputs */
void		print_status(t_philo *philo, char *s);
void		print_die(t_philo *philo);

/* Dev tools */
void		print_arguments(t_vars vars);

#endif
