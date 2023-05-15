#include "CWlib.h"
#include "read_write.h"
#include "func.h"


int main(){
    RGB clr = {0, 0, 0};
    RGB clr2 = {230, 150, 200};
    draw_Minkowski_frame("ver3.bmp", 30, 0, clr, clr);
    return 0;
}
