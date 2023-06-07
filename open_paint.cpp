#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string exec(string command) {
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

int main()
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = true;

    HINSTANCE hInstance = ShellExecuteA (NULL, "open", "mspaint.exe", NULL, NULL, SW_SHOWNORMAL);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    string output = exec("tasklist | findstr mspaint.exe");
    
    unsigned first = output.find(" ");
    unsigned last = output.find(" Console");

    string paintPID = output.substr(first,last-first);

    paintPID.erase(std::remove_if(paintPID.begin(), paintPID.end(), ::isspace),paintPID.end());

    DWORD result = strtol(paintPID.c_str(), 0, 0);

    cout << result;
    
    return 0;
}