#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

std::string back_to_front(std::string s){
   std::size_t a=s.find('\\');
   //cout<<s<<endl;
   while (a!=std::string::npos)
   {
      s.replace(a,1,"/");
      a=s.find('\\');
   }
   return s;
}

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
   
   for (const auto & entry : fs::directory_iterator(root)){
      if (fs::is_directory(entry.path())==1)
      {
         list.push_back(entry.path());
      }
   }

   for (int i = 0; i < list.size(); i++)
   {
      if (fs::is_regular_file(list[i]/"descriptor.mod")==0)
      {
         list.erase(list.begin()+i);
         i--;
      }
   }
   
   std::fstream new_desc, target;
   fs::path active;
   fs::path reciever;
   std::string x, y, tmp;
   for (int i = 0; i < list.size(); i++)
   {
      active = root/list[i].stem()/"descriptor.mod";
      reciever = root/list[i].stem(); reciever += ".mod";
      x = back_to_front(active.string().c_str()); y = back_to_front(reciever.string().c_str());
      target.open(x, std::fstream::in);
      new_desc.open(y, std::fstream::in|std::fstream::out|std::fstream::trunc);
      if (!(target.is_open() || new_desc.is_open())){
         cout<<"file open fail";
         return -1;
      }
      while (!target.eof())
      {
         getline(target, tmp);
         if (!(tmp.find("path=")==0))
         {
            new_desc<<tmp<<"\n";
         }
      }
      reciever = root/list[i].stem();
      tmp = back_to_front(reciever.string().c_str());
      tmp = tmp.substr(tmp.find_last_of("/"));
      tmp = "C:/Users/Karol/Documents/Paradox Interactive/Stellaris/mod" + tmp;
      new_desc<<"path=\""<<tmp<<"\"";
      
      
      target.close();
      new_desc.close();
   }
   return 0;
}