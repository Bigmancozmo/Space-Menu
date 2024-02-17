#pragma once

class SMRandomData(){
public:
    void setIsOpen(bool val);
    bool getIsOpen();
private:
    bool gui_isOpen = false;
}

void SMRandomData::setIsOpen(bool val){
    gui_isOpen = val;
}

bool SMRandomData::getIsOpen(){
    return gui_isOpen;
}