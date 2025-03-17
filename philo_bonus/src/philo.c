/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/17 12:24:31 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// TODO this the base structures of project go ahead and make the child processes work with thread
// TODO you can use the mandatory part simulation for testing

//! You must fix:
// ./philo_bonus 200 120 60 60 -> STUCK
// ./philo_bonus 20 120 60 60  -> Fast die


int main(int ac, char **av)
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
