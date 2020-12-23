#pragma once
class CountPlugin{
    public:
        CountPlugin();

        virtual ~CountPlugin();

        virtual void Count() = 0;
        virtual void Help() = 0;
        virtual int GetID() = 0;
};
