#include "task.h"
#include <sstream>

int Task::tasks_number=0;

Task::Task(unsigned short int _rank, string _text)
    :   id(++tasks_number), rank(_rank), text(_text), checked(false)
{
}

Task::Task(string import)
{
    string attr;
    stringstream ss(import);
    char delimitor = ';';
    string attributes[4];
    int a = 0;

    while (getline(ss, attr, delimitor) && a<4)
    {
        attributes[a] = attr;
        a ++;
    };

    id = stoi(attributes[0]);
    rank = stoi(attributes[1]);
    text = attributes[2];
    checked = stoi(attributes[3]);
    if (id >= tasks_number)
    {
        tasks_number = id;
    }
}

void Task::check()
{
    checked = !checked;
}

string Task::formatSave()
{
    stringstream ret;
    ret << id << ";" << rank << ";" << text << ";" << checked;
    return ret.str();
}

ostream& operator <<(ostream& os, const Task& T)
{
    os << "\033[";
    switch(T.rank)
    {
        case 0:
            os << "0;37m";
            break;
        case 1:
            os << "0;97m";
            break;
        case 2:
            os << "0;94m";
            break;
        case 3:
            os << "0;33m";
            break;
        case 4:
            os << "0;31m";
            break;
        case 5:
            os << "1;31m";
            break;
        default:
            os << "0;39m";
            break;
    }

    os << T.id << " - " << "[" << (T.checked ? "x" : " ") << "] " << T.text;

    os << "\033[0;39m";

    return os;
}
