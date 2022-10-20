#pragma once

class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual auto update(double dt) -> void = 0;
    virtual auto draw(double dt) -> void = 0;
protected:
};