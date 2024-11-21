#include <iostream>
#include <vector>

using namespace std;

vector<int> buildPartialMatchTable(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> findSubsequenceOccurrences(const string& dna, const string& target) {
    vector<int> occurrences;
    int n = dna.size();
    int m = target.size();
    vector<int> lps = buildPartialMatchTable(target);
    int i = 0;
    int j = 0;

    while (i < n) {
        if (target[j] == dna[i]) {
            i++;
            j++;
        }
        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && target[j] != dna[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return occurrences;
}

int main() {
    string dna = "ATCGATCGATCGTACG";
    string target = "ATCG";
    cout<<"This is a example:"<<endl<<"The index:";
    vector<int> occurrences1 = findSubsequenceOccurrences(dna, target);
    for (int index : occurrences1) {
        cout << index << " ";
    }
    cout << endl;

    cout<<endl<<"User input:"<<endl;
    string inputdna,inputtarget;
    cout<<"dna:"<<endl;
    cin>>inputdna;
    cout<<"target"<<endl;
    cin>>inputtarget;

    cout<<"The index:";
    vector<int> occurrences2 = findSubsequenceOccurrences(inputdna, inputtarget);
    for (int index : occurrences2) {
        cout << index << " ";
    }
    cout<<endl;
    return 0;
}
