#ifndef MENU_H_
#define MENU_H_



typedef enum{
        MENU_1, //main menu
        MENU_2, //set pass
        MENU_3, //set tel
        MENU_4, //set max ppm for lpg and smoke, also set max temp
        MENU_MAX
}Menu_Select_typedef;


typedef struct{
        char pass[5];
        char tel[9];
        int ppm_lpg_max;
        int ppm_smoke_max;
        int temp_max;
}Data_typedef;


typedef void (*menu_fp) (Data_typedef *data);

typedef struct{
        Menu_Select_typedef     menu;
        Data_typedef            *data;
        menu_fp                 lcd_fp;
        menu_fp                 menu_fp;
}Menu_typedef;


#endif
