/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:49:37 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/24 16:18:47 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->dead_flag == TRUE)
		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time() - philo->start_time;
	printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	print_message("has taken a fork", philo, philo->ph_id);
	if (philo->data->philo_nbr == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->r_fork->fork_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	print_message("has taken a fork", philo, philo->ph_id);
	philo->eating = TRUE;
	print_message("is eating", philo, philo->ph_id);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = FALSE;
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->ph_id);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->ph_id);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->ph_id % 2 == 0)
		ft_usleep(1);
	while (!is_dead(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (data);
}

// t_bool	is_dead(t_philo *philo)
// {
// }

// void	*dinner_simulation(void *param)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)param;
// 	while (!is_dead(philo))
// 	{
// 		eat(philo);
// 	}
// 	return (param);
// }

int	dinner_start(t_data *data)
{
	int			i;
	pthread_t	observer;

	i = 0;
	if (pthread_create(&observer, NULL, &ft_monitor, data->philos))
		return (ERROR_FAILURE);
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &dinner_simulation,
				&data->philos[i]))
			return (ERROR_FAILURE);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL))
		return (ERROR_FAILURE);
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (ERROR_FAILURE);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (error_exit("Error:\nYour argument should be correct"));
	if (parse_input(&data, av) == ERROR_FAILURE)
		return (ERROR_FAILURE);
	if (init_data(&data) == ERROR_FAILURE)
		return (ERROR_FAILURE);
	if (dinner_start(&data))
		return (ERROR_FAILURE);
	return (0);
}