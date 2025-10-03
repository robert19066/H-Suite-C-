
#include <iostream>
#include <filesystem>
#include "./hsuite/fancyprint.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    FancyPrint fp;

    fp.Print_delimiter("HSuite Installer");

    fp.Print_info("This installer will copy the 'hsuite' folder to your project directory.", false);

    // Ask for project path
    std::string pathStr = fp.Print_input("Please enter the full path to your project directory");
    fs::path targetPath(pathStr);

    fp.Print_info("Headers and libraries will be copied to: " + targetPath.string(), false);

    try {
        // Locate the source hsuite folder relative to executable
        fs::path exePath = fs::absolute(argv[0]).parent_path();
        fs::path sourceFolder = exePath.parent_path().parent_path().parent_path() / "hsuite"; // two levels up

        if (!fs::exists(sourceFolder) || !fs::is_directory(sourceFolder)) {
            throw std::runtime_error("Cannot locate 'hsuite' folder at: " + sourceFolder.string());
        }

        // Create target folder if it doesn't exist
        fs::create_directories(targetPath / "hsuite");

        fp.Print_info("Copying files...", false);
        fp.Print_loading(5, 150, '=');

        // Recursive copy of hsuite folder
        for (const auto& entry : fs::recursive_directory_iterator(sourceFolder)) {
            fs::path relativePath = fs::relative(entry.path(), sourceFolder);
            fs::path targetEntry = targetPath / "hsuite" / relativePath;

            if (fs::is_directory(entry)) {
                fs::create_directories(targetEntry);
            }
            else if (fs::is_regular_file(entry)) {
                fs::copy_file(entry.path(), targetEntry, fs::copy_options::overwrite_existing);
            }
        }

        fp.Print_success("Installation of 'hsuite' completed successfully to " + targetPath.string(), false);

        // Optional: open folder
        if (fp.Print_confirm("Do you want to open the project folder now?")) {
#ifdef _WIN32
            std::string cmd = "start \"\" \"" + targetPath.string() + "\"";
#else
            std::string cmd = "xdg-open \"" + targetPath.string() + "\""; // Linux
#endif
            std::system(cmd.c_str());
        }

    }
    catch (const std::exception& e) {
        fp.Print_error("An error occurred during installation.", false);
        fp.Print_error(e.what(), false);
        return 1;
    }

    return 0;
}
