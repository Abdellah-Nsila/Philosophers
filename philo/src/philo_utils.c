/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:44:12 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/26 11:24:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(t_data *data, time_t milliseconds)
{
	time_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (ft_is_death(data))
			break;
		// printf("current: %ld,   start: %ld,  peack: %ld, diff: %ld\n", get_current_time(), start, milliseconds / 1000, (get_current_time() - start));	
		usleep(100);
	}
	return (0);
}

void	ft_colored_msg(time_t	timestamp, int id, char *msg, int type)
{
	if (type == TAKE_FORK)
		printf("%s%ld %d %s\n%s", WHT, timestamp, id, msg, RESET);
	else if (type == THINK)
		printf("%s%ld %d %s\n%s", BLU, timestamp, id, msg, RESET);
	else if (type == EAT)
		printf("%s%ld %d %s\n%s", GRN, timestamp, id, msg, RESET);
	else if (type == SLEEP)
		printf("%s%ld %d %s\n%s", MAG, timestamp, id, msg, RESET);
	else if (type == DIE)
		printf("%s%ld %d %s\n%s", RED, timestamp, id, msg, RESET);
}

void	ft_print_msg(t_data *data, t_philo *philo, char *msg, int type)
{
	time_t	timestamp;
	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_current_time() - data->start_time;
	// printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
	ft_colored_msg( timestamp, philo->id + 1, msg, type);
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

t_bool	ft_is_death(t_data	*data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (false);
}
