#pragma once
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <limits>
#include "stb.h" // Your Simple Text Buffer

// ANSI escape codes for colors
#define FP_COLOR_RESET   "\033[0m"
#define FP_COLOR_INFO    "\033[36m"
#define FP_COLOR_WARN    "\033[33m"
#define FP_COLOR_ERROR   "\033[31m"
#define FP_COLOR_SUCCESS "\033[32m"
#define FP_COLOR_SYSTEM  "\033[35m"

class FancyPrint {
public:
    // --- Logging methods ---
    static void Print_info(const std::string& message, bool minimal = false) {
        STB::printText((minimal ? FP_COLOR_INFO "[+] " : FP_COLOR_INFO "[INFO] ") + message + FP_COLOR_RESET + "\n");
    }

    static void Print_warning(const std::string& message, bool minimal = false) {
        STB::printText((minimal ? FP_COLOR_WARN "[!] " : FP_COLOR_WARN "[WARNING] ") + message + FP_COLOR_RESET + "\n");
    }

    static void Print_error(const std::string& message, bool minimal = false) {
        STB::printText((minimal ? FP_COLOR_ERROR "[!!!] " : FP_COLOR_ERROR "[ERROR] ") + message + FP_COLOR_RESET + "\n");
    }

    static void Print_success(const std::string& message, bool minimal = false) {
        STB::printText((minimal ? FP_COLOR_SUCCESS "[+] " : FP_COLOR_SUCCESS "[SUCCESS] ") + message + FP_COLOR_RESET + "\n");
    }

    // --- Input ---
    static std::string Print_input(const std::string& prompt) {
        STB::printText(FP_COLOR_INFO "[INPUT] " + prompt + ": " + FP_COLOR_RESET);
        return STB::getText();
    }

    // --- Delimiter ---
    static void Print_delimiter(const std::string& message) {
        STB::printText(FP_COLOR_SYSTEM "==================== " + message + " ====================" FP_COLOR_RESET "\n");
    }

    // --- Loading animation ---
    static void Print_loading(int steps, int waitMsPerStep = 200, char charload = '=') {
        std::string line = "[LOADING] ";
        for (int i = 0; i < steps; ++i) {
            line += charload;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitMsPerStep));
        }
        STB::printText(line + "\n");
    }

    // --- Selection menu ---
    static int Print_selection(const std::string options[], int size) {
        STB::printText("[SELECTION] Please select an option:\n");
        for (int i = 0; i < size; ++i)
            STB::printText(std::to_string(i + 1) + ". " + options[i] + "\n");

        int choice;
        while (true) {
            choice = STB::getNumber();
            if (choice >= 1 && choice <= size) return choice;
            Print_error("Invalid choice. Please select a valid option.");
        }
    }

    // --- Confirmation ---
    static bool Print_confirm(const std::string& message) {
        while (true) {
            STB::printText(FP_COLOR_INFO "[CONFIRM] " + message + " (y/n): " + FP_COLOR_RESET);
            std::string input = STB::getText();
            if (input == "y" || input == "Y") return true;
            if (input == "n" || input == "N") return false;
            Print_error("Invalid choice. Please enter 'y' or 'n'.");
        }
    }

    // --- Countdown ---
    static void Print_countdown(int seconds) {
        std::string line = "[COUNTDOWN] ";
        for (int i = seconds; i > 0; --i) {
            line += std::to_string(i) + " ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        STB::printText(line + "\n");
    }

    // --- ASCII Graph ---
    static void Graph(const std::string options[], const int values[], int size) {
        STB::printText("[GRAPH]\n");
        for (int i = 0; i < size; ++i) {
            std::string line = options[i] + " ";
            for (int j = 0; j < values[i]; ++j) line += "*";
            line += " (" + std::to_string(values[i]) + ")";
            STB::printText(line + "\n");
        }
    }

    // --- Vector Representation ---
    static void Represent_vector(const std::vector<int>& vec) {
        std::string line = "[SYSTEM] Vector elements:";
        for (int val : vec) line += " " + std::to_string(val);
        STB::printText(line + "\n");
    }

    // --- Math Representation ---
    static void Represent_math(const std::string& expr, double result) {
        STB::printText("[MATH] " + expr + " = " + std::to_string(result) + "\n");
    }
};
