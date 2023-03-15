/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:20:03 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/15 17:39:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"

#define WIDTH  640
#define HEIGHT 480
#define MAX_ITER 1000
#define THRESHOLD 2.0
#define C_REAL -0.8
#define C_IMAG 0.156
#define COLOR_SCHEME 3

typedef struct s_complex {
    double real;
    double imag;
} t_complex;

int julia(t_complex z, t_complex c)
{
    int n = 0;
    t_complex zn = z;
    
    while (n < MAX_ITER && zn.real*zn.real + zn.imag*zn.imag < THRESHOLD*THRESHOLD) {
        t_complex tmp = zn;
        zn.real = tmp.real*tmp.real - tmp.imag*tmp.imag + c.real;
        zn.imag = 2*tmp.real*tmp.imag + c.imag;
        n++;
    }
    
    return n;
}

int color(int iter)
{
    switch (COLOR_SCHEME) {
        case 1:  return iter % 255;                                 // grayscale
        case 2:  return iter * 255 / MAX_ITER;                      // grayscale ramp
        case 3:  return 255 * sin(iter * M_PI / MAX_ITER);          // smooth rainbow
        default: return 0;
    }
}

void draw_julia(void *mlx_ptr, void *win_ptr, void *img_ptr)
{
	int             bits_per_pixel;
	int             line_length;
	int             endian;
    int *data = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &line_length, &endian);
    char	*dst;
    
    t_complex c = { 0, 0 };
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            t_complex z = {
                -1.5 + 3.0 * x / (WIDTH-1),
                -1.0 + 2.0 * y / (HEIGHT-1)
            };
            int iter = julia(z, c);
            int col = color(iter);
	    dst = data + (y * line_length + x * (bits_per_pixel / 8));
	    *(unsigned int*)dst = col;
	    //my_mlx_pixel_put(img_ptr, x, y, col);
            //data[y*WIDTH+x] = mlx_get_color_value(mlx_ptr, col);
        }
    }
    
    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
}

int main()
{
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Julia Set");
    img_ptr = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
    
    draw_julia(mlx_ptr, win_ptr, img_ptr);
    
    mlx_loop(mlx_ptr);
    
    return 0;
}
