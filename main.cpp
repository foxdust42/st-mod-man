#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

//Returns console output of passed command
string exec(string command) {
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = _popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   _pclose(pipe);
   return result;
}

int main() {
   string ls = exec("ls");
   cout << ls;
}