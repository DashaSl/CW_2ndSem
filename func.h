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
void draw_line(BMP bmp, RGB color, int x1, int y1, int x2, int y2);
void draw_thick_line(BMP bmp, RGB color, int x1, int y1, int x2, int y2, int width, int flag);
void draw_hexagon(char* file_name, int* data, int mode, int width, RGB line_color, int fill_flag, RGB fill_color);
float c(int x1, int y1, int x2, int y2);
float b(int x1, int y1, int x2, int y2);
#endif //CW_2NDSEM_FUNC_H
