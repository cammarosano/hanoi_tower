#include "libft.h"
#include <time.h>

typedef struct	s_towers
{
	t_list	*rod_a;
	t_list 	*rod_b;
	t_list	*rod_c;
	int		*rings;
}				t_towers;

t_list	*lst_get_n_elem(t_list *lst, int n);
t_list	*lst_2ndtolast(t_list *lst);
void	free_towers(int n, t_towers *game);
void color_switch(int x);
void color_reset();


// debugging

void print_game_content(t_towers game);