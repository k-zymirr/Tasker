#include <iostream>
#include <vector>
#include <string>
#include "taskslist.h"

#define VERSION "1.0"

using namespace std;

int main(int argc, char* argv[])
{
    TasksList tl;

    int args = argc - 2;
    vector<string> argw;
    for (int a=2; a<argc; a++)
        argw.push_back(argv[a]);

    if (argc == 1) {
        cout << "tasker" << endl;
        cout << "    A task manager from the terminal. For help, type tasker -h or --help" << endl;

        return EXIT_SUCCESS;
    }

    string action = argv[1];

    if (action == "-h" || action == "--help")
    {
        cout << "Usage: tasker [ACTION] [ARGUMENTS]" << endl << endl;

        cout << "-h, --help    Display the help message" << endl;
        cout << "-v, --version       See the version of tasker" << endl << endl;

        cout << "Actions:" << endl;
        cout << "    ls     List currents tasks" << endl;
        cout << "    add    Add a task to the list" << endl;
        cout << "    check  Mark a task as done" << endl;
        cout << "    rm     Remove a task from the list" << endl;
        cout << "    class  Manage classes" << endl << endl;

        cout << "To see how to use an action, type tasker [ACTION] -h or --help" << endl;

        return EXIT_SUCCESS;
    }

    if (action == "-v" || action == "--version")
    {
        cout << VERSION << endl;
        return EXIT_SUCCESS;
    }

    else if (action == "ls")
    {
        if (args == 0)
        {
            tl.list();
            return EXIT_SUCCESS;
        }

        int class_id = -1;
        bool c;

        for (const string& option: argw)
        {
            if (option == "-h" || option == "--help")
            {
                cout << "Usage: tasker list (ARGUMENTS)" << endl << endl;

                cout << "tasker list    Display all currents tasks" << endl << endl;

                cout << "Arguments:" << endl;
                cout << "    -c, --class    [int]    Select a specific class to display by ID" << endl;

                return EXIT_SUCCESS;
            }

            if (option == "-c" || option == "--class")
            {
                c = true;
                continue;
            }

            if (c)
            {
                try
                {
                    class_id = stoi(option);

                    if (class_id < 1)
                        throw new out_of_range("class < 1");

                    c = false;
                } catch (const invalid_argument&)
                {
                    cerr << "Error: The 'class' argument must be an interger greater than 0." << endl;
                    return EXIT_FAILURE;
                } catch (const out_of_range&)
                {
                    cerr << "Error: You must specify an  integer for 'class' argument." << endl;
                    return EXIT_FAILURE;
                }
            }
        }

        if (class_id != -1)
        {
            if (tl.listOneClass(c))
            {
                return EXIT_SUCCESS;
            }
            else
            {
                cerr << "Error: Class with ID " << c << " does not exist." << endl;
                return EXIT_FAILURE;
            }
        }

        cerr << "Error: Invalid arguments for 'list' action. Try tasker list -h or --help." << endl;
        return EXIT_FAILURE;
    }

    else if (action == "add")
    {
        if (args == 0)
        {
            cerr << "Error: Missing arguments for 'add' action. Try tasker add -h or --help." << endl;
            return EXIT_FAILURE;
        }

        int rank=-1, class_id=-1;
        string title="";

        bool r=false, c=false, t=false;

        for (const string& option: argw)
        {
            if (option == "-h" || option == "--help")
            {
                cout << "Usage: tasker add [ARGUMENTS]" << endl << endl;

                cout << "Arguments:" << endl;
                cout << "    -r, --rank     [int]       Select the importance of the new task (lower 0, higher 5)" << endl;
                cout << "    -c, --class    [int]       Select the class of the new task by ID" << endl;
                cout << "    -t, --title    [string]    Select the title of the new task." << endl;

                return EXIT_SUCCESS;
            }

            if (option == "-r" || option == "--rank")
            {
                r = true;
                continue;
            }

            if (option == "-c" || option == "--class")
            {
                c = true;
                continue;
            }

            if (option == "-t" || option =="--title")
            {
                t = true;
                continue;
            }

            if (r)
            {
                try
                {
                    rank = stoi(option);
                    if ((rank < 0) || (rank > 5))
                    {
                        throw new invalid_argument("out of range");
                    }
                } catch (const invalid_argument& e)
                {
                    cerr << "Error: the 'rank' argument must be a integer between 0 and 5." << endl;
                    return EXIT_FAILURE;
                } catch (const out_of_range&)
                {
                    cerr << "Error: you must specify an integer between 0 and 5 for the 'rank' argument." << endl;
                    return EXIT_FAILURE;
                }

                r = false;
            }

            if (c)
            {
                try
                {
                    class_id = stoi(option);
                } catch (const invalid_argument&)
                {
                    cerr << "Error: the 'class' argument must be a integer." << endl;
                    return EXIT_FAILURE;
                }

                c = false;
            }

            if (t)
            {
                title = option;
                t = false;
            }
        }

        if (rank != -1 && class_id != -1 && title != "")
        {
            if (tl.add(rank, title, class_id))
                return EXIT_SUCCESS;
            else
            {
                cerr << "Error: Unknow class with the ID" << c << "." << endl;
                return EXIT_FAILURE;
            }
        }

        cerr << "Error: Invalid arguments for 'add' action. Try tasker add -h or --help." << endl;
        return EXIT_FAILURE;
    }

    else if (action == "check")
    {
        if (args == 0)
        {
            cerr << "Error: Missing arguments for 'check' action. Try tasker check -h or --help." << endl;
            return EXIT_FAILURE;
        }

        if (argw[0] == "-h" || argw[0] == "--help")
        {
            cout << "Usage: tasker check [task_id]" << endl << endl;
            return EXIT_SUCCESS;
        }

        try {
            int task_id = stoi(argw[0]);
            if (tl.check(task_id))
                return EXIT_SUCCESS;
            else
            {
                cerr << "Error: Unknow task with the ID" << task_id << "." << endl;
                return EXIT_FAILURE;
            }
        } catch (const invalid_argument&)
        {
            cerr << "Error: you must specify an integer for 'task'option." << endl;
            return EXIT_FAILURE;
        }
    }

    else if (action == "class")
    {
        if (args == 0)
        {
            cerr << "Error: Missing arguments for 'class' action. Try tasker add -h or --help." << endl;
            return EXIT_FAILURE;
        }

        int delete_class=-1;
        string new_class="", color="";
        bool n=false, d=false, c=false;

        for (const string& option: argw)
        {
            if (option == "-h" || option == "--help")
            {
                cout << "Usage: tasker class [ARGUMENTS]" << endl << endl;

                cout << "Arguments:" << endl;
                cout << "    -n, --new       [string]    Create a new class and naming it." << endl;
                cout << "    -d, --delete    [int]       Delete a task by ID." << endl;
                cout << "    -c, --color     [string]    Select the color of the new class." << endl;
                cout << "                                Possible values :" << endl;
                cout << "                                    - red" << endl;
                cout << "                                    - green" << endl;
                cout << "                                    - yellow" << endl;
                cout << "                                    - blue" << endl;
                cout << "                                    - magenta" << endl;
                cout << "                                    - cyan" << endl;
                cout << "                                    - gray" << endl;
                cout << "                                    - white" << endl;

                return EXIT_SUCCESS;
            }

            if (option == "-n" || option == "--new")
            {
                n = true;
                continue;
            }

            if (option == "-d" || option == "--delete")
            {
                d = true;
                continue;
            }

            if (option == "-c" || option == "--color")
            {
                c = true;
                continue;
            }

            if (n)
            {
                new_class = option;
                n = false;
            }

            if (d)
            {
                try {
                    delete_class = stoi(option);
                }catch (const invalid_argument&)
                {
                    cerr << "Error: invalid argument for 'delete' option" << endl;
                    return EXIT_FAILURE;
                }

                d = false;
            }

            if (c)
            {
                color = option;
                c = false;
            }
        }

        if (new_class != "")
        {
            if (color != "")
                tl.createClass(new_class, color);
            else
                tl.createClass(new_class);

            return EXIT_SUCCESS;
        }

        if (delete_class != -1)
        {
            if (tl.eraseClass(delete_class))
                return EXIT_SUCCESS;
            else
            {
                cerr << "Error: Uknow task with ID " << delete_class << "." << endl;
                return EXIT_FAILURE;
            }
        }

        cerr << "Error: Invalid arguments for 'class' action. Try tasker class -h or --help." << endl;
        return EXIT_FAILURE;
    }

    else if (action == "rm")
    {
        if (args == 0)
        {
            cerr << "Error: Missing arguments for 'check' action. Try tasker check -h or --help." << endl;
            return EXIT_FAILURE;
        }

        if (argw[0] == "-h" || argw[0] == "--help")
        {
            cout << "Usage: tasker rm [task_id]" << endl;
            return EXIT_SUCCESS;
        }

        try {
            int task_id = stoi(argw[0]);
            if (tl.del(task_id))
                return EXIT_SUCCESS;
            else
            {
                cerr << "Error: Uknow task with ID " << task_id << "." << endl;
                return EXIT_FAILURE;
            }
        } catch (const invalid_argument&)
        {
            cerr << "Error: Invalid argument for 'rm' action." << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_FAILURE;
}
