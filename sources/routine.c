/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:44:18 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/20 18:47:35 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	assign_forks(t_philo *philos[], pthread_mutex_t *forks[],
		int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		philos[i]->left_fork = forks[philos[i]->id - 1];
		philos[i]->right_fork = forks[philos[i]->id];
		if (i == num_of_philos - 1)
			philos[i]->right_fork = forks[num_of_philos - 1];
		i++;
	}
}

int	thinking(t_philo *philo)
{
	print_message("is thinking.\n", philo);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_message("is sleeping.\n", philo);
	ft_usleep(philo->time_to_sleep * 1000);
	return (0);
}

int	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (-1);
	print_message("has taken a fork.\n", philo);
	if (pthread_mutex_lock(philo->left_fork) != 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	print_message("has taken a fork.\n", philo);
	print_message("is eating.\n", philo);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	ft_usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*routine(void *ptr)
{
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)ptr;
	while (1)
	{
		while (table->philos[i])
		{
			thinking(table->philos[i]);
			eating(table->philos[i]);
			sleeping(table->philos[i]);
			i++;
		}
		if (table->dead)
			break ;
	}
	return (ptr);
}
