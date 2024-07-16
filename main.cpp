#include <iostream>
#include "graph.h"
#include "task.h"

using namespace std;

void prikaziMeni() {
    cout << "a. Dodaj aktivnost" << endl;
    cout << "b. Dodaj preduslov" << endl;
    cout << "c. Prikazi aktivnosti" << endl;
    cout << "d. Izracunaj EST i LST" << endl;
    cout << "f. Prikazi kriticni put" << endl;
    cout << "e. Izlaz" << endl;
    cout << "Choose an option: ";
}

int main() {
    Graph g;
    int id, duration, task, prereq;
    char option;

    while (true) {
        prikaziMeni();
        cin >> option;

        switch (option) {
        case 'a':
            cout << "Unesi ID aktivnosti i trajanje: ";
            cin >> id >> duration;
            g.addTask(id, duration);
            break;
        case 'b':
            cout << "Unesi ID aktivnosti i ID preduslova: ";
            cin >> task >> prereq;
            g.addPrereq(task, prereq);
            break;
        case 'c':
            g.printTasks();
            break;
        case 'd':
            g.calculateEst();
            g.calculateLst();
            g.printResults();
            break;
        case 'f':
            g.printResults();
            break;
        case 'e':
            return 0;
        default:
            cout << "Nevalidna opcija!" << endl;
        }
    }

    return 0;
}
