// src/parser.cpp
#include "../include/parser.h"

void Parser::parse_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        error(0, "Unable to open file", "Check if the file path is correct.");
        return;
    }

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        current_line_num++;
        // Remove comments
        size_t comment_pos = line.find("//");
        if (comment_pos != string::npos) {
            line = line.substr(0, comment_pos);
        }
        // Trim whitespace
        line = regex_replace(line, regex("^\\s+|\\s+$"), "");
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    file.close();

    size_t current_line = 0;
    while (current_line < lines.size()) {
        string current = lines[current_line];
        if (current.find("App") != string::npos && current.find("{") != string::npos) {
            if (!parse_app_block(lines, current_line)) {
                error(current_line_num, "Failed to parse App block", "Ensure the App block is correctly defined.");
                return;
            }
        } else {
            error(current_line_num, "Unexpected token", "Expected 'App {' to start the application.");
            current_line++;
        }
    }
}

bool Parser::parse_app_block(const vector<string>& lines, size_t& current_line) {
    // Assumes current_line is at "App {"
    current_line++; // Move to next line after "App {"

    while (current_line < lines.size()) {
        string line = lines[current_line];
        current_line_num++;

        if (line.find("}") != string::npos) {
            current_line++;
            break;
        } else if (line.find("init") != string::npos && line.find("{") != string::npos) {
            if (!parse_init_block(lines, current_line)) {
                error(current_line_num, "Failed to parse init block", "Ensure the init block is correctly defined.");
                return false;
            }
        } else if (line.find("label") != string::npos && line.find("{") != string::npos) {
            Label label;
            if (!parse_label_block(lines, current_line, label)) {
                // Error reported within parse_label_block
                return false;
            }
            app.labels.push_back(label);
        } else if (line.find("button") != string::npos && line.find("{") != string::npos) {
            Button button;
            if (!parse_button_block(lines, current_line, button)) {
                // Error reported within parse_button_block
                return false;
            }
            app.buttons.push_back(button);
        } else if (line.find("fn") != string::npos && line.find("{") != string::npos) {
            Function function;
            if (!parse_function_block(lines, current_line, function)) {
                // Error reported within parse_function_block
                return false;
            }
            app.functions.push_back(function);
        } else {
            error(current_line_num, "Unknown block", "Unrecognized block type.");
            current_line++;
        }
    }

    return true;
}

bool Parser::parse_init_block(const vector<string>& lines, size_t& current_line) {
    // Assumes current_line is at "init {"
    current_line++; // Move to next line after "init {"

    while (current_line < lines.size()) {
        string line = lines[current_line];
        current_line_num++;

        if (line.find("}") != string::npos) {
            current_line++;
            break;
        }

        // Parse name
        regex name_regex(R"(name\s*:\s*\"([^"]+)\";)");
        smatch matches;
        if (regex_search(line, matches, name_regex)) {
            if (matches.size() == 2) {
                app.init.name = matches[1];
                current_line++;
                continue;
            }
        }

        // Parse logo
        regex logo_regex(R"(logo\s*:\s*\"([^"]+)\";)");
        if (regex_search(line, matches, logo_regex)) {
            if (matches.size() == 2) {
                app.init.logo = matches[1];
                current_line++;
                continue;
            }
        }

        // If line doesn't match any known init properties
        error(current_line_num, "Invalid init property", "Expected 'name' or 'logo' declarations.");
        current_line++;
    }

    return true;
}

