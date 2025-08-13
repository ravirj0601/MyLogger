#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <syslog.h>
#include <stdio.h>
#include <string>
#include <chrono>
#include <unistd.h>
#include <iomanip>
using namespace std;
class FileLog{
private:
    ofstream logfile;
public:
    FileLog(string fileName){
        logfile.open(fileName, ios::app);
        if (!logfile) {
            cerr <<  "Can not open log file.\n";
        }
    }

    void logmsg(string msg){
        if (logfile.is_open()) {
            logfile << msg;
        }
    }

    ~FileLog(){
        if (logfile.is_open()) {
            logfile.close();     
        }
    }

};

class Logger1{
private:
    enum LogLevel { 
        INFO = 1, 
        WARNING = 2, 
        ERROR = 3
    };
    FileLog mylog;

public:
    
    Logger1(const string &filepath) : mylog(filepath){
    }

    void myLogger(int level, string& info, bool logging){
        LogLevel myLevel = static_cast<LogLevel>(level);
        
        // Date related operations using chrono
        auto now = chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        ostringstream oss;
        oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
        string curr_time = oss.str();
        
        //Segrigating level wise infos
        switch (myLevel) {
            case INFO:{
                string msg = "Date: " + curr_time + " [INFO] " + info + "\n";
                cout << msg;
                if (logging) {
                    mylog.logmsg(msg);
                }
                break;
                      }
            case WARNING:{
                string msg1 = "Date: " + curr_time + " [WARNING] " + info + "\n";
                cerr << msg1;
                if (logging) {
                    mylog.logmsg(msg1);
                }
                break;
                         }
            case ERROR:{
                string msg2 = "Date: " + curr_time + " [ERROR] " + info + "\n";
                cerr << msg2; 
                if (logging) {
                    mylog.logmsg(msg2);
                }
                break;
                       }
        }
        usleep(500000);
    }
    
};

int main() {
    string filepath = "/Users/raviranjanrajak/Documents/My_Project/Studies/CPP_Practice/linkedList/log.txt";
    Logger1 mylogs(filepath);
    string msg1 = "Here is a info";
    string msg2 = "Here is a Warning 010011101010";
    string msg3 = "Error Occured Due to 0101010100";
    mylogs.myLogger(1, msg1, false);
    mylogs.myLogger(2, msg2, true);
    mylogs.myLogger(3, msg3, true);
    return 0;
}

