/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:26:17 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/17 23:58:15 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialise_forks(char *argv[], pthread_mutex_t **forks[])
{
	int	i;
	int	num_of_forks;

	i = 0;
	num_of_forks = ft_atoi(argv[1]);
	while (i < num_of_forks)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
		{
			ft_putendl_fd("Error: Memory Allocation", 2);
			free_arr(forks);
			return ;
		}
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}

t_philo	*initialise_philo(t_table *table, int id, char *argv[],
		bool meals_number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return ((ft_putendl_fd("Error: Memory Allocation", 2),
				free_table(table)), NULL);
	pthread_create(&philo->thread, NULL, routine, (void *)&philo);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_of_philos = ft_atoi(argv[1]);
	if (meals_number)
		philo->num_of_meals = ft_atoi(argv[5]);
	else
		philo->num_of_meals = -1;
	philo->eating = false;
	philo->dead = &(table->dead);
	philo->last_meal = get_current_time();
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->start_time = get_current_time();
	philo->write_lock = &(table->write_lock);
	philo->meal_lock = &(table->meal_lock);
	philo->dead_lock = &(table->dead_lock);
	return (philo);
}

void	initialise_locks(t_table *table)
{
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
}

void	initialise_table(char *argv[], t_table **table, bool meals_number)
{
	int	i;
	int	num_of_philos;

	num_of_philos = ft_atoi(argv[1]);
	*table = malloc(sizeof(t_table) + sizeof(t_philo) * num_of_philos);
	if (!*table)
		return (ft_putendl_fd("Error: Memory Allocation", 2), (void)0);
	initialise_locks(*table);
	(*table)->dead = false;
	i = 0;
	while (i < num_of_philos)
	{
		(*table)->philos[i] = initialise_philo(*table, i + 1, argv,
				meals_number);
		if (!(*table)->philos[i])
			return (ft_putendl_fd("Error: Memory Allocation", 2),
				free_table(*table), (void)0);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int				i;
	int				num_of_philos;
	bool			meals_number;
	t_table			*table;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("Error: Invalid arguments.", 1), 0);
	if (argc == 5)
		meals_number = false;
	else if (argc == 6)
		meals_number = true;
	initialise_forks(argv, forks);
	initialise_table(argv, &table, meals_number);
	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	assign_forks(table->philos, forks, num_of_philos);
	while (i < num_of_philos)
		pthread_join(table->philos[i++]->thread, NULL);
}

/*
	TO DO:
			1. finish philosopher's routine function (void ptr arg like the monitor function)
			2. initialise monitor thread and hook on monitor function
			3. finish main()
				- better arg checking?
				- separate init functions to keep main simple
			4. clean up functions
			5. finish Makefile
			6. testing + memory leaks
			7. clean up code + norminette
			8. submit
*/