#include <iostream>
#include <Windows.h>

int main()
{
    int code = MessageBox(0, L"content", L"title", MB_OKCANCEL);
    if (code == IDOK)
    {
        std::cout << "ok";
    }
    else if (code == IDCANCEL)
    {
        std::cout << "cancel";
    }

    return 0;
}
