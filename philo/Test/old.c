#include "../includes/philo.h"

// void	*ft_monitor(void *arg)
// {
// 	t_data	*data = (t_data *)arg;
// 	int		i;
// 	time_t	current_time;
// 	time_t	time_since_last_meal;

// 	while (1)
// 	{
// 		i = 0;
// 		current_time = get_current_time();
// 		while (i < data->num_of_philos)
// 		{
// 			pthread_mutex_lock(&data->meal_mutex);
// 			// current_time = get_current_time();
// 			time_since_last_meal = current_time - data->philos[i].last_meal_time;

// 			if (time_since_last_meal >= data->time_to_die)
// 			{
// 				pthread_mutex_lock(&data->death_mutex);
// 				data->someone_died = 1;
// 				ft_print_msg(data, &data->philos[i], "died", DIE);
// 				pthread_mutex_unlock(&data->death_mutex);
// 				pthread_mutex_unlock(&data->meal_mutex);
// 				return (NULL);
// 			}
// 			i++;
// 			pthread_mutex_unlock(&data->meal_mutex);
// 		}
// 	}
// 	return (NULL);
// }

// void	ft_simulate_eating(t_data *data, t_philo *philo)
// {
// 	// Update last meal time
// 	pthread_mutex_lock(&data->meal_mutex);
// 	philo->last_meal_time = get_current_time();
// 	pthread_mutex_unlock(&data->meal_mutex);

// 	// Eating
// 	ft_print_msg(data, philo, "is eating", EAT);
// 	philo->meals_eaten++;
// 	ft_usleep(data->time_to_eat);
// }

// void	ft_eat(t_data *data, t_philo *philo)
// {
// 	if (pthread_mutex_lock(philo->r_fork) == 0)
// 	{
// 		if (ft_is_death(data))
// 		{
// 			pthread_mutex_unlock(philo->r_fork);
// 			return ;
// 			// return (void)pthread_mutex_unlock(philo->r_fork);
// 		}
// 		ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
// 		if (pthread_mutex_lock(philo->l_fork) == 0)
// 		{
// 			if (ft_is_death(data))
// 			{
// 				pthread_mutex_unlock(philo->r_fork);
// 				pthread_mutex_unlock(philo->l_fork);
// 				return ;
// 				// return (void)(pthread_mutex_unlock(philo->r_fork)
// 				// 				, pthread_mutex_unlock(philo->l_fork));
// 			}
// 			ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
// 			ft_simulate_eating(data, philo);
// 			pthread_mutex_unlock(philo->r_fork);
// 			pthread_mutex_unlock(philo->l_fork);
// 		}
// 		else
// 			pthread_mutex_unlock(philo->r_fork);
// 	}
// }

// void	*ft_philo_routine_thread(void *arg)
// {
// 	t_philo	*philo = (t_philo *)arg;
// 	t_data	*data = philo->data;

// 	while (1)
// 	{
// 		//* Check death flag before attempting to eat
// 		if (ft_is_death(data))
// 			break ;
// 		ft_eat(data, philo);

// 		//* Check death flag after eating
// 		if (ft_is_death(data))
// 			break ;
// 		ft_print_msg(data, philo, "is sleeping", SLEEP);
// 		ft_usleep(data->time_to_sleep);

// 		//* Check death flag after sleeping
// 		if (ft_is_death(data))
// 			break ;
// 		ft_print_msg(data, philo, "is thinking", THINK);
// 	}
// 	return (NULL);
// }

// void	ft_create_threads(t_data *data)
// {
// 	int			i;

// 	i = 0;
// 	data->start_time = get_current_time();
// 	while (i < data->num_of_philos)
// 	{
// 		data->philos[i].id = i;
// 		data->philos[i].data = data;
// 		data->philos[i].last_meal_time = data->start_time;
// 		if (i % 2 == 0)
// 		{
// 			data->philos[i].r_fork = &data->forks_mutex[i];
// 			data->philos[i].l_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
// 		}
// 		else
// 		{
// 			data->philos[i].l_fork = &data->forks_mutex[i];
// 			data->philos[i].r_fork = &data->forks_mutex[(i + 1) % data->num_of_philos];
// 		}
// 		pthread_create(&data->philos[i].thread, NULL, &ft_philo_routine_thread, &data->philos[i]);
// 		i++;
// 	}
// 	pthread_create(&data->monitor, NULL, &ft_monitor, data);
// }



// void	ft_eat(t_data *data, t_philo *philo)
// {
// 	if (philo->id % 2 == 1)
// 		ft_usleep(data, data->time_to_eat);
		
// 	if (pthread_mutex_lock(philo->r_fork) == 0)
// 	{
// 		if (ft_is_death(data))
// 		{
// 			pthread_mutex_unlock(philo->r_fork);
// 			return ;
// 			// return (void)pthread_mutex_unlock(philo->r_fork);
// 		}
// 		ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
// 		if (pthread_mutex_lock(philo->l_fork) == 0)
// 		{
// 			if (ft_is_death(data))
// 			{
// 				pthread_mutex_unlock(philo->r_fork);
// 				pthread_mutex_unlock(philo->l_fork);
// 				return ;
// 				// return (void)(pthread_mutex_unlock(philo->r_fork)
// 				// 				, pthread_mutex_unlock(philo->l_fork));
// 			}
// 			ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
// 			ft_simulate_eating(data, philo);
// 			ft_usleep(data, 100);
// 			pthread_mutex_unlock(philo->r_fork);
// 			pthread_mutex_unlock(philo->l_fork);
// 		}
// 		else
// 			pthread_mutex_unlock(philo->r_fork);
// 	}
// }

// ! Eat functions
// void	ft_eat(t_data *data, t_philo *philo)
// {
// 	if (philo->id % 2 == 1)
// 		ft_usleep(data, data->time_to_eat);
		
// 	if (pthread_mutex_lock(philo->first_fork) == 0)
// 	{
// 		if (ft_is_death(data))
// 		{
// 			pthread_mutex_unlock(philo->first_fork);
// 			return ;
// 			// return (void)pthread_mutex_unlock(philo->first_fork);
// 		}
// 		ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
// 		if (pthread_mutex_lock(philo-second_fork2) == 0)
// 		{
// 			if (ft_is_death(data))
// 			{
// 				pthread_mutex_unlock(philo->first_fork);
// 				pthread_mutex_unlock(philo->second_fork);
// 				return ;
// 				// return (void)(pthread_mutex_unlock(philo->first_fork)
// 				// 				, pthread_mutex_unlock(philo->fsecond_fork);
// 			}
// 			ft_print_msg(data, philo, "has taken a fork", TAKE_FORK);
// 			ft_simulate_eating(data, philo);
// 			pthread_mutex_unlock(philo->first_fork);
// 			pthread_mutex_unlock(philo->second_fork);
// 		}
// 		else
// 			pthread_mutex_unlock(philo->first_fork);
// 	}
// }

//! Init functions
// void	ft_init_philos(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->num_of_philos)
// 	{
// 		data->philos[i].id = i + 1;
// 		data->philos[i].data = data;
// 		data->philos[i].l_fork = &data->forks_mutex[i];
// 		if (i == 0)
// 			data->philos[i].r_fork
// 				= &data->forks_mutex[data->num_of_philos - 1];
// 		else
// 			data->philos[i].r_fork = &data->forks_mutex[i - 1];
// 	}
// }

// void ft_init_philos(t_data *data)
// {
// 	int i;
// 	int left_index;
// 	int right_index;

// 	i = 0;
// 	while (i < data->num_of_philos)
// 	{
// 		data->philos[i].id = i + 1;
// 		data->philos[i].data = data;
// 		left_index = i;
// 		right_index = (i + 1) % data->num_of_philos;
// 		if (left_index < right_index)
// 		{
// 			data->philos[i].first_fork = &data->forks_mutex[left_index];
// 			data->philos[i].second_fork = &data->forks_mutex[right_index];
// 		}
// 		else
// 		{
// 			data->philos[i].first_fork = &data->forks_mutex[right_index];
// 			data->philos[i].second_fork = &data->forks_mutex[left_index];
// 		}
// 		i++;
// 	}
// }