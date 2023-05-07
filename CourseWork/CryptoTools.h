#pragma comment(lib, "crypt32.lib")
#pragma once
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <Wincrypt.h>

#define MY_ENCODING_TYPE  (CALG_RC4)
void MyHandleError(char* s);
void GetConsoleInput(char*, UINT);
#define PASSWORD_LENGTH 512
using namespace std;
class CryptoTools
{
private:
    HCRYPTPROV hCryptProv;
    HCRYPTKEY hKey;
    HCRYPTHASH hHash;
    CHAR szPassword[PASSWORD_LENGTH] = "";
    DWORD dwLength;
	void MyHandleError(char* s);
    void GetConsoleInput(char* strInput,
        UINT  intMaxChars);

public:
	CryptoTools();
    ~CryptoTools();
    void Crypt(char* chars, int charsLen);
    void Decrypt(char* chars, int charsLen);
};

