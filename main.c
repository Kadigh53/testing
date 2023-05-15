/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:50:25 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/05/15 22:46:32 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("\033[32m %llu\t%d\thas taken a fork\n",ft_mstime() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("\033[32m %llu\t%d\thas taken a fork\n",ft_mstime() - philo->start_time, philo->id);
	printf("\033[1;33m %llu\t%d\tis eating\n",ft_mstime() - philo->start_time, philo->id);
	philo->meals_count++;
	philo->last_meal_time = ft_mstime();
	// usleep(philo->vars->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eating(t_philo	*philo)
{
	pick_forks(philo);
	usleep(philo->vars->time_to_eat * 1000);
	drop_forks(philo);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (ft_mstime() - philo->last_meal_time >= philo->vars->time_to_die && *philo->dead != 1)
	{
		*philo->dead = 1;
		usleep(1000);
		printf("\033[31m %llu\t%d\tdead\n",ft_mstime() - philo->start_time,philo->id);
		exit(0);
	}
	pthread_mutex_unlock(philo->death_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	if (philo->id % 2 != 0)
		usleep(500);
	while (1)
	{
		if (philo->meals_count >= philo->vars->nbrof_meals && philo->vars->nbrof_meals != -1)
			break;
		check_death(philo);
		eating(philo);
		printf("\033[34m %llu\t%d\tis sleeping\n",ft_mstime() - philo->start_time,philo->id);
		usleep(philo->vars->time_to_sleep * 1000);
		if (philo->last_meal_time + philo->vars->time_to_die > ft_mstime() - philo->start_time)
		{
			printf("\033[0m %llu\t%d\tis thinking\n",ft_mstime() - philo->start_time,philo->id);
		}
	}
	return (NULL);
}

void	create_philos(t_data **data)
{
	int i;

	i = -1;
	// printf("%d\t%p \n\n",(*data)->dead,&(*data)->dead);
	while (++i < (*data)->vars->nbr_of_philos)
	{
		printf("%d\n",i);
		(*data)->philos[i]->dead = &(*data)->dead;
		// (*data)->philos[i].start_time = ft_mstime();
		// (*data)->philos[i]->last_meal_time = ft_mstime();
		// (*data)->philos[i]->meals_count = 0;
		// (*data)->philos[i]->id = i;
		// (*data)->philos[i]->dead = &(*data)->dead;
		(*data)->philos[i]->death_mutex = (*data)->death_mutex;
		(*data)->philos[i]->vars = (*data)->vars;
	}
	// return;
	// i = -1;
	// while (++i < (*data)->vars->nbr_of_philos)
	// {
	// 	pthread_mutex_init((*data)->forks[i], NULL);
	// 	if (i  == (*data)->vars->nbr_of_philos - 1)
	// 	{
	// 		(*data)->philos[i]->right_fork = (*data)->forks[i];
	// 		(*data)->philos[i]->left_fork = (*data)->forks[0];
	// 	}
	// 	else
	// 	{
	// 		(*data)->philos[i]->right_fork = (*data)->forks[i];
	// 		(*data)->philos[i]->left_fork = (*data)->forks[i + 1];
	// 	}	
	// }
	// i = -1;
	// while (++i < (*data)->vars->nbr_of_philos)
	// {
	// 	pthread_create((*data)->philos_thread[i], NULL, routine, (*data)->philos[i]);
	// }
	// i = -1;
	// while (++i < (*data)->vars->nbr_of_philos)
	// 	pthread_join(*(*data)->philos_thread[i], NULL);
	// i = -1;
	// while (++i < (*data)->vars->nbr_of_philos)
	// 	pthread_mutex_destroy((*data)->forks[i]);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->vars = malloc(sizeof(t_vars));
	data->dead = 0;
	printf("%d\t%p \n\n",data->dead,&data->dead);
	data->death_mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->death_mutex, NULL);
	if (ac > 6 || ac < 5)
		error("invalid nbr of args\n");
	printf("ok\n");
	init_args(ac, av, &data);
	create_philos(&data);
	printf("heloo\n");
	pthread_mutex_destroy(data->death_mutex);
}
