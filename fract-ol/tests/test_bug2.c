#include <stdio.h>
#include <stdlib.h>

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*buf;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	kr;
	double	ki;
	double	sx;
	double	rx;
	double	fx;
	int		*palette;
	int		color_pattern;
	int		color;
}	t_fractol;

void function2(t_fractol *fractol)
{
	if(!fractol)
		exit(1);
	printf("OK\n");
	if(fractol->palette)
		free(fractol->palette);
	printf("ok2\n");
	exit(0);
}

void function1(t_fractol *fractol)
{
	printf("fonction 1 \n");
	function2(fractol);
}


int main(int ac, char **argv)
{
	t_fractol fractol;
	function1(&fractol);
	printf("main(0)\n");
	return (0);
}