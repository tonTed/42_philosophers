/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:38 by tonted            #+#    #+#             */
/*   Updated: 2022/10/16 22:31:20 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_arguments(t_vars vars)
{
	printf("[%d, %d, %d, %d, %d]\n",
		vars.args[0],
		vars.args[1],
		vars.args[2],
		vars.args[3],
		vars.args[4]
		);
}
