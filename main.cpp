
#include <iostream>
#include <string>
#include <filesystem>
#include "fancyprint.h"

using namespace std;
using namespace std::filesystem;

int main(int argc, char* argv[])
{
    FancyPrint fp;
    string pathStr;
    string HfilenameFP = "fancyprint.h";
    string HfilenameTS = "typesuite.h";

    fp.Print_delimiter("FancyPrint + TypeSuite Installer");
    fp.Print_info("This installer will copy the FancyPrint and TypeSuite header files to your project directory.", false);

    pathStr = fp.Print_input("Please enter the full path to your project directory (e.g., C:\\Users\\YourName\\Documents\\MyProject)");
    cout << "Thank you. Headers will be copied to " << pathStr << endl;

    // --- Selection Menu ---
    string options[] = {
        "Install FancyPrint only",
        "Install TypesSuite only",
        "Install both FancyPrint and TypesSuite"
    };
    int choice = fp.Print_selection(options, 3);

    path projectPath(pathStr);
    path targetParent = projectPath; // parent path for headers

    try
    {
        // Locate project root dynamically
        path exePath = absolute(argv[0]).parent_path();

        auto findRoot = [&](const string& filename) -> path {
            path current = exePath;
            while (!current.empty()) {
                if (exists(current / filename)) return current;
                current = current.parent_path();
            }
            throw runtime_error("Could not locate " + filename);
            };

        path sourceFileFP, sourceFileTS;
        if (choice == 1 || choice == 3)
            sourceFileFP = findRoot(HfilenameFP) / HfilenameFP;
        if (choice == 2 || choice == 3)
            sourceFileTS = findRoot(HfilenameTS) / HfilenameTS;

        fp.Print_info("Copying files...", false);
        fp.Print_loading(5, 200, '=');

        create_directories(targetParent);

        if (choice == 1 || choice == 3)
            copy_file(sourceFileFP, projectPath / HfilenameFP, copy_options::overwrite_existing);
        if (choice == 2 || choice == 3)
            copy_file(sourceFileTS, projectPath / HfilenameTS, copy_options::overwrite_existing);

        fp.Print_success("Installation completed successfully to " + projectPath.string(), false);
    }
    catch (exception& e)
    {
        fp.Print_error("An error occurred while copying the headers. Ensure the paths are correct and you have permissions.", false);
        cout << e.what() << endl;
    }

    return 0;
}
