/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/24 16:00:48 by abnsila          ###   ########.fr       */
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
	size_t	current_time;
	size_t	time_since_last_meal;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->meal_mutex);
			current_time = get_current_time();
			time_since_last_meal = current_time - data->philos[i].last_meal_time;
			pthread_mutex_unlock(&data->meal_mutex);

			if (time_since_last_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->death_mutex);
				data->someone_died = 1;
				ft_print_msg(data, &data->philos[i], "died", DIE);
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) == 0)
	{
		// Check death flag before taking the right fork
		if (ft_is_death(data))
		{
			pthread_mutex_unlock(philo->r_fork);
			return ;
		}
		ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);

		if (pthread_mutex_lock(philo->l_fork) == 0)
		{
			// Check death flag before taking the left fork
			if (ft_is_death(data))
			{
				pthread_mutex_unlock(philo->r_fork);
				pthread_mutex_unlock(philo->l_fork);
				return ;
			}
			ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);

			// Update last meal time
			pthread_mutex_lock(&data->meal_mutex);
			philo->last_meal_time = get_current_time();
			pthread_mutex_unlock(&data->meal_mutex);

			// Eating
			ft_print_msg(data, philo, "is eating", EAT);
			philo->meals_eaten++;
			usleep(data->time_to_eat * 1000);

			// Release forks
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
		}
		else
		{
			// Failed to get left fork: release right fork
			pthread_mutex_unlock(philo->r_fork);
		}
	}
}

// void ft_eat(t_data *data, t_philo *philo)
// {
//     // Lock right fork
//     pthread_mutex_lock(philo->r_fork);
//     if (ft_is_death(data)) {
//         pthread_mutex_unlock(philo->r_fork);
//         return;
//     }
//     ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);

//     // Lock left fork
//     pthread_mutex_lock(philo->l_fork);
//     if (ft_is_death(data)) {
//         pthread_mutex_unlock(philo->l_fork);
//         pthread_mutex_unlock(philo->r_fork);
//         return;
//     }
//     ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);

//     // Log eating and update last meal time
//     ft_print_msg(data, philo, "is eating", EAT);
//     philo->meals_eaten++;
//     pthread_mutex_lock(&data->meal_mutex);
//     philo->last_meal_time = get_current_time();
//     pthread_mutex_unlock(&data->meal_mutex);

//     if (ft_is_death(data)) {
//         // If death was detected after updating the meal time, unlock forks and return.
//         pthread_mutex_unlock(philo->l_fork);
//         pthread_mutex_unlock(philo->r_fork);
//         return;
//     }
//     // Simulate eating
//     usleep(data->time_to_eat * 1000);

//     // Release forks after eating
//     pthread_mutex_unlock(philo->l_fork);
//     pthread_mutex_unlock(philo->r_fork);
// }


void	*ft_philo_routine_thread(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_data	*data = philo->data;

	while (1)
	{
		//* Check death flag before attempting to eat
		if (ft_is_death(data))
			break ;
		ft_eat(data, philo);

		//* Check death flag after eating
		if (ft_is_death(data))
			break ;
		ft_print_msg(data, philo, "is sleeping", SLEEP);
		usleep(data->time_to_sleep * 1000);

		//* Check death flag after sleeping
		if (ft_is_death(data))
			break ;
		ft_print_msg(data, philo, "is thinking", THINK);
	}
	return (NULL);
}

void	ft_create_threads(t_data *data)
{
	int			i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].last_meal_time = get_current_time();
		if (i % 2 == 0)
		{
			data->philos[i].r_fork = &data->forks_mutex[i];
			data->philos[i].l_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
		}
		else
		{
			data->philos[i].l_fork = &data->forks_mutex[i];
			data->philos[i].r_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
		}
		pthread_create(&data->philos[i].thread, NULL, &ft_philo_routine_thread, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, &ft_monitor_thread, data);
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
