/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errorendl_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:37:40 by tonted            #+#    #+#             */
/*   Updated: 2022/10/16 14:01:55 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_errormess_fd(int fd, char *message, int status)
{
	ft_putstr_fd(BRED, fd);
	ft_putstr_fd(message, fd);
	ft_putstr_fd(RESET, fd);
	return (status);
}
