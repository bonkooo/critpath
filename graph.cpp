#include "graph.h"
#include "task.h"

#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

void Graph::addTask(int id, int duration)
{
	Task task;
	task.id = id;
	task.duration = duration;
	task.est = 0;
	task.lst = INT_MAX;
	task.prereqs = {};

	tasks[id] = task;
}

void Graph::addPrereq(int task, int prereq)
{
	tasks[task].prereqs.push_back(prereq);
	adjList[prereq].push_back(task);
}

void Graph::calculateEst()
{
	queue<int> q;
	unordered_map<int, int> inDegree; //mapa koja cuva ulazni stepen cvora

	//inicijalizacija ulaznih stepena
	for (const auto& taskObj : tasks) {
		int id = taskObj.first;
		const Task& task = taskObj.second;
		inDegree[id] = task.prereqs.size();
		//dodaj u red taskove sa ulaznim stepenom 0
		if (inDegree[id] == 0) {
			q.push(id);
			tasks[id].est = 0;
		}
	}

	//prodji kroz taskove u topoloskom poretku
	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		for (int neighbor : adjList[curr]) {
			inDegree[neighbor]--; //smanji ulazni stepen za sve susedne cvorove i proveri da li je nekom 0
			if (inDegree[neighbor] == 0) {
				q.push(neighbor);
			}
			//updateuj est za sledbenike
			tasks[neighbor].est = max(tasks[neighbor].est, tasks[curr].est + tasks[curr].duration);
		}
	}
}

void Graph::calculateLst() {
	queue<int> q;
	unordered_map<int, int> outDegree;
	vector<int> TopoOrder;

	// Inicijalizuj izlazne stepene
	for (const auto& taskObj : tasks) {
		int id = taskObj.first;
		outDegree[id] = adjList[id].size();
		if (outDegree[id] == 0) {
			q.push(id);
			tasks[id].lst = tasks[id].est;  //inicijalno LST = EST
		}
	}

	// odredi topoloski poredak
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		TopoOrder.push_back(curr);
		for (int neighbor : adjList[curr]) {
			outDegree[neighbor]--;
			if (outDegree[neighbor] == 0) {
				q.push(neighbor);
			}
		}
	}

	// okreni topoloski poredak
	std::reverse(TopoOrder.begin(), TopoOrder.end());

	// izracunaj vrednosti za lst
	for (int id : TopoOrder) {
		for (int prereq : tasks[id].prereqs) {
			tasks[prereq].lst = min(tasks[prereq].lst, tasks[id].lst - tasks[prereq].duration);
		}
	}

	// cvorovi sa ulaznim stepenom 0
	for (auto& taskObj : tasks) {
		if (taskObj.second.prereqs.empty()) {
			taskObj.second.lst = taskObj.second.est; 
		}
	}
}



void Graph::printTasks()
{
	cout << "Aktivnosti i njihovi preduslovi: \n";
	for (const auto& taskObj : tasks) {
		cout << "ID: " << taskObj.first << " Trajanje aktivnosti: " << taskObj.second.duration << " \n";
		cout << "Preduslovi: ";
		for (int prereq : taskObj.second.prereqs) {
			cout << prereq << " ";
		}
		cout << "\n";
	}
}

void Graph::printResults() {
	cout << "Aktivnost\tEST\tLST\tDozv. kasnjenje\n";
	for (const auto& taskObj : tasks) {
		std::cout << taskObj.first << "\t" << taskObj.second.est << "\t" << taskObj.second.lst << "\t" << taskObj.second.lst - taskObj.second.est << endl;
	}

	std::cout << "Kriticni put: ";
	for (const auto& taskObj : tasks) {
		if (taskObj.second.est == taskObj.second.lst) {
			cout << taskObj.first << " ";
		}
	}
	cout << endl;
}
