/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:25 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/11 14:46:35 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"
# define THREADS 5
# define PLAYERS 20
# define SLOTS 5

sem_t	sem;

void	*routine(void *arg)
{
	int	*n;
	
	n = (int *)arg;
	printf("%sPlayers: %d Waiting in the login queue\n%s",BYEL, *n, RESET);
	sem_wait(&sem);
	printf("%sPlayers: %d Logged in\n%s",BGRN, *n, RESET);
	printf("%sPlayers: %d Palying now .....\n%s",BBLU, *n, RESET);
	usleep(500000);
	sem_post(&sem);
	printf("%sPlayers: %d Logged out\n%s",BRED, *n, RESET);
	free(arg);
	return (NULL);
}

int	main()
{
	int			i;
	int			*n;
	pthread_t	threads[PLAYERS];	

	i = 0;
	sem_init(&sem, 0, SLOTS);
	while (i < PLAYERS)
	{
		n = malloc(sizeof(int));
		*n = i + 1;
		pthread_create(&threads[i], NULL, &routine, n);
		i++;
	}
	i = 0;
	while (i < PLAYERS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	sem_destroy(&sem);
}
