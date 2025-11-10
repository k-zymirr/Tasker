#include "taskslist.h"
#include <filesystem>
#include <fstream>
#include <cstdlib>

namespace fs = std::filesystem;

TasksList::TasksList()
{
    const char* home = getenv("HOME");
    if(!home)
        return;

    using namespace fs;
    path taskerDir = path(home) / ".tasker";
    path saveFile = taskerDir / "tasks.tls";
    if (! exists(taskerDir) || ! exists(saveFile))
        return;

    using namespace std;
    ifstream file(saveFile);

    if (! file.is_open())
        return;

    int pl = 0;
    string buffer;
    char c;
    bool first = true;

    while (file.get(c))
    {
        buffer += c;
        switch (pl)
        {
        case 0:
            if (c == '\n')
                pl ++;
            break;
        case 1:
            if (c == '<')
                pl ++;
            break;
        case 2:
            if (c == '>')
                pl ++;
            break;
        case 3:
            if (c == '\n')
            {
                if (first)
                {
                    first = false;
                }else {
                    buffer.erase(buffer.size() - 4);
                    TaskClass tc(buffer);
                    tasksclasses.push_back(tc);
                }
                buffer.clear();
            }
        default:
            pl = 0;
            break;
        }
    }

    if (! first)
    {
        buffer.erase(buffer.size() - 1);
        TaskClass tc(buffer);
        tasksclasses.push_back(tc);
    }
}

TasksList::~TasksList()
{
    const char* home = getenv("HOME");
    if (!home)
    {
        cerr << "Failed to get HOME directory, unable to save tasks." << endl;
        return;
    }

    using namespace fs;
    path taskerDir = path(home) / ".tasker";
    path saveFile = taskerDir / "tasks.tls";
    if (! exists(taskerDir))
    {
        try {
            create_directory(taskerDir);
        } catch (const filesystem_error& e)
        {
            cerr << "Failed to create ~/.tasker dirrectory, unable to save tasks." << endl;
            return;
        }
    }

    using namespace std;
    ofstream file(saveFile);
    if (!file)
    {
        cerr << "Error opening file : ~/.tasker/tasks.tls, unable to save tasks." << endl;
        return;
    }

    file << "\n";

    for (TaskClass& tc: tasksclasses)
        file << tc.formatSave();

    file.close();
}

void TasksList::list()
{
    for (const TaskClass& tc: tasksclasses)
    {
        cout << tc << endl;
    }
}

bool TasksList::listOneClass(int id)
{
    for (const TaskClass& tc: tasksclasses)
    {
        if (tc.id == id)
        {
            cout << tc << endl;
            return true;
        }
    }

    return false;
}

bool TasksList::add(unsigned short int rank, string text, int id)
{
    for (TaskClass& tc: tasksclasses)
    {
        if (tc.id == id)
        {
            Task t = tc.add(rank, text);
            cout << "New task added : " << t << endl;
            return true;
        }
    }

    return false;
}

bool TasksList::check(int id)
{
    for (TaskClass& tc: tasksclasses)
    {
        if (tc.check(id))
        {
            cout << tc << endl;
            return true;
        }
    }

    return false;
}

bool TasksList::del(int id)
{
    for (TaskClass& tc: tasksclasses)
    {
        if(tc.del(id))
        {
            cout << tc << endl;
            return true;
        }
    }

    return false;
}

void TasksList::createClass(string title)
{
    Color color = getRandomColor();
    TaskClass tc(title, color);
    tasksclasses.push_back(tc);
    cout << tc << endl;
}

void TasksList::createClass(string title, string _color)
{
    Color color = stringToColor(_color);
    TaskClass tc(title, color);
    tasksclasses.push_back(tc);
    cout << tc << endl;
}

bool TasksList::eraseClass(int id)
{
    for (int tc=0; tc < tasksclasses.size(); tc++)
    {
        if (tasksclasses.at(tc).id == id)
        {
            tasksclasses.erase(tasksclasses.begin()+tc);
            return true;
        }
    }

    return false;
}
