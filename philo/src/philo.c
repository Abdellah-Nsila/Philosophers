/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/23 16:41:22 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//TODO 1: Parsing 4 or 5 arg all is numbers 
//TODO 2: Create the main struct for shared data, and one for each philo 
//TODO 3: Init the struct and validate the args after fiiling all data we need
//TODO 4: 

void	*ft_monitor_thread(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;
	size_t	c;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->death_mutex);
			c = get_current_time() - data->philos[i].last_meal_time;
			printf("------- c: %ld --------\n", c);
			if (c >= data->time_to_die && data->someone_died == 0)
			{
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_mutex);
				ft_print_msg(data, &data->philos[i], "is died");
				return (NULL);
			}
			i++;
			pthread_mutex_unlock(&data->death_mutex);
		}
	}
}

void	ft_eat(t_data *data, t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) == 0)
	{	
		// ft_print_msg(data, philo, "has taken a right fork");
		if (pthread_mutex_lock(philo->l_fork) == 0)
		{
			// ft_print_msg(data, philo, "has taken a left fork");

			ft_print_msg(data, philo, "is eating");
			philo->meals_eaten++;
			pthread_mutex_lock(&data->meal_mutex);
			philo->last_meal_time = get_current_time();
			pthread_mutex_unlock(&data->meal_mutex);
			usleep(data->time_to_eat * 1000);
			
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
		}
		else
			pthread_mutex_unlock(philo->r_fork);
	}
}

void	*ft_philo_routine_thread(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;

	while (data->someone_died == 0)
	{
		ft_eat(data, philo);
		// ft_print_msg(data, philo, "is sleeping");
		usleep(data->time_to_sleep * 1000);
		// ft_print_msg(data, philo, "is thinking");
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	// Todo You have the init data for each philo, now simulate the eat, think, sleep ...
	while (i < data->num_of_philos + 1)
	{
		if (i == data->num_of_philos)
			pthread_create(&data->philos[i].thread, NULL, &ft_monitor_thread, &data->philos[i]);
		else
		{
			data->philos[i].id = i;
			data->philos[i].data = data;
			data->philos[i].last_meal_time = get_current_time();
			data->philos[i].r_fork = &data->forks_mutex[i];
			data->philos[i].l_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
			pthread_create(&data->philos[i].thread, NULL, &ft_philo_routine_thread, &data->philos[i]);
		}
		i++;
	}
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
	data->philos = ft_calloc(data->num_of_philos + 1, sizeof(t_philo));
	data->forks_mutex = ft_calloc(data->num_of_philos, sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->start_time = get_current_time();
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos + 1)
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

	printf("current time: %ld\n", get_current_time());
	if (ft_validate_arg((av + 1), ac - 1))
		printf("%sValide args\n%s", GRN, RESET);
	else
		printf("%sError\n%s", RED, RESET);
	ft_init_data(&data, ac, av);
	ft_create_threads(&data);
	ft_destroy(&data);
}
