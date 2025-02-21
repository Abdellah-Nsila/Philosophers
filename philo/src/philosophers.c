/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/21 17:41:30 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//*Usage:    ./philo philo_num time_die time_eat time_sleep <eat_repeat>
//*Example:  ./philo 5         800      200      200        <20>    (Last arg optional)
//TODO 1: Parsing 4 or 5 arg all is numbers 
//TODO 2: Create the main struct for shared data, and one for each philo 
//TODO 3: Init the struct and validate the args after fiiling all data we need
//TODO 4: 

t_bool	ft_is_valid_number(char *str)
{
	if (!ft_isnumber(str))
		return (false);
	return (true);
}

t_bool	ft_validate_arg(char **arr, int size)
{
	int	i;

	if (size < 4)
		return (false);
	i = 0;
	while (i < size)
	{
		if (!ft_is_valid_number(arr[i]))
			return (false);		
		else if (i == 0 && ft_atoi(arr[i]) > 200)
			return (false);
		else if (i == 4 && ft_atoi(arr[i]) < 0)
			return (false);
		else if (i != 0 && i != 4 && ft_atoi(arr[i]) <= 0)
			return (false);
		i++;
	}
	return (true);
}

//TODO Go to deepsheck and github guide to understand the flow and structures of data:
// https://github.com/TommyJD93/Philosophers?tab=readme-ov-file#General_idea
// https://chat.deepseek.com/a/chat/s/ec8b053a-633d-4566-8f8c-fab85a9977fa
int	main(int ac, char **av)
{
	struct timeval	current_time;
	if (ft_validate_arg((av + 1), ac - 1))
		printf("%sValide args\n%s", GRN, RESET);
	else
		printf("%sError\n%s", RED, RESET);
	gettimeofday(&current_time, NULL);
	printf("second: %ld\n", current_time.tv_sec);
	printf("microsecond: %ld\n", current_time.tv_usec);
}
