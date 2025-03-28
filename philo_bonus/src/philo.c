/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:05:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/28 17:25:23 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data data;
	pid_t pids[PHILO_MAX];

	if (ft_check_parse(ac, av) == false)
		return (EXIT_FAILURE);
	ft_init_data(&data, ac, av);
	ft_launch_processes(&data, pids);
	if (ft_launch_monitor(&data, pids))
		ft_exit(&data, EXIT_FAILURE);
	else
		ft_exit(&data, EXIT_SUCCESS);
}
