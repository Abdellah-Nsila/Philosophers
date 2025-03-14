/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/14 10:16:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// TODO this the base structures of project go ahead and make the child processes work with thread
// TODO you can use the mandatory part simulation for testing

t_bool	ft_launch_monitor(t_data *data, pid_t pids[PHILO_MAX])
{
	int 	status;
	int 	exit_code;
	int		remaining;
	t_bool	failure_found;
	(void)pids;

	remaining = data->num_of_philos;
	failure_found = false;
	// Monitor child processes in a non-blocking loop.
	while (remaining > 0) {
		pid_t wpid = waitpid(-1, &status, WNOHANG);
		if (wpid > 0) {
			remaining--;
			if (WIFEXITED(status)) {
				exit_code = WEXITSTATUS(status);
				printf("%sChild PID %d exited with code %d\n%s",BWHT, wpid, exit_code, RESET);
				if (exit_code == EXIT_FAILURE)
				{
					printf("%sChild PID %d failed %d\n%s",BMAG, wpid, exit_code, RESET);
				}
			}
		}
		usleep(10000); // Sleep briefly to avoid busy-waiting.
	}
	return (failure_found);
}

int	main(int ac, char **av)
{
	int		i = 0;
	t_data	data;
	pid_t	pids[PHILO_MAX];

	if (ft_check_parse(ac, av) == false)
		return (EXIT_FAILURE);
	ft_init_data(&data, ac, av);
	ft_launch_processes(&data, pids);
	ft_launch_monitor(&data, pids);
	while (wait(NULL) > 0)
		;
	while (i < data.num_of_philos)
	{
		printf("PID[%d]: %d\n",i, pids[i]);
		i++;
	}
	ft_exit(&data, EXIT_SUCCESS);
}
