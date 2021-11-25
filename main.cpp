#include <iostream>
//#include <stdexcept>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

/*
//Executes a console command and returns it's console output
//Stolen from https://www.tutorialspoint.com/How-to-execute-a-command-and-get-the-output-of-command-within-Cplusplus-using-POSIX
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
*/

bool safety_check(){
   char control = '\0';
   while (true)
   {
      cout<<"Do you wish to Continue? [Y/n]:";
      cin>>control;
      if (control == 'Y')
      {
         cout<<"Continiuing...\n";
         return 1;
      }
      else if (control == 'n' || control == 'N')
      {
         cout<<"Terminating program...";
         return 0;
      }
      else
      {
         cout<<"Input not understood, please try again.\n";
      }
   }
   return 0;
}

int main(int argc, char const *argv[]) {
   
   cout << "Program Begin\n";
   //Safety check begin
   if(safety_check()==0){return 0;};
   //Safety check end
   fs::path root;
   while (true)
   {
      std::string s;
      cout<<"Enter path to directory:\n";
      cin.ignore();
      getline(cin, s);
      if (s[0]=='"')
      {
         s.erase(0,1);
         s.erase(s.length()-1,1);
      }
      root = s; 
      if(fs::is_directory(root)==1){
         cout<<"Directory dedected.\n";
         cout<<"This program has no real way of checking this directoies' contents.\n";
         cout<<"Please make sure that the entered directory has >>only<< the folders you wish to affect.\n";
         if(safety_check()==1){
            break;
         }
         else
         {
            return 0;
         }
      }
      else
      {
         cout<<"not a directory\n";
         if(safety_check()==0){
            return 0;
         }
      }
   }
   
   std::vector<fs::path> list;
   
/*    //debug block
   cout<<"Full dir:\n";
   for (const auto & entry : fs::directory_iterator(root)){
      cout<<entry.path()<<"\n";
   } */
   
   cout<<"\nSub-dirs only:\n";
   for (const auto & entry : fs::directory_iterator(root)){
      if (fs::is_directory(entry.path())==1)
      {
         cout<<entry.path()<<"\n";
         list.push_back(entry.path());
      }
   }
 /*   //debug block
   cout<<"\nlist array 1:\n";
   for (int i = 0; i < list.size(); i++)
   {
      cout<<list[i]<<endl;
   } */

   for (int i = 0; i < list.size(); i++)
   {
      if (fs::is_regular_file(list[i]/"descriptor.mod")==1)
      {
         list[i]=list[i]/"descriptor.mod";
      }
      else
      {
         list.erase(list.begin()+i);
         i--;
      }
      
   }
   
/*    //debug block
    cout<<"\nlist array 2:\n";
   for (int i = 0; i < list.size(); i++)
   {
      cout<<list[i]<<endl;
   }
 */
   return 0;
}