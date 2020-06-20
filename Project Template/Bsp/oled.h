#include "spi.h"
#include "i2c.h"
#include "gpio.h"
#include <vector>
#include "buffer.h"



#define COLUMN_START   1
#define COLUMN_MIDDLE  63
#define COLUMN_END     127

#define BAR_HEIGHT     6

#define __NAME_TAG     0
#define __VALUE_TAG    1
#define __UNIT_TAG     2

extern ScreenLabel label_buffer[8];

typedef struct{
    uint8_t pos_x;
    uint8_t pos_y;
}CursorPos;

typedef enum{
    ASC6X8,
    ASC8X16,
    NUM16X24,
    ASC15X24,
}FontSize;

typedef enum{
    ALIGN_RIGHT,
    CENTER_TEXT,
    ALIGN_LEFT,
}AlignOption;

typedef enum{
    Bar_Filled,
    Bar_Hollow,
}BarOption;


typedef struct{
    uint8_t     page;
    uint8_t     column;
    AlignOption align;
    FontSize    fs;
}TextConfig;

typedef enum{
    SPI_SOFTWARE,
    SPI_HARDWARE,
    I2C_SOFTWARE,
    I2C_HARDWARE,
}OLED_DRIVER_MODE;

typedef enum{
    __STD,
    __VIVID,
    __COLUMN_CHART,
    __BAR_CHART,
    __NO_THEME,
}ThemeOption;

static const TextConfig themeTable__VIVID[3][MAX_GUI_LABELS] = {
    {//postion of <name> 
        {0,COLUMN_START         ,ALIGN_LEFT ,ASC8X16},  //tag0
        {6,COLUMN_START         ,ALIGN_LEFT ,ASC6X8},   //tag1
        {7,COLUMN_START         ,ALIGN_LEFT ,ASC6X8},   //tag2
        {6,COLUMN_START+9*6     ,ALIGN_LEFT ,ASC6X8},   //tag3
        {7,COLUMN_START+9*6     ,ALIGN_LEFT ,ASC6X8}},  //tag4

    {//postion of <value>  
        {2,COLUMN_MIDDLE        ,CENTER_TEXT,NUM16X24}, //tag0
        {6,COLUMN_START+3*6     ,ALIGN_LEFT ,ASC6X8},   //tag1
        {7,COLUMN_START+3*6     ,ALIGN_LEFT ,ASC6X8},   //tag2
        {6,COLUMN_START+12*6    ,ALIGN_LEFT ,ASC6X8},   //tag3
        {7,COLUMN_START+12*6    ,ALIGN_LEFT ,ASC6X8}},  //tag4

    {//postion of <unit> 
        {3,COLUMN_MIDDLE+8+16+2 ,ALIGN_LEFT ,ASC8X16},  //tag0
        {6,COLUMN_START+6*6     ,ALIGN_LEFT ,ASC6X8 },  //tag1
        {7,COLUMN_START+6*6     ,ALIGN_LEFT ,ASC6X8 },  //tag2
        {6,COLUMN_START+16*6    ,ALIGN_LEFT ,ASC6X8 },  //tag3
        {7,COLUMN_START+16*6    ,ALIGN_LEFT ,ASC6X8 }}  //tag4
};

static const TextConfig themeTable__COLUMN_CHART[3][MAX_GUI_LABELS] = {
    {//postion of <name> 
        {0,COLUMN_START+2       ,ALIGN_LEFT ,ASC8X16},  //tag0
        {3,COLUMN_START+2       ,ALIGN_LEFT ,ASC6X8 },  //tag1
        {4,COLUMN_START+2       ,ALIGN_LEFT ,ASC6X8 },  //tag2
        {5,COLUMN_START+2       ,ALIGN_LEFT ,ASC6X8 },  //tag3
        {6,COLUMN_START+2       ,ALIGN_LEFT ,ASC6X8 },  //tag4
        {7,COLUMN_START+2       ,ALIGN_LEFT ,ASC6X8 }}, //tag5
    

    {//postion of <value>  
        {0,COLUMN_START+2+6*8   ,ALIGN_LEFT ,ASC8X16},  //tag0
        {3,},   //tag1
        {4,},   //tag2
        {5,},   //tag3
        {6,},   //tag4
        {7,}},  //tag5
    

    {//postion of <unit> 
        {0,COLUMN_START+2+10*8  ,ALIGN_LEFT ,ASC8X16},  //tag0
        {},  //tag1
        {},  //tag2
        {},  //tag3
        {},  //tag4
        {}}, //tag5
};

class OLED:public SPI,public I2C{
public:
	OLED(SPI_TypeDef* base,PTX_n DC_Pin,PTX_n RST_Pin,uint8_t width,uint8_t height,const char* moduleName = "SSD1306");
	OLED(I2C_TypeDef* base,uint8_t width,uint8_t height,uint8_t addr = 0x78,const char* moduleName = "SSD1306");
	void fill(uint8_t data = 0xff);
	void fill(size_t page,uint8_t data,size_t pos_start,size_t pos_end);
	void clear(void);
	void clear(size_t page,size_t pos_start,size_t pos_end);
    void clear(size_t page_start,size_t page_end,size_t pos_start,size_t pos_end);
    void clear(size_t page,size_t pos_start,FontSize font,uint8_t NumOfLetter);
	void displayChar(uint8_t page,uint8_t column,char letter   ,FontSize font = ASC6X8);
	void displayStr(uint8_t page,uint8_t column,string&     str,FontSize font = ASC6X8,AlignOption align = ALIGN_LEFT,\
                    bool clear = false,uint8_t activeNumOfLetter = 0);
	void displayStr(uint8_t page,uint8_t column,const char* str,FontSize font = ASC6X8,AlignOption align = ALIGN_LEFT,\
                    bool clear = false,uint8_t activeNumOfLetter = 0);
	void bar(size_t page,size_t pos_start,size_t pos_end,BarOption bar_option);
    void progressBar(size_t page,size_t pos_start,size_t pos_end,float ratio);
    void line();
    void print(const char* format);
    void printTest(void);
    void lightness(uint8_t lightness);

    void GUIConfig(ScreenLabel* label ,ThemeOption theme);
    void GUIConfig(ScreenLabel* labels, size_t size,ThemeOption theme);
    void showResult(void);
private:
	void delay(void);
	void writeCMD(uint8_t cmd);
	void writeDAT(uint8_t data);
	void writeBYTE(uint8_t byte);
    inline uint8_t RecalculateAlignColumn(uint8_t column,size_t length,FontSize font,AlignOption align);
	string  moduleName;
	OLED_DRIVER_MODE driver;
	uint8_t i2c_slave_address;
	GPIO    DC;
    GPIO    RST;

    uint8_t width;
	uint8_t height;
	
	ScreenBuffer buf;
    ScreenLabel* label;
    ThemeOption  theme;
    	
};




