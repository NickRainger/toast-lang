#include <iostream>
#include <string>

char src[] =
    "func->{"
    ;

enum Token {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5
};

static std::string IdentifierStr;
static double NumVal;

static int CurrChar = 0;

static int GetToken() {
    static int LastChar = ' ';
    
    while (isspace(LastChar)) {
        LastChar = getchar();
        if (isalpha(LastChar)) {
            IdentifierStr = LastChar;
            while (isalnum((LastChar = getchar())))
                IdentifierStr += LastChar;
            
            std::cout << IdentifierStr << std::endl;

            if (IdentifierStr == "def")
                return tok_def;
            if (IdentifierStr == "extern")
                return tok_def;
            return tok_identifier;
        }
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    if (LastChar == '#') {
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        
        if (LastChar != EOF)
            return GetToken();
    }

    if (LastChar == EOF || LastChar == 0)
        return tok_eof;
    
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

int main() {
    int token = GetToken();
    while (token != EOF) {
        std::cout << token << std::endl;
        int token = GetToken();
    }
    return 0;
}