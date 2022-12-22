/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:04:19 by tonted            #+#    #+#             */
/*   Updated: 2022/12/21 20:10:54 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char **argv)
{
	t_vars	vars;

	if ((argc < 5 || argc > 6) || init(argc, &argv[1], &vars))
		return (exit_mess());
	
	print_arguments(vars);

	clean_exit(&vars);
	return (EXIT_SUCCESS);
}
