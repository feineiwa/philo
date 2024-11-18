/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:49:37 by frahenin          #+#    #+#             */
/*   Updated: 2024/11/18 17:16:14 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		ft_usleep(500);
	return (0);
}

t_bool	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == TRUE)
		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (FALSE);
}

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s", time, id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->ph_id);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->ph_id);
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
	philo->eating = 1;
	print_message("is eating", philo, philo->ph_id);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->ph_id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (data);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eaten_count == 0)
		return (pthread_mutex_unlock(&philo->data->meal_lock), 1);
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->philo_nbr)
	{
		if (philosopher_dead(&philos[i], philos[i].data->time_to_die))
		{
			print_message("died", &philos[i], philos[i].ph_id);
			pthread_mutex_lock(&philos->data->dead_lock);
			philos->data->dead_flag = 1;
			pthread_mutex_unlock(&philos->data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos->data->total_meals == -1)
		return (0);
	while (i < philos->data->philo_nbr)
	{
		pthread_mutex_lock(&philos->data->meal_lock);
		if (philos[i].eaten_count >= philos[i].data->total_meals)
			finished_eating++;
		pthread_mutex_unlock(&philos->data->meal_lock);
		i++;
	}
	if (finished_eating == philos->data->philo_nbr)
	{
		pthread_mutex_lock(&philos->data->dead_lock);
		philos->data->dead_flag = 1;
		pthread_mutex_unlock(&philos->data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}

int	dinner_start(t_data *data)
{
	int			i;
	pthread_t	observer;

	i = 0;
	if (pthread_create(&observer, NULL, &monitor, data->philos) != 0)
		return (error_exit("Thread creation error"));
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &dinner_simulation,
				&data->philos[i]))
			return (ERROR_FAILURE);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		return (ERROR_FAILURE);
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			return (ERROR_FAILURE);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data data;

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