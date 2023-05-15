#include "CWlib.h"
#include "func.h"
#include <math.h>
void erase_line(BMP bmp, RGB** arr_copy,  int x1, int y1, int x2, int y2){
    if(x1 == x2){
        int min = y1;
        int max = y2;
        if(y1 > y2){
            min = y2;
            max = y1;
        }
        for(int i = min; i <= max; i++){
            change_clr((bmp.arr)[i]+x1,arr_copy[i][x1]);
        }
    }else if (y1 == y2){
        int min = x1;
        int max = x2;
        if(x1 > x2){
            min = x2;
            max = x1;
        }
        for(int i = min; i <= max; i++){
            change_clr((bmp.arr)[y1]+i,arr_copy[y1][i]);
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
            change_clr((bmp.arr)[tmp_y]+i, arr_copy[tmp_y][i]);
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
            change_clr((bmp.arr)[i]+tmp_x,arr_copy[i][tmp_x]);
        }
    }
}

void draw_Koch_snowflake(BMP bmp,RGB** arr_copy, int x1, int y1, int x2, int y2, RGB color, int n){
    if(n){
        float L = hypot((x1-x2), (y1-y2));
        float cos_x = (x2-x1)/L;
        float sin_x = (y2-y1)/L;
        float h = (L/3) * (sqrt(3)/2);
        int x_new = ((x1+x2)/2)- h*sin_x;
        int y_new = ((y1+y2)/2) + h*cos_x;
        int d_x = x2-x1; int d_y = y2-y1;
        int x_new_1 = x1 +d_x/3; int x_new_2 = x2 - d_x/3;
        int y_new_1 = y1 +d_y/3; int y_new_2 = y2 - d_y/3;

        erase_line(bmp, arr_copy, x1, y1, x2, y2);
        draw_line(bmp, color, x1, y1, x_new_1, y_new_1);
        draw_line(bmp, color, x_new_2, y_new_2, x2, y2);

        draw_line(bmp, color, x_new_1, y_new_1, x_new, y_new);
        draw_line(bmp, color, x_new, y_new, x_new_2, y_new_2);
        draw_Koch_snowflake(bmp, arr_copy, x1, y1, x_new_1, y_new_1, color,n-1);
        draw_Koch_snowflake(bmp, arr_copy, x_new_1, y_new_1, x_new, y_new, color,n-1);
        draw_Koch_snowflake(bmp, arr_copy, x_new, y_new, x_new_2, y_new_2, color,n-1);
        draw_Koch_snowflake(bmp, arr_copy, x_new_2, y_new_2, x2, y2, color,n-1);

    }
}

void fill_frame(BMP bmp, RGB fill_color, RGB line_color, int x, int y){ //better not use this, cause it works only with small pictures (otherwise stak overflow, cause too many recursions)
    int case1 = x >= 0 && x < bmp.inf.Width;
    int case2 = y >= 0 && y < abs(bmp.inf.Height);
    if(case1 && case2){
        int case3 = !cmp_rgb(bmp.arr[y][x], fill_color);
        int case4 = !cmp_rgb(bmp.arr[y][x], line_color);
        if(case3 && case4){
            change_clr(bmp.arr[y] + x, fill_color);
            fill_frame(bmp, fill_color, line_color, x+1, y);
            fill_frame(bmp, fill_color, line_color, x-1, y);
            fill_frame(bmp, fill_color, line_color, x, y+1);
            fill_frame(bmp, fill_color, line_color, x, y-1);
        }
    }
}

int ret_n(int L_teory){
    int n = 1;
    if(L_teory > 75) n = 2;
    if(L_teory > 200) n = 3;
    if(L_teory > 400) n = 4;
    if(L_teory > 600) n = 5;
    return n;
}

void draw_Koch_frame(char* file_name, int width, int fill_flag, RGB line_color, RGB fill_color){
    BMP bmp_ans = get_img(file_name);
    BMP bmp_copy = get_img(file_name);
    float L_theory = width * 2 * sqrt(3);
    int frame_width = bmp_ans.inf.Width - (2 * width);
    int frame_height = abs(bmp_ans.inf.Height) - (2 * width);
    int actual_num_wid = 2 + frame_width/L_theory;
    int actual_num_hei = 2 + frame_height/L_theory;
    int d_wid = frame_width/actual_num_wid;
    int d_hei = frame_height/actual_num_hei;

    draw_line(bmp_ans, line_color, width, width, width, bmp_ans.inf.Height - width);
    draw_line(bmp_ans, line_color, width, bmp_ans.inf.Height - width, bmp_ans.inf.Width -width, bmp_ans.inf.Height - width);
    draw_line(bmp_ans, line_color, bmp_ans.inf.Width -width, bmp_ans.inf.Height - width, bmp_ans.inf.Width - width, width);
    draw_line(bmp_ans, line_color, bmp_ans.inf.Width - width, width, width, width);

    int n_wid = ret_n(d_wid);
    int n_hei = ret_n(d_hei);
    for(int i = 0; i < actual_num_wid; i++){
        draw_Koch_snowflake(bmp_ans, bmp_copy.arr, width + (i+1)*d_wid, width, width + i*d_wid, width ,line_color , n_wid);
        draw_Koch_snowflake(bmp_ans, bmp_copy.arr, width + i*d_wid, abs(bmp_ans.inf.Height) - width, width + (i+1)*d_wid, abs(bmp_ans.inf.Height) - width , line_color, n_wid);
    }
    for(int i = 0; i < actual_num_hei; i++){
        draw_Koch_snowflake(bmp_ans, bmp_copy.arr, width, width + i*d_hei, width, width + (i+1)*d_hei ,line_color , n_hei);
        draw_Koch_snowflake(bmp_ans, bmp_copy.arr, bmp_ans.inf.Width - width, width + (i+1)*d_hei, bmp_ans.inf.Width - width, width+ d_hei*i , line_color, n_hei);
    }
    /*if(fill_flag){
        fill_frame(bmp_ans, fill_color, line_color, 0, 0);
    }*/
    put_img(file_name, bmp_ans);
    free_BMP(bmp_ans);
    free_BMP(bmp_copy);
}

