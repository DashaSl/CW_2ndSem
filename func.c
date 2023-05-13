#include "CWlib.h"
#include "func.h"

void change_clr(RGB* source, RGB clr){
    source->r = clr.r;
    source->g = clr.g;
    source->b = clr.b;
}

int cmp_rgb(RGB rgb1, RGB rgb2){
    if(rgb1.r == rgb2.r && rgb1.g == rgb2.g && rgb1.b == rgb2.b){
        return 1;
    }
    return 0;
}

void copy_paste(char* source, char* paste_here, int xs1, int ys1, int xs2, int ys2, int xp, int yp){
    BMP sour = get_img(source);
    BMP paste = get_img(paste_here);
    int width = xs2 - xs1;
    int height = ys1 - ys2;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            change_clr((paste.arr)[yp - i]+xp+j, (sour.arr)[ys1-i][xs1+j]);
        }
    }
    put_img(paste_here, paste);
    free_BMP(sour);
    free_BMP(paste);
};

void change_color(char* file_name, RGB to_be_changed, RGB base){
    BMP bmp = get_img(file_name);
    for(int i = 0; i < abs(bmp.inf.Height); i++){
        for(int j = 0; j < abs(bmp.inf.Width); j++){
            if(cmp_rgb((bmp.arr)[i][j], to_be_changed)){
                change_clr((bmp.arr)[i]+j, base);
            }
        }
    }
    put_img(file_name, bmp);
    free_BMP(bmp);
}

int lin_func(float b, float c, int y){
    int x = b*y+c;
    return x;
}

void draw_line(BMP bmp, RGB color, int x1, int y1, int x2, int y2){
    if(x1 == x2){
        int min = y1;
        int max = y2;
        if(y1 > y2){
            min = y2;
            max = y1;
        }
        for(int i = min; i <= max; i++){
            change_clr((bmp.arr)[i]+x1,color);
        }
    }else if (y1 == y2){
        int min = x1;
        int max = x2;
        if(x1 > x2){
            min = x2;
            max = x1;
        }
        for(int i = min; i <= max; i++){
            change_clr((bmp.arr)[y1]+i,color);
        }
    }else if(abs(x1 - x2) > abs(y1-y2)){
        float d_x = x1- x2;;
        float b = (y1-y2)/d_x;
        float c = (x1*y2-y1*x2)/d_x;

        int min = x1;
        int max = x2;
        if(x1 > x2){
            min = x2;
            max = x1;
        }
        int tmp_y;
        for(int i = min; i <= max; i++){
            tmp_y = lin_func(b, c, i);
            change_clr((bmp.arr)[tmp_y]+i, color);
        }
    }else{
        float d_y = y1-y2;
        float b = (x1-x2)/d_y;
        float c = (y1*x2 - x1*y2)/d_y;
        int tmp_x;

        int min = y1;
        int max = y2;
        if(y1 > y2){
            min = y2;
            max = y1;
        }
        for(int i = min; i <= max; i++){
            tmp_x = lin_func(b, c, i);
            change_clr((bmp.arr)[i]+tmp_x,color);
        }
    }
}

void draw_thick_line(BMP bmp, RGB color, int x1, int y1, int x2, int y2, int width, int flag){ //flaf - 1 - to right 0 - to left or 1 - down 0 - up
    if(y1 == y2){
        if(flag){
            for(int i = 0; i < width; i++){
                draw_line(bmp, color, x1, y1-i, x2, y2-i);
            }
        }else{
            for(int i = 0; i < width; i++){
                draw_line(bmp, color, x1, y1+i, x2, y2+i);
            }
        }
    }else {
        int wid = width /
                  0.87; // 0.87 ~ sin(60), but it would be better to use math.h here, but gcc can't eat it correctly
        if (flag) {
            for (int i = 0; i < wid; i++) {
                draw_line(bmp, color, x1 + i, y1, x2 + i, y2);
            }
        } else {
            for (int i = 0; i < wid; i++) {
                draw_line(bmp, color, x1 - i, y1, x2 - i, y2);
            }
        }
    }
}

void fill_hexagon_v1(RGB** arr, RGB fill_color, int x1, int x2, int y1, int y2, float d_c, float c_up, float c_down){
    for(int x = x1; x <= x2; x++){
        for(int y = y1; y <= y2; y++){
            if(y <= x*1.73205+c_down && y <= x*(-1.73205)+c_up+d_c && y >= x*1.73205 +c_down - d_c && y >= x*(-1.73205) + c_up){
                change_clr(arr[y]+x, fill_color);
            }
        }
    }
}

void draw_hexagon(char* file_name, int* data, int mode, int width, RGB line_color, int fill_flag, RGB fill_color){ //mode - 0 - 2 coordinates[x1][y1][x2][y2], 1 - radius and point[rad][x][y]; data - array with cord/rad&point;
    int y1, y2, y3, x1, x2, x3, x4; //try to image hexagon and you will understand why
    int rad;
    if(mode){ //rad&point
        rad = data[0]; int x = data[1]; int y = data[2];
        y2 = y;
        x1 = x - rad;
        x4 = x + rad;
    }else{//two cord
        int x_up = data[0]; int y_up = data[1]; int x_down = data[2]; int y_down = data[3];
        y2 = (y_up+y_down)/2; //y_down + (y_up-y_down)/2  - if you scared/gonna work with big pictures(height/width more than 2**15)
        printf("%d - y2\n", y2 );
        x1 = x_up;
        x4 = x_down;
        rad = (x4-x1)/2;
    }
    x2 = x1 + rad/2;
    x3 = x4 - rad/2;
    y3 = y2 + rad*0.866;
    y1 = y2 - rad*0.866;
    BMP bmp = get_img(file_name);

    /*if(fill_flag){
        float d_c = 2*(y3-y1);
        float d_x = x1 - x2;
        float c_up = (x1*y1 - x2*y2)/d_x;
        float c_down = (x1*y3 - x2*y2)/d_x;
        fill_hexagon_v1(bmp.arr, fill_color, x1, x4, y1, y3, d_c, c_up, c_down);
    }
    */
    draw_thick_line(bmp, line_color, x2, y3, x3, y3, width, 1);
    draw_thick_line(bmp, line_color, x3, y3, x4, y2, width, 0);
    draw_thick_line(bmp, line_color, x4, y2, x3, y1, width, 0);
    draw_thick_line(bmp, line_color, x3, y1, x2, y1, width, 0);
    draw_thick_line(bmp, line_color, x2, y1, x1, y2, width, 1);
    draw_thick_line(bmp, line_color, x1, y2, x2, y3, width, 1);


    put_img(file_name, bmp);
    free_BMP(bmp);
}