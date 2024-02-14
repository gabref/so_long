#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/inc/libft.h"
# include "../libs/mlx/mlx.h"
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

#endif
