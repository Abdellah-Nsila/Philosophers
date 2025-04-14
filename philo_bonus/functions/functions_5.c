/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:56:54 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 14:46:19 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	ft_reverse_str(char *buffer, int *i)
{
	int		start;
	int		end;
	char	tmp;

	start = 0;
	end = *i - 1;
	while (start < end)
	{
		tmp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = tmp;
		start++;
		end--;
	}
}

static int	ft_itoa_buf(long n, char *buffer)
{
	int		i;
	int		is_neg;

	i = 0;
	is_neg = 0;
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	else if (n == 0)
		buffer[i++] = '0';
	while (n > 0)
	{
		buffer[i++] = '0' + (n % 10);
		n /= 10;
	}
	if (is_neg)
		buffer[i++] = '-';
	ft_reverse_str(buffer, &i);
	return (i);
}

static void	copy_str_to_buffer(char *buffer, const char *str, int *pos)
{
	int	i;

	i = 0;
	while (str[i])
		buffer[(*pos)++] = str[i++];
}

static void	copy_num_to_buffer(char *buffer, long num, int *pos)
{
	char	num_buf[64];
	int		len;
	int		i;

	len = ft_itoa_buf(num, num_buf);
	i = 0;
	while (i < len)
		buffer[(*pos)++] = num_buf[i++];
}

void	ft_write(long time, int id, const char *msg)
{
	char	buffer[1024];
	int		pos;

	pos = 0;
	copy_num_to_buffer(buffer, time, &pos);
	buffer[pos++] = ' ';
	copy_num_to_buffer(buffer, id, &pos);
	buffer[pos++] = ' ';
	copy_str_to_buffer(buffer, msg, &pos);
	buffer[pos++] = '\n';
	write(1, buffer, pos);
}
