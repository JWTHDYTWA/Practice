// Универсальный граф
#include <iostream>
#include <map>
#include <Windows.h>
#include "uGraph.h"

using namespace std;

template <typename type1>
void print(type1 S) {
    cout << S << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    uGraph G;
    G.readFile("graph.txt");
    G.print();
    auto PATH = G.pathFind(G["Москва"],G["Омск"]);
    while (!PATH.empty()) {
        cout << PATH.top().first->label << " (" << PATH.top().second << ")" << " ";
        PATH.pop();
    }
    cout << endl << endl;
    G.rmVertex("Чебоксары");
    cout << "Удаляю Чебоксары" << endl << endl;
    G.print();
    PATH = G.pathFind(G["Москва"], G["Омск"]);
    while (!PATH.empty()) {
        cout << PATH.top().first->label << " (" << PATH.top().second << ")" << " ";
        PATH.pop();
    }
    cout << endl;
}
