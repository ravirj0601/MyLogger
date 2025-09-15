#include <iostream>
#include <mutex>
#include <string>
using namespace std;


class FileOps{
    string path;

};

// Logger with Singleton Design pattern

class Log{
    private:
        Log(){cout<<"Config Created\n";}
        ~Log() = default;

        // Delete move & copy to prevent cloning
        Log(const Log&) = delete;
        Log&  operator=(const Log&) = delete;

        string logtext;
        mutex mtx_;
    public:
        
};

int main() {
    
    return 0;
}

