#include "math.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"

typedef	struct	s_complexe
{
	double		r;
	double		i;
}				t_complex;

int	absolute(double value)
{
	if (value > 0)
		return (value);
	else
		return (-value);
}

t_complex init_complex(double r, double i)
{
	t_complex complex;
	complex.r = r;
	complex.i = i;
	return (complex);
}

t_complex sum_complex(t_complex complex1, t_complex complex2)
{
	complex1.r += complex2.r;
	complex1.i += complex2.i;
	return (complex1);
}

t_complex multiply_complex(t_complex complex1, t_complex complex2) {
    t_complex result;

    result.r = (complex1.r * complex2.r) - (complex1.i * complex2.i);
    result.i = (complex1.r * complex2.i) + (complex1.i * complex2.r);

    return result;
}

t_complex divide_complex(t_complex complex1, t_complex complex2) {
    t_complex res;
    double denominator = complex2.r * complex2.r + complex2.i * complex2.i;

    res.r = (complex1.r * complex2.r + complex1.i * complex2.i) / denominator;
    res.i = (complex1.i * complex2.r - complex1.r * complex2.i) / denominator;

    return res;
}

t_complex complex_inverse(t_complex complex)
{
	return divide_complex(init_complex(1,0), complex);
}

t_complex complex_power(t_complex complex, int power)
{
	t_complex res;
	int			i;

	res = init_complex(1,0);
	i = 0;
	while (i++ < absolute(power))
		res = multiply_complex(res, complex);
	if (power < 0)
	{
		res = complex_inverse(res);
	}
	return (res);
}

double get_module(t_complex complex)
{
	return (sqrt((pow(complex.r, 2) + pow(complex.i, 2))));
}

t_complex	julia_sequence(t_complex complex, t_complex c)
{
	complex = complex_power(complex, 2);
	complex = sum_complex(complex, c);
	return (complex);
}

int get_julia_convergence(int max_iter, t_complex point, t_complex julia_settings)
{
	double max_module = 10000000;
	int iter = 0;

	while (get_module(point) < max_module && iter++ < max_iter)
		point = julia_sequence(point, julia_settings);
	if (iter >= max_iter)
		return (0);
	return (iter);
}

#define	WIN1_SX		600
#define	WIN1_SY		600

int	manage_key_input(int key,void *param)
{
  printf("Key is : %d\n",key);
  if (key==0xFF1B)
    mlx_loop_end(param);
}

int get_endian()
{
	int a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		return(1);
	else
		return(0);
}

int	color_map_2(void *mlx, int local_endian, unsigned char *data,int bpp,int sl,int w,int h,int endian)
{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	color2;
  unsigned char *ptr;
  int 	converge;
  int	sum_conv = 0;
  int	sum_div = 0;


  opp = bpp/8;
  y = h;
  while (y--)
    {
      	ptr = data+y*sl;
      	x = w;
      	while (x--)
    	{
			converge = get_julia_convergence(1000, init_complex(x/10,y/10),init_complex(-1,0));
			if (converge)
			{
			 	color = ((255)<<16)+((255)<<8)+(255);
				sum_conv++;
			}
			else
			{
				sum_div++;
				printf("div en x = %d, y=%d\n",x,y);
				color = ((0)<<16)+((0)<<8)+(0);
			}
        	color2 = mlx_get_color_value(mlx,color);
	  		dec = opp;
	  		while (dec--)
	    	{	
				if (endian==local_endian)
	      		{
					if (endian)
		  				*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
					else
		  				*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[dec];
			    }
	    		else
	      		{
					if (endian)
		  				*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
					else
		  				*(ptr+x*opp+dec) = ((unsigned char *)(&color2))[3-dec];
	      		}
			}
        }
    }
	printf("sum_div : %d\nsum_conv : %d\n", sum_div, sum_conv);
}

int main()
{
	void	*mlx;
	void	*win1;
	void	*im1;
	int		bpp1;
	int		sl1;
	char	*data1;
	int		endian1;
	int	local_endian;

	local_endian = get_endian();
	if (!(mlx = mlx_init()))
    {
        printf(" !! KO on mlx_init!!\n");
        exit(1);
    }
	if (!(win1 = mlx_new_window(mlx,WIN1_SX, WIN1_SY,"Title1")))
    {
      printf(" !! KO on new window!!\n");
      exit(1);
    }
	if (!(im1 = mlx_new_image(mlx,WIN1_SX, WIN1_SY)))
	{
		printf(" !! KO on new image!!\n");
		exit(1);
	}
	data1 = mlx_get_data_addr(im1,&bpp1,&sl1,&endian1);
	color_map_2(mlx, local_endian, data1, bpp1, sl1, WIN1_SX, WIN1_SY, endian1);
	mlx_put_image_to_window(mlx,win1,im1,0,0);

	mlx_key_hook(win1, manage_key_input, mlx);

	
	mlx_loop(mlx);

	//free
	mlx_destroy_image(mlx, im1);
	mlx_destroy_window(mlx, win1);
	mlx_destroy_display(mlx);
	free(mlx);
}