#include <iostream>
#include <memory>
#include <stack>
#include <string>

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Receiver
class MusicSystem {
public:
    void play() {
        std::cout << "Music playing\n";
    }

    void pause() {
        std::cout << "Music paused\n";
    }
};

// Concrete Command
class PlayCommand : public Command {
    MusicSystem& music;
public:
    explicit PlayCommand(MusicSystem& m) : music(m) {}

    void execute() override {
        std::cout << "[LOG] Executing PlayCommand\n";
        music.play();
    }

    void undo() override {
        std::cout << "[LOG] Undo PlayCommand\n";
        music.pause();
    }
};

class PauseCommand : public Command {
    MusicSystem& music;
public:
    explicit PauseCommand(MusicSystem& m) : music(m) {}

    void execute() override {
        std::cout << "[LOG] Executing PauseCommand\n";
        music.pause();
    }

    void undo() override {
        std::cout << "[LOG] Undo PauseCommand\n";
        music.play();
    }
};

// Invoker with undo/redo
class Remote {
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

public:
    void press(std::unique_ptr<Command> cmd) {
        cmd->execute();
        undoStack.push(std::move(cmd));
        while (!redoStack.empty()) redoStack.pop(); // clear redo history
    }

    void undo() {
        if (undoStack.empty()) {
            std::cout << "Nothing to undo\n";
            return;
        }
        auto cmd = std::move(undoStack.top());
        undoStack.pop();
        cmd->undo();
        redoStack.push(std::move(cmd));
    }

    void redo() {
        if (redoStack.empty()) {
            std::cout << "Nothing to redo\n";
            return;
        }
        auto cmd = std::move(redoStack.top());
        redoStack.pop();
        cmd->execute();
        undoStack.push(std::move(cmd));
    }
};

int main() {
    MusicSystem music;
    Remote remote;

    remote.press(std::make_unique<PlayCommand>(music));
    remote.undo();
    remote.redo();

    remote.press(std::make_unique<PauseCommand>(music));
    remote.undo();
    remote.redo();
}
