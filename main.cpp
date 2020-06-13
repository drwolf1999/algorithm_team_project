#include "doyeop.h"
//#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


int main() {
    const char * CURRENT_DIR = "/Users/doyeopkim/Study/myProject/School/algorithm_team_project/";
    const char * REFERENCE_FILE = (std::string(CURRENT_DIR) + "refer.txt").c_str();
    const char * SHORT_READ_FILE = (std::string(CURRENT_DIR) + "shortread.txt").c_str();
    DoYeop * dy = new DoYeop(REFERENCE_FILE, SHORT_READ_FILE);
    std::string ans = dy->Solve();

    return 0;
}