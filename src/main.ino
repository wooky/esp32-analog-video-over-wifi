#include "usersettings.hpp"

UserSettings settings {
#include "settings.h"
};

#include "interface/decoder/decoder_interface.hpp"
#include "interface/wifi_interface.hpp"

WifiInterface wifi(settings);
DecoderInterface decoder(settings);

void setup() {
  wifi.start();
  decoder.setup();
}

void loop() {
  // put your main code here, to run repeatedly:

}
