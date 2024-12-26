/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:05:40 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/26 14:37:14 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_status status, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time() - philo->start_time;
	if (!is_dead(philo))
	{
		if (status == DIED)
			printf(RED "%zu %d %s\n" RESET, time, id, "died");
		else if (status == THINKING)
			printf(YELLOW "%zu %d %s\n" RESET, time, id, "is thinking");
		else if (status == EATING)
			printf(GREEN "%zu %d %s\n" RESET, time, id, "is eating");
		else if (status == TAKE_FORK)
			printf(CYAN "%zu %d %s\n" RESET, time, id, "has taken a fork");
		else if (status == SLEEPING)
			printf(MAGENTA "%zu %d %s\n" RESET, time, id, "is sleeping");
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error gettimeofday()\n");
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

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while (((get_current_time() - start) < milliseconds) && !is_dead(philo))
		usleep(500);
	return (0);
}
