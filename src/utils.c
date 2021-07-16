#include "libft.h"
#include "utils.h"

t_list	*lst_get_n_elem(t_list *lst, int n)
{
	t_list	*ptr;

	ptr = lst;
	while (n--)
	{
		if (!ptr)
			return (NULL);
		ptr = ptr->next;
	}
	return (ptr);
}

t_list	*lst_2ndtolast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (!lst->next)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

void	free_towers(int n, t_towers *game)
{
	ft_lstclear(&(game->rod_a), (void *) 0);
	ft_lstclear(&(game->rod_b), (void *) 0);
	ft_lstclear(&(game->rod_c), (void *) 0);
	free(game->rings);
}

// colors

void color_reset()
{
	ft_putstr_fd("\033[0m", 1);
}

void red()
{
	ft_putstr_fd("\033[1;31m", 1);
}

void green()
{
	ft_putstr_fd("\033[1;32m", 1);
}

void yellow()
{
	ft_putstr_fd("\033[1;33m", 1);
}

void blue()
{
	ft_putstr_fd("\033[1;34m", 1);
}

void purple()
{
	ft_putstr_fd("\033[1;35m", 1);
}

void cyan()
{
	ft_putstr_fd("\033[1;36m", 1);
}

void white()
{
	ft_putstr_fd("\033[1;37m", 1);
}

void color_switch(int x)
{
	void (*array[7])(void);

	array[0] = &red;
	array[1] = &green;
	array[2] = &yellow;
	array[3] = &blue;
	array[4] = &purple;
	array[5] = &cyan;
	array[6] = &white;

	(*array[x % 7])();
}


// debugging

void	print_lst(t_list *lst)
{
	while (lst)
	{
		ft_putnbr_fd(*(int *)lst->content, 1);
		ft_putstr_fd(" ", 1);
		lst = lst->next;
	}
	ft_putstr_fd("\n", 1);
}

void print_game_content(t_towers game)
{
	ft_putstr_fd("list a: ", 1);
	print_lst(game.rod_a);
	ft_putstr_fd("list b: ", 1);
	print_lst(game.rod_b);
	ft_putstr_fd("list c: ", 1);
	print_lst(game.rod_c);
}