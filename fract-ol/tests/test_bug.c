#include <stdio.h>
#include <stdlib.h>

// typedef struct s_fractol
// {
// 	void	*mlx;
// 	void	*win;
// 	void	*img;
// 	char	*data;
// 	int		*palette;
// 	int		set;
// 	double	min_r;
// 	double	max_r;
// 	double	min_i;
// 	double	max_i;
// 	double	julia_r;
// 	double	julia_i;
// 	int		color_pattern;
// 	int 	color;
// } t_fractol;

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		set;
	double	min_r;
	double	max_r;
	double	min_i;
	double	max_i;
	double	julia_r;
	double	julia_i;
	int		*colors;
	int		color_pattern;
	int		color;
}	t_fractol;

void function2(t_fractol *fractol)
{
	if(!fractol)
		exit(1);
	printf("OK\n");
	if(fractol->colors)
	{
		printf("OK1.5\n");
		free(fractol->colors);
	}
		
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