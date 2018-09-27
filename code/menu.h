#ifndef MENU_H_
#define MENU_H_



typedef enum{
        MENU_1, //main menu
        MENU_2, //set pass //set tel
        MENU_3, //set max ppm for lpg and smoke, also set max temp
        MENU_4, //startup and loading info section. also, show welcome massege meanwhile 
        MENU_5, 
        MENU_MAX
}Menu_Select_typedef;


typedef struct{
        int is_resigter;
        
        char pass[5];
        char tel[9];
        
        int ppm_lpg;
        int ppm_lpg_max;
        int ppm_smoke;
        int ppm_smoke_max;
        
        int temp;
        int temp_max;
        
        Menu_Select_typedef     next_menu;
        
        char lcd_line_1[16];
        char lcd_line_2[16];
        
        
        float Ro;// = 10;  //Ro is initialized to 10 kilo ohms

        char keypad_ready;
        char keypad_last;
        
}Data_typedef;


/*
 * function pointer:
 * we assigin a functin for every menu state
 * */
typedef void (*menu_fp) (Data_typedef *data);


typedef struct{
        Menu_Select_typedef     menu;
        Data_typedef            *data;
        menu_fp                 lcd_fp;
        menu_fp                 menu_fp;
}Menu_typedef;











void welcome(void);
void calib_mq2(void);
int pass_query(void);
int pass_set(void);
int tel_set(void);
int max_mq2_set(void);
int max_lm35_set(void);
void show_mq2_lm35(void);

void state_machine(void);
void set_state(void);

/*
menu_fp Menu_Functions[] = {



};

*/


extern Data_typedef g_data;
extern Menu_typedef g_menu;


#endif
