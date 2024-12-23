/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:05:40 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/23 16:31:10 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		write (1, "Error gettimeofday\n", 19);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_bool	is_dead(t_philo *philo)
{
	t_bool	dead;
	
	pthread_mutex_lock(&philo->data->dead_lock);
	dead = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (dead);
}

int	ft_usleep(size_t milliseconds)
{
	size_t start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}