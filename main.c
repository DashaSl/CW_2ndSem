#include "CWlib.h"
#include "read_write.h"
#include "func.h"


int main(){
    RGB clr = {0, 0, 0};
    RGB clr2 = {230, 150, 200};
    BMP bmp1 = get_img("blank.bmp");
    BMP bmp2 = get_img("blank.bmp");
    draw_Minkowski_sausage(bmp1, bmp2.arr, 0, 100, 200, 100, clr, 1);
    draw_Minkowski_sausage(bmp1, bmp2.arr, 150, 100, 350, 100, clr, 1);
    put_img("new.bmp", bmp1);
    return 0;
}
