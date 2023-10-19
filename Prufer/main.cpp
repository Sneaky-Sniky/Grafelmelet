#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    int pontok, elek;
    vector <vector<int>> szomszedsagi;

    ifstream fin(argv[1]);

    fin >> pontok;
    fin >> elek;
    szomszedsagi = vector<vector<int>>(pontok+1);

    for(int i = 0; i <= pontok; i++){
        szomszedsagi[i].push_back(0);
    }
    for(int i = 0; i < elek; i++){
        int p1, p2;
        fin >> p1 >> p2;
        szomszedsagi[p1].push_back(p2);
        szomszedsagi[p2].push_back(p1);
        szomszedsagi[p1][0]++;
        szomszedsagi[p2][0]++;
    }

    cout << "Prufer kod elott: ";
    for(int i = 1; i <= pontok; i++){
        for(int j = 0; j < szomszedsagi[i].size(); j++){
            cout << szomszedsagi[i][j] << " ";
        }
        cout << endl;
    }




    return 0;
}