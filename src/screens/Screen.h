#pragma once

class Screen {
public:
    virtual ~Screen() = default;

    virtual void begin() = 0;
    virtual void update() = 0;
};