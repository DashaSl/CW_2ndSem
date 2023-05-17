#include "CWlib.h"
#include "func.h"
#include <math.h>

//fill algorithm
typedef struct NODE{
    int x;
    int y;
    struct NODE* next;
}NODE;

typedef struct que{
    NODE* tail;
    NODE* head;
    int size;
}que;

NODE* cr_node(int x_, int y_){
    NODE* ans = malloc(sizeof(NODE));
    ans->x = x_;
    ans->y = y_;
    ans->next = NULL;
    return ans;
}

void add_node(que* ochrd, int x, int y){
    NODE* tmp = cr_node(x, y);
    if(ochrd->size){
        ochrd->tail->next = tmp;
        ochrd->tail = tmp;
        ochrd->size++;
    }else {
        ochrd->size = 1;
        ochrd->tail = tmp;
        ochrd->head = tmp;
    }
}

void pop_first_node(que* ochrd){
    NODE* tmp = ochrd->head;
    ochrd->head = ochrd->head->next;
    ochrd->size--;
    free(tmp);
}

void fill_v2(BMP bmp, RGB fill_color, RGB line_color, int a, int b){
    que* ochrd = malloc(sizeof(que));
    ochrd->size = 0;
    add_node(ochrd, a, b);
    int x, y;
    int case1, case2;
    while(ochrd->size){
        x = ochrd->head->x;
        y = ochrd->head->y;
        case1 = x >= 0 && x < bmp.inf.Width;
        case2 =  y>=0 && y < abs(bmp.inf.Height);
        if(case1 && case2){
            case1 = !cmp_rgb(bmp.arr[y][x], fill_color);
            case2 = !cmp_rgb(bmp.arr[y][x], line_color);
            if(case1 && case2){
                change_clr(bmp.arr[y]+x, fill_color);
                add_node(ochrd, x+1, y);
                add_node(ochrd, x-1, y);
                add_node(ochrd, x, y+1);
                add_node(ochrd, x, y-1);
            }
        }
        pop_first_node(ochrd);
    }
    free(ochrd);
}

//end fill algorithm
//Koch start

int check_bmp(BMP bmp, int width){
    int case1 = width >= (abs(bmp.inf.Height)/2);
    int case2 = width >= bmp.inf.Width/2;
    return (case1 || case2);
}
void draw_Koch_snowflake(BMP bmp, int x1, int y1, int x2, int y2, RGB color, int n){
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

        draw_Koch_snowflake(bmp, x1, y1, x_new_1, y_new_1, color, n-1 );
        draw_Koch_snowflake(bmp, x_new_1, y_new_1, x_new, y_new, color, n-1 );
        draw_Koch_snowflake(bmp, x_new, y_new, x_new_2, y_new_2, color, n-1 );
        draw_Koch_snowflake(bmp, x_new_2, y_new_2, x2, y2, color, n-1 );

    }else{
        draw_line(bmp, color, x1, y1, x2, y2);
    }
}

int ret_n(int L_teory){
    int n = 1;
    if(L_teory > 50) n = 2;
    if(L_teory >= 100) n = 3;
    if(L_teory >= 250) n = 4;
    if(L_teory >= 500) n = 5;
    if(L_teory >= 1000) n = 6;
    return n;
}

void draw_Koch_frame(char* file_name, int width, int fill_flag, RGB line_color, RGB fill_color){
    BMP bmp_ans = get_img(file_name);
    if(check_bmp(bmp_ans, width)){
        printf("this frame will cover the whole picture! Dont do that\n");
        exit(1);
    }
    float L_theory = width * 2 * sqrt(3);

    int frame_width = bmp_ans.inf.Width - (2 * width);
    int frame_height = abs(bmp_ans.inf.Height) - (2 * width);

    int actual_num_wid = 1 + frame_width/L_theory;
    int actual_num_hei = 1 + frame_height/L_theory;

    int d_wid = frame_width/actual_num_wid;
    int d_hei = frame_height/actual_num_hei;

    int n_wid = ret_n(d_wid);
    int n_hei = ret_n(d_hei);
    int i;
    for(i = 0; i < actual_num_wid; i++){
        draw_Koch_snowflake(bmp_ans, width + (i+1)*d_wid, width, width + i*d_wid, width ,line_color , n_wid);
        draw_Koch_snowflake(bmp_ans, width + i*d_wid, abs(bmp_ans.inf.Height) - width, width + (i+1)*d_wid, abs(bmp_ans.inf.Height) - width , line_color, n_wid);
    }
    draw_line(bmp_ans, line_color, width + i*d_wid, width, bmp_ans.inf.Width - width, width);
    draw_line(bmp_ans, line_color, bmp_ans.inf.Width - width, abs(bmp_ans.inf.Height) - width, width + i*d_wid, abs(bmp_ans.inf.Height) - width);

    for(i = 0; i < actual_num_hei; i++){
        draw_Koch_snowflake(bmp_ans, width, width + i*d_hei, width, width + (i+1)*d_hei ,line_color , n_hei);
        draw_Koch_snowflake(bmp_ans, bmp_ans.inf.Width - width, width + (i+1)*d_hei, bmp_ans.inf.Width - width, width+ d_hei*i , line_color, n_hei);
    }
    draw_line(bmp_ans, line_color, width, abs(bmp_ans.inf.Height) - width, width, width + i*d_hei);
    draw_line(bmp_ans, line_color, bmp_ans.inf.Width - width, width + i*d_hei, bmp_ans.inf.Width - width, abs(bmp_ans.inf.Height) - width);

    if(fill_flag){
        fill_v2(bmp_ans, fill_color, line_color, 0, 0);
    }

    put_img(file_name, bmp_ans);
    free_BMP(bmp_ans);
}
//Koch end
//Minkowski start
void draw_Minkowski_sausage(BMP bmp, int x1, int y1, int x2, int y2, RGB color, int n){
    if(n){
        if(y1 == y2){
            int x_1 = (3*x1+x2)/4;
            int x_2 = (x1+x2)/2;
            int x_3 = (3*x2+x1)/4;
            int d_y = (x2-x1)/4;

            draw_Minkowski_sausage(bmp, x1, y1, x_1, y1,color, n-1);
            draw_Minkowski_sausage(bmp, x_1, y1, x_1, y1+d_y,color, n-1);
            draw_Minkowski_sausage(bmp, x_1, y1+d_y, x_2, y1+d_y,color, n-1);
            draw_Minkowski_sausage(bmp, x_2, y1+d_y, x_2, y1,color, n-1);

            draw_Minkowski_sausage(bmp, x_2, y1, x_2, y1-d_y,color, n-1);
            draw_Minkowski_sausage(bmp, x_2, y1-d_y, x_3, y1-d_y,color, n-1);
            draw_Minkowski_sausage(bmp, x_3, y1-d_y, x_3, y1,color, n-1);
            draw_Minkowski_sausage(bmp, x_3, y1, x2, y1, color, n-1);
        }else{
            int y_1 = (3*y1+y2)/4;
            int y_2 = (y1+y2)/2;
            int y_3 = (3*y2+y1)/4;
            int d_x = (y2-y1)/4;
            draw_Minkowski_sausage(bmp, x1, y1, x1, y_1,color, n-1);
            draw_Minkowski_sausage(bmp, x1, y_1, x1-d_x, y_1,color, n-1);
            draw_Minkowski_sausage(bmp, x1-d_x, y_1, x1-d_x, y_2,color, n-1);
            draw_Minkowski_sausage(bmp, x1-d_x, y_2, x1, y_2,color, n-1);

            draw_Minkowski_sausage(bmp, x1, y_2, x1+d_x, y_2,color, n-1);
            draw_Minkowski_sausage(bmp, x1+d_x, y_2, x1+d_x, y_3,color, n-1);
            draw_Minkowski_sausage(bmp, x1+d_x, y_3, x1, y_3,color, n-1);
            draw_Minkowski_sausage(bmp, x1, y_3, x1, y2,color, n-1);
        }
    }else{
        draw_line(bmp, color, x1, y1, x2, y2);
    }
}

