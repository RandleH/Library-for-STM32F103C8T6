#include <iostream>
#include <string>
#include "oled.h"
#include "delay.h"
#include "font.h"
using namespace std; 

static const uint8_t CMD_List[] = {
    0xae,//--Turn off oled panel
	0x00,//--Set low column address
	0x10,//--Set high column address
	0x40,//--Set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	0x81,//--Set contrast control register
	0xcf,//--Set SEG Output Current Brightness
	0xa1,//--Set SEG/Column Mapping     
	0xc8,//--Set COM/Row Scan Direction 
	0xa6,//--Set normal display
	0xa8,//--Set multiplex ratio(1 to 64)
	0x3f,//--1/64 duty
	0xd3,//--Set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	0x00,//--Not offset
	0xd5,//--Set display clock divide ratio/oscillator frequency
	0x80,//--Set divide ratio, Set Clock as 100 Frames/Sec
	0xd9,//--Set pre-charge period
	0xf1,//--Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	0xda,//--Set com pins hardware configuration
	0x12,
	0xdb,//--set vcomh
	0x40,//--Set VCOM Deselect Level
	0x20,//--Set Page Addressing Mode (0x00/0x01/0x02)
	0x02,//
	0x8d,//--Set Charge Pump enable/disable
	0x14,//--Set(0x10) disable
	0xa4,//--Disable Entire Display On (0xa4/0xa5)
	0xa6,//--Disable Inverse Display On (0xa6/a7)
	0xaf,//--Turn on oled panel
};

OLED::OLED(SPI_TypeDef* base,PTX_n DC_Pin,PTX_n RST_Pin,uint8_t width,uint8_t height,const char* moduleName):\
SPI(base,80000000,true,0),DC(DC_Pin,GPO),RST(RST_Pin,GPO),I2C(),moduleName(moduleName),buf(width/6,height/8),\
theme(__NO_THEME){
	this->width  = width;
    this->height = height; 
    this->driver = SPI_HARDWARE;

    this->delay();
    this->RST.set(GPL);
    this->delay();
    this->RST.set(GPH);
    this->delay();

    for(int i=0;i<sizeof(CMD_List)/sizeof(*CMD_List);i++)
    	this->writeCMD(*(CMD_List+i));
    this->clear();
}

OLED::OLED(I2C_TypeDef* base,uint8_t width,uint8_t height,uint8_t addr,const char* moduleName):\
I2C(base,80000000),DC(),RST(),SPI(),moduleName(moduleName),buf(width/6,height/8),theme(__NO_THEME){
	this->width  = width;
    this->height = height; 
    this->driver = I2C_HARDWARE;
    this->i2c_slave_address = addr;

    this->delay();
    this->delay();

    for(int i=0;i <sizeof(CMD_List)/sizeof(*CMD_List);i++)
    	this->writeCMD(*(CMD_List+i));
    this->clear();
}

void OLED::writeCMD(uint8_t cmd){
	switch(this->driver){
		case SPI_HARDWARE:
		case SPI_SOFTWARE:this->DC.set(GPL);
		                  this->SPI::write(cmd);
		                  break;
		case I2C_HARDWARE:
		case I2C_SOFTWARE:this->I2C::write(this->i2c_slave_address,0x00,cmd);
		                  break;
	} 
}

void OLED::writeDAT(uint8_t data){
    switch(this->driver){
		case SPI_HARDWARE:
		case SPI_SOFTWARE:this->DC.set(GPH);
		                  this->SPI::write(data);
		                  break;
		case I2C_HARDWARE:
		case I2C_SOFTWARE:this->I2C::write(this->i2c_slave_address,0x40,data);
		                  break;
	}
}

void OLED::delay(void){delay_ms(50);}

