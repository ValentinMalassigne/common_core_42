#include "stdio.h"
#include "math.h"

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

t_complex real_complex_prod(double real, t_complex complex)
{
	complex.r *= real;
	complex.i *= real;
	return (complex);
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
	return (iter);
}

void test_math()
{
	t_complex complex1 =  init_complex(1, 2);
	t_complex complex2 =  init_complex(4, 3);

	t_complex sum = sum_complex(complex1, complex2);
	t_complex prod = multiply_complex(complex1, complex2);
	t_complex quotient = divide_complex(complex1, complex2);
	t_complex inverse = complex_inverse(complex1);
	t_complex power = complex_power(complex1, 2);

	printf("complex 1\n");
	printf("z = %lf + %lfi\n", complex1.r, complex1.i);
	printf("complex 2\n");
	printf("z = %lf + %lfi\n", complex2.r, complex2.i);
	printf("sum\n");
	printf("z = %lf + %lfi\n", sum.r, sum.i);
	printf("complex prod\n");
	printf("z = %lf + %lfi\n", prod.r, prod.i);
	printf("complex quotient\n");
	printf("z = %lf + %lfi\n", quotient.r, quotient.i);
	printf("complex inverse\n");
	printf("z = %lf + %lfi\n", inverse.r, inverse.i);
	printf("complex power\n");
	printf("z = %lf + %lfi\n", power.r, power.i);
	printf("get module\n");
	printf("module : %lf\n", get_module(complex1));
}

int main()
{
	test_math();
}