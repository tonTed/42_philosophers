/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:13:23 by tblanco           #+#    #+#             */
/*   Updated: 2022/11/18 10:13:39 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time()
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((uint64_t)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}
