#include<iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <string>
#include <fcntl.h>
#include <fstream>

using namespace std;

//string OLDPWD;
vector<string> cmd;
vector<int> pids;

char temp[PATH_MAX];
string OLDPWD = getcwd(temp, PATH_MAX);

string trim (string input){
    int i=0;
    while (i < input.size() && input [i] == ' ')
        i++;
    if (i < input.size())
        input = input.substr (i);
    else{
        return "";
    }
    
    i = input.size() - 1;
    while (i>=0 && input[i] == ' ')
        i--;
    if (i >= 0)
        input = input.substr (0, i+1);
    else
        return "";
    
    return input;
    

}

vector<string> split (string line, string separator=" "){
    vector<string> result;
    while (line.size()){
        vector<int> pos;
        size_t found = line.find(separator);
        if (found == string::npos){
            string lastpart = trim (line);
            if (lastpart.size()>0){
                result.push_back(lastpart);
            }
            break;
        }
        string segment = trim (line.substr(0, found));
        //cout << "line: " << line << "found: " << found << endl;
        line = line.substr (found+1);
        if (segment.size() != 0)
            result.push_back (segment);
        
        if (separator == " ") {
            
            vector<int> pos;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == '\"' || line[i] == '\'') {
                    pos.push_back(i);
                }
            }
            if (pos.size() == 2) {
                string quote_str = line.substr(pos[0]+1,pos[1]-pos[0]-1);
                result.push_back(quote_str);
                line = line.substr(pos[1]+1);
            }
        }
        //cout << "[" << segment << "]"<< endl;
    }
    return result;
}

char** vec_to_char_array (vector<string> parts){
    char ** result = new char * [parts.size() + 1]; // add 1 for the NULL at the end
    for (int i=0; i<parts.size(); i++){
        // allocate a big enough string
        result [i] = new char [parts [i].size() + 1]; // add 1 for the NULL byte
        strcpy (result [i], parts[i].c_str());
    }
    result [parts.size()] = NULL;
    return result;
}

void execute (string command){
    vector<string> argstrings = split (command, " ");
    
    if (argstrings[0] == "time" || argstrings[0] == "date" || argstrings[0] == "custom") {
        time_t now = time(0);
        char *dt = ctime(&now);
        char temp[PATH_MAX];
        string currentdir = getcwd(temp, PATH_MAX);
        cout << dt;
        cout << currentdir << endl;
        vector<string> username;
        username.push_back("id");
        username.push_back("-u");
        username.push_back("-n");
        char** args = vec_to_char_array (username);
        execvp (args[0],args);
        return;
    }else{
        size_t out_label = command.find(">");
        size_t in_label = command.find("<");
        int num_out = 0;
        int num_in = 0;
        
        for (int i = 0; i < command.size(); i++) {
            if (command[i] == '>') {
                ++num_out;
            }else if (command[i] == '<'){
                ++num_in;
            }
        }
        
        if (out_label != string::npos && in_label != string::npos) { // both < and > are found
            if (out_label > in_label) {
                vector<string> instrings1 = split(command,">");
                string command2 = instrings1[0];
                vector<string> instrings = split(command2,"<");
                const char *filename2 = instrings[1].c_str();
                int fd2 = open(filename2, O_RDONLY);
                dup2(fd2, 0);
                vector<string> argstrings2 = split(instrings[0], " ");
                char** args2 = vec_to_char_array (argstrings2);// convert vec<string> into an array of char*
                const char *filename = instrings1[1].c_str();
                int fd = open(filename, O_WRONLY|O_TRUNC|O_CREAT,0666);
                dup2(fd, 1);
                execvp (args2[0], args2);
                close(fd2);
                close(fd);
            }else{
                vector<string> outstrings1 = split(command,"<");
                string new_command = outstrings1[0];
                vector<string> outstrings = split(new_command,">");
                const char *filename = outstrings[1].c_str();
                int fd = open(filename, O_WRONLY|O_TRUNC|O_CREAT,0666);
                dup2(fd, 1);
                vector<string> argstrings = split(outstrings[0], " ");
                char** args = vec_to_char_array (argstrings);// convert vec<string> into an array of char*
                execvp (args[0], args);
                close(fd);
            }
            return;
        }else if (out_label != string::npos){
            vector<string> outstrings = split(command,">");
            for (int i = 1; i < outstrings.size()-1; i++) {
                const char *tempfilename = outstrings[i].c_str();
                int fd = open(tempfilename, O_WRONLY|O_TRUNC|O_CREAT,0666);
                close(fd);
            }
            const char *filename = outstrings[outstrings.size()-1].c_str();
            int fd = open(filename, O_WRONLY|O_TRUNC|O_CREAT,0666);
            dup2(fd, 1);
            vector<string> argstrings = split(outstrings[0], " ");
            char** args = vec_to_char_array (argstrings);// convert vec<string> into an array of char*
            execvp (args[0], args);
            close(fd);
            return;
        }else if (in_label != string::npos){
            vector<string> instrings = split(command,"<");
            const char *filename = instrings[1].c_str();
            int fd = open(filename, O_RDONLY);
            dup2(fd, 0);
            vector<string> argstrings = split(instrings[0], " ");
            char** args = vec_to_char_array (argstrings);// convert vec<string> into an array of char*
            execvp (args[0], args);
            close(fd);
            return;
        }else{
            char** args = vec_to_char_array (argstrings);// convert vec<string> into an array of char*
            execvp (args[0], args);
        }
    }
}

