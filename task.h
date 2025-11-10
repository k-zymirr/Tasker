#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>

using namespace std;

class Task
{
private:
    static int tasks_number;
    unsigned short int rank;
    string text;
    bool checked;

public:
    int id;

    Task(unsigned short int, string);
    Task(string);
    ~Task() = default;

    void check();

    string formatSave();
    friend ostream& operator <<(ostream&, const Task&);
};

#endif // TASK_H
