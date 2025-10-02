// fancyprint.h : FancyPrint - an improved iostream helper
// Provides styled logging, prompts, loaders, selections, confirmations, and ASCII graphs.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// ANSI escape codes for colors (portable in most modern terminals)
#define FP_COLOR_RESET   "\033[0m"
#define FP_COLOR_INFO    "\033[36m"  // Cyan
#define FP_COLOR_WARN    "\033[33m"  // Yellow
#define FP_COLOR_ERROR   "\033[31m"  // Red
#define FP_COLOR_SUCCESS "\033[32m"  // Green
#define FP_COLOR_SYSTEM  "\033[35m"  // Magenta

using namespace std;

class FancyPrint {
public:

    // --- Logging methods ---
    static void Print_info(const string& message, bool minimal) {
        if (!minimal)
            cout << FP_COLOR_INFO << "[INFO] " << message << FP_COLOR_RESET << endl;
        else
            cout << FP_COLOR_INFO << "[+] " << message << FP_COLOR_RESET << endl;
    }

    static void Print_warning(const string& message, bool minimal) {
        if (!minimal)
            cout << FP_COLOR_WARN << "[WARNING] " << message << FP_COLOR_RESET << endl;
        else
            cout << FP_COLOR_WARN << "[!] " << message << FP_COLOR_RESET << endl;
    }

    static void Print_error(const string& message, bool minimal) {
        if (!minimal)
            cout << FP_COLOR_ERROR << "[ERROR] " << message << FP_COLOR_RESET << endl;
        else
            cout << FP_COLOR_ERROR << "[!!!] " << message << FP_COLOR_RESET << endl;
    }

    static void Print_success(const string& message, bool minimal) {
        if (!minimal)
            cout << FP_COLOR_SUCCESS << "[SUCCESS] " << message << FP_COLOR_RESET << endl;
        else
            cout << FP_COLOR_SUCCESS << "[+] " << message << FP_COLOR_RESET << endl;
    }

    // --- Input ---
    static string Print_input(const string& prompt) {
        cout << FP_COLOR_INFO << "[INPUT] " << prompt << ": " << FP_COLOR_RESET;
        string input;
        cin >> input;
        return input;
    }

    // --- Delimiter ---
    static void Print_delimiter(const string& message) {
        cout << FP_COLOR_SYSTEM
            << "==================== " << message << " ===================="
            << FP_COLOR_RESET << endl;
    }

    // --- Loading animation ---
    static void Print_loading(int timeout, int waitTimePerSeg, char charload) {
        cout << "[LOADING] ";
        for (int i = 0; i < timeout; i++) {
            cout << charload << flush;
            this_thread::sleep_for(chrono::milliseconds(waitTimePerSeg));
        }
        cout << endl;
    }

    // --- Selection menu ---
    static int Print_selection(const string options[], int size) {
        cout << "[SELECTION] Please select an option:" << endl;
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << options[i] << endl;
        }
        int choice;
        cin >> choice;
        while (choice < 1 || choice > size) {
            cout << "[ERROR] Invalid choice. Please select a valid option:" << endl;
            cin >> choice;
        }
        return choice;
    }

    // --- Confirmation ---
    static bool Print_confirm(const string& message) {
        cout << "[CONFIRM] " << message << " (y/n): ";
        char choice;
        cin >> choice;
        while (choice != 'y' && choice != 'n') {
            cout << "[ERROR] Invalid choice. Please enter 'y' or 'n': ";
            cin >> choice;
        }
        return choice == 'y';
    }

    // --- Countdown ---
    static void Print_countdown(int seconds) {
        cout << "[COUNTDOWN] ";
        for (int i = seconds; i > 0; i--) {
            cout << i << " " << flush;
            this_thread::sleep_for(chrono::seconds(1));
        }
        cout << endl;
    }

    // --- ASCII Graph ---
    static void Graph(const string options[], const int valuemap[], int size) {
        cout << "[GRAPH]" << endl;
        for (int i = 0; i < size; i++) {
            cout << options[i] << " ";
            for (int j = 0; j < valuemap[i]; j++) {
                cout << "*";
            }
            cout << " (" << valuemap[i] << ")" << endl;
        }
    }

    // --- Vector Representation ---
    static void Represent_vector(const vector<int>& vec) {
        cout << "[SYSTEM] Vector elements:";
        for (const int& elem : vec) {
            cout << " " << elem;
        }
        cout << endl;
    }

    // --- Math Representation ---
    static void Represent_math(const string& expression, double result) {
        cout << "[MATH] " << expression << " = " << result << endl;
    }
};

