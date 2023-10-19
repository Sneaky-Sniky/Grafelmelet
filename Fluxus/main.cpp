#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
vector<vector<int>> graf;
bool volt[500];
int tavolsagok[500];
int utak[500];

void bfs(int kezd, int n, vector<int>& sorrend) {
    queue<int> sor;
    // sorrend.clear();
    volt[kezd] = true;
    sor.push(kezd);
    while (!sor.empty()) {
        int most = sor.front();
        sor.pop();
        // cout << most << " ";
        sorrend.push_back(most);
        for (int i = 1; i <= n; i++) {
            if(graf[most][i] == 1) {
              if (!volt[i]) {
                  volt[i] = true;
                  sor.push(i);
                  utak[i]+=utak[most];
                  tavolsagok[i] = tavolsagok[most] + 1;
              }
              else{
                  if(tavolsagok[most] + 1 == tavolsagok[i]){
                      utak[i]+=utak[most];
                  }
              }
            }
        }
    }

}

void fluxus_szamolas(int n, vector<int>& sorrend,
  vector<vector<int>>& szomszedsagi, vector<vector<double>>& fluxusok) {
    for(int i = n - 1; i >= 0; i--) {
        int pont = sorrend[i];
        double sum = 1;
        for(int j = 1; j <= n; j++) {
            if(szomszedsagi[pont][j] == 1 && tavolsagok[pont] < tavolsagok[j]) {
                sum += fluxusok[pont][j];
            }
        }
        double arany = sum / utak[pont];
        for(int j = 1; j <= n; j++) {
            if(szomszedsagi[pont][j] == 1 && tavolsagok[pont] > tavolsagok[j]) {
                fluxusok[pont][j] = utak[j] * arany;
                fluxusok[j][pont] = utak[j] * arany;
            }
        }
    }
}

void lepes(int n, vector<vector<double>>& fluxusok) {
    for(int gyoker = 1; gyoker <= n; gyoker++) {
        for(int i = 1; i <= n; i++) {
            tavolsagok[i] = 0;
            utak[i] = 0;
            volt[i] = false;
        }
        vector<int> sorrend;
        utak[gyoker] = 1;
        bfs(gyoker, n, sorrend);
        for(int i = 1; i <= n; i++) {
            if(!volt[i]) {
                utak[i] = 1;
                bfs(i, n, sorrend);
            }
        }
        // for(int i = 0; i < n; i++) {
        //     cout << sorrend[i] << ' ';
        // }
        // cout << endl;

        vector<vector<double>> fluxus(n+1, vector<double>(n+1));
        for(int y = 1; y <= n; y++) {
            for(int x = 1; x <= n; x++) {
                if(graf[y][x] == 1) {
                    fluxus[y][x] = 0;
                } else {
                    fluxus[y][x] = -1;
                }
            }
        }
        fluxus_szamolas(n, sorrend, graf, fluxus);

        for(int y = 1; y <= n; y++) {
            for(int x = 1; x <= n; x++) {
                if(fluxus[y][x] != -1) {
                    fluxusok[y][x] += fluxus[y][x];
                }
            }
        }
    }
}

void torol_max(int n, vector<vector<double>>& fluxusok) {
    int i, j;
    double maxi = -1;
    for(int y = 1; y <= n; y++) {
        for(int x = 1; x < y; x++) {
            if(graf[y][x] == 1 && fluxusok[y][x] != 0) {
                if(fluxusok[y][x] > maxi) {
                    i = y;
                    j = x;
                    maxi = fluxusok[y][x];
                }
            }
        }
    }

    graf[i][j] = 0;
    graf[j][i] = 0;

    cout << "Torolte a " << i << '-' << j << " elet (" << fluxusok[i][j] << ").\n";
}

int main(int argc, char **argv) {
    //cout << argv[1];
    ifstream fin(argv[1]);
    int pont, el, pont1, pont2;


    cout << "Kerem a pontok szamat: " << endl;
    fin >> pont;
    cout << "Kerem az elek szamat: " << endl;
    fin >> el;

    graf = vector<vector<int>>(pont+1, vector<int>(pont+1, 0));

    for (int i = 0; i < el; i++) {
        fin >> pont1 >> pont2;
        graf[pont1][pont2] = 1;
        graf[pont2][pont1] = 1;
    }

    vector<vector<double>> fluxusok(pont+1, vector<double>(pont+1, 0));

    for(int i = 0; i < el; i++) {
        lepes(pont, fluxusok);
        torol_max(pont, fluxusok);
    }

    return 0;
}