//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <stack>
//
//struct Punct {
//    double x, y;
//
//    Punct(double x, double y) : x(x), y(y) {}
//};
//
//double Calculeaza_Dist(const Punct& punct1, const Punct& punct2) {
//    double dx = punct2.x - punct1.x;
//    double dy = punct2.y - punct1.y;
//
//    return std::sqrt(dx * dx + dy * dy);
//}
//
//void DFS(const std::vector<Punct>& graf, int nodCurent, std::vector<double>& distante) {
//    for (int vecin = 0; vecin < graf.size(); ++vecin) {
//        if (distante[vecin] < 0) {  // Verificăm dacă nu am mai vizitat acest nod
//            distante[vecin] = distante[nodCurent] + Calculeaza_Dist(graf[nodCurent], graf[vecin]);
//            DFS(graf, vecin, distante);
//        }
//    }
//}
//
//std::vector<double> Calculeaza_Distante_DFS(const std::vector<Punct>& graf, int nodSursa) {
//    int n = graf.size();
//    std::vector<double> distante(n, -1.0);  // Inițializăm toate distanțele cu -1
//
//    distante[nodSursa] = 0.0;  // Distanța de la sursă la sursă este 0
//    DFS(graf, nodSursa, distante);
//
//    return distante;
//}
//
//int main() {
//    // Exemplu de utilizare
//    std::vector<Punct> graf = {{0.0, 0.0}, {1.0, 2.0}, {3.0, 1.0}, {4.0, 4.0}};
//    int nodSursa = 0;
//
//    std::vector<double> distante = Calculeaza_Distante_DFS(graf, nodSursa);
//
//    for (int i = 0; i < distante.size(); ++i) {
//        std::cout << "Distanta de la nodul " << nodSursa << " la nodul " << i << " este " << distante[i] << std::endl;
//    }
//
//    return 0;
//}

/*
 * Distanta de la nodul 0 la nodul 0 este 0
Distanta de la nodul 0 la nodul 1 este 2.23607
Distanta de la nodul 0 la nodul 2 este 4.47214
Distanta de la nodul 0 la nodul 3 este 7.63441

 * */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

struct Punct {
    double x, y;

    Punct(double x, double y) : x(x), y(y) {}
};

double Calculeaza_Dist(const Punct& punct1, const Punct& punct2) {
    double dx = punct2.x - punct1.x;
    double dy = punct2.y - punct1.y;

    return std::sqrt(dx * dx + dy * dy);
}

std::vector<double> Calculeaza_Distante_BFS(const std::vector<Punct>& graf, int nodSursa) {
    int n = graf.size();
    std::vector<double> distante(n, -1.0);  // Inițializăm toate distanțele cu -1

    distante[nodSursa] = 0.0;  // Distanța de la sursă la sursă este 0

    std::queue<int> coada;
    coada.push(nodSursa);

    while (!coada.empty()) {
        int nodCurent = coada.front();
        coada.pop();

        for (int vecin = 0; vecin < n; ++vecin) {
            if (distante[vecin] < 0) {  // Verificăm dacă nu am mai vizitat acest nod
                distante[vecin] = distante[nodCurent] + Calculeaza_Dist(graf[nodCurent], graf[vecin]);
                coada.push(vecin);
            }
        }
    }

    return distante;
}

int main() {
    // Exemplu de utilizare
    std::vector<Punct> graf = {{0.0, 0.0}, {1.0, 2.0}, {3.0, 1.0}, {4.0, 4.0}};
    int nodSursa = 0;

    std::vector<double> distante = Calculeaza_Distante_BFS(graf, nodSursa);

    for (int i = 0; i < distante.size(); ++i) {
        std::cout << "Distanta de la nodul " << nodSursa << " la nodul " << i << " este " << distante[i] << std::endl;
    }

    return 0;
}


