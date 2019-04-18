#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int main() {
    srand((unsigned int)time(NULL));

    cout << "bought how much? ";
    int bought_how_much; cin >> bought_how_much;

    vector<vector<int>> lottoList;

    while( bought_how_much-- ) {
        vector<int> temp;
        for(int i=0; i<6; i++) {
            temp.push_back(rand()%45 + 1);
        }
        sort(temp.begin(), temp.end());
        lottoList.push_back(temp);
    }

    for(auto &i : lottoList) {
        for(auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}
