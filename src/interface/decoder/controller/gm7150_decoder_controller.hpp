#pragma once

#include "decoder_controller.hpp"

class DecoderController : public BaseDecoderController
{
public:
    DecoderController(const UserSettings& settings)
    : BaseDecoderController(settings)
    {}

    void setup() override
    {
        // TODO:
        // 0x03 enable output ???
        // 0x0D Set mode to BT.601
        // 0x0F Set clock to pixel clock ??? -> probably not
    }
};
