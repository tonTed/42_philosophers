/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:06:02 by tonted            #+#    #+#             */
/*   Updated: 2022/10/16 14:38:26 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include "../libft/include/libft.h"

/* structs */

enum arguments {
	AMOUNT_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILISOPHER_MUST_EAT
};
typedef	struct philosophers
{
	char	status;
	int		last_eat;
}	t_philo;

typedef struct s_vars {
	t_philo	*tab_philo;
	int		arguments[5];
}	t_vars;

/* errors */
int	exit_mess(void);

/* Dev tools */
# define WHOAMI printf(GRN"Function "BMAG"%s"GRN" ran "BGRN"SUCCESSFULLY\n"RESET, __func__);
void	print_arguments(t_vars vars);

#endif
