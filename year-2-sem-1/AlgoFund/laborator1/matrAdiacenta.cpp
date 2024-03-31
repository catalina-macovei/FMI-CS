#include <fstream>
#include <iostream>

using namespace std;

void display(int arr[100][100]) {
    //int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}
int main() {
    const char* filename = "laborator1/graf.in";
    ifstream inFile(filename);

    // Make sure the file stream is good
    if(!inFile) {
        cout << endl << "Failed to open file " << filename;
        return 1;
    }

    int n1 = 0;
    int n2 = 0;
    int nr_muchii = 0;
    int nr_varfuri = 0;
    int matrix[100][100];
    if (!inFile.eof()) {
        inFile >> nr_varfuri >> nr_muchii;
        while (!inFile.eof()) {
            inFile >> n1 >> n2;
            matrix[n1 - 1][n2 - 1] = 1;
        }
    }
    display(matrix);

    cout << endl;
    return 0;
}