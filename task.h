#ifndef _TASK_H
#define _TASK_H

#include <vector>
using namespace std;

struct Task {
	int id;
	int duration;
	int est;
	int lst;
	vector<int> prereqs; //vektor koji cuva id-ove taskova koji su preduslovi datog taska
};

#endif // _TASK_H
