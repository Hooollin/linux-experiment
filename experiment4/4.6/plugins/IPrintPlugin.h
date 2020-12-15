#pragma once
class IPrintPlugin{
    public:
        IPrintPlugin();

        virtual ~IPrintPlugin();

        virtual void Print() = 0;
        virtual void Help() = 0;
        virtual int GetID() = 0;
};
