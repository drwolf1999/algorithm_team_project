#include "doyeop.h"
#define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <string>

int main() {
    // const std::string CURRENT_DIR = "/Users/doyeopkim/Study/myProject/School/algorithm_team_project/";
    const std::string CURRENT_DIR = "E:/DownloadsFold/assignment/algorithm/algorithm_team_project/";
    const std::string REFERENCE_FILE = (CURRENT_DIR + "refer.txt");
    const std::string SHORT_READ_FILE = (CURRENT_DIR + "shortread.txt");
    const int MISMATCH = 4;
    DoYeop * dy = new DoYeop(REFERENCE_FILE.c_str(), SHORT_READ_FILE.c_str(), MISMATCH, 10);
    std::string ans = dy->Solve();
    std::cout << ans;
    return 0;
}