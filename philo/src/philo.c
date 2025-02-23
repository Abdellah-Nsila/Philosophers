/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/23 11:39:53 by abnsila          ###   ########.fr       */
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

void	*ft_philo_routine_thread(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	printf("Philosopher %d is thinking\n", philo->id);
	return (NULL);
}


void	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i;
		pthread_create(&data->philos[i].thread, NULL, &ft_philo_routine_thread, &data->philos[i]);
		i++;
	}
}

void	ft_print_data(t_data *data)
{
	printf("num_of_philos: %d\n", data->num_of_philos);
	printf("time_to_die: %ld\n", data->time_to_die);
	printf("time_to_eat: %ld\n", data->time_to_eat);
	printf("time_to_sleep: %ld\n", data->time_to_sleep);
	printf("max_meals: %d\n", data->max_meals);
}

void	ft_init_data(t_data *data, int ac, char **av)
{
	int		i;

	ft_bzero(data, sizeof(t_data));
	data->num_of_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->max_meals = ft_atol(av[5]);
	data->philos = ft_calloc(data->num_of_philos, sizeof(t_philo));
	data->forks_mutex = ft_calloc(data->num_of_philos, sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	ft_print_data(data);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philos);
	free(data->forks_mutex);
}

//TODO Go to DeepSeeck and github guide to understand the flow and structures of data:
// https://github.com/TommyJD93/Philosophers?tab=readme-ov-file#General_idea
// https://chat.deepseek.com/a/chat/s/ec8b053a-633d-4566-8f8c-fab85a9977fa
int	main(int ac, char **av)
{
	t_data	data;
	// struct timeval	current_time;
	if (ft_validate_arg((av + 1), ac - 1))
		printf("%sValide args\n%s", GRN, RESET);
	else
		printf("%sError\n%s", RED, RESET);
	ft_init_data(&data, ac, av);
	ft_create_threads(&data);
	ft_destroy(&data);
	// gettimeofday(&current_time, NULL);
	// printf("second: %ld\n", current_time.tv_sec);
	// printf("microsecond: %ld\n", current_time.tv_usec);
}
