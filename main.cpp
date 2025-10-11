
// Note: this code is used for testing purposes only.
// It may contain intentional errors or verry sketchy c++ practices i dont recomand.
// you have been warned.

#include "hsuite/cllama.h"
#include "hsuite/stb.h"

// Example chatbot with CLLama
int main() {
	string model = "smollm:135m"; // Change this to your desired model
	string user_input;
	while (true) {
		;
		FancyPrint::Print_custom("", "You");
		user_input = STB::getText();
		if (user_input == "exit" || user_input == "quit") {
			break;
		}
		CLLama::prompt(user_input, model);
	}
	return 0;
}