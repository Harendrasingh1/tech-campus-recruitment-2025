#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <limits>
#include <direct.h>

#define MAKE_DIR(path) _mkdir(path)

using namespace std;

void createOutputDir() {
    struct stat info;
    if (stat("output", &info) != 0) {
        mkdir("output");
    }
}

long long binarySearchDate(ifstream &logFile, const string &targetDate) {
    logFile.seekg(0, ios::end);
    long long left = 0, right = logFile.tellg(), mid;
    string line;

    while (left < right) {
        mid = left + (right - left) / 2;

        logFile.seekg(mid);
        if (mid > 0) {
            logFile.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (!getline(logFile, line)) break;

        if (line.substr(0, 10) >= targetDate) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

void extractLogs(const string &filePath, const string &targetDate) {
    ifstream logFile(filePath);
    if (!logFile) {
        cerr << "Error: Unable to open file.\n";
        return;
    }

    long long startPos = binarySearchDate(logFile, targetDate);
    logFile.seekg(startPos);

    string line;
    string outputFileName = "../output/output_" + targetDate + ".txt";
    ofstream outFile(outputFileName);

    if (!outFile) {
        cerr << "Error: Unable to create output file.\n";
        return;
    }

    while (getline(logFile, line)) {
        if (line.substr(0, 10) == targetDate) {
            outFile << line << '\n';
        } else if (line.substr(0, 4) > targetDate.substr(0, 4)) {
            break;
        }
    }

    logFile.close();
    outFile.close();
    cout << "Logs extracted to " << outputFileName << '\n';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./extract_logs <log_file> <YYYY-MM-DD>\n";
        return 1;
    }

    string logFile = argv[1];
    string targetDate = argv[2];

    extractLogs(logFile, targetDate);
    return 0;
}