// src/compiler.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "include/parser.h"

using namespace std;

// Forward declarations for validation and code generation
bool validate_app(const App& app);
bool generate_cpp(const App& app, const string& output_filename);

int main(int argc, char* argv[]) {
    cout << "Pulse Compiler v1.0" << endl;

    if (argc < 3) {
        cerr << "Usage: pulse <source_file.pls> <output_file.cpp>" << endl;
        return 1;
    }

    string source_file = argv[1];
    string output_file = argv[2];
    Parser parser;

    // Parse the source file
    parser.parse_file(source_file);

    // Display parsed App details (for debugging)
    parser.display_app();

    // Validate the parsed App
    if (!validate_app(parser.get_app())) {
        cerr << "Compilation failed due to semantic errors." << endl;
        return 1;
    }

    // Generate C++ code
    if (!generate_cpp(parser.get_app(), output_file)) {
        cerr << "Error: Code generation failed." << endl;
        return 1;
    }

    cout << "Compilation successful! Generated " << output_file << endl;

    return 0;
}

bool generate_cpp(const App& app, const string& output_filename) {
    ofstream out(output_filename);
    if (!out.is_open()) {
        error(0, "Unable to create output file.", "Check if you have write permissions.");
        return false;
    }

    // Write headers
    out << "#include <iostream>\n";
    out << "#include <string>\n";
    out << "#include <thread>\n";
    out << "#include <chrono>\n\n";
    out << "using namespace std;\n\n";

    // Write functions
    for (const auto& fn : app.functions) {
        out << "void " << fn.name << "() {\n";
        for (const auto& lbl : fn.labels) {
            out << "    // Label: " << lbl.name << "\n";
            out << "    cout << \"" << lbl.text << "\" << endl;\n";
            out << "    // Position: " << lbl.position.first << ", " << lbl.position.second << "\n";
            out << "    // Size: " << lbl.size << "\n";
            if (lbl.text.find("time") != string::npos) {
                // Extract time value
                regex time_regex(R"(time\s*:\s*(\d+)s;)");
                smatch matches;
                if (regex_search(lbl.text, matches, time_regex)) {
                    if (matches.size() == 2) {
                        int seconds = stoi(matches[1]);
                        out << "    this_thread::sleep_for(chrono::seconds(" << seconds << "));\n";
                        out << "    // Automatically remove label after " << seconds << " seconds.\n";
                    }
                }
            }
            out << "\n";
        }
        out << "}\n\n";
    }

    // Write main function
    out << "int main() {\n";
    out << "    // App Initialization\n";
    out << "    string app_name = \"" << app.init.name << "\";\n";
    out << "    char app_logo = '" << app.init.logo << "';\n\n";

    // Initialize labels
    for (const auto& lbl : app.labels) {
        out << "    // Label: " << lbl.name << "\n";
        out << "    string " << lbl.name << "_text = \"" << lbl.text << "\";\n";
        out << "    int " << lbl.name << "_size = " << lbl.size << ";\n";
        out << "    string " << lbl.name << "_position_x = \"" << lbl.position.first << "\";\n";
        out << "    int " << lbl.name << "_position_y = " << lbl.position.second << ";\n\n";
    }

    // Initialize buttons
    for (const auto& btn : app.buttons) {
        out << "    // Button: " << btn.name << "\n";
        out << "    string " << btn.name << "_text = \"" << btn.text << "\";\n";
        out << "    pair<int, int> " << btn.name << "_size = {" << btn.size.first << ", " << btn.size.second << "};\n";
        out << "    pair<string, int> " << btn.name << "_position = {\"" << btn.position.first << "\", " << btn.position.second << "};\n";
        out << "    // Function: " << btn.function << "\n\n";
    }

    // Display App Information
    out << "    // Display App Information\n";
    out << "    cout << \"App Name: \" << app_name << endl;\n";
    out << "    cout << \"App Logo: \" << app_logo << endl;\n\n";

    // Simulate button click
    for (const auto& btn : app.buttons) {
        out << "    // Simulating button '" << btn.name << "' click\n";
        out << "    cout << \"" << btn.name << " clicked!\" << endl;\n";
        out << "    " << btn.function << "();\n\n";
    }

    out << "    return 0;\n";
    out << "}\n";

    out.close();
    return true;
}