bool Parser::parse_label_block(const vector<string>& lines, size_t& current_line, Label& label) {
    // Assumes current_line is at 'label <name> {'
    regex label_regex(R"(label\s+(\w+)\s*\{)");
    smatch matches;
    if (regex_search(lines[current_line], matches, label_regex)) {
        if (matches.size() == 2) {
            label.name = matches[1];
        } else {
            error(current_line_num, "Invalid label declaration", "Ensure label name is correctly specified.");
            return false;
        }
    } else {
        error(current_line_num, "Invalid label declaration", "Expected 'label <name> {'.");
        return false;
    }

    current_line++; // Move to next line after 'label <name> {'

    while (current_line < lines.size()) {
        string line = lines[current_line];
        current_line_num++;

        if (line.find("}") != string::npos) {
            current_line++;
            break;
        }

        // Parse text
        regex text_regex(R"(text\s*:\s*\"([^"]+)\";)");
        if (regex_search(line, matches, text_regex)) {
            if (matches.size() == 2) {
                label.text = matches[1];
                current_line++;
                continue;
            }
        }

        // Parse size
        regex size_regex(R"(size\s*:\s*(\d+);)");
        if (regex_search(line, matches, size_regex)) {
            if (matches.size() == 2) {
                label.size = stoi(matches[1]);
                current_line++;
                continue;
            }
        }

        // Parse position
        regex position_regex(R"(position\s*:\s*(\w+|\d+)\s*,\s*(\w+|\d+);)");
        if (regex_search(line, matches, position_regex)) {
            if (matches.size() == 3) {
                label.position = {matches[1], matches[2]};
                current_line++;
                continue;
            }
        }

        // If line doesn't match any known label properties
        error(current_line_num, "Invalid label property", "Expected 'text', 'size', or 'position' declarations.");
        current_line++;
    }

    return true;
}

bool Parser::parse_button_block(const vector<string>& lines, size_t& current_line, Button& button) {
    // Assumes current_line is at 'button <name> {'
    regex button_regex(R"(button\s+(\w+)\s*\{)");
    smatch matches;
    if (regex_search(lines[current_line], matches, button_regex)) {
        if (matches.size() == 2) {
            button.name = matches[1];
        } else {
            error(current_line_num, "Invalid button declaration", "Ensure button name is correctly specified.");
            return false;
        }
    } else {
        error(current_line_num, "Invalid button declaration", "Expected 'button <name> {'.");
        return false;
    }

    current_line++; // Move to next line after 'button <name> {'

    while (current_line < lines.size()) {
        string line = lines[current_line];
        current_line_num++;

        if (line.find("}") != string::npos) {
            current_line++;
            break;
        }

        // Parse text
        regex text_regex(R"(text\s*:\s*\"([^"]+)\";)");
        if (regex_search(line, matches, text_regex)) {
            if (matches.size() == 2) {
                button.text = matches[1];
                current_line++;
                continue;
            }
        }

        // Parse size
        regex size_regex(R"(size\s*:\s*(\d+)\s*,\s*(\d+);)");
        if (regex_search(line, matches, size_regex)) {
            if (matches.size() == 3) {
                button.size = {stoi(matches[1]), stoi(matches[2])};
                current_line++;
                continue;
            }
        }

        // Parse position
        regex position_regex(R"(position\s*:\s*(\w+|\d+)\s*,\s*(\w+|\d+);)");
        if (regex_search(line, matches, position_regex)) {
            if (matches.size() == 3) {
                button.position = {matches[1], stoi(matches[2])};
                current_line++;
                continue;
            }
        }

        // Parse function
        regex function_regex(R"(function\s*:\s*(\w+)\(\);)");
        if (regex_search(line, matches, function_regex)) {
            if (matches.size() == 2) {
                button.function = matches[1];
                current_line++;
                continue;
            }
        }

        // If line doesn't match any known button properties
        error(current_line_num, "Invalid button property", "Expected 'text', 'size', 'position', or 'function' declarations.");
        current_line++;
    }

    return true;
}

