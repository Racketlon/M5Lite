// include/parser.h
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include "error.h"

using namespace std;

// Structs to represent various constructs
struct Init {
    string name;
    string logo;
};

struct Label {
    string name;
    string text;
    int size;
    pair<string, string> position;
};

struct Button {
    string name;
    string text;
    pair<int, int> size; // width, height
    pair<string, int> position; // x, y
    string function;
};

struct Function {
    string name;
    // Additional properties can be added as needed
    // For simplicity, we'll assume functions contain labels
    vector<Label> labels;
};

struct App {
    Init init;
    vector<Label> labels;
    vector<Button> buttons;
    vector<Function> functions;
};

class Parser {
private:
    App app;
    int current_line_num; // To keep track of the current line number

    // Helper methods to parse different blocks
    bool parse_app_block(const vector<string>& lines, size_t& current_line);
    bool parse_init_block(const vector<string>& lines, size_t& current_line);
    bool parse_label_block(const vector<string>& lines, size_t& current_line, Label& label);
    bool parse_button_block(const vector<string>& lines, size_t& current_line, Button& button);
    bool parse_function_block(const vector<string>& lines, size_t& current_line, Function& function);

public:
    // Method to parse an entire file
    void parse_file(const string& filename);

    // Methods for validation and display
    void display_app() const;
    const App& get_app() const;
};

#endif
