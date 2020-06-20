
#include <string.h>
#include "buffer.h"

ScreenLabel label_buffer[MAX_GUI_LABELS];

ScreenBuffer::ScreenBuffer(uint8_t MaxTextPerLine,uint8_t MaxLinePerScreen):p(this->buffer){
	this->MaxTextPerLine = MaxTextPerLine;
	this->MaxLinePerScreen = MaxLinePerScreen;
}


string& ScreenBuffer::toString(const char* src){
	string tmpStr;
    int EraseSectionCount = -1;
	const int TotalTextSection = strlen(src)/this->MaxTextPerLine+1; 
    for(int i=0;i<TotalTextSection;i++){
        EraseSectionCount = this->countSections() - this->MaxLinePerScreen;
    	if(EraseSectionCount >= 0){
            size_t postion = 0,last_postion = 0;
            do{
                postion = this->p.find('\n',last_postion)+1;
                this->p.erase(last_postion,postion);
                last_postion = postion;
            }while(EraseSectionCount--);
    	}
        tmpStr.assign(src,i*this->MaxTextPerLine,this->MaxTextPerLine);
        this->p.append(tmpStr.data());
        this->p.append("\n");
    }
    return this->p;
}

count_t ScreenBuffer::countSections(void){
	int position=0;
    int i=0;
    while((position=(int)this->p.find("\n",position))!=string::npos){
        position++;
        i++;
        //cout<<"position  "<<i<<" : "<<position<<endl;
    }
    //cout<<"i="<<i<<endl;
    return i;
}



