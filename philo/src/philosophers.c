/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:48:15 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/18 11:57:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_fuel_filling(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) arg;
	i = 0;
	while (i < 10)
	{	
		pthread_mutex_lock(&philo->mutex);
		philo->fuel += 25;
		printf("%sFuel filling: %d\n%s",BLU, philo->fuel, RESET);
		i++;
		pthread_mutex_unlock(&philo->mutex);
		pthread_cond_broadcast(&philo->cond);
		sleep(1);
	}
	return (NULL);
}

void	*ft_car(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->mutex);
	while (philo->fuel < 40)
	{
		printf("%sNo Fuel, Waiting...\n%s", RED, RESET);
		pthread_cond_wait(&philo->cond, &philo->mutex);
	}
	philo->fuel -= 40;
	printf("%sGot Fuel, Left: %d, Bye!\n%s", GRN, philo->fuel, RESET);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

void	ft_init_philo(t_philo *philo)
{
	srand(time(NULL));
	ft_bzero(philo, sizeof(t_philo));
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_cond_init(&philo->cond, NULL);
}

int	main()
{
	t_philo		philo;
	pthread_t	threads[THREADS];
	int			i = 0;

	ft_init_philo(&philo);
	while (i < 6)
	{
		if (i == 4 || i == 5)
		{
			if (pthread_create(&threads[0], NULL, &ft_fuel_filling, (void *) &philo) != 0)
				return (EXIT_FAILURE);
		}
		else
		{
			if (pthread_create(&threads[1], NULL, &ft_car, (void *) &philo) != 0)
				return (EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (pthread_join(threads[0], NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	pthread_mutex_destroy(&philo.mutex);
	pthread_cond_destroy(&philo.cond);
	return (0);
}

//! 2 Threads onr for filling fuel and one for car to get wait for fuel
// void	*ft_fuel_filling(void *arg)
// {
// 	t_philo	*philo;
// 	int		i;

// 	philo = (t_philo *) arg;
// 	i = 0;
// 	while (i < 10)
// 	{	
// 		pthread_mutex_lock(&philo->mutex);
// 		philo->fuel += 10;
// 		printf("Fuel: %d\n", philo->fuel);
// 		i++;
// 		pthread_mutex_unlock(&philo->mutex);
// 		pthread_cond_signal(&philo->cond);
// 		sleep(1);
// 	}
// 	return (NULL);
// }

// void	*ft_car(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) arg;
// 	pthread_mutex_lock(&philo->mutex);
// 	while (philo->fuel < 100)
// 	{
// 		printf("No Fuel, Waiting...\n");
// 		pthread_cond_wait(&philo->cond, &philo->mutex);
// 	}
// 	printf("Got Fuel: %d%%\n", philo->fuel);
// 	philo->fuel -= 100;
// 	pthread_mutex_unlock(&philo->mutex);
// 	return (NULL);
// }

// void	ft_init_philo(t_philo *philo)
// {
// 	srand(time(NULL));
// 	ft_bzero(philo, sizeof(t_philo));
// 	pthread_mutex_init(&philo->mutex, NULL);
// 	pthread_cond_init(&philo->cond, NULL);
// }

// int	main()
// {
// 	t_philo		philo;
// 	pthread_t	threads[THREADS];

// 	ft_init_philo(&philo);
	
// 	if (pthread_create(&threads[0], NULL, &ft_fuel_filling, (void *) &philo) != 0)
// 		return (EXIT_FAILURE);
// 	if (pthread_create(&threads[1], NULL, &ft_car, (void *) &philo) != 0)
// 		return (EXIT_FAILURE);
		
// 	if (pthread_join(threads[0], NULL) != 0)
// 		return (EXIT_FAILURE);
// 	if (pthread_join(threads[1], NULL) != 0)
// 		return (EXIT_FAILURE);
	
// 	pthread_mutex_destroy(&philo.mutex);
// 	pthread_cond_destroy(&philo.cond);
// 	return (0);
// }


//! Array sum using threads
// pthread_mutex_t	mutex;
// int	arr[THREADS] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// void	ft_init_philo(t_philo *philo)
// {
// 	srand(time(NULL));
// 	pthread_mutex_init(&philo->mutex, NULL);
// 	ft_bzero(philo, sizeof(t_philo));
// 	pthread_mutex_init(&philo->mutex, NULL);
// }

//? arr[i] = (rand() % (max - min)) + min;

// void	*ft_get_unique_num(void *arg)
// {
// 	int	i;

// 	pthread_mutex_lock(&mutex);
// 	i = *((int *)arg);
// 	printf("%d\n", arr[i]);
// 	free(arg);
// 	pthread_mutex_unlock(&mutex);
// 	return ((void *)(&arr[i]));
// }

// int	main()
// {
// 	t_philo		philo;
// 	pthread_t	threads[THREADS];
// 	int			i = 0;
// 	int			*temp = 0;
// 	int			sum = 0;

// 	ft_init_philo(&philo);
// 	while (i < THREADS)
// 	{	
// 		int *a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&threads[i], NULL, &ft_get_unique_num, (void *) a) != 0)
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < THREADS)
// 	{
// 		if (pthread_join(threads[i], (void **)&temp) != 0)
// 			return (EXIT_FAILURE);
// 		sum += *temp;
// 		i++;
// 	}
// 	printf("\nSum of Num: %d\n", sum);
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }

//! You 10 threades, an array of numbers, each tread, print a unique prime number
// pthread_mutex_t	mutex;
// int	arr[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// void	ft_init_philo(t_philo *philo)
// {
// 	srand(time(NULL));
// 	pthread_mutex_init(&philo->mutex, NULL);
// 	philo->score = 0;
// }

// void	*ft_get_unique_num(void *arg)
// {
// 	int	i;

// 	pthread_mutex_lock(&mutex);
// 	i = *((int *)arg);
// 	printf("%d\n", arr[i]);
// 	free(arg);
// 	pthread_mutex_unlock(&mutex);
// 	return (NULL);
// }

// int	main()
// {
// 	t_philo		philo;
// 	pthread_t	threads[THREADS];
// 	int			i = 0;

// 	pthread_mutex_init(&mutex, NULL);
// 	ft_init_philo(&philo);
	
// 	while (i < THREADS)
// 	{	
// 		// if (pthread_create(&threads[i], NULL, &ft_get_unique_num, (arr + i)) != 0)
// 		// 	return (EXIT_FAILURE);
// 		int *a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&threads[i], NULL, &ft_get_unique_num, (void *) a) != 0)
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < THREADS)
// 	{
// 		if (pthread_join(threads[i], NULL) != 0)
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }


//! Get the return of a function from tread
// void	*ft_random_num()
// {
// 	int	i;
// 	int	*res;

// 	res = malloc(sizeof(int));
// 	i = (rand() % 6) + 1;
// 	printf("Random Num in: %d\n", i);
// 	*res = i;
	
// 	return ((void *)res);
// }

// int	main()
// {
// 	t_philo		philo;
// 	pthread_t	threads[THREADS];
// 	int			i = 0;
// 	int			sum = 0;
// 	int			*res;

// 	ft_init_philo(&philo);
	
// 	while (i < THREADS)
// 	{	
// 		if (pthread_create(&threads[i], NULL, &ft_random_num, &philo) != 0)
// 			return (EXIT_FAILURE);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < THREADS)
// 	{
// 		if (pthread_join(threads[i], (void **)&res) != 0)
// 			return (EXIT_FAILURE);
// 		sum += *res;
// 		i++;
// 	}
// 	printf("\nSum of Random Num: %d\n", sum);
// 	pthread_mutex_destroy(&philo.mutex);
// 	return (0);
// }

//! Create multiple treads using loop 
// void	*ft_routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;
// 	int	i = 0;

// 	while (i < 1000000)
// 	{	
// 		pthread_mutex_lock(&philo->mutex);
// 		philo->score++;
// 		i++;
// 		pthread_mutex_unlock(&philo->mutex);
// 	}
// 	return (NULL);
// }

// void	ft_init_philo(t_philo *philo)
// {
// 	pthread_mutex_init(&philo->mutex, NULL);
// 	philo->score = 0;
// }

// int	main()
// {
// 	t_philo		philo;
// 	pthread_t	threads[THREADS];
// 	int			i = 0;

// 	ft_init_philo(&philo);
// 	// Create threads
// 	while (i < THREADS)
// 	{	
// 		if (pthread_create(&threads[i], NULL, &ft_routine, &philo) != 0)
// 			return (EXIT_FAILURE);
// 		printf("Thread Started Execution\n");
// 		i++;
// 	}
// 	// Join thrades
// 	i = 0;
// 	while (i < THREADS)
// 	{
// 		if (pthread_join(threads[i], NULL) != 0)
// 			return (EXIT_FAILURE);
// 		printf("Thread Finished Execution\n");
// 		i++;
// 	}
// 	printf("Score: %d\n", philo.score);
// 	pthread_mutex_destroy(&philo.mutex);
// 	return (0);
// }
