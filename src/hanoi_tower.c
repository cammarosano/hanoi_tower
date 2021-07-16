#include "utils.h"
#include <stdio.h>

int 	create_towers(int n, t_towers *game)
{
	int	i;

	game->rings = malloc(sizeof(int) * n);
	if (!game->rings)
		return (-1);
	i = -1;
	while (++i < n)
		game->rings[i] = i + 1;
	game->rod_a = NULL;
	game->rod_b = NULL;
	game->rod_c = NULL;
	i = -1;
	while (++ i < n)
	{
		ft_lstadd_front(&(game->rod_a), ft_lstnew(game->rings + i));
		if (!game->rod_a)
			return (-1);
	}
	return (1);
}

void	print_tower_line(t_list *lst, int i, int n)
{
	t_list *ptr;
	int		ring;
	int		j;

	ptr = lst_get_n_elem(lst, n - 1 - i);
	if (!ptr)
		ring = 0;
	else
		ring = *(int *)(ptr->content);
	j = 0;
	while (j++ < n - ring)
		write(1, "  ", 2);
	j = 0;
	color_switch(ring);
	while (j++ < ring)
		write(1, "##", 2);
	color_reset();
	write(1, "|", 1);
	j = 0;
	color_switch(ring);
	while (j++ < 2 * ring)
		write(1, "#", 1);
	color_reset();
	j = 0;
	while (j++ < n - ring)
		write(1, "  ", 2);
}

void	print_base(int n)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < 3)
	{	
		j = 0;
		while (j++ < 4 * n + 1)
			write(1, "-", 1);
		write(1, "  ", 2);
	}
	write(1, "\n", 1);
}

void	print_game(t_towers game, int n, long time)
{
	int	i;

	system("clear");	
	i = 0;
	while (i < n)
	{
		print_tower_line(game.rod_a, i, n);
		write(1, "  ", 2);
		print_tower_line(game.rod_b, i, n);
		write(1, "  ", 2);
		print_tower_line(game.rod_c, i, n);
		write (1, "\n", 1);
		i++;
	}
	print_base(n);
	usleep(time * 1000);
}

void	move_ring(t_list **origin, t_list **dest)
{
	t_list	*origin_last;
	t_list	*origin_2ndtolast;
	t_list	*dest_last;

	origin_last = ft_lstlast(*origin);
	dest_last = ft_lstlast(*dest);
	origin_2ndtolast = lst_2ndtolast(*origin);
	if (!dest_last)
		*dest = origin_last;
	else
		dest_last->next = origin_last;
	if (!origin_2ndtolast)
		*origin = NULL;
	else
		origin_2ndtolast->next = NULL;
}

void	move_piramid(int size, t_list **origin, t_list **interm, t_list **dest, t_towers *game, int n, long time)
{
	if (size == 1)
	{
		move_ring(origin, dest);
		print_game(*game, n, time);
	}
	else
	{
		move_piramid(size - 1, origin, dest, interm, game, n, time);
		move_ring(origin, dest);
		print_game(*game, n, time);
		move_piramid(size - 1, interm, origin, dest, game, n, time);
	}
}

int	parse_args(int *n, long *time, int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putendl_fd("Usage: hanoi_tower n_rings [time_is_ms], where n_rings >= 1", 2);
		return (-1);
	}
	*n = ft_atoi(argv[1]);
	if (*n < 1)
		return (-1);
	*time = 1000000;
	if (argc >= 3)
		*time = ft_atoi(argv[2]);
	if (*time < 0)
	{
		ft_putendl_fd("Bad value for time", 2);
		return (-1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int			n;
	long		time;
	t_towers	game;

	if (parse_args(&n, &time, argc, argv) == -1)
		return (1);
	if (create_towers(n, &game) == -1)
		return (1);
	print_game(game, n, time);
	move_piramid(n, &game.rod_a, &game.rod_b, &game.rod_c, &game, n, time);
	free_towers(n, &game);
	return (0);
}
