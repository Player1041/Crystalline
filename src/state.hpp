#pragma once

class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual auto update(double dt) -> void = 0;
    virtual auto draw(double dt) -> void = 0;
protected:
};

namespace StateManagement {
    static std::vector<std::shared_ptr<State>> stateStack;
    inline auto set_state(std::shared_ptr<State> state) {
        stateStack.clear();
        stateStack.push_back(state);
        stateStack.shrink_to_fit();
    }
} // StateManagement