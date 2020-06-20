#include <iostream>
#include <cstdint>

using namespace std;

#ifndef _BUFFER_H
#define _BUFFER_H 

#define MAX_GUI_LABELS 6

typedef uint8_t count_t;

class ScreenLabel{
public:
	ScreenLabel(){
		this->name  = NULL;
		this->value = NULL;
		this->unit  = NULL;
	}

	const char* name;
    uint16_t*    value;
    const char* unit;
};

class ScreenBuffer{
public:
	ScreenBuffer(uint8_t MaxTextPerLine,uint8_t MaxLinePerScreen);
    string& toString(const char* src);

private:
	uint8_t MaxTextPerLine;
	uint8_t MaxLinePerScreen;
	string  buffer;
	string& p;
	count_t countSections(void);
	
};


class SystemLogBuffer{
public:

};


#endif
