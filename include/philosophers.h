/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:06:02 by tonted            #+#    #+#             */
/*   Updated: 2022/11/26 16:59:48 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include "../libft/include/libft.h"
# include <sys/time.h>
# include <pthread.h>

# define SLEEPING 0x1
# define THINKING 0x2
# define EATING 0x4
# define DIE 0x8

enum {
	AMOUNT_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILISOPHER_MUST_EAT
};

typedef pthread_mutex_t	mutex_t;

/* structs */
typedef struct s_vars {
	int			args[5];
	uint64_t	start_time;
	int			status;
	char		die;
	mutex_t		m_die;
}	t_vars;

typedef struct s_philosophers {
	t_vars		*vars;
	pthread_t	thd;
	uint8_t		id;
	char		status;
	int			last_eat;
}	t_philo;

/* errors */
int	exit_mess(void);

/* initialization */
int	init(int argc, char **argv, t_vars *vars, t_philo **philos);

/* utils_time */
uint64_t	get_time();

/* Dev tools */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);
void	print_arguments(t_vars vars);

#endif
