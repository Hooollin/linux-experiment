#include "EncryptionPlugin.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int FUNC_ID = 2;

class CaesarDecrypt : public EncryptionPlugin {
    public:
        CaesarDecrypt() {}

        ~CaesarDecrypt() {}

        virtual string help() {
            return "Function ID: " + to_string(FUNC_ID) + ", Caesar decryption.\n";
        }

        virtual string work(string input) {
            string decrypted;
            for (auto ch : input) {
                if (isalpha(ch)) {
                    decrypted += shift(ch);
                } else {
                    decrypted += ch;
                }
            }
            return decrypted;
        }

        int getID() { return FUNC_ID; }

    private:
        int shiftAmount = 15;

        char shift(char ch) {
            if (isupper(ch))
                return 'A' + ((ch - 'A') - shiftAmount + 26) % 26;
            return 'a' + ((ch - 'a') - shiftAmount + 26) % 26;
        }
};

extern "C" void createObj(EncryptionPlugin **plugin) {
    static CaesarDecrypt decryptor;
    *plugin = &decryptor;
}
