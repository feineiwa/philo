/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:57:19 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/24 13:32:39 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_atol(char *str)
{
	long	n;
	size_t	i;

	i = 0;
	n = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '\0')
		return (-2);
	if (str[i] == '-')
		return (-3);
	else if (str[i] == '+')
		i++;
	while (str[i] && is_digit(str[i]))
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	while (is_space(str[i]))
		i++;
	if (str[i])
		return (-4);
	if (n > INT_MAX)
		return (-5);
	return (n);
}

int	parse_input(t_data *data, char **av)
{
	data->philo_nbr = (int)ft_atol(av[1]);
	if (data->philo_nbr > PHILO_MAX)
		return (error_exit("Error\nThe philo number should be lower than 200"));
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat =	ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->total_meals = ft_atol(av[5]);
	else
		data->total_meals = -1;
	if (print_error(data))
		return (ERROR_FAILURE);
	return (0);
}
