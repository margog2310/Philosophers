/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:26:17 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/20 23:59:07 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(char *argv[], t_table *table, int meals_number,
		pthread_mutex_t **forks)
{
	int	i;
	int	num_of_philos;

	initialise_forks(argv, &forks);
	initialise_table(argv, table, meals_number);
	assign_forks(table->philos, forks, ft_atoi(argv[1]));
	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	pthread_create(&table->waiter_id, NULL, &monitor, (void *)table);
	while (i < num_of_philos)
	{
		pthread_create(&table->philos[i]->thread, NULL, &routine,
			(void *)table->philos[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int				i;
	int				num_of_philos;
	bool			meals_number;
	t_table			table;
	pthread_mutex_t	**forks;

	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("Error: Invalid arguments.", 1), -1);
	if (argc == 5)
		meals_number = false;
	if (argc == 6)
		meals_number = true;
	if (!check_args(argv, meals_number))
		return (ft_putendl_fd("Error: Invalid arguments.", 1), -1);
	forks = NULL;
	init(argv, &table, meals_number, forks);
	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	pthread_join(table.waiter_id, NULL);
	while (i < num_of_philos)
		pthread_join(table.philos[i++]->thread, NULL);
	free_all(&table, forks);
	return (0);
}

/*
	TO DO:
			//1. finish philosopher's routine function (void ptr arg like the monitor function)
			//2. initialise monitor thread and hook on monitor function
			//3. finish main()
			//	- better arg checking?
			//	- separate init functions to keep main simple
			4. clean up functions
			5. finish Makefile
			6. testing + memory leaks
			7. clean up code + norminette
			8. submit
*/