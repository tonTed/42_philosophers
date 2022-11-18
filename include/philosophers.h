/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:06:02 by tonted            #+#    #+#             */
/*   Updated: 2022/10/16 22:57:03 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include "../libft/include/libft.h"
# include <sys/time.h>
# include <pthread.h>

enum {
	AMOUNT_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILISOPHER_MUST_EAT
};

enum {
	thrd_success,
	thrd_busy,
	thrd_error,
	thrd_nomem,
	thrd_timedout
};

/* structs */
typedef struct s_philosophers {
	pthread_t	thread;
	char		status;
	int			last_eat;
}	t_philo;

typedef struct s_vars {
	t_philo		*tab_philo;
	int			args[5];
	uint64_t	start_time;
}	t_vars;

# define SLEEPING 0x1
# define THINKING 0x2
# define EATING 0x4
# define DIE 0x8

/* errors */
int	exit_mess(void);

/* Dev tools */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);
void	print_arguments(t_vars vars);

#endif