void OLED::fill(uint8_t data){
	for(uint8_t y=0;y<(this->height>>3);y++){
		this->writeCMD(0xb0+y);
		if(this->moduleName.compare("SSD1106")==0)
			this->writeCMD(0x02);
		else
			this->writeCMD(0x01);       
		this->writeCMD(0x02);
		this->writeCMD(0x10);
		for(uint8_t x=0;x<this->width;x++)	
			this->writeDAT(data); 
	}
}

void OLED::fill(size_t page,uint8_t data,size_t pos_start,size_t pos_end){
    this->writeCMD(0xb0+page);
	this->writeCMD((pos_start>>4)|0x10);
	this->writeCMD(pos_start&0x0f);
	for(uint8_t i=pos_start;i<pos_end;i++)
		this->writeDAT(data);
}

void OLED::clear(void){ this->fill(0x00); }

void OLED::clear(size_t page,size_t pos_start,size_t pos_end){
    this->fill(page,0x00,pos_start,pos_end);
}

void OLED::clear(size_t page_start,size_t page_end,size_t pos_start,size_t pos_end){
	for(size_t i=page_start;i<page_end;i++)
		this->clear(i,pos_start,pos_end);
}

void OLED::clear(size_t page,size_t pos_start,FontSize font,uint8_t NumOfLetter){
	switch(font){
case NUM16X24:
    this->clear(page+2,pos_start,pos_start+NumOfLetter*FontBook[font]->width);
case ASC8X16:
    this->clear(page+1,pos_start,pos_start+NumOfLetter*FontBook[font]->width);
case ASC6X8:
    this->clear(page,pos_start,pos_start+NumOfLetter*FontBook[font]->width);
	}
}


void OLED::displayChar(uint8_t page,uint8_t column,char letter,FontSize font){
	switch(font){
case ASC6X8:
	letter -= ASCII_SHIFT;
	this->writeCMD(0xb0+page);
	this->writeCMD((column>>4)|0x10);
	this->writeCMD(column&0x0f);
	for(uint8_t i=0;i<font_6x8.width;i++)
		this->writeDAT(font_6x8.font[letter*font_6x8.width+i]);
    break;
case ASC8X16:
    letter -= ASCII_SHIFT;
    for(int i=0;i<2;i++){
		this->writeCMD(0xb0+page+i);
		this->writeCMD((column>>4)|0x10);
		this->writeCMD(column&0x0f);
		for(int cnt=0;cnt<font_8x16.width;cnt++)
			this->writeDAT(font_8x16.font[(letter<<4)+cnt+(i<<3)]);
	}
	break;
case NUM16X24:
	letter -= '0';
	letter %= 10;
	for(int i=0;i<3;i++){
		this->writeCMD(0xb0+page+i);
		this->writeCMD((column>>4)|0x10);
		this->writeCMD(column&0x0f);
		for(int cnt=0;cnt<font_16x24.width;cnt++)
			this->writeDAT(font_16x24.font[((letter*3)<<4)+cnt+(i<<4)]);
    }
	break;

	}

}

void OLED::displayStr(uint8_t page,uint8_t column,string& str,FontSize font,AlignOption align,bool clear,uint8_t activeNumOfLetter){
	uint8_t column_start = this->RecalculateAlignColumn(column,str.length(),font,align);
	if(clear==true){
        this->clear(page,this->RecalculateAlignColumn(column,activeNumOfLetter,font,align),font,activeNumOfLetter);
	}
	string::iterator p = str.begin();
    while(p != str.end()){
		this->displayChar(page,column_start,*(p++),font);
		switch(font){
			case ASC6X8:  column_start+=6; break;
			case ASC8X16: column_start+=8; break;
			case NUM16X24:column_start+=16;break;
	    }
	}
}

void OLED::displayStr(uint8_t page,uint8_t column,const char* str,FontSize font,AlignOption align,bool clear,uint8_t activeNumOfLetter){
    string  str_t(str);
	this->displayStr(page,column,str_t,font,align);
}

