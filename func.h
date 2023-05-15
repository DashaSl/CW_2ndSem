#include "CWlib.h"

#ifndef CW_2NDSEM_READ_WRITE_H
#define CW_2NDSEM_READ_WRITE_H
void free_BMP(BMP bmp);
BMP get_img(char* file_name);
void put_img(char* file_name, BMP bmp);
#endif

#ifndef CW_2NDSEM_FUNC_H
#define CW_2NDSEM_FUNC_H
void change_clr(RGB* source, RGB clr);
int cmp_rgb(RGB rgb1, RGB rgb2);
void copy_paste(char* source, char* paste_here, int xs1, int ys1, int xs2, int ys2, int xp, int yp);
void change_color(char* file_name, RGB to_be_changed, RGB base);
int lin_func(float b, float c, int y);
void draw_line(BMP bmp, RGB color, int x1, int y1, int x2, int y2);
void draw_thick_line(BMP bmp, RGB color, int x1, int y1, int x2, int y2, int width, int flag);
void draw_hexagon(char* file_name, int* data, int mode, int width, RGB line_color, int fill_flag, RGB fill_color);
float c(int x1, int y1, int x2, int y2);
float b(int x1, int y1, int x2, int y2);
#endif //CW_2NDSEM_FUNC_H

#ifndef CW_2NDSEM_FRAME_H
#define CW_2NDSEM_FRAME_H
void erase_line(BMP bmp, RGB** arr_copy,  int x1, int y1, int x2, int y2);
void draw_Koch_snowflake(BMP bmp,RGB** arr_copy, int x1, int y1, int x2, int y2, RGB color, int n);
void draw_Koch_frame(char* file_name, int width, int fill_flag, RGB line_color, RGB fill_color);
void draw_Minkowski_sausage(BMP bmp, int x1, int y1, int x2, int y2, RGB color, int n);
void draw_Minkowski_frame(char* file_name, int width, int fill_flag, RGB line_color, RGB fill_color);
void fill_v2(BMP bmp, RGB fill_color, RGB line_color, int a, int b);
void draw_simple_frame(char* file_name, int width, RGB fill_color);
#endif