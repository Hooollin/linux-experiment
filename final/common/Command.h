#include <string>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Command{
    public:
        Command(){

        }
        Command(int _encryptionFunction, string _fileContent){
            encryptFunction = _encryptionFunction;
            fileContent = _fileContent;
        }

        ~Command(){

        }

        

        bool serialize(const char *p){
            ofstream ofs(p);           
            ofs << encryptFunction << "," << fileContent.size() << "," << fileContent;
            return true;
        }

        bool deserialize(const char *p){
            ifstream ifs(p);
            int len = 0;
            char comma;
            ifs >> encryptFunction;
            ifs >> comma;
            ifs >> len;
            ifs >> comma;
            if(ifs && len){
                vector<char> tmp(len);
                ifs.read(tmp.data(), len);
                fileContent.assign(tmp.data(), len);
            }
            return true;
        }
        
        int getEncryptionFunction(){
            return encryptFunction;
        }
        
        string getFileContent(){
            return fileContent;
        }

    private:
        int encryptFunction = 0;
        string fileContent;
};

