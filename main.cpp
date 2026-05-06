#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Task {
public:
    string title;
    bool completed;

    Task(string t, bool c = false) {
        title = t;
        completed = c;
    }
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask() {
        string title;
        cout << "Enter task: ";
        cin.ignore();
        getline(cin, title);
        tasks.push_back(Task(title));
        cout << "Task added successfully!\n";
    }

    void viewPendingTasks() {
        cout << "\n--- Pending Tasks ---\n";
        bool found = false;

        for (int i = 0; i < tasks.size(); i++) {
            if (!tasks[i].completed) {
                cout << i + 1 << ". " << tasks[i].title << endl;
                found = true;
            }
        }

        if (!found)
            cout << "No pending tasks.\n";
    }

    void viewCompletedTasks() {
        cout << "\n--- Completed Tasks ---\n";
        bool found = false;

        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].completed) {
                cout << i + 1 << ". " << tasks[i].title << endl;
                found = true;
            }
        }

        if (!found)
            cout << "No completed tasks.\n";
    }

    void markCompleted() {
        int index;
        viewPendingTasks();
        cout << "Enter task number to mark as completed: ";
        cin >> index;

        if (index > 0 && index <= tasks.size() && !tasks[index - 1].completed) {
            tasks[index - 1].completed = true;
            cout << "Task marked as completed!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

    void saveToFile() {
        ofstream file("tasks.txt");
        for (auto &task : tasks) {
            file << task.title << "|" << task.completed << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("tasks.txt");
        if (!file) return;

        string title;
        bool completed;

        while (getline(file, title, '|')) {
            file >> completed;
            file.ignore();
            tasks.push_back(Task(title, completed));
        }

        file.close();
    }
};

int main() {
    ToDoList todo;
    todo.loadFromFile();

    int choice;

    do {
        cout << "\n===== TO-DO LIST MENU =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Pending Tasks\n";
        cout << "3. View Completed Tasks\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: todo.addTask(); break;
            case 2: todo.viewPendingTasks(); break;
            case 3: todo.viewCompletedTasks(); break;
            case 4: todo.markCompleted(); break;
            case 5: todo.saveToFile(); cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}