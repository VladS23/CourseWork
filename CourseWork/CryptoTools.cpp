#include "CryptoTools.h"
#include <iostream>
#include <windows.h>
#include <strsafe.h>
void ErrorExit(LPTSTR lpszFunction)
{


}
void MyHandleError(char* s)
{
    printf("Ошибка при работе программы.\n");
    printf("%s\n", s);
    printf("Номер ошибки %x\n.", GetLastError());
    printf("Программа завершена.\n");
    exit(1);
}
void CryptoTools::MyHandleError(char* s)
{
    HCRYPTPROV hCryptProv;
    HCRYPTKEY hKey;
    HCRYPTHASH hHash;
    CHAR szPassword[PASSWORD_LENGTH] = "";
    DWORD dwLength;
}
CryptoTools::~CryptoTools()
{
    if (hHash)
    {
        if (!(CryptDestroyHash(hHash))) {
            char er[32] = "Ошибка при уничтожении хеша";
            MyHandleError(er);
        }
    }

    if (hKey)
    {
        if (!(CryptDestroyKey(hKey))) {
            char er[32] = "Ошибка уничтожения ключа";
            MyHandleError(er);
        }
    }

    if (hCryptProv)
    {
        if (!(CryptReleaseContext(hCryptProv, 0))) {
            char er[34] = "Ошибка реализации контекста";
            MyHandleError(er);
        }
    }
}
CryptoTools::CryptoTools() {


    fprintf(stderr, "Введите пароль для генерации ключа: ");


    GetConsoleInput(szPassword, PASSWORD_LENGTH);
    dwLength = (DWORD)strlen(szPassword);


    if (CryptAcquireContext(
        &hCryptProv,
        NULL,
        NULL,
        PROV_RSA_FULL,
        0))
    {
        printf("Контекст был получен \n");
    }
    else
    {
        char er[34] = "Ошибка получения контекста";
        MyHandleError(er);
    }


    if (CryptCreateHash(
        hCryptProv,
        CALG_MD5,
        0,
        0,
        &hHash))
    {
        printf("Пустой объект хеша создан \n");
    }
    else
    {
        char er[33] = "Ошибка при создании пустого хеша";
        MyHandleError(er);
    }

    if (CryptHashData(
        hHash,
        (BYTE*)szPassword,
        dwLength,
        0))
    {
        printf("Пароль был создан \n");
    }
    else
    {
        char er[32] = "Ошибка создания пароля";
        MyHandleError(er);
    }
   

    if (CryptDeriveKey(
        hCryptProv,
        CALG_RC4,
        hHash,
        CRYPT_EXPORTABLE,
        &hKey))
    {
        printf("Ключ был создан \n");
    }
    else
    {
        char er[32] = "Ошибка создания ключа";
        MyHandleError(er);
    }

}
void CryptoTools::Crypt(char* chars, int charsLen)
{
    DWORD count = strlen(chars);
    DWORD bufSize = charsLen;
    if (!CryptEncrypt(hKey, NULL, true, 0, (BYTE*)chars, &count, charsLen))
    {
        LPCTSTR lpszFunction = (LPCTSTR)"gvhbn";
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);


        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
            (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
        StringCchPrintf((LPTSTR)lpDisplayBuf,
            LocalSize(lpDisplayBuf) / sizeof(TCHAR),
            TEXT("%s failed with error %d: %s"),
            lpszFunction, dw, lpMsgBuf);
        MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

        LocalFree(lpMsgBuf);
        LocalFree(lpDisplayBuf);
        ExitProcess(dw);
    }
}
void CryptoTools::Decrypt(char* chars, int charsLen)
{
    DWORD count1 = charsLen;
    if (!CryptDecrypt(hKey, 0, true, 0, (BYTE*)chars, &count1))
    {
        LPCTSTR lpszFunction = (LPCTSTR)"gvhbn";
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);

        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
            (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
        StringCchPrintf((LPTSTR)lpDisplayBuf,
            LocalSize(lpDisplayBuf) / sizeof(TCHAR),
            TEXT("%s failed with error %d: %s"),
            lpszFunction, dw, lpMsgBuf);
        MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

        LocalFree(lpMsgBuf);
        LocalFree(lpDisplayBuf);
        ExitProcess(dw);
    }
}
void CryptoTools::GetConsoleInput(char* strInput,
    UINT  intMaxChars)
{
    char ch;
    char minChar = ' ';
    minChar++;

    ch = (char)_getch();
    while (ch != '\r')
    {
        if (ch == '\b' && strlen(strInput) > 0)
        {
            strInput[strlen(strInput) - 1] = '\0';
            printf("\b \b");
        }
        else if ((ch >= minChar) && (strlen(strInput) < intMaxChars))
        {
            strInput[strlen(strInput) + 1] = '\0';
            strInput[strlen(strInput)] = ch;
            _putch('*');
        }
        ch = (char)_getch();
    }
    _putch('\n');
}




