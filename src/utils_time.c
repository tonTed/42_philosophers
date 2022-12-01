/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:13:23 by tblanco           #+#    #+#             */
/*   Updated: 2022/12/01 07:55:18 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time()
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
	int	time_at_beginning;

	time_at_beginning = get_time();
	while (get_time() - time_at_beginning <= time)
		usleep(10);
}