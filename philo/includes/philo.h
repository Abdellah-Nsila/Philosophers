/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 15:42:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "functions.h"
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
# endif

# define USAGE_MSG "philo: Usage: \
./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define INPUT_ERROR "philo: Invalid input: %s: \
Value must be a positive integer.\n"
# define TIME_ERROR "philo: Invalid input: %s: \
Value must be between 0 and 2147483647.\n"
# define PHILO_ERROR "philo: Invalid input: %s: \
there must be > 0.\n"
# define APT_ERROR "philo: Invalid input: %s: \
there must be >= 0.\n"

typedef enum e_state
{
	TAKING_FORK,
	THINKING,
	EATING,
	SLEEPING,
	DIED,
}	t_state;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	time_t			last_meal_time;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		monitor;
	int				num_of_philos;
	int				max_meals;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	stop_mutex;
	t_bool			stop;
}				t_data;

// Parsing
t_bool	ft_is_valid_number(char *str);
t_bool	ft_validate_arg(char **arr, int size);
t_bool	ft_check_parse(int ac, char **av);

// Threads
void	ft_create_threads(t_data *data);
void	ft_join_threads(t_data *data);

// Monitor
t_bool	ft_did_everyone_eat(t_data *data);
t_bool	ft_did_anyone_die(t_data *data);
void	*ft_monitor(void *arg);

// Actions
t_bool	ft_take_forks(t_data *data, t_philo *philo);
t_bool	ft_eat(t_data *data, t_philo *philo);
void	ft_think(t_philo *philo);
t_bool	ft_philo_routine(t_data *data, t_philo *philo);
void	*ft_start_simulation(void *arg);

// Time Utils
time_t	ft_get_time(void);
void	ft_usleep(t_data *data, time_t milliseconds);
void	ft_start_delay(time_t start_time);

// Utils
t_bool	ft_stop_simulation(t_data *data);
void	ft_print_data(t_data *data);

// Structs Utils
void	ft_init_data(t_data *data, int ac, char **av);
void	ft_destroy(t_data *data);

// Status
void	ft_colored_msg(time_t timestamp, int id, int type);
void	ft_format_msg(time_t timestamp, int id, int type);
void	ft_print_msg(t_data *data, t_philo *philo, int type);

#endif
