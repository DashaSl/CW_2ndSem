#include "CWlib.h"
#include "read_write.h"
#include "func.h"
#include "getopt.h"


int main(int argc, char *argv[]){
    RGB clr1, clr2;
    int r, g, b;
    int clr1_is_taken_flag = 0; int clr2_is_taken_flag = 0;
    int width = -1; int radius = -1;
    int data[4];
    int xp = -1; int yp = -1;
    int data_len = 0;
    int flag_opt_choosen = 0;
    char option = 'h';
    char* file_name = NULL; char* output_file = NULL;
    int mode = -1; int fill_flag = -1;
    int some_index;

    opterr = 0;
    char* optstring = "hHCGFs:e:p:r:g:w:b:f:o:m:z:i:";
    struct option longg[] = {
            {"help",      no_argument, NULL, 'h'},
            {"hexagon",   no_argument, NULL, 'H'},
            {"copy",      no_argument, NULL, 'C'},
            {"changeclr", no_argument, NULL, 'G'},
            {"frame", no_argument, NULL, 'F'},
            {"start", required_argument, NULL, 's'},
            {"end", required_argument, NULL, 'e'},
            {"point", required_argument, NULL, 'p'},
            {"radius", required_argument, NULL, 'r'},
            {"rgb1", required_argument, NULL, 'g'},
            {"rgb2", required_argument, NULL, 'b'},
            {"width", required_argument, NULL, 'w'},
            {"file_name", required_argument, NULL, 'f'},
            {"out_file", required_argument, NULL, 'o'},
            {"mode", required_argument, NULL, 'm'},
            {"fill_flag", required_argument, NULL, 'z'},
            {"info", required_argument, NULL, 'i'}
    };
    int opt;
    while((opt = getopt_long(argc, argv, optstring, longg, &some_index)) != -1){
        switch(opt){
            case 'h':
                if(!flag_opt_choosen){
                    option = 'h';
                    flag_opt_choosen = 1;
                }else{
                    printf("you cant do two things at the same time. You are not Caesar.\n");
                    exit(1);
                }
                break;
            case 'H':
                if(!flag_opt_choosen){
                    option = 'H';
                    flag_opt_choosen = 1;
                }else{
                    printf("you cant do two things at the same time. You are not Caesar.\n");
                    exit(1);
                }
                break;
            case 'C':
                if(!flag_opt_choosen){
                    option = 'C';
                    flag_opt_choosen = 1;
                }else{
                    printf("you cant do two things at the same time. You are not Caesar.\n");
                    exit(1);
                }
                break;
            case 'G':
                if(!flag_opt_choosen){
                    option = 'G';
                    flag_opt_choosen = 1;
                }else{
                    printf("you cant do two things at the same time. You are not Caesar.\n");
                    exit(1);
                }
                break;
            case 'F':
                if(!flag_opt_choosen){
                    option = 'F';
                    flag_opt_choosen = 1;
                }else{
                    printf("you cant do two things at the same time. You are not Caesar.\n");
                    exit(1);
                }
                break;
            case 's':
                if(optind >= argc){
                    printf("not enough arguments\n");
                    exit(1);
                }
                if(not_num_check(optarg) || not_num_check(argv[optind])){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    data_len += 2;
                    data[0] = atoi(optarg);
                    data[1] = atoi(argv[optind]);
                }
                break;
            case 'e':
                if(optind >= argc){
                    printf("not enough arguments\n");
                    exit(1);
                }
                if(not_num_check(optarg) || not_num_check(argv[optind])){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    data_len += 2;
                    data[2] = atoi(optarg);
                    data[3] = atoi(argv[optind]);
                }
                break;
            case 'p':
                if(optind >= argc){
                    printf("not enough arguments\n");
                    exit(1);
                }
                if(not_num_check(optarg) || not_num_check(argv[optind])){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    xp = atoi(optarg);
                    yp = atoi(argv[optind]);
                }
                break;
            case 'r':
                if(not_num_check(optarg)){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    radius = atoi(optarg);
                }
                break;
            case 'g':
                if(optind+1 >= argc){
                    printf("not enough arguments\n");
                    exit(1);
                }
                if(clr1_is_taken_flag){
                    printf("you cant have two colors in one\n");
                    exit(1);
                }
                if(not_num_check(optarg) || not_num_check(argv[optind]) || not_num_check(argv[optind+1])){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    r = atoi(optarg);
                    g = atoi(argv[optind]);
                    b = atoi(argv[optind+1]);
                    if(r > 255 || g > 255 || b > 255){
                        printf("Impossible color! r, g, b should be less than 256\n");
                        exit(1);
                    }
                    clr1.r = r;
                    clr1.g = g;
                    clr1.b = b;
                }
                clr1_is_taken_flag = 1;
                break;
            case 'b':
                if(optind+1 >= argc){
                    printf("not enough arguments\n");
                    exit(1);
                }
                if(clr2_is_taken_flag){
                    printf("you cant have two colors in one\n");
                    exit(1);
                }
                if(not_num_check(optarg) || not_num_check(argv[optind]) || not_num_check(argv[optind+1])){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    r = atoi(optarg);
                    g = atoi(argv[optind]);
                    b = atoi(argv[optind+1]);
                    if(r > 255 || g > 255 || b > 255){
                        printf("Impossible color! r, g, b should be less than 256\n");
                        exit(1);
                    }
                    clr2.r = r;
                    clr2.g = g;
                    clr2.b = b;
                }
                clr2_is_taken_flag = 1;
                break;
            case 'w':
                if(not_num_check(optarg)){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    width = atoi(optarg);
                }
                break;
            case 'f':
                file_name = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'm':
                if(not_num_check(optarg)){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    mode = atoi(optarg);
                    if(mode != 0 && mode != 1 && mode != 2){
                        printf("mode can only be 2, 1 or 0\n");
                        exit(1);
                    }
                }
                break;
            case 'z':
                if(not_num_check(optarg)){
                    printf("There is an impostor! Not Natural number found.\n");
                    exit(1);
                }else{
                    fill_flag = atoi(optarg);
                    if(fill_flag != 0 && fill_flag != 1){
                        printf("fill flag can only be 1 or 0\n");
                        exit(1);
                    }
                }
                break;
            case 'i':
                printinf(optarg);
                return 0;
            case '?':
                printf("%c - is unknown.\n", optopt);
                return 0;

        }
    }
    if(data_len > 4){
        printf("why so many data?\n");
        exit(1);
    }
    switch(option){
        case 'h':
            printhelp();
            break;
        case 'H':
            if(mode == 1){
                data[2] = data[1];
                data[1] = data[0];
                data[0] = radius;
            }
            if(fill_flag == -1 || fill_flag == 0){
                clr2_is_taken_flag = 1;
                clr2.r = 0; clr2.b = 0; clr2.g = 0;
            }
            if(!file_name || data_len < 2 || mode == -1 || mode == 2 || width == -1 || !clr2_is_taken_flag || !clr2_is_taken_flag){
                printf("not enough arguments(or mode is equal 2)\n");
                exit(1);
            }
            if(mode == 0){
                if(!check_cord(data[0], data[1], data[2], data[3])){
                    printf("wrong order of coordinates\n");
                    exit(1);
                }
            }
            draw_hexagon(file_name, data, mode, width, clr1, fill_flag, clr2);
            break;
        case 'C':
            if(!file_name || !output_file || data_len < 4 || xp == -1 || yp == -1){
                printf("not enough arguments\n");
                exit(1);
            }
            if(!check_cord(data[0], data[1], data[2], data[3])){
                printf("wrong order of coordinates\n");
                exit(1);
            }
            copy_paste(file_name, output_file, data[0], data[1], data[2], data[3], xp, yp);
            break;
        case 'G':
            if(!file_name || !clr2_is_taken_flag || !clr1_is_taken_flag){
                printf("not enough arguments\n");
                exit(1);
            }
            change_color(file_name, clr1, clr2);
            break;
        case 'F':
            if(!file_name || !width || !clr1_is_taken_flag){
                printf("not enough arguments\n");
                exit(1);
            }
            if(mode == 0){
                draw_simple_frame(file_name, width, clr1);
            }else if(mode == 1){
                if(fill_flag == -1 || !clr2_is_taken_flag){
                    printf("not enough arguments\n");
                    exit(1);
                }
                draw_Koch_frame(file_name, width, fill_flag, clr1, clr2);
            }else{
                if(fill_flag == -1 || !clr2_is_taken_flag){
                    printf("not enough arguments\n");
                    exit(1);
                }
                draw_Minkowski_frame(file_name, width, fill_flag, clr1, clr2);
            }
            break;
    }
    return 0;
}