void draw_Minkowski_sausage(BMP bmp,RGB** arr_copy, int x1, int y1, int x2, int y2, RGB color, int n){
    if(n){
        if(y1 == y2){
            int x_1 = (3*x1+x2)/4;
            int x_2 = (x1+x2)/2;
            int x_3 = (3*x2+x1)/4;
            int d_y = (x2-x1)/4;

            draw_Minkowski_sausage(bmp, arr_copy, x1, y1, x_1, y1,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x_1, y1, x_1, y1+d_y,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x_1, y1+d_y, x_2, y1+d_y,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x_2, y1+d_y, x_2, y1,color, n-1);

            draw_Minkowski_sausage(bmp, arr_copy, x_2, y1, x_2, y1-d_y,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x_2, y1-d_y, x_3, y1-d_y,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x_3, y1-d_y, x_3, y1,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x_3, y1, x2, y1, color, n-1);
        }else{
            int y_1 = (3*y1+y2)/4;
            int y_2 = (y1+y2)/2;
            int y_3 = (3*y2+y1)/4;
            int d_x = (y2-y1)/4;
            draw_Minkowski_sausage(bmp, arr_copy, x1, y1, x1, y_1,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x1, y_1, x1-d_x, y_1,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x1-d_x, y_1, x1-d_x, y_2,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x1-d_x, y_2, x1, y_2,color, n-1);

            draw_Minkowski_sausage(bmp, arr_copy, x1, y_2, x1+d_x, y_2,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x1+d_x, y_2, x1+d_x, y_3,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x1+d_x, y_3, x1, y_3,color, n-1);
            draw_Minkowski_sausage(bmp, arr_copy, x1, y_3, x1, y2,color, n-1);
        }
    }else{
        if(y1 == y2){
            int x_1 = (3*x1+x2)/4;
            int x_2 = (x1+x2)/2;
            int x_3 = (3*x2+x1)/4;
            int d_y = (x2-x1)/4;

            draw_line(bmp, color, x1, y1, x_1, y1);
            draw_line(bmp, color, x_1, y1, x_1, y1+d_y);
            draw_line(bmp, color, x_1, y1+d_y, x_2, y1+d_y);
            draw_line(bmp, color, x_2, y1+d_y, x_2, y1);

            draw_line(bmp, color, x_2, y1, x_2, y1-d_y);
            draw_line(bmp, color, x_2, y1-d_y, x_3, y1-d_y);
            draw_line(bmp, color, x_3, y1-d_y, x_3, y1);
            draw_line(bmp, color, x_3, y1, x2, y1);
        }else{
            int y_1 = (3*y1+y2)/4;
            int y_2 = (y1+y2)/2;
            int y_3 = (3*y2+y1)/4;
            int d_x = (y2-y1)/4;
            draw_line(bmp, color, x1, y1, x1, y_1);
            draw_line(bmp, color, x1, y_1, x1-d_x, y_1);
            draw_line(bmp, color, x1-d_x, y_1, x1-d_x, y_2);
            draw_line(bmp, color, x1-d_x, y_2, x1, y_2);

            draw_line(bmp, color, x1, y_2, x1+d_x, y_2);
            draw_line(bmp, color, x1+d_x, y_2, x1+d_x, y_3);
            draw_line(bmp, color, x1+d_x, y_3, x1, y_3);
            draw_line(bmp, color, x1, y_3, x1, y2);

        }
    }
}

void draw_Minkowski_frame(char* file_name, int width, int fill_flag, RGB line_color, RGB fill_color){
    BMP bmp_ans = get_img(file_name);
    BMP bmp_copy = get_img(file_name);



    /*if(fill_flag){
        fill_frame(bmp_ans, fill_color, line_color, 0, 0);
    }*/
    put_img(file_name, bmp_ans);
    free_BMP(bmp_ans);
    free_BMP(bmp_copy);
}