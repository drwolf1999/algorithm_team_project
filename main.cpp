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
#include <algorithm>
#include <time.h>

/// <summary>
/// 20000 100 2000
/// 25000 100 2000
/// 30000 100 2000
/// </summary>
/// <returns></returns>
int main() {
    auto min = [](int x, int y) {
        return x > y ? y : x;
    };
    auto abs = [](int x) {
        return x > 0 ? x : -x;
    };
    //const std::string CURRENT_DIR = "/Users/doyeopkim/Study/myProject/School/algorithm_team_project/";
    //const std::string CURRENT_DIR = "E:/DownloadsFold/assignment/algorithm/algorithm_team_project/";
    const std::string CURRENT_DIR = "E:/test_data_set/";
    const std::string REFERENCE_FILE = (CURRENT_DIR + "test_ref_1000.txt");
    const std::string SHORT_READ_FILE = (CURRENT_DIR + "shortread_1000.txt");
    const std::string COMPARE_FILE = (CURRENT_DIR + "compare.txt");
    const std::string MY_FILE = (CURRENT_DIR + "Mydna_1000.txt");
    const int MISMATCH = 4;
    DoYeop * dy = new DoYeop(REFERENCE_FILE.c_str(), SHORT_READ_FILE.c_str(), MISMATCH, 7);
    clock_t __time__ = clock();
    std::vector<std::string> ans = dy->Solve();
    __time__ = clock() - __time__;
    std::sort(ans.begin(), ans.end(), [](const std::string& l, const std::string& r) {
        if (l.size() == r.size()) return l < r;
        return l.size() > r.size();
        });

    //// get my dna ////
    std::ifstream my(MY_FILE.c_str());
    std::string myDNA;
    my >> myDNA;
    /////////
    KMP kmp;
    std::vector<int> f = kmp.run(myDNA, ans[0]);
    std::cout << "It taskes " << double(__time__) / CLOCKS_PER_SEC << "seconds\n\n";
    //if (f.empty()) {
        int length = 0;
        int idx = -1;
        for (int i = 0; i < ans.size(); i++) {
            length += ans[i].size();
            idx = i;
            if (length * 2 >= myDNA.size()) break;
        }
        int min_cnt = myDNA.size();
		for (int push = 0; push <= abs(myDNA.size() - ans[idx].size()); push++) {
            int cnt = 0;
            for (int i = 0; i < min(myDNA.size(), ans[idx].size()); i++) {
                cnt += ans[idx][i] == myDNA[i + push];
            }
            min_cnt = min(min_cnt, cnt);
        }
        std::cout << "N50 is a measure to describe the quality of assembled genomes that are fragmented in contigs of different length.\n"
                  << "This value is meaningful when it is more than 1/4 of the my original DNA length.\n";
        std::cout << "Matching Rate : " << double(min_cnt) * 100.0 / myDNA.size() << "%\n";
        std::cout << "N50 of this algorithm is " << ans[idx].size() << "\n\n";
    //}
    //else {
        std::cout << "Accuracy of this algorithm is " << double(ans[0].size()) * 100.0 / myDNA.size() << "%\n\n";
    //}
    //// Compare ///////
    std::ofstream comp(COMPARE_FILE.c_str());
    comp << "------------Original\n";
    comp << myDNA << "\n\n";
    comp << "------------Restore\n";
    for (int t = 0; t < ans.size(); t++) {
        int cnt = 0;
        comp << "Contig " << t << '\n';
        comp << ans[t] << '\n';
        for (unsigned long i = 0; i < min(myDNA.size(), ans[t].size()); i++) {
            if (myDNA[i] == ans[t][i]) cnt++;
        }
        comp << "---------------------------------------------------------------------------------------------------------------\n";
    }
    std::cout << "End Process\nShow \"compare.txt\" file!\n\n";
    return 0;
}