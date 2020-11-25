#pragma once
#include <iostream>
#include <fstream>

class ILSerializable{
    public:
        virtual bool serialize(const char *p) = 0;

        virtual ILSerializable* deserialize(const char *p) = 0;

        virtual int getType() = 0;

        ILSerializable(){

        }

        virtual ~ILSerializable(){

        }

};
