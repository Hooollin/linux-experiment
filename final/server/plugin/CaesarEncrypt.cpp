#include "EncryptionPlugin.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int FUNC_ID = 1;

class CaesarEncrypt : public EncryptionPlugin {
    public:
        CaesarEncrypt() {}

        ~CaesarEncrypt() {}

        virtual string help() {
            return "Function ID: " + to_string(FUNC_ID) + ", Caesar encryption.\n";
        }

        virtual string work(string input) {
            string encrypted;
            for (auto ch : input) {
                if (isalpha(ch)) {
                    encrypted += shift(ch);
                } else {
                    encrypted += ch;
                }
            }
            return encrypted;
        }

        int getID() { return FUNC_ID; }

    private:
        int shiftAmount = 15;

        char shift(char ch) {
            if (isupper(ch))
                return 'A' + ((ch - 'A') + shiftAmount) % 26;
            return 'a' + ((ch - 'a') + shiftAmount) % 26;
        }
};

extern "C" void createObj(EncryptionPlugin **plugin) {
    static CaesarEncrypt encryptor;
    *plugin = &encryptor;
}
