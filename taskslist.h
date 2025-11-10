#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <vector>
#include <string>

#include "taskclass.h"

using namespace std;

class TasksList
{
private:
    vector<TaskClass> tasksclasses;
public:
    TasksList();
    ~TasksList();

    void list();
    bool listOneClass(int);

    bool add(unsigned short int, string, int);
    bool check(int);
    bool del(int);

    void createClass(string);
    void createClass(string, string);
    bool eraseClass(int);
};

#endif // TASKSLIST_H
