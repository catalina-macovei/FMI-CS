#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;



// calculul Distantelor Levenshtein intre doua siruri
int levenshteinDistance(const string& word1, const string& word2) {
    int m = word1.length();
    int n = word2.length();

    // Creare matrice pentru stocarea distantelor
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Calcularea matricei pentru Distanta Levenshtein
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0) {
                dp[i][j] = j; // Initializare pentru cazul in care word1 este gol
            } else if (j == 0) {
                dp[i][j] = i; // Initializare pentru cazul in care word2 este gol
            } else {
                // Completați matricea cu distanțele minime de editare
                dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1)});
            }
        }
    }

    return dp[m][n]; // Returneaza distanta minima de editare finala
}

// Functie pentru gasirea distantei minime intre perechi de cuvinte in grupuri
int findMinDistancePair(const vector<vector<string>>& clusters) {
    int minDistance = INT_MAX;

    // Gasirea distantei minime intre cuvinte din diferite grupuri
    for (size_t i = 0; i < clusters.size(); ++i) {
        for (size_t j = i + 1; j < clusters.size(); ++j) {
            for (const auto& word1 : clusters[i]) {
                for (const auto& word2 : clusters[j]) {
                    int distance = levenshteinDistance(word1, word2);
                    minDistance = min(minDistance, distance);
                }
            }
        }
    }

    return minDistance; // Returneaza distanta minima gasita
}

// Functie pentru realizarea partitionarii k-cluster
void kCluster(vector<string>& words, int k) {
    vector<int> clusterIds(words.size()); // Stocare ID-uri de cluster pentru cuvinte

    // Initial, fiecare cuvant formeaza un cluster separat
    for (int i = 0; i < static_cast<int>(words.size()); ++i) {
        clusterIds[i] = i;
    }

    // Implementarea algoritmului de clusterizare
    for (int i = 1; i <= static_cast<int>(words.size()) - k; ++i) {
        // Gasirea a doua obiecte din clustere diferite cu distanta minima
        int minDistance = INT_MAX;
        int minOr = -1, minOt = -1;

        for (int orIndex = 0; orIndex < static_cast<int>(words.size()); ++orIndex) {
            for (int otIndex = orIndex + 1; otIndex < static_cast<int>(words.size()); ++otIndex) {
                int currentDistance = levenshteinDistance(words[orIndex], words[otIndex]);
                if (currentDistance < minDistance && clusterIds[orIndex] != clusterIds[otIndex]) {
                    minDistance = currentDistance;
                    minOr = orIndex;
                    minOt = otIndex;
                }
            }
        }

        // Unirea clusterelor lui minOr si minOt
        int clusterIdOr = clusterIds[minOr];
        int clusterIdOt = clusterIds[minOt];

        for (int j = 0; j < static_cast<int>(words.size()); ++j) {
            if (clusterIds[j] == clusterIdOt) {
                clusterIds[j] = clusterIdOr;
            }
        }
    }

    // Initializarea si afisarea clusterelor
    vector<vector<string>> clusters(k);

    for (int i = 0; i < static_cast<int>(words.size()); ++i) {
        clusters[clusterIds[i]].push_back(words[i]);
    }

    // Afișarea cuvintelor din fiecare cluster
    for (size_t i = 0; i < clusters.size(); ++i) {
        for (const auto& word : clusters[i]) {
            cout << word << " ";
        }
        cout << endl;
    }

    // Calcularea și afișarea gradului de separare
    int separationDegree = findMinDistancePair(clusters);
    cout << "Grad de Separare: " << separationDegree << endl;
}

int main() {
    vector<string> words;
    string word;

    ifstream inputFile("tema2Lab/cluster.in");

    if (!inputFile.is_open()) {
        cerr << "Eroare la deschiderea fisierului.\n";
        return 1;
    }

    // Citirea cuvintelor din fisier
    while (inputFile >> word) {
        words.push_back(word);
    }

    int k;
    cout << "Introduceti valoarea lui k: ";
    cin >> k;

    // Apelul algoritmului de clusterizare
    /**
     * K-Means: Acest algoritm împarte datele într-un număr predeterminat de clustere (K)
     * și încearcă să minimizeze variația în interiorul fiecărui cluster.
     * */
    kCluster(words, k + 1);

    inputFile.close();

    return 0;
}