int ret_n_Min(int n){
    int ans = 1;
    if(n > 40) ans = 2;
    if(n >= 130) ans = 3;
    if(n >= 350) ans = 4;
    return ans;
}

void draw_Minkowski_frame(char* file_name, int width, int fill_flag, RGB line_color, RGB fill_color){
    BMP bmp = get_img(file_name);
    if(check_bmp(bmp, width)){
        printf("this frame will cover the whole picture! Dont do that\n");
        exit(1);
    }
    int x_right = bmp.inf.Width - width;
    int x_left = width;

    int y_up = bmp.inf.Height - width;
    int y_down = width;

    int k_x = (x_right-x_left)/((width-1)*2);
    int k_y = (y_up-y_down)/((width-1)*2);

    int l_x = (x_right-x_left)/k_x;
    int l_y = (y_up-y_down)/k_y;
    int n = ret_n_Min(l_x);

    int i;
    for(i = 0; i < k_x; i++){
        draw_Minkowski_sausage(bmp, x_left + i*l_x, y_down, x_left + (i+1)*l_x, y_down, line_color, n);
        draw_Minkowski_sausage(bmp, x_right - (i+1)*l_x, y_up, x_right - i*l_x, y_up, line_color, n);
    }
    draw_line(bmp, line_color, x_left + (i)*l_x, y_down, x_right, y_down);
    draw_line(bmp, line_color, x_left, y_up, x_right - (i)*l_x, y_up);

    n = ret_n_Min(l_y);
    for(i = 0; i < k_y; i++){
        draw_Minkowski_sausage(bmp, x_left, y_up - i*l_y , x_left, y_up - (i+1)*l_y, line_color, n);
        draw_Minkowski_sausage(bmp, x_right, y_down + (i+1)*l_y, x_right, y_down + i*l_y, line_color, n);
    }
    draw_line(bmp, line_color, x_left, y_up - i*l_y, x_left, y_down);
    draw_line(bmp, line_color, x_right, y_down + i*l_y, x_right, y_up);

     if(fill_flag){
         fill_v2(bmp, fill_color, line_color, 0, 0);
     }
    put_img(file_name, bmp);
    free_BMP(bmp);
}
//Minkowski end
//simple start
void draw_simple_frame(char* file_name, int width, RGB fill_color){
    BMP bmp = get_img(file_name);
    if(check_bmp(bmp, width)){
        printf("this frame will cover the whole picture! Dont do that\n");
        exit(1);
    }
    int wid = bmp.inf.Width;
    int hei = abs(bmp.inf.Height);
    draw_thick_line(bmp, fill_color,0, 0, 0, hei-1, width, 1);
    draw_thick_line(bmp, fill_color,wid-1, 0, wid-1, hei-1, width, 0);
    draw_thick_line(bmp, fill_color,0, hei-1, wid-1, hei-1, width, 1);
    draw_thick_line(bmp, fill_color,0, 0, wid-1, 0, width, 0);

    draw_thick_line(bmp, fill_color,0, 0, 0, hei-1, width, 1);
    draw_thick_line(bmp, fill_color,wid-1, 0, wid-1, hei-1, width, 0);
    draw_thick_line(bmp, fill_color,0, hei-1, wid-1, hei-1, width, 1);
    draw_thick_line(bmp, fill_color,0, 0, wid-1, 0, width, 0);

    put_img(file_name, bmp);
    free_BMP(bmp);
}
//simple end