/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:06:02 by tonted            #+#    #+#             */
/*   Updated: 2022/12/01 10:27:48 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include "../libft/include/libft.h"
# include <sys/time.h>
# include <pthread.h>

/* status */
# define SLEEPING 0x1
# define THINKING 0x2
# define EATING 0x4
# define DIE 0x8

/* outputs */
# define PUTS_FORK "has taken a fork"
# define PUTS_EAT "is eating"
# define PUTS_SLEEP "is sleeping"
# define PUTS_THINK "is thinking"
# define PUTS_DIE "die"

enum {
	AMOUNT_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILISOPHER_MUST_EAT
};

enum {
	PRINT
};

typedef pthread_mutex_t	t_mutex;

/* structs */
typedef struct s_vars {
	int			args[5];
	uint64_t	start_time;
	t_mutex		mutexs[1];
}	t_vars;

typedef struct s_philosophers {
	t_vars		*vars;
	pthread_t	thd;
	uint8_t		id;
	t_mutex		left_hand;
	t_mutex		*right_hand;
	t_mutex		m_next_eat;
	uint64_t	next_eat;
}	t_philo;

/* errors */
int			exit_mess(void);

/* initialization */
int			init(int argc, char **argv, t_vars *vars, t_philo **philos);

/* utils_time */
uint64_t	get_time(void);
uint64_t	get_time_from_beginning(u_int64_t begin);
void		ft_usleep(u_int64_t time);

/* outputs */
void		print_status(t_philo *philo, char *s);
void		print_die(t_philo *philo);

/* Dev tools */
void		print_arguments(t_vars vars);
void		print_philos(t_philo **philos);

#endif
