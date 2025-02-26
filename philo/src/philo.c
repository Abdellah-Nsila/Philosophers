/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/26 12:39:19 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//TODO 1: Parsing 4 or 5 arg all is numbers 
//TODO 2: Create the main struct for shared data, and one for each philo 
//TODO 3: Init the struct and validate the args after filing all data we need
//TODO 4: Test, Test, Teest, Teeeeesst, .... Debug, fix, optimize, repeat, ....


//TODO Go to DeepSeeck and github guide to understand the flow and structures of data:
// https://github.com/TommyJD93/Philosophers?tab=readme-ov-file#General_idea
// https://chat.deepseek.com/a/chat/s/ec8b053a-633d-4566-8f8c-fab85a9977fa


int	main(int ac, char **av)
{
	t_data	data;
	
	if (ft_check_parse(ac, av) == false)
		return (EXIT_FAILURE);
	ft_init_data(&data, ac, av);
	ft_create_threads(&data);
	ft_destroy(&data);
}
