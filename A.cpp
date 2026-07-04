#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<set<int>> sensores(n);
    for (int i = 0; i < n; i++) {
        int m; cin >> m;
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            sensores[i].insert(x);
        }
    }
    set<int> comun = sensores[0];
    for (int i = 1; i < n; i++) {
        set<int> tmp;
        set<int>::iterator it = comun.begin();
        while (it != comun.end()) {
            if (sensores[i].count(*it)) tmp.insert(*it);
            it++;
        }
        comun = tmp;
    }
    bool primero = true;
    set<int>::iterator it = comun.begin();
    while (it != comun.end()) {
        if (!primero) cout << " ";
        cout << *it;
        primero = false;
        it++;
    }
    cout << "\n";
}
