/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:54:22 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/29 19:34:41 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(char *msg, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!is_dead_loop(philo))
		printf("%zu %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

bool	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (!philo->eating && (get_current_time()
			- philo->last_meal > philo->time_to_die))
		return (pthread_mutex_unlock(philo->meal_lock), true);
	pthread_mutex_unlock(philo->meal_lock);
	return (false);
}

bool	is_dead(t_table *table)
{
	int		i;
	int		num_of_philos;
	size_t	time;

	i = 0;
	num_of_philos = table->philos[0]->num_of_philos;
	while (i < num_of_philos)
	{
		if (philo_is_dead(table->philos[i]))
		{
			pthread_mutex_lock(&table->write_lock);
			time = get_current_time() - table->philos[i]->start_time;
			printf("%zu %d died.\n", time, table->philos[i]->id);
			pthread_mutex_lock(&table->dead_lock);
			table->dead = true;
			pthread_mutex_unlock(&table->dead_lock);
			pthread_mutex_unlock(&table->write_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	finished_eating(t_table *table)
{
	int	i;
	int	num_of_philos;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	num_of_philos = table->philos[0]->num_of_philos;
	if (table->philos[0]->num_of_meals == -1)
		return (false);
	while (i < num_of_philos)
	{
		pthread_mutex_lock(table->philos[i]->meal_lock);
		if (table->philos[i]->meals_eaten >= table->philos[i]->num_of_meals)
			finished_eating++;
		pthread_mutex_unlock(table->philos[i]->meal_lock);
		i++;
	}
	if (finished_eating == num_of_philos)
	{
		pthread_mutex_lock(&table->dead_lock);
		table->dead = true;
		pthread_mutex_unlock(&table->dead_lock);
		return (true);
	}
	return (false);
}

void	*monitor(void *ptr)
{
	t_table	*table;

	table = (t_table *)ptr;
	while (1)
	{
		if (is_dead(table) || finished_eating(table))
			break ;
	}
	return (ptr);
}
