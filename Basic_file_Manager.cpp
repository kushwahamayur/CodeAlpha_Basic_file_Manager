#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sys/stat.h>D:\Users\mayur kushwah\Documents
#include <cstring>
#include <cstdlib>

using namespace std;

// Function to list the files in a directory
void listFiles(const string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir == nullptr) {
        cerr << "Unable to open directory: " << path << endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }

    closedir(dir);
}

// Function to create a directory
void createDirectory(const string& path) {
    if (mkdir(path.c_str()) == 0) {
        cout << "Directory created: " << path << endl;
    } else {
        cerr << "Failed to create directory: " << path << endl;
    }
}

// Function to view the contents of a file
void viewFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Function to copy a file
void copyFile(const string& source, const string& destination) {
    ifstream src(source, ios::binary);
    if (!src) {
        cerr << "Source file not found: " << source << endl;
        return;
    }

    ofstream dest(destination, ios::binary);
    if (!dest) {
        cerr << "Failed to create destination file: " << destination << endl;
        return;
    }

    dest << src.rdbuf();  // Copy contents from source to destination
    cout << "File copied from " << source << " to " << destination << endl;

    src.close();
    dest.close();
}

// Function to move a file (copy + remove the original)
void moveFile(const string& source, const string& destination) {
    copyFile(source, destination);
    if (remove(source.c_str()) == 0) {
        cout << "File moved from " << source << " to " << destination << endl;
    } else {
        cerr << "Failed to remove original file: " << source << endl;
    }
}

int main() {
    string command;
    string path, source, destination;

    cout << "Basic File Manager\n";
    cout << "Available commands: list, create, view, copy, move, exit\n";

    while (true) {
        cout << "\nEnter command: ";
        cin >> command;

        if (command == "list") {
            cout << "Enter directory path: ";
            cin >> path;
            listFiles(path);
        }
        else if (command == "create") {
            cout << "Enter directory name to create: ";
            cin >> path;
            createDirectory(path);
        }
        else if (command == "view") {
            cout << "Enter filename to view: ";
            cin >> path;
            viewFile(path);
        }
        else if (command == "copy") {
            cout << "Enter source filename: ";
            cin >> source;
            cout << "Enter destination filename: ";
            cin >> destination;
            copyFile(source, destination);
        }
        else if (command == "move") {
            cout << "Enter source filename: ";
            cin >> source;
            cout << "Enter destination filename: ";
            cin >> destination;
            moveFile(source, destination);
        }
        else if (command == "exit") {
            cout << "Exiting file manager." << endl;
            break;
        }
        else {
            cout << "Invalid command! Available commands are: list, create, view, copy, move, exit." << endl;
        }
    }

    return 0;
}