bool Parser::parse_function_block(const vector<string>& lines, size_t& current_line, Function& function) {
    // Assumes current_line is at 'fn <name> {'
    regex fn_regex(R"(fn\s+(\w+)\s*\{)");
    smatch matches;
    if (regex_search(lines[current_line], matches, fn_regex)) {
        if (matches.size() == 2) {
            function.name = matches[1];
        } else {
            error(current_line_num, "Invalid function declaration", "Ensure function name is correctly specified.");
            return false;
        }
    } else {
        error(current_line_num, "Invalid function declaration", "Expected 'fn <name> {'.");
        return false;
    }

    current_line++; // Move to next line after 'fn <name> {'

    while (current_line < lines.size()) {
        string line = lines[current_line];
        current_line_num++;

        if (line.find("}") != string::npos) {
            current_line++;
            break;
        }

        // Parse label within function
        if (line.find("label") != string::npos && line.find("{") != string::npos) {
            Label label;
            if (!parse_label_block(lines, current_line, label)) {
                // Error reported within parse_label_block
                return false;
            }
            function.labels.push_back(label);
        } else {
            error(current_line_num, "Unknown construct in function", "Only labels are supported within functions currently.");
            current_line++;
        }
    }

    return true;
}

void Parser::display_app() const {
    cout << "App Name: " << app.init.name << endl;
    cout << "App Logo: " << app.init.logo << endl;

    cout << "\nLabels:\n";
    for (const auto& lbl : app.labels) {
        cout << "  Name: " << lbl.name << "\n";
        cout << "    Text: " << lbl.text << "\n";
        cout << "    Size: " << lbl.size << "\n";
        cout << "    Position: " << lbl.position.first << ", " << lbl.position.second << "\n";
    }

    cout << "\nButtons:\n";
    for (const auto& btn : app.buttons) {
        cout << "  Name: " << btn.name << "\n";
        cout << "    Text: " << btn.text << "\n";
        cout << "    Size: " << btn.size.first << "x" << btn.size.second << "\n";
        cout << "    Position: " << btn.position.first << ", " << btn.position.second << "\n";
        cout << "    Function: " << btn.function << "\n";
    }

    cout << "\nFunctions:\n";
    for (const auto& fn : app.functions) {
        cout << "  Function Name: " << fn.name << "\n";
        for (const auto& lbl : fn.labels) {
            cout << "    Label:\n";
            cout << "      Text: " << lbl.text << "\n";
            cout << "      Position: " << lbl.position.first << ", " << lbl.position.second << "\n";
            cout << "      Size: " << lbl.size << "\n";
        }
    }
}

const App& Parser::get_app() const {
    return app;
}

bool validate_app(const App& app) {
    bool is_valid = true;
    // Validate logo length
    if (app.init.logo.length() != 1) {
        error(0, "Logo must be a single character.", "Provide a single character for the logo.");
        is_valid = false;
    }

    // Check for duplicate names
    set<string> names;
    // Check labels
    for (const auto& lbl : app.labels) {
        if (names.find(lbl.name) != names.end()) {
            error(0, "Duplicate label name '" + lbl.name + "'.", "Use unique names for each label.");
            is_valid = false;
        }
        names.insert(lbl.name);
    }
    // Check buttons
    for (const auto& btn : app.buttons) {
        if (names.find(btn.name) != names.end()) {
            error(0, "Duplicate button name '" + btn.name + "'.", "Use unique names for each button.");
            is_valid = false;
        }
        names.insert(btn.name);
    }
    // Check functions
    for (const auto& fn : app.functions) {
        if (names.find(fn.name) != names.end()) {
            error(0, "Duplicate function name '" + fn.name + "'.", "Use unique names for each function.");
            is_valid = false;
        }
        names.insert(fn.name);
    }

    // Check if functions used in buttons are defined
    set<string> function_names;
    for (const auto& fn : app.functions) {
        function_names.insert(fn.name);
    }
    for (const auto& btn : app.buttons) {
        if (function_names.find(btn.function) == function_names.end()) {
            error(0, "Function '" + btn.function + "' used in button '" + btn.name + "' is not defined.", "Define the function '" + btn.function + "'.");
            is_valid = false;
        }
    }

    return is_valid;
}