void OLED::bar(size_t page,size_t pos_start,size_t pos_end,BarOption bar_option){
	this->writeCMD(0xb0+page);
	this->writeCMD((pos_start>>4)|0x10);
	this->writeCMD(pos_start&0x0f);
	for(size_t i=pos_start;i<=pos_end;i++){
		if(i==pos_start||i==pos_end)
		    this->writeDAT(0xff);
        else{
        	if(bar_option == Bar_Filled)
        		this->writeDAT((uint8_t)((0xff+(i&0x01))|0x81));
        	else
        		this->writeDAT((uint8_t)0x81);
        }
	}

}

void OLED::progressBar(size_t page,size_t pos_start,size_t pos_end,float ratio){
	if(ratio > 1.0||ratio < 0.0) return;
	size_t joint = (size_t)((pos_end-pos_start)*ratio+pos_start);
    this->bar(page,pos_start,joint,Bar_Filled);
    this->bar(page,joint,pos_end,Bar_Hollow);
    this->clear(page,pos_end+1,this->width);
}

void OLED::print(const char* format){
	uint8_t column = 1;
	uint8_t selectedPage = 0;
	string& tmp = this->buf.toString(format);

	string::iterator p = tmp.begin();
    while(p != tmp.end()){
    	if(*p=='\n'){
    		this->clear(selectedPage,column,this->width);
    		selectedPage++;
    		column = 2;
    		p++;
    		continue;
    	}
		this->displayChar(selectedPage,column,*(p++));
		column+=6;
	}
}

void OLED::printTest(void){
	const char* str = "!@#$%^&*()_+-=.><?0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\n\n";
	this->print(str);
}

void OLED::lightness(uint8_t lightness){
	this->writeCMD(0x81);
	this->writeCMD(lightness);
}

void OLED::GUIConfig(ScreenLabel* label ,ThemeOption theme){
    if(label == NULL || theme == NULL) return;
    this->theme = __VIVID;
    label_buffer[0].name  = label[0].name;
	label_buffer[0].value = label[0].value;
	
	for(int i=1;i<MAX_GUI_LABELS;i++){
		label_buffer[i].name  = NULL;
	    label_buffer[i].value = NULL;
	}
}

void OLED::GUIConfig(ScreenLabel* labels, size_t size,ThemeOption theme){
    if(labels == NULL || theme == NULL) return;

	size_t NumOfLabel = 0;
	this->theme = theme;
	switch(theme){
case __VIVID:
        NumOfLabel = 5;break;
case __COLUMN_CHART:
        NumOfLabel = 6;break;
        
default:
case __NO_THEME:
    	return;
	}
	this->label = new ScreenLabel[NumOfLabel];
	for(size_t i=0;i<NumOfLabel;i++){
        	this->label[i].name  = labels[i].name;
			this->label[i].value = labels[i].value;
			this->label[i].unit  = labels[i].unit;
        }
	
    
}

#include "num.h"

