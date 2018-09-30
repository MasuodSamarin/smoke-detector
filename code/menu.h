#ifndef MENU_H_
#define MENU_H_


/*eeprom address book*/
#define IS_REGISTER_ADDR 0x00

#define LPG_MAX_REGISTER_ADDR 0x04
#define SMK_MAX_REGISTER_ADDR 0x08
#define TMP_MAX_REGISTER_ADDR 0x0A

#define PASS_REGISTER_ADDR 0x20
#define PASS_REGISTER_LENGTH 5

#define TEL_REGISTER_ADDR 0x30
#define TEL_REGISTER_LENGTH 12



typedef enum{
        MENU_1=0, //main menu
        MENU_2, //set pass //set tel
        MENU_3, //set max ppm for lpg and smoke, also set max temp
        MENU_4, //startup and loading info section. also, show welcome massege meanwhile 
        MENU_5,
        MENU_6, 
        MENU_MAX
}Menu_Select_typedef;


typedef struct{
        int is_resigter;
        
        char pass[5];
        char tel[12];
        
        int ppm_lpg;
        int ppm_lpg_max;
        int ppm_smoke;
        int ppm_smoke_max;
        
        int temp;
        int temp_max;
        
        Menu_Select_typedef     next_menu;
        
        //char lcd_line_1[16];
        //char lcd_line_2[16];
        
        
        float Ro;// = 10;  //Ro is initialized to 10 kilo ohms

        char keypad_ready;
        char keypad_last;
        
        
        int warn;
        
        
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






void reset_keypad(void);




void welcome(void);
void calib_mq2(void);
int pass_query(void);
int pass_set(void);
int tel_set(void);
int max_mq2_set(void);
int max_lm35_set(void);
void main_menu(void);

void state_machine(void);
void set_state(void);


void warn_handler(void);
void show_warn(void);
int warning(void);
void reset_warn(void);

void eeprom_save(void);
int eeprom_read(void);
/*
menu_fp Menu_Functions[] = {



};

*/

void my_test_eep(void);

extern Data_typedef g_data;
extern Menu_typedef g_menu;


#endif
