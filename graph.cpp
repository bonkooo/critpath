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

		for (int neighbor: adjList[curr]) {
			inDegree[neighbor]--; //smanji ulazni stepen za sve susedne cvorove i proveri da li je nekom 0
			if (inDegree[neighbor] == 0) {
				q.push(neighbor);
			}
			//updateuj est za susede 
			tasks[neighbor].est = max(tasks[neighbor].est, tasks[curr].est + tasks[curr].duration);
		}
	}
}

void Graph::calculateLst()
{
	queue<int> q;
	unordered_map<int, int> outDegree;
	vector<int> TopoOrder;

	for (const auto& taskObj : tasks) {
		int id = taskObj.first;
		const Task& task = taskObj.second;
		outDegree[id] = adjList[id].size();
		if (outDegree[id] == 0) {
			tasks[id].lst = tasks[id].est;
		}
	}
}

void Graph::printTasks()
{
}

void Graph::printResults()
{
}
