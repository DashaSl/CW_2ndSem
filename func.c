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

int check_bmp_c_p(BMP sour, BMP paste, int xs1, int ys1, int xs2, int ys2, int xp, int yp){
    int sour_wid = sour.inf.Width;
    int sour_hei = abs(sour.inf.Height);

    int pa_wid = paste.inf.Width;
    int pa_hei = abs(paste.inf.Height);
    //if x1, y1, x2, y2 inside the pick
    int case1 = (xs1 <0) || (xs1 >= sour_wid);
    int case2 = (ys1 < 0) || (ys1 >= sour_hei);
    int case3 = (xs2 <0) || (xs2 >= sour_wid);
    int case4 = (ys2 < 0) || (ys2 >= sour_hei);
    //if xp, yp
    int case5 = (yp < 0) || (yp >= pa_hei);
    int case6 = (xp < 0) || (xp >= pa_wid);
    //if there is a place
    int cmp_wid = xs2 - xs1;
    int cmp_hei = ys1 - ys2;

    int case7 = (pa_wid - xp) < cmp_wid;
    int case8 = yp < cmp_hei;
    return (case1 || case2 || case3 || case4 || case5 || case6 || case7 || case8);
}

void copy_paste(char* source, char* paste_here, int xs1, int ys1, int xs2, int ys2, int xp, int yp){
    BMP sour = get_img(source);
    BMP paste = get_img(paste_here);
    if(check_bmp_c_p(sour, paste, xs1, ys1, xs2, ys2, xp, yp)){
        printf("impossible coordinates for these pictures!\n");
        exit(1);
    }
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
        int wid = width/0.87; // 0.87 ~ sin(60), but it would be better to use math.h here, but gcc can't eat it correctly
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

void fill_hexagon_v1(RGB** arr, RGB fill_color, int x1, int x2, int y1, int y2, float* c, float* b){
    for(int x = x1; x <= x2; x++){
        for(int y = y1; y <= y2; y++){
            if(x >= lin_func(b[0], c[0], y) && x <= lin_func(b[1], c[1], y) && x <= lin_func(b[2], c[2], y) && x >= lin_func(b[3], c[3], y)){
                change_clr(arr[y]+x, fill_color);
            }
        }
    }
}

float b_k(int x1, int y1, int x2, int y2){
    float d_y = y1-y2;
    float b = (x1-x2)/d_y;
    return b;
}

float c_k(int x1, int y1, int x2, int y2){
    float d_y = y1-y2;
    float c = (y1*x2 - y2*x1)/d_y;
    return c;
}

int check_coord_hex(BMP bmp,int x1, int x2, int y1, int y2, int width){
    int hei = abs(bmp.inf.Height);
    int wid = bmp.inf.Width;
    int case1 = x1 < 0 || x1 >= wid;
    int case2 = x2 <0 || x2 >= wid;
    int case3 = y1 < 0 || y1 >= hei;
    int case4 = y2 < 0 || y2 >= hei;
    int case5 = (width > (x2 - x1)) || (width > (y2 - y1));
    return (case1 || case2 || case3 || case4 || case5);
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
        int x_right = data[0]; int y_up = data[1]; int x_left = data[2]; int y_down = data[3];
        y2 = (y_up+y_down)/2; //y_down + (y_up-y_down)/2  - if you scared/gonna work with big pictures(height/width more than 2**15)
        x1 = x_right;
        x4 = x_left;
        rad = (x4-x1)/2;
    }
    x2 = x1 + rad/2;
    x3 = x4 - rad/2;
    y3 = y2 + rad*0.866;
    y1 = y2 - rad*0.866;
    BMP bmp = get_img(file_name);

    if(check_coord_hex(bmp, x1, x4, y1, y3, width)){
        printf("impossible coordinates\n");
        exit(1);
    }

    if(fill_flag){
        float* c = malloc(sizeof(float)*4);
        float* b = malloc(sizeof(float)*4);
        if(c == NULL || b == NULL){
            printf("couldn't do malloc in draw_hexagon.\n");
            exit(1);
        }
        c[0] = c_k(x1, y2, x2, y3);
        c[1] = c_k(x3, y3, x4, y2);
        c[2] = c_k(x4, y2, x3, y1);
        c[3] = c_k(x2, y1, x1, y2);

        b[0] = b_k(x1, y2, x2, y3);
        b[1] = b_k(x3, y3, x4, y2);
        b[2] = b_k(x4, y2, x3, y1);
        b[3] =  b_k(x2, y1, x1, y2);
        fill_hexagon_v1(bmp.arr, fill_color, x1, x4, y1, y3, c, b);
        free(c);
        free(b);
    }

    draw_thick_line(bmp, line_color, x1, y2, x2, y3, width, 1); //c[0], b[0] - left up side
    draw_thick_line(bmp, line_color, x2, y3, x3, y3, width, 1);
    draw_thick_line(bmp, line_color, x3, y3, x4, y2, width, 0); //c[1] b[1] - right up side
    draw_thick_line(bmp, line_color, x4, y2, x3, y1, width, 0); //c[2] b[2] - right down side
    draw_thick_line(bmp, line_color, x3, y1, x2, y1, width, 0);
    draw_thick_line(bmp, line_color, x2, y1, x1, y2, width, 1); //c[3] b[3] - left down side

    put_img(file_name, bmp);
    free_BMP(bmp);
}
