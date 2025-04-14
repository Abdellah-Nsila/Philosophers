
void	ft_colored_msg(time_t timestamp, int id, int type)
{
	char	*format;

	format = "%s%ld %d %s\n%s";
	if (type == TAKING_FORK)
		printf(format, BWHT, timestamp, id, "has taken a fork", RESET);
	else if (type == THINKING)
		printf(format, BBLU, timestamp, id, "is thinking", RESET);
	else if (type == EATING)
		printf(format, BGRN, timestamp, id, "is eating", RESET);
	else if (type == SLEEPING)
		printf(format, BMAG, timestamp, id, "is sleeping", RESET);
	else if (type == DIED)
		printf(format, BRED, timestamp, id, "died", RESET);
	// fflush(stdout);
}

void	ft_format_msg(time_t timestamp, int id, int type)
{
	char	*format;

	format = "%ld %d %s\n";
	if (type == TAKING_FORK)
		printf(format, timestamp, id, "has taken a fork");
	else if (type == THINKING)
		printf(format, timestamp, id, "is thinking");
	else if (type == EATING)
		printf(format, timestamp, id, "is eating");
	else if (type == SLEEPING)
		printf(format, timestamp, id, "is sleeping");
	else if (type == DIED)
		printf(format, timestamp, id, "died");
}

void ft_colored_msg(time_t timestamp, int id, int type)
{
	if (type == TAKING_FORK)
		ft_colored_write(BWHT, timestamp, id, "has taken a fork", RESET);
	else if (type == THINKING)
		ft_colored_write(BBLU, timestamp, id, "is thinking", RESET);
	else if (type == EATING)
		ft_colored_write(BGRN, timestamp, id, "is eating", RESET);
	else if (type == SLEEPING)
		ft_colored_write(BMAG, timestamp, id, "is sleeping", RESET);
	else if (type == DIED)
		ft_colored_write(BRED, timestamp, id, "died", RESET);
}

void	ft_colored_write(const char *color, long time, int id, const char *msg,
	const char *reset)
{
char	buffer[1024];
int		pos;

pos = 0;
copy_str_to_buffer(buffer, color, &pos);
copy_num_to_buffer(buffer, time, &pos);
buffer[pos++] = ' ';
copy_num_to_buffer(buffer, id, &pos);
buffer[pos++] = ' ';
copy_str_to_buffer(buffer, msg, &pos);
buffer[pos++] = '\n';
copy_str_to_buffer(buffer, reset, &pos);
write(1, buffer, pos);
}
