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
#include <fstream>

int main() {
    //const std::string CURRENT_DIR = "/Users/doyeopkim/Study/myProject/School/algorithm_team_project/";
    const std::string CURRENT_DIR = "E:/DownloadsFold/assignment/algorithm/algorithm_team_project/";
    const std::string REFERENCE_FILE = (CURRENT_DIR + "refer.txt");
    const std::string SHORT_READ_FILE = (CURRENT_DIR + "shortread.txt");
    const std::string COMPARE_FILE = (CURRENT_DIR + "compare.txt");
    const std::string MY_FILE = (CURRENT_DIR + "my.txt");
    const int MISMATCH = 4;
    DoYeop * dy = new DoYeop(REFERENCE_FILE.c_str(), SHORT_READ_FILE.c_str(), MISMATCH, 27);
    std::vector<std::string> ans = dy->Solve();
    //for (int i = 0; i < ans.size(); i++) {
    //    std::cout << ans[i] << '\n';
    //}

    //// get my dna ////
    std::ifstream my(MY_FILE.c_str());
    std::string myDNA;
    my >> myDNA;
    ////// Compare ///////
    std::ofstream comp(COMPARE_FILE.c_str());
    comp << "------------Original\n";
    comp << myDNA << "\n\n";
    comp << "------------Restore\n";
    auto min = [](int x, int y) {
        return x > y ? y : x;
    };
    auto abs = [](int x) {
        return x > 0 ? x : -x;
    };
    for (int t = 0; t < ans.size(); t++) {
        int cnt = 0;
        comp << ans[t] << '\n';
        for (unsigned long i = 0; i < min(myDNA.size(), ans[t].size()); i++) {
            if (myDNA[i] == ans[t][i]) cnt++;
        }
        comp << double(cnt) * 100.0 / min(myDNA.size(), ans[t].size()) << '\n';
        comp << abs(ans[t].size() - myDNA.size()) << '\n';
        comp << "ans " << (ans[t].size() > myDNA.size() ? '>' : '<') << " myDNA" << '\n';
        comp << "\n";
    }
    std::cout << "End Process\nShow \"compare.txt\" file!\n\n";
    return 0;
}