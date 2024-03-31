#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

int viz[100001] = {0};
vector<int> graf[100001];
vector<int> componente[1000];

int counter = 0;
int indexare_componente = 0;

void DFS(int nod, int indexare_componente) {
    int nr_vecini = 0;
    int vecin = -1;
    viz[nod] = 1;
    nr_vecini = graf[nod].size();
    componente[indexare_componente].push_back(nod);
    //cout << nod << "\t";
    counter++;
    for(int i = 0; i < nr_vecini; i++) {
        vecin = graf[nod][i];
        if(viz[vecin] == 0)
        {
            DFS(vecin, indexare_componente);
        }
    }

}


// nr componente prim

bool isPrime(int number) {
    if (number <= 1) {
        return false; // 0 and 1 are not prime numbers
    }

    int sqrtNumber = sqrt(number);

    for (int i = 2; i <= sqrtNumber; ++i) {
        if (number % i == 0) {
            return false; // If the number is divisible by any i, it's not prime
        }
    }

    return true; // If no divisor is found, the number is prime
}

// flux patrat perfect
bool isPerfectSquare(int number) {
    int sqrtNumber = sqrt(number);
    return (sqrtNumber * sqrtNumber == number);
}

// flux palindrom
bool isPalindrome(int number) {
    std::string numStr = std::to_string(number);
    int left = 0, right = numStr.length() - 1;

    while (left < right) {
        if (numStr[left] != numStr[right]) {
            return false; // If characters at symmetric positions don't match, it's not a palindrome
        }
        left++;
        right--;
    }

    return true; // If the loop completes, the number is a palindrome
}

int main () {

    int n, m, k;

    cin >> n >> m >> k;
    int i, x, y, nr_conexe = 0;

    // gestionare limite
    assert(n >= 1 && n <= 100000); // 10^5
    assert(k >= 1 && k <= 100000);
    assert(m >=1 && m <= (min(n*(n-1)/2, 2*100000)));

    for ( i= 0 ; i < m; i++) {
        cin >> x >> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    for (i =1; i <= n; i++) {
        if (!viz[i]) {
            if (counter >= k) {
                nr_conexe++;
            }
            cout << endl;
            counter = 0;
            indexare_componente++;
            DFS(i, indexare_componente);
        }
    }

    cout << nr_conexe << endl;

    for (i = 0; i < n; i++) {

        if(componente[i].size())
            cout << "componenta: " << i << endl;
            for (int j = 0 ; j < componente[i].size(); j++) {
                cout << componente[i][j] << endl;
            }
    }
    return 0;
}

/* TESTARE
10 5 2
2 6
4 6
4 9
4 10
8 10
 * */
