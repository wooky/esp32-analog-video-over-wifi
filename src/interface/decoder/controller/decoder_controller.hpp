#pragma once

#include "../../../usersettings.hpp"

class BaseDecoderController
{
protected:
    BaseDecoderController(const UserSettings& settings)
    : _settings(settings)
    {}

public:
    virtual void setup();

protected:
    const UserSettings& _settings;
};

#if DECODER_MODEL == GM7150 /* AKA SLES213 */
#include "gm7150_decoder_controller.hpp"
#else
#error Video decoder model is unknown or undefined
#endif
