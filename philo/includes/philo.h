/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/02 15:56:10 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "functions.h"
# include "colors.h"
# include <unistd.h>
# include <time.h>
#include <sys/time.h>
# include <pthread.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
# endif

# define PHILO_MAX 200

// typedef struct s_philo
// {
// 	pthread_mutex_t	mutex;
// 	pthread_cond_t	cond;
// 	int				fuel;
// 	int				*arr;
// 	int				score;
// 	pthread_mutex_t	mutex_arr[4];
// 	pthread_cond_t	cond_arr[4];
// 	int				stove[4];
// }				t_philo;

typedef enum s_MSG
{
	TAKE_FORK,
	THINK,
	EAT,
	SLEEP,
	DIE,
}			t_MSG;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	time_t			born_time;
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
	int				num_of_philos;  // Total philosophers
	int				max_meals;      // Optional: meals per philosopher
	time_t			time_to_die;    // Max time without eating (ms)
	time_t			time_to_eat;    // Eating duration (ms)
	time_t			time_to_sleep;  // Sleeping duration (ms)
	time_t			start_time;     // Start time for all threads (ms)
	pthread_mutex_t	*forks_mutex;   // Array of mutexes (forks)
	pthread_mutex_t	print_mutex;    // Protect logging
	pthread_mutex_t	meal_mutex;     // Protect last meal time
	pthread_mutex_t	death_mutex;    // Protect death flag
	pthread_mutex_t	stop_mutex;    	// Protect death flag
	int				someone_died;   // Global death flag
	int				stop;   		// Global stop flag
}				t_data;

// Parsing
t_bool	ft_is_valid_number(char *str);
t_bool	ft_validate_arg(char **arr, int size);
t_bool	ft_check_parse(int ac, char **av);

// Threads
void	ft_create_threads(t_data *data);

// Monitor
void	*ft_monitor(void *arg);

// Actions
void	sim_start_delay(time_t start_time);
void	ft_simulate_eating(t_data *data, t_philo *philo);
void	ft_eat(t_data *data, t_philo *philo);

// Utils
time_t	get_current_time(void);
void	ft_usleep(t_data *data, time_t milliseconds);
void	ft_print_msg(t_data *data, t_philo *philo, char *msg, int type);
void	ft_print_data(t_data *data);
t_bool	ft_is_death(t_data	*data);
t_bool	ft_is_all_eat(t_data *data);
t_bool	ft_stop_simulation(t_data *data);


// Structs Utils
void	ft_init_data(t_data *data, int ac, char **av);
void	ft_destroy(t_data *data);


#endif
