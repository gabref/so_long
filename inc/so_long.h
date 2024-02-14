#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/inc/libft.h"
# include "multiplatform.h"
# include <stdio.h>

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