void OLED::showResult(void){
	bool  clear_flag;
    static uint16_t* previous_value = new uint16_t[6];
	switch(this->theme){
		case __VIVID:
	    	
	    	clear_flag = true;
	        for(int i=0;i<5;i++){
	        	if(this->label[i].name!=NULL){
	                this->displayStr(themeTable__VIVID[__NAME_TAG][i].page,\
	                	             themeTable__VIVID[__NAME_TAG][i].column,\
	                	             this->label[i].name,\
	                	             themeTable__VIVID[__NAME_TAG][i].fs,\
	                	             themeTable__VIVID[__NAME_TAG][i].align);
	            }
	            if(this->label[i].value!=NULL){
	            	if(
	        			(previous_value[i] >=1000&&*(this->label[i].value)<1000)||
	            		(previous_value[i] >=100 && *(this->label[i].value)<100)||
	            		(previous_value[i] >=10  && *(this->label[i].value)<10) ||
	            		(*(this->label[i].value) >=100 && previous_value[i]<100)||
	            		(*(this->label[i].value) >=10  && previous_value[i] <10)||
	            		(*(this->label[i].value) >=1000&& previous_value[i]<1000)
	            		)
	            		clear_flag = true;
	            	else
	            		clear_flag = false;
	                string num = to_string(*(this->label[i].value));
	                this->displayStr(themeTable__VIVID[__VALUE_TAG][i].page,\
	                	             themeTable__VIVID[__VALUE_TAG][i].column,\
	                	             num,\
	                	             themeTable__VIVID[__VALUE_TAG][i].fs,\
	                	             themeTable__VIVID[__VALUE_TAG][i].align,\
	                	             clear_flag,4);
	                previous_value[i] = *(this->label[i].value);
	            }
	            if(this->label[i].unit!=NULL){
	            	this->displayStr(themeTable__VIVID[__UNIT_TAG][i].page,\
	            		             themeTable__VIVID[__UNIT_TAG][i].column,
	            		             this->label[i].unit,\
	            		             themeTable__VIVID[__UNIT_TAG][i].fs,\
	            		             themeTable__VIVID[__UNIT_TAG][i].align);
	            }
	        }
	        break;
	    case __COLUMN_CHART:
	    
	        for(int i=0;i<6;i++){
	        	
                if(this->label[i].name!=NULL){
	                this->displayStr(themeTable__COLUMN_CHART[__NAME_TAG][i].page,\
	                	             themeTable__COLUMN_CHART[__NAME_TAG][i].column,\
	                	             this->label[i].name,\
	                	             themeTable__COLUMN_CHART[__NAME_TAG][i].fs,\
	                	             themeTable__COLUMN_CHART[__NAME_TAG][i].align);
	            }

	        	if(this->label[i].value!=NULL){
	        		if(i==0){
	        			if(
	        			(previous_value[i] >=1000&&*(this->label[i].value)<1000)||
	            		(previous_value[i] >=100 && *(this->label[i].value)<100)||
	            		(previous_value[i] >=10  && *(this->label[i].value)<10) ||
	            		(*(this->label[i].value) >=100 && previous_value[i]<100)||
	            		(*(this->label[i].value) >=10  && previous_value[i] <10)||
	            		(*(this->label[i].value) >=1000&& previous_value[i]<1000)
	            		)
	            			clear_flag = true;
		            	else
		            		clear_flag = false;
		                string num = to_string(*(this->label[i].value));
		                this->displayStr(themeTable__COLUMN_CHART[__VALUE_TAG][i].page,\
		                	             themeTable__COLUMN_CHART[__VALUE_TAG][i].column,\
		                	             num,\
		                	             themeTable__COLUMN_CHART[__VALUE_TAG][i].fs,\
		                	             themeTable__COLUMN_CHART[__VALUE_TAG][i].align,\
		                	             clear_flag,4);
	        		}
	        	    else
	        		    this->progressBar(themeTable__COLUMN_CHART[__VALUE_TAG][i].page,\
	        			              36,\
	        			              125,\
	        			              MATH::normalization(*(this->label[i].value),0,4096) );
	        		previous_value[i] = *(this->label[i].value);
	        	}
	        	if(this->label[i].unit!=NULL){
	        		/* ... */
	        	}
	        }
	        break;
	    
	}

}

inline uint8_t OLED::RecalculateAlignColumn(uint8_t column,size_t length,FontSize font,AlignOption align){   
	switch(align){
		size_t temp;
		case ALIGN_RIGHT:temp = (size_t)(length*FontBook[font]->width);
		                 (column-temp)>0 ? column-=temp : column=0;break;
		case CENTER_TEXT:temp = (size_t)((length*FontBook[font]->width)>>1);
		                 (column-temp)>0 ? column-=temp : column=0; break;
		default:
		case ALIGN_LEFT: break;
	}
	return column;
}




