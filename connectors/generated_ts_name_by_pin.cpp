//DO NOT EDIT MANUALLY, let automation work hard.

// auto-generated by PinoutLogic.java based on ../../../connectors/custom_firmware.yaml
#include "pch.h"

// see comments at declaration in pin_repository.h
const char * getBoardSpecificPinName(brain_pin_e brainPin) {
	switch(brainPin) {
		case Gpio::B14: return "B14 Output";
		case Gpio::E2: return "VR/Hall 1 (E2)";
		case Gpio::E3: return "VR/Hall 2 (E3)";
		case Gpio::E4: return "VR/Hall 3 (E4)";
		default: return nullptr;
	}
	return nullptr;
}
