#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"

#define	WIN1_SX		242
#define	WIN1_SY		242
#define	IM1_SX		42
#define	IM1_SY		42

int	manage_key_input(int key,void *param)
{
  printf("Key is : %d\n",key);
  if (key==0xFF1B)
    mlx_loop_end(param);
}

int	manage_mouse_input(int button,int x,int y, void *p)
{
  printf("Mouse in Win3, button %d at %dx%d.\n",button,x,y);
}

int	manage_mouse_move(int x,int y, void *p)
{
  printf("Mouse moving in Win3, at %dx%d.\n",x,y);
}

int	color_image_pixel(void *mlx, int local_endian, unsigned char *data,int bpp,int sl,int endian, int color)
{
  	int	opp;
  	int	dec;
  	unsigned char *ptr;

  	opp = bpp/8;
	ptr = data;
    color = mlx_get_color_value(mlx,color);
	dec = opp;
	while (dec--)
	{
		if (endian==local_endian)
		{
			if (endian)
				*(ptr+dec) = ((unsigned char *)(&color))[4-opp+dec];
			else
				*(ptr+dec) = ((unsigned char *)(&color))[dec];
		}
		else
		{
			if (endian)
				*(ptr+dec) = ((unsigned char *)(&color))[opp-1-dec];
			else
				*(ptr+dec) = ((unsigned char *)(&color))[3-dec];
		}
	}
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

  opp = bpp/8;
  y = h;
  while (y--)
    {
      	ptr = data+(y+10)*sl;
      	x = w;
      	while (x--)
    	{
	    	color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
        	color2 = mlx_get_color_value(mlx,color);
	  		dec = opp;
	  		while (dec--)
	    	{	
				if (endian==local_endian)
	      		{
					if (endian)
		  				*(ptr+(x+10)*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
					else
		  				*(ptr+(x+10)*opp+dec) = ((unsigned char *)(&color2))[dec];
			    }
	    		else
	      		{
					if (endian)
		  				*(ptr+(x+10)*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
					else
		  				*(ptr+(x+10)*opp+dec) = ((unsigned char *)(&color2))[3-dec];
	      		}
			}
        }
    }
}

int	color_affine(void *mlx, int local_endian, unsigned char *data,int bpp,int sl,int w,int h,int endian)
{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	color2;
  unsigned char *ptr;

  opp = bpp/8;
  y = h;
  while (y--)
    {
      	ptr = data+(y)*sl;
		printf("y = %d, w = %d\n",y,w);
      	x = w - y - 1;
    	{
	    	color = ((255-x)<<16)+((255-y)<<8)+(255);
        	color2 = mlx_get_color_value(mlx,color);
	  		dec = opp;
			printf("point creer en %d,%d\n",x,y);
	  		while (dec--)
	    	{	
				if (endian==local_endian)
	      		{
					if (endian)
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
					else
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[dec];
			    }
	    		else
	      		{
					if (endian)
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
					else
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[3-dec];
	      		}
			}
        }
    }
}

int	color_square_center(void *mlx, int local_endian, unsigned char *data,int bpp,int sl,int w,int h,int endian)
{
  int	x;
  int	y;
  int	opp;
  int	dec;
  int	color;
  int	color2;
  unsigned char *ptr;

  opp = bpp/8;
  y = h;
  while (y-- )
    {
      	ptr = data+(y)*sl;
      	x = w;
      	while (x--)
    	{
	    	color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
        	color2 = mlx_get_color_value(mlx,color);
	  		dec = opp;
	  		while (dec--)
	    	{	
				if (endian==local_endian)
	      		{
					if (endian)
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
					else
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[dec];
			    }
	    		else
	      		{
					if (endian)
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
					else
		  				*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[3-dec];
	      		}
			}
        }
    }
}

int color_pixel(void *mlx, int local_endian, unsigned char *data,int bpp,int sl,int x,int y,int endian, int color)
{
	int dec;
	int	color2;
  	unsigned char *ptr;
	int opp = bpp/8;

	ptr = data+(y)*sl;
	color2 = mlx_get_color_value(mlx,color);
	dec = opp;
	while (dec--)
	{	
		if (endian==local_endian)
		{
			if (endian)
		  		*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[4-opp+dec];
			else
		  		*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[dec];
		}
		else
	    {
			if (endian)
		  		*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[opp-1-dec];
			else
		  		*(ptr+(x)*opp+dec) = ((unsigned char *)(&color2))[3-dec];
	    }
	}
}

int draw_rectangle(void *mlx, int local_endian, unsigned char *data,int bpp,int sl,int x, int y, int width, int height,int endian)
{
	int color;
	int i;
	int j;

	
	i = -1;
	while (i++ < height)
	{
		j = -1;
		while (j++ < width)
		{
			color = ((255-3*i)<<16)+((255-3*j)<<8)+(255-i-j);
			color_pixel(mlx, local_endian, data, bpp, sl, x+i , y+j, endian, color);
		}
	}
}

int draw_center_rectangle(void *mlx, int local_endian, unsigned char *data,int bpp,int sl, int windows_width, int windows_height, int width, int height,int endian)
{
	draw_rectangle(mlx, local_endian, data, bpp, sl, windows_width / 2 - width / 2, windows_height / 2 - height / 2, width, height, endian);
}

int get_endian()
{
	int a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		return(1);
	else
		return(0);
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
	if (!(win1 = mlx_new_window(mlx,WIN1_SX,WIN1_SY,"Title1")))
    {
      printf(" !! KO on new window!!\n");
      exit(1);
    }
	if (!(im1 = mlx_new_image(mlx,WIN1_SX,WIN1_SY)))
	{
		printf(" !! KO on new image!!\n");
		exit(1);
	}
	data1 = mlx_get_data_addr(im1,&bpp1,&sl1,&endian1);

	//color_map_2(mlx, local_endian, data1, bpp1, sl1, 42, 42, endian1);
	//color_affine(mlx, local_endian, data1, bpp1, sl1, WIN1_SX, WIN1_SY, endian1);
	//color_square_center(mlx, local_endian, data1, bpp1, sl1, 42, 42, endian1);
	//draw_rectangle(mlx, local_endian, data1, bpp1, sl1, 1, 1, 42, 42, endian1);
	draw_center_rectangle(mlx, local_endian, data1, bpp1, sl1, WIN1_SX, WIN1_SY, 42, 42, endian1);
	draw_rectangle(mlx, local_endian, data1, bpp1, sl1, 0, 0, 42, 42, endian1);
	draw_rectangle(mlx, local_endian, data1, bpp1, sl1, 0, 43, 42, 42, endian1);
	draw_rectangle(mlx, local_endian, data1, bpp1, sl1, 43, 0, 42, 42, endian1);

	mlx_put_image_to_window(mlx,win1,im1,0,0);

	mlx_key_hook(win1, manage_key_input, mlx);
	mlx_mouse_hook(win1,manage_mouse_input,0);
	mlx_hook(win1, MotionNotify, PointerMotionMask, manage_mouse_move, 0);

	mlx_loop(mlx);

	//free
	mlx_destroy_image(mlx, im1);
	mlx_destroy_window(mlx, win1);
	mlx_destroy_display(mlx);
	free(mlx);
}