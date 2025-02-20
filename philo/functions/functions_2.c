/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:10:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/20 15:10:20 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isdigit(int n)
{
	return (n >= 48 && n <= 57);
}

int	ft_isnumber(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_handle_max_case(int sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	unsigned long long	num;
	unsigned long long	max;

	i = 0;
	num = 0;
	sign = 1;
	max = 9223372036854775807;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && ft_isdigit((int)str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		if (num >= max)
			return (ft_handle_max_case(sign));
		i++;
	}
	return ((int)(num * sign));
}
