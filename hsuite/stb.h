#pragma once
#include <iostream>
#include <string>
#include <cctype>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

class STB {
public:
    // Print text to console and always append newline
    static void printText(const std::string& text) {
        std::cout << text << std::endl;
    }

    // Capture text from user key-by-key
    static std::string getText() {
        std::string input;
        char c;

        while (true) {
            c = getKey();

            // Enter ends input
            if (c == '\r' || c == '\n') {
                printText(""); // move to next line
                break;
            }
            // Backspace support
            else if (c == '\b' || c == 127) {
                if (!input.empty()) {
                    input.pop_back();
                    std::cout << "\b \b" << std::flush;
                }
            }
            else {
                input += c;
                std::cout << c << std::flush; // echo char
            }
        }

        return input;
    }

    // Capture integer input key-by-key
    static int getNumber() {
        std::string input;
        char c;

        while (true) {
            c = getKey();

            if (c == '\r' || c == '\n') {
                printText(""); // move to next line
                if (!input.empty())
                    break;
            }
            else if (c == '\b' || c == 127) {
                if (!input.empty()) {
                    input.pop_back();
                    std::cout << "\b \b" << std::flush;
                }
            }
            else if (std::isdigit(c) || (c == '-' && input.empty())) {
                input += c;
                std::cout << c << std::flush;
            }
        }

        return std::stoi(input);
    }

private:
    // Cross-platform single key capture
    static char getKey() {
#ifdef _WIN32
        return _getch();
#else
        char c;
        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        c = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return c;
#endif
    }
};
