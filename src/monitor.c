/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 14:13:26 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/24 13:32:33 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

static t_bool	check_if_dead(t_philo *philos)
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
			return (pthread_mutex_unlock(&philos[i].data->meal_lock), TRUE);
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
		if (check_all_full(philos) == TRUE || check_if_dead(philos) == TRUE)
			break ;
	}
	return (param);
}
