/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:26 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/23 17:53:08 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static t_bool	check_all_full(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos->data->total_meals == -1)
		return (FALSE);
	while (i < philos->data->philo_nbr)
	{
		pthread_mutex_lock(&philos[i].data->meal_lock);
		if (philos[i].eaten_count >= philos->data->total_meals)
			finished_eating++;
		pthread_mutex_unlock(&philos[i].data->meal_lock);
		i++;
	}
	if (finished_eating == philos->data->philo_nbr)
	{
		pthread_mutex_lock(&philos->data->dead_lock);
		philos->data->dead_flag = TRUE;
		pthread_mutex_unlock(&philos->data->dead_lock);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_if_dead(t_philo *philos)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < philos->data->philo_nbr)
	{
		current_time = get_current_time(philos->data);
		pthread_mutex_lock(&philos[i].data->meal_lock);
		if ((current_time - philos[i].last_meal >= philos->data->time_to_die)
			&& philos[i].eating == FALSE)
		{
			print_status(DIED, &philos[i], philos[i].ph_id);
			pthread_mutex_lock(&philos->data->dead_lock);
			philos->data->dead_flag = TRUE;
			pthread_mutex_unlock(&philos->data->dead_lock);
			pthread_mutex_unlock(&philos[i].data->meal_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&philos[i].data->meal_lock);
		i++;
	}
	return (FALSE);
}

void	*ft_monitor(void *param)
{
	t_philo	*philos;

	philos = (t_philo *)param;
	while (!is_dead(&philos[0]))
	{
		usleep(1);
		if (check_all_full(philos) == TRUE || check_if_dead(philos))
			break ;
	}
	return (param);
}