int main (){
    while (true){ // repeat this loop until the user presses Ctrl + C
        cout << ">PA4$ ";
        int stdin_copy = dup(STDIN_FILENO);
        int stdout_copy = dup(STDOUT_FILENO);
        
        string commandline = "";/*get from STDIN, e.g., "ls  -la |   grep Jul  | grep . | grep .cpp" */
        getline(cin, commandline);
        
        if (!pids.empty()) {
            for (int i = 0; i < pids.size(); i++) {
                int status;
                pid_t pid = waitpid(pids[i], &status, WNOHANG);
                //cout << i+1 << " -> " << pid << " -> v:" << pids[i] << endl;
                if (pid == pids[i]) {
                    pids.erase(pids.begin()+i);
                    cmd.erase(cmd.begin()+i);
                }
            }
        }
        
        vector<string> tparts;
        // split the command by the "|", which tells you the pipe levels
        size_t check_l_in_quote = commandline.find("|");
        if (check_l_in_quote != string::npos) {
            if (commandline.find("\"") != string::npos || commandline.find("\'") != string::npos) {
                vector<int> pos;
                for (int i = 0; i < commandline.size(); i++) {
                    if (commandline[i] == '\"' || commandline[i] == '\'') {
                        pos.push_back(i);
                    }
                    if (pos.size() == 2) {
                        break;
                    }
                }
                
                if (check_l_in_quote > pos[0] && check_l_in_quote < pos[1]) {
                    tparts.push_back(commandline);
                }else{
                    tparts = split (commandline, "|");
                }
            }else{
                tparts = split (commandline, "|");
            }
        }else{
            tparts = split (commandline, "|");
        }
        
        if (tparts[0].find("&") != string::npos) {
            string push = "[" + to_string(cmd.size()+1) + "]+ Running                  " + tparts[0];
            //cmd.push_back(tparts[0]);
            cmd.push_back(push);
            string pidout = "";
            pid_t pid = fork();
            if (pid < 0) {
                cout << "Error open child process" << endl;
            }
            else if (pid == 0) {
                vector<string> argstrings = split(tparts[0]," ");
                argstrings.pop_back();
                char** args = vec_to_char_array (argstrings);
                execvp (args[0], args);
                exit(0);
            }else{
                pids.push_back(pid);
                cout << "[" << cmd.size() << "] " << pid << endl;
            }
        }else if (tparts[0].find("cd") != string::npos){
            vector<string> argstrings = split(tparts[0]," ");
            if (argstrings[1] == "-") {
                const char *p = OLDPWD.c_str();
                char temp[PATH_MAX];
                string new_OLDPWD = getcwd(temp, PATH_MAX);
                chdir(p);
                OLDPWD = new_OLDPWD;
            }else if (argstrings[1] == ".."){
                char temp[PATH_MAX];
                string new_OLDPWD = getcwd(temp, PATH_MAX);
                for (int i = new_OLDPWD.size()-1; i >= 0; i--) {
                    if (OLDPWD[i] == '/') {
                        const char *p = new_OLDPWD.substr(0,i).c_str();
                        chdir(p);
                        OLDPWD = new_OLDPWD;
                        break;
                    }
                }
            }else{
                const char *p = argstrings[1].c_str();
                char temp[PATH_MAX];
                string new_OLDPWD = getcwd(temp, PATH_MAX);
                chdir(p);
                OLDPWD = new_OLDPWD;
            }
        }else if (tparts[0] == "jobs") {
            for (int i = 0; i < cmd.size(); i++) {
                cout << cmd[i] << endl;
            }
        }else if (tparts[0].find("echo") != string::npos) {
            vector<string> argstrings = split(tparts[0], " ");
            string content = argstrings[argstrings.size()-1];
            cout << content << endl;
        }else{
            for (int i=0; i<tparts.size(); i++){
                // make pipe
                int fd[2];
                pipe(fd);
                
                if (!fork()){
                    // redirect output to the next level
                    // unless this is the last level
                    if (i < tparts.size() - 1){
                        // redirect STDOUT to fd[1], so that it can write to the other side
                        dup2(fd[1], 1);
                        
                        close (fd[1]);   // STDOUT already points fd[1], which can be closed
                    }
                    //execute function that can split the command by spaces to
                    // find out all the arguments, see the definition
                    execute (tparts [i]); // this is where you execute
                }else{
                    wait(0);            // wait for the child process
                    // then do other redirects
                    dup2(fd[0], 0);
                    close(fd[1]);
                }
            }
        }
        
        // for each pipe, do the following:
        
        dup2(stdin_copy, STDIN_FILENO);
        dup2(stdout_copy, STDOUT_FILENO);
        close(stdin_copy);
        close(stdout_copy);
    }
}
