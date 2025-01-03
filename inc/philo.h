/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frahenin <frahenin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:34:59 by frahenin          #+#    #+#             */
/*   Updated: 2024/12/27 16:46:56 by frahenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_FAILURE 1
# define PHILO_MAX 200

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[1;0m"

typedef enum e_bool
{
	FALSE,
	TRUE,
}						t_bool;

typedef enum e_status
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORK,
}						t_status;

typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

typedef long long		t_time;

typedef struct s_fork
{
	int					fork_id;
	t_mutex				fork_mutex;
}						t_fork;

typedef struct s_philo
{
	int					ph_id;
	int					eaten_count;
	pthread_t			thread_id;
	t_fork				*l_fork;
	t_fork				*r_fork;
	t_data				*data;
	t_time				start_time;
	t_time				last_meal;
	t_bool				eating;
}						t_philo;

typedef struct s_data
{
	int					philo_nbr;
	t_time				time_to_die;
	t_time				time_to_eat;
	t_time				time_to_sleep;
	int					total_meals;
	t_philo				*philos;
	t_fork				*forks;
	t_mutex				dead_lock;
	t_mutex				meal_lock;
	t_mutex				write_lock;
	t_bool				dead_flag;
}						t_data;

int						error_exit(char *str);
int						print_error(t_data *data);

int						parse_input(t_data *data, char **av);

int						init_data(t_data *data);

void					*ft_monitor(void *param);
void					eat(t_philo *philo);
void					think(t_philo *philo);
void					snooze(t_philo *philo);

void					print_status(t_status status, t_philo *philo, int id);
t_bool					is_dead(t_philo *philo);
size_t					get_current_time(void);
int						ft_usleep(size_t milliseconds, t_philo *philo);

int						destroy_all(t_data *data);
void					*ft_free(void *ptr);

#endif