/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/23 10:31:19 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//*Usage:    ./philo philo_num time_die time_eat time_sleep <eat_repeat>
//*Example:  ./philo 5         800      200      200        <20>    (Last arg optional)
//TODO 1: Parsing 4 or 5 arg all is numbers 
//TODO 2: Create the main struct for shared data, and one for each philo 
//TODO 3: Init the struct and validate the args after fiiling all data we need
//TODO 4: 

t_bool	ft_is_valid_number(char *str)
{
	if (!ft_isnumber(str))
		return (false);
	return (true);
}

t_bool	ft_validate_arg(char **arr, int size)
{
	int	i;

	if (size < 4)
		return (false);
	i = 0;
	while (i < size)
	{
		if (!ft_is_valid_number(arr[i]))
			return (false);
		else if (i == 0 && ft_atol(arr[i]) > 200)
			return (false);
		else if (i == 4 && ft_atol(arr[i]) < 0)
			return (false);
		else if (i != 0 && i != 4 && ft_atol(arr[i]) <= 0)
			return (false);
		i++;
	}
	return (true);
}

// void	*ft_monitor_thread()
// {
	
// }

// void	*ft_philo_routine_thread()
// {
	
// }

// void	ft_create_threads(int ac, char **av)
// {
// 	t_data	data;
	
// }

void	ft_print_data(t_data *data)
{
	printf("num_philos: %d\n", data->num_philos);
	printf("time_to_die: %ld\n", data->time_to_die);
	printf("time_to_eat: %ld\n", data->time_to_eat);
	printf("time_to_sleep: %ld\n", data->time_to_sleep);
	printf("max_meals: %d\n", data->max_meals);
}

void	ft_init_data(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	data.num_philos = ft_atol(av[1]);
	data.time_to_die = ft_atol(av[2]);
	data.time_to_eat = ft_atol(av[3]);
	data.time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data.max_meals = ft_atol(av[5]);
	ft_print_data(&data);
}

//TODO Go to deepsheck and github guide to understand the flow and structures of data:
// https://github.com/TommyJD93/Philosophers?tab=readme-ov-file#General_idea
// https://chat.deepseek.com/a/chat/s/ec8b053a-633d-4566-8f8c-fab85a9977fa
int	main(int ac, char **av)
{
	// struct timeval	current_time;
	if (ft_validate_arg((av + 1), ac - 1))
		printf("%sValide args\n%s", GRN, RESET);
	else
		printf("%sError\n%s", RED, RESET);
	ft_init_data(ac, av);
	// gettimeofday(&current_time, NULL);
	// printf("second: %ld\n", current_time.tv_sec);
	// printf("microsecond: %ld\n", current_time.tv_usec);
}
