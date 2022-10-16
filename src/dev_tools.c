/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:38 by tonted            #+#    #+#             */
/*   Updated: 2022/10/16 14:35:12 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_arguments(t_vars vars)
{
	printf("[%d, %d, %d, %d, %d]\n",
		vars.arguments[0],
		vars.arguments[1],
		vars.arguments[2],
		vars.arguments[3],
		vars.arguments[4]
		);
}
