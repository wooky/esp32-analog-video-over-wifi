#pragma once

#include "controller/decoder_controller.hpp"

class DecoderInterface
{
public:
    DecoderInterface(const UserSettings& settings)
    : _controller(settings)
    {}

    inline void setup()
    {
        _controller.setup();
    }

private:
    DecoderController _controller;
};
