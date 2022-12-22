/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:13:23 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/21 20:20:50 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <sys/semaphore.h>

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

uint64_t	get_time_from_beginning(u_int64_t begin)
{
	return (get_time() - begin);
}

void	ft_usleep(u_int64_t time)
{
	u_int64_t	time_at_beginning;

	time_at_beginning = get_time();
	while (get_time() - time_at_beginning < time)
		usleep(10);
}

int	exit_mess(void)
{
	return (ft_errormess_fd(STDERR_FILENO, "Error\n", EXIT_FAILURE));
}

void	free_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
