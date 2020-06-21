//// 2018112051 ÄÄÇ»ÅÍ°øÇÐ°ú ±èµµ¿±
//#include <string>
//#include <iostream>
//#include <assert.h>
//#include <fstream>
//#include <algorithm>    // std::random_shuffle
//#include <vector>       // std::vector
//#include <ctime>        // std::time
//#include <cstdlib>      // std::rand, std::srand
//#include <iomanip>
//#include <set>
//using namespace std;
//const string PATH = "E:/DownloadsFold/assignment/algorithm/algorithm_team_project/"; // File path
//const string REFER_PATH = PATH + "refer.txt"; // reference DNA file path
//const string SHORT_PATH = PATH + "shortread.txt"; // shortread DNA file path
//const string MY_PATH = PATH + "my.txt"; // my DNA file path
//const string RESTORE_PATH = PATH + "restore.txt"; // restored my DNA file path
//const string DNA_OBJ = "ACGT"; // DNA elements
//const int REFER_DNA_LEN = 100; // reference DNA length
//const bool RESET = true; /// 20000, 2000, 100 // 20000, 5000, 100 // 100000, 2000, 100 // 100000, 4000, 100
//inline char getACGTRandom() { return DNA_OBJ[rand() % 4]; } // get one of ('A', 'C', 'G', 'T') by random
//inline int getACGTToInt(const char ACGT) { // Mapping 'A'=0, 'C'=1, 'G'=2, 'T'=3
//    switch (ACGT)
//    {
//    case 'A':
//        return 0;
//        break;
//    case 'C':
//        return 1;
//        break;
//    case 'G':
//        return 2;
//        break;
//    case 'T':
//        return 3;
//        break;
//    default:
//        break;
//    }
//    return -1;
//}
//class AhoCorasick {
//    AhoCorasick* child[4]; // child (0=>'A', 1=>'C', 2=>'G', 3=>'T')
//    int position; // Save where pattern appeared
//    void insert(const char* s, const int p) { // Save the appearance of the pattern string s in the p position of the reference
//        if (*s == '\0') { // end pattern string
//            position = p;
//            return;
//        }
//        int next = getACGTToInt(*s);
//        if (child[next] == nullptr) child[next] = new AhoCorasick(); // Create new if child[next] is empty
//        child[next]->insert(s + 1, p); // Insert from child[next]
//    }
//    int find(const char* s) {
//        if (*s == '\0') return position; // return position if found
//        int next = getACGTToInt(*s);
//        if (child[next] == nullptr) return -1; // return -1 if child[next] is empty ==> not found
//        return child[next]->find(s + 1); // return find(s + 1) from child[next]
//    }
//public:
//    AhoCorasick() : position(0) { for (int i = 0; i < 4; i++) child[i] = nullptr; }
//    void insert(const string& s, int p) { insert(s.c_str(), p); }
//    int find(const string& s) { return find(s.c_str()); }
//};
//void createReferDNA() {
//    ifstream referChecker(REFER_PATH.c_str());
//    // if(!RESET && !referChecker.fail()) return;
//    /*
//    To avoid repetition of the substrings,
//    the substrings are constantly checked against suffixes of a certain length.
//    Conduct a "process".
//
//    "Process"
//    The suffix has appeared now. ==> Change the last character of the suffix and create a string that does not appear
//    (If this is not the case, choose the first one with the last position among the strings that appear).
//
//    Record the position of the current suffix and move on to the next.
//    */
//    const int suffixLen = 20;
//    AhoCorasick* ac = new AhoCorasick();
//    string suffix, referDNA; // suffix : suffix (length: suffixLen), referDNA : reference DNA from a problem
//    for (int i = 0; i < REFER_DNA_LEN; i++) {
//        char acgt = getACGTRandom(); // get acgt (by random)
//        suffix.push_back(acgt); // add acgt to suffix
//        if (i < suffixLen - 1) { // Simple insertion into referenceDNA until a specific length is reached
//            referDNA.push_back(acgt);
//            continue;
//        }
//        int frontP = ac->find(suffix); // last location where the suffix appeared
//        if (frontP != -1) { // frontP is -1 ==> Try to replace it with a different character.
//            char frontIdx = acgt;
//            for (int j = 0; j < 4; j++) {
//                if (acgt == DNA_OBJ[j]) continue; // Avoid meaningless operations
//                suffix.pop_back();
//                suffix.push_back(DNA_OBJ[j]);
//                int p = ac->find(suffix);
//                if (p < frontP) { // There is a substring that appeared earlier.
//                    p = frontP;
//                    frontIdx = DNA_OBJ[j]; // Finally, the last character of the souffix will be replaced by j.
//                }
//            }
//            suffix.pop_back();
//            suffix.push_back(frontIdx);
//        }
//        ac->insert(suffix, i); // Record that suffix appeared on the i-position
//        referDNA.push_back(suffix.back());
//        suffix.erase(suffix.begin());
//    }
//    for (int i = 0; i < referDNA.size(); i++) {
//        bool chk = false;
//        for (int j = 0; j < DNA_OBJ.size(); j++) {
//            chk |= DNA_OBJ[j] == referDNA[i];
//        }
//        assert(chk);
//    }
//    ofstream refer(REFER_PATH.c_str());
//    assert(referDNA.size() == REFER_DNA_LEN);
//    refer << referDNA;
//    refer.close();
//}
//void createMyDNA() {
//    string myDNA;
//    ifstream refer(REFER_PATH.c_str());
//    refer >> myDNA; // MyDNA is initially set as referenceDNA.
//    refer.close();
//    const int diffX = 20; // The difference between myDNA and referenceDNA.
//    for (int i = 0; i < myDNA.size(); i++) {
//        if (rand() % 100 + 1 <= diffX) { // probability processing
//            char c = myDNA[i];
//            while (c == myDNA[i]) c = getACGTRandom(); // To exchange with another character.
//            myDNA[i] = c;
//        }
//    }
//    ofstream my(MY_PATH.c_str());
//    my << myDNA;
//    my.close();
//}
//vector<bool> visit;
//bool justDo = false;
//bool allVisit()
//{
//    if (justDo == true)
//    {
//        return true;
//    }
//    for (int i = 0; i < visit.size(); ++i)
//    {
//        if (visit[i] == false)
//            return false;
//    }
//    justDo = true;
//    return true;
//}
//void createShortRead(int k, int n) { // k is length, n is number of shortread
//    createMyDNA();
//    string myDNA;
//    ifstream my(MY_PATH.c_str());
//    my >> myDNA;
//    my.close();
//    visit.resize(myDNA.size());
//    justDo = false;
//    int len = int(myDNA.size());
//    for (int i = 0; i < visit.size(); ++i)
//        visit[i] = false;
//    vector<int> candidates; // Save all positions that can be candidates for n partial string position with length k.
//    for (int i = 0; i + k - 1 < myDNA.size(); i++) candidates.push_back(i);
//    random_shuffle(candidates.begin(), candidates.end()); // shuffle
//    ofstream shortreadF(SHORT_PATH.c_str());
//    set<int> pos_set;
//    for (int i = 0; i < n; i++) {
//        string s;
//        if (allVisit()) {
//            for (int j = candidates[i]; j < candidates[i] + k; j++) {
//                s.push_back(myDNA[j]);
//                visit[j] = true;
//            }
//        }
//        else {
//            int firstPos = 0;
//            for (int j = 0; j < visit.size(); ++j) {
//                cout << j << ' ' << visit.size();
//                if (!visit[j]) {
//                    do {
//                        firstPos = j - (rand() % (k / 4 - (k / 4 > 0 ? 5 : 0)) + 5);
//                    } while (pos_set.find(firstPos) != pos_set.end());
//                    break;
//                }
//            }
//            cout << i << '\n';
//            while (firstPos < 0) firstPos++;
//            while (firstPos + k > len) firstPos--;
//            for (int j = firstPos; j < firstPos + k; j++) {
//                assert(j < REFER_DNA_LEN);
//                s.push_back(myDNA[j]);
//                assert(j < visit.size());
//                visit[j] = true;
//            }
//            pos_set.insert(firstPos);
//        }
//        shortreadF << s;
//        if (i != n - 1) shortreadF << "\n";
//    }
//    shortreadF.close();
//}
//void init(string& referDNA, string& myDNA, vector<string>& shortreads) {
//    // Read the file to proceed with initial setup
//    ifstream refer(REFER_PATH.c_str()), my(MY_PATH.c_str()), shortreadF(SHORT_PATH.c_str());
//    refer >> referDNA;
//    my >> myDNA;
//    while (!shortreadF.eof()) {
//        string s;
//        shortreadF >> s;
//        shortreads.push_back(s);
//    }
//    refer.close(), my.close(), shortreadF.close();
//}
//int main() {
//    int k, n;
//    string referDNA, // reference DNA
//        myDNA, // orginal my DNA
//        restoredMyDNA; // restored my DNA
//    vector<string> shortreads; // shortreads
//    srand(time(NULL));
//    cout << "Enter k(length of short-read) n(number of short-reads) >> ";
//    cin >> k >> n;
//    createReferDNA();
//    createShortRead(k, n);
//    init(referDNA, myDNA, shortreads); // initial setting
//    // start restore
//    const int Missmatch_Allowance = 2; // Miss match allowed count
//    restoredMyDNA = referDNA; // restoredMyDNA is initially set as referenceDNA.
//    clock_t duration = clock();
//    for (int s = 0; s < shortreads.size(); s++) { // Start search for short read
//        for (int i = 0; i + k - 1 < restoredMyDNA.size(); i++) {
//            int cnt = 0;
//            for (int j = i; j < i + k && Missmatch_Allowance >= cnt; j++) cnt += shortreads[s][j - i] != restoredMyDNA[j];
//            if (Missmatch_Allowance < cnt) continue;
//            // Miss match is within the acceptable number. Replace with short read
//            for (int j = i; j < i + k; j++) restoredMyDNA[j] = shortreads[s][j - i];
//            break;
//        }
//        cout.flags(ios::left);
//        cout << '\r' << setw(10) << double((s + 1) * 100) / shortreads.size() << "% restore complete";
//    }
//    duration = clock() - duration;
//    cout << "\n";
//    // end restore
//    assert(restoredMyDNA.size() == REFER_DNA_LEN);
//    ofstream restore(RESTORE_PATH.c_str());
//    restore << restoredMyDNA;
//    restore.close();
//    // start compare
//    cout << "compare start";
//    int matchingCount = 0;
//    // count calculation of matching rate
//    for (int i = 0; i < restoredMyDNA.size(); i++) matchingCount += restoredMyDNA[i] == myDNA[i];
//    cout << '\r' << double(matchingCount * 100) / restoredMyDNA.size() << "% match (tasks time : " << double(duration) / 1000 << " (s)\n";
//    // end compare
//    return 0;
//}