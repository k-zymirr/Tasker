#include "taskclass.h"
#include <sstream>

int TaskClass::taskClasses_number=0;

string colorToPrintable(Color c)
{
    switch (c)
    {
        case Color::Red :
            return "\033[31m";
            break;
        case Color::Green :
            return "\033[32m";
            break;
        case Color::Yellow :
            return "\033[33m";
            break;
        case Color::Blue :
            return "\033[34m";
            break;
        case Color::Magenta :
            return "\033[35m";
            break;
        case Color::Cyan :
            return "\033[36m";
            break;
        case Color::Gray :
            return "\033[37m";
            break;
        case Color::White :
            return "\033[97m";
            break;
    }

    return "\033[97m";
}

string colorToString(Color c)
{
    switch (c)
    {
    case Color::Red :
        return "red";
        break;
    case Color::Green :
        return "green";
        break;
    case Color::Yellow :
        return "yellow";
        break;
    case Color::Blue :
        return "blue";
        break;
    case Color::Magenta :
        return "magenta";
        break;
    case Color::Cyan :
        return "cyan";
        break;
    case Color::Gray :
        return "gray";
        break;
    case Color::White :
        return "white";
        break;
    }

    return "white";
}

Color stringToColor(string s)
{
    if (s == "red") {
        return Color::Red;
    } else if (s == "green") {
        return Color::Green;
    } else if (s == "yellow") {
        return Color::Yellow;
    } else if (s == "blue") {
        return Color::Blue;
    } else if (s == "magenta") {
        return Color::Magenta;
    } else if (s == "cyan") {
        return Color::Cyan;
    } else if (s == "gray") {
        return Color::Gray;
    } else if (s == "white") {
        return Color::White;
    }

    return Color::White;
}

Color getRandomColor()
{
    return Color(rand()%8);
}

TaskClass::TaskClass(string _title, Color _color)
    : id(++taskClasses_number), title(_title), color(_color)
{}

TaskClass::TaskClass(string import)
{
    string ts;
    stringstream ss(import);
    char delimitor = '\n';
    vector<string> tsks;

    while (getline(ss, ts, delimitor))
    {
        tsks.push_back(ts);
    }

    string attr;
    stringstream ssAtr(tsks.at((0)));
    char delim = ';';
    string attributes[3];
    int a = 0;

    while (getline(ssAtr, attr, delim) && a<3)
    {
        attributes[a] = attr;
        a ++;
    };

    id = stoi(attributes[0]);
    title = attributes[1];
    color = stringToColor(attributes[2]);

    tsks.erase(tsks.begin());
    for (const string& ti: tsks)
    {
        Task task(ti);
        tasks.push_back(task);
    }

    if (id > taskClasses_number)
    {
        taskClasses_number = id;
    }
}

Task TaskClass::add(unsigned short int rank, string text)
{
    Task newTask(rank, text);
    tasks.push_back(newTask);
    return newTask;
}

bool TaskClass::check(int _id)
{
    for (Task& t: tasks)
    {
        if (t.id == _id)
        {
            t.check();
            return true;
        }
    }

    return false;
}

bool TaskClass::del(int _id)
{
    for (int t=0; t<tasks.size(); t++)
    {
        if (tasks.at(t).id == _id)
        {
            tasks.erase(tasks.begin() + t);
            return true;
        }
    }

    return false;
}

string TaskClass::formatSave()
{
    string Scolor = colorToString(color);
    stringstream ret;
    ret << "<>" << "\n" << id << ";" << title << ";" << Scolor << "\n";

    for (Task& t: tasks) {
        ret << t.formatSave() << "\n";
    }

    return ret.str();
}

ostream& operator <<(ostream& os, const TaskClass& TC)
{
    os << colorToPrintable(TC.color) << TC.id << ". " << TC.title << "\033[0;39m" << "\n";
    for (const Task& t: TC.tasks)
    {
        os << "    " << t << "\n";
    }

    return os;
}
