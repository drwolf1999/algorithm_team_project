#include "doyeop.h"
#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


int main() {
    // const char * CURRENT_DIR = "/Users/doyeopkim/Study/myProject/School/algorithm_team_project/";
    const char * CURRENT_DIR = "E:/DownloadsFold/assignment/algorithm/algorithm_team_project/";
    const char * REFERENCE_FILE = (std::string(CURRENT_DIR) + "refer.txt").c_str();
    const char * SHORT_READ_FILE = (std::string(CURRENT_DIR) + "shortread.txt").c_str();
    const int MISMATCH = 4;
    DoYeop * dy = new DoYeop(REFERENCE_FILE, SHORT_READ_FILE, MISMATCH);
    std::string ans = dy->Solve();
    std::cout << ans;
    return 0;
}