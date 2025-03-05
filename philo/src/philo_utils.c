/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/05 14:53:28 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_colored_msg(time_t timestamp, int id, char *msg, int type)
{
	char	*format;

	format = "%s%ld %d %s\n%s";
	if (type == TAKE_FORK)
		printf(format, WHT, timestamp, id, msg, RESET);
	else if (type == THINK)
		printf(format, BLU, timestamp, id, msg, RESET);
	else if (type == EAT)
		printf(format, GRN, timestamp, id, msg, RESET);
	else if (type == SLEEP)
		printf(format, MAG, timestamp, id, msg, RESET);
	else if (type == DIED)
		printf(format, RED, timestamp, id, msg, RESET);
}

t_bool	ft_is_death(t_data	*data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (false);
}

t_bool	ft_is_all_eat(t_data *data)
{
	int		i;
	t_bool	all_eaten;

	all_eaten = true;
	pthread_mutex_lock(&data->meal_mutex);
	for (i = 0; i < data->num_of_philos; i++)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			all_eaten = false;
			break ;
		}
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (all_eaten);
}

t_bool	ft_stop_simulation(t_data *data)
{
	t_bool	stop;

	if (data->max_meals != -1 && ft_is_all_eat(data))
		stop = true;
	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}


void	ft_usleep(t_data *data, time_t milliseconds)
{
	time_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (ft_stop_simulation(data))
			break;
		usleep(100);
	}
}

void	ft_print_msg(t_data *data, t_philo *philo, char *msg, int type)
{
	time_t	timestamp;
	time_t	current_time;

	if (ft_stop_simulation(data))
		return ;
	pthread_mutex_lock(&data->print_mutex);
	if (ft_stop_simulation(data))
		return ;
	current_time = get_current_time();
	timestamp = current_time - data->start_time;
	ft_colored_msg(timestamp, philo->id, msg, type);
	pthread_mutex_unlock(&data->print_mutex);
}


void	ft_print_data(t_data *data)
{
	printf("num_of_philos: %d\n", data->num_of_philos);
	printf("time_to_die: %ld\n", data->time_to_die);
	printf("time_to_eat: %ld\n", data->time_to_eat);
	printf("time_to_sleep: %ld\n", data->time_to_sleep);
	printf("max_meals: %d\n", data->max_meals);
}

