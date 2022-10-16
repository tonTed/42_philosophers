/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:21:57 by tonted            #+#    #+#             */
/*   Updated: 2022/10/16 14:23:15 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_mess(void)
{
	return(ft_errormess_fd(STDERR_FILENO, "Error\n", EXIT_FAILURE));
}