#ifndef TASKCLASS_H
#define TASKCLASS_H

#include <string>
#include <vector>
#include <iostream>

#include "task.h"

using namespace std;

enum class Color
{
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    Gray,
    White
};

string colorToPrintable(Color);
string colorToString(Color);
Color stringToColor(string);
Color getRandomColor();

class TaskClass
{
private:
    static int taskClasses_number;
    string title;
    Color color;
    vector<Task> tasks;

public:
    int id;

    TaskClass(string, Color);
    TaskClass(string);
    ~TaskClass() = default;

    Task add(unsigned short int, string);
    bool check(int);
    bool del(int);

    string formatSave();
    friend ostream& operator <<(ostream&, const TaskClass&);
};

#endif // TASKCLASS_H
