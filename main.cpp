#include <iostream>
#include <list>
#include <dirent.h>

using namespace std;

const string _NEW_FILE_ = " > ";
const string _NEW_LINE_ = " >> ";

const string _DIRECTORY_ = ".";
const string _DESTINATION_ = "class";

const string _FIRST_COMMAND_ =  "const " + _DESTINATION_ + " = [" + _NEW_FILE_;
const string _LAST_COMMAND_ =  "export {" + _DESTINATION_ + "};" + _NEW_LINE_;

list <string> getFiles(){
    list <string> l;
    struct dirent *dir;
    DIR *d = opendir(_DIRECTORY_.c_str());
    if(d){
        while ((dir = readdir(d)) != NULL)
            l.push_back(dir->d_name);
        closedir(d);
    }
    return l;
}

void saveLine(string line){
    line = "echo " + line + " " + _DESTINATION_ + ".js";
    system(line.c_str());
}

void createModule(list <string> l){
    saveLine(_FIRST_COMMAND_);
    for (auto file : l){
        string line = "\'" + file + "\'," + _NEW_LINE_;
        saveLine(line);
    }
    saveLine("];" + _NEW_LINE_);
    saveLine(_LAST_COMMAND_);
}

int main(){
    list <string> files = getFiles();
    if(!files.empty())
        createModule(files);
    else
        cout << "No files found" << endl;
    return 0;
}
