#pragma once
#include "stb.h"
#include "typesuite.h"
#include "fancyprint.h"
#include <string>

class CLLama {
public:
    // Static method to query a model
    static void prompt(const string prompt, const string model) {
        // Run the command via Cmd
		std::string command = "ollama run " + model + " " + prompt;

        std::string output = Cmd::run(command);

        // Print output with FancyPrint
        FancyPrint::Print_custom(output, "BOT");
    }
    static string promptReturnString(const string prompt, const string model) {
        // Run the command via Cmd
        std::string command = "ollama run " + model + " " + prompt;

        std::string output = Cmd::run(command);

        // Print output with FancyPrint
        return output;
    }
    static string listModels() {
		return Cmd::run("ollama list");
    }

    static string promptReturn(const string prompt, const string model) {
        return Cmd::run("ollama run " + model + " " + prompt);
    }

    static void installModel(const string model) {
        Cmd::run("ollama pull " + model);
	}
    static void removeModel(const string model) {
        Cmd::run("ollama rm " + model);
    }
		
};
