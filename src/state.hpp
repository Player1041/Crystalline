#pragma once

/**
 * @brief This is the base class for a game state
 * Game States have update() and draw() methods
 * Game States are initialized in the constructor
 * Game States are cleaned up in the destructor
 * Prefer using std::shared_ptr<> or std::unique_ptr<> to cleanup
 *
 */
class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual auto update(double dt) -> void = 0;
    virtual auto draw(double dt) -> void = 0;
protected:
};

/**
 * @brief A simple state management namespace
 * All you need to do is set_state(new_state);
 * 
 */
namespace StateManagement {
    static std::vector<std::shared_ptr<State>> stateStack;
    inline auto set_state(std::shared_ptr<State> state) {
        stateStack.clear();
        stateStack.push_back(state);
        stateStack.shrink_to_fit();
    }
} // StateManagement