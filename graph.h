#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <vector>
#include "task.h"
using namespace std;

class Graph {
	unordered_map<int, vector<int>> adjList;
	unordered_map<int, Task> tasks;
public:
	void addTask(int id, int duration);
	void addPrereq(int task, int prereq);
	void calculateEst();
	void calculateLst();
	void printTasks();
	void printResults();
};

#endif // !_GRAPH_H

