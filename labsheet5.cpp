// Name  Abhishke kumar
// ROLLNO 2301010322
// SUBJECT DATASTRUCTURE 


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cassert>

class TextEditor {
private:
    std::vector<char> text; // To store the characters
    std::stack<std::string> undoStack; // For undo operations
    std::stack<std::string> redoStack; // For redo operations
    std::queue<std::string> clipboard; // For clipboard management

    std::string getTextAsString() {
        return std::string(text.begin(), text.end());
    }

    void setTextFromString(const std::string& str) {
        text.assign(str.begin(), str.end());
    }

public:
    void insertText(int position, const std::string& newText) {
        undoStack.push(getTextAsString()); // Save current state
        while (!redoStack.empty()) redoStack.pop(); // Clear redo stack

        text.insert(text.begin() + position, newText.begin(), newText.end());
    }

    void deleteText(int position, int length) {
        undoStack.push(getTextAsString()); // Save current state
        while (!redoStack.empty()) redoStack.pop(); // Clear redo stack

        text.erase(text.begin() + position, text.begin() + position + length);
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(getTextAsString()); // Save current state to redo
            setTextFromString(undoStack.top()); // Revert to last state
            undoStack.pop();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(getTextAsString()); // Save current state to undo
            setTextFromString(redoStack.top()); // Reapply last undone state
            redoStack.pop();
        }
    }

    void copy(int position, int length) {
        std::string copiedText(text.begin() + position, text.begin() + position + length);
        clipboard.push(copiedText);
    }

    void paste(int position) {
        if (!clipboard.empty()) {
            std::string pastedText = clipboard.back(); // Get the most recent copied text
            insertText(position, pastedText);
        }
    }

    std::string getText() {
        return getTextAsString();
    }
};

// Example Test Cases
int main() {
    TextEditor editor;

    // Insert Text
    editor.insertText(0, "Hello");
    assert(editor.getText() == "Hello");

    // Delete Text
    editor.deleteText(0, 2);
    assert(editor.getText() == "llo");

    // Undo
    editor.undo();
    assert(editor.getText() == "Hello");

    // Redo
    editor.redo();
    assert(editor.getText() == "llo");

    // Copy-Paste
    editor.insertText(0, "Hello");
    editor.copy(0, 2);
    editor.paste(5);
    assert(editor.getText() == "HelloHe");

    std::cout << "All test cases passed." << std::endl;

    return 0;
}



