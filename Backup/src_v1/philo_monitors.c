/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:15:31 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/28 15:08:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	ft_did_finish_eat(t_data *data, t_philo *philo)
{
	// printf("Philo: %d -> %d / %d\n", data->id, philo->meals_eaten, data->max_meals);
	sem_wait(&philo->meal_sem);
	if (philo->meals_eaten == data->max_meals)
	{
		sem_post(&philo->meal_sem);
		sem_wait(&philo->stop_sem);
		philo->stop_flag = true;
		sem_post(&philo->stop_sem);
		return (true);
	}
	sem_post(&philo->meal_sem);
	return (false);
}

t_bool	ft_is_died(t_data *data, t_philo *philo)
{
	time_t	current_time;
	time_t	timestamp;

	sem_wait(&philo->meal_sem);
	current_time = get_current_time();
	if ((current_time - philo->last_meal_time) > data->time_to_die)
	{
		sem_wait(&philo->stop_sem);
		philo->stop_flag = true;
		sem_post(&philo->stop_sem);
		sem_post(&philo->meal_sem);
		sem_wait(data->print_sem);
		timestamp = get_current_time() - data->global_start_time;
		ft_colored_msg(timestamp, data->id, DIED);
		// sem_post(data->print_sem);
		return (true);
	}
	sem_post(&philo->meal_sem);
	return (false);
}

void    *ft_philo_monitor(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data  *data = philo->data;

	ft_start_delay(data->global_start_time);
	while (true)
	{
		sem_wait(&philo->stop_sem);
		if (philo->stop_flag)
		{
			sem_post(&philo->stop_sem);
			break;
		}
		sem_post(&philo->stop_sem);
		if (ft_is_died(data, philo))
		{
			philo->exit_code = EXIT_FAILURE;
			break;
			int i = 0;
			while (i < data->num_of_philos)
			{
				sem_post(&philo->stop_sem);
				i++;
			}
		}
		if (data->max_meals != -1 && ft_did_finish_eat(data, philo))
		{
			philo->exit_code = EXIT_SUCCESS;
			break;
		}
	}
	return (NULL);
}

void	ft_check_others()
{
	
}

void	ft_kill_processes(t_data *data, pid_t pids[PHILO_MAX])
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

t_bool  ft_launch_monitor(t_data *data, pid_t pids[PHILO_MAX])
{
	int status, exit_code, remaining = data->num_of_philos;
	int success_count = 0;
	t_bool failure_found = false;

	while (remaining > 0)
	{
		pid_t wpid = waitpid(-1, &status, WNOHANG);
		if (wpid > 0)
		{
			remaining--;
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				if (exit_code == EXIT_FAILURE)
				{
					// printf("Child %d died\n", wpid);
					ft_kill_processes(data, pids);
					failure_found = true;
				}
				else if (exit_code == EXIT_SUCCESS)
					success_count++;
			}
		}
		if (success_count == data->num_of_philos)
		{
			// printf("All Child reach max meals\n");
			ft_kill_processes(data, pids);
			break;
		}
		// usleep(1000);
	}
	return (failure_found);
}
