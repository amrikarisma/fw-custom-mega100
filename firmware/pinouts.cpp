#include "pch.h"
#include "bench_test.h"
#include "flash_main.h"
#include "tunerstudio.h"

static void setBoard_04_pinout() {
	engineConfiguration->injectionPins[0] = Gpio::B15;
	engineConfiguration->injectionPins[1] = Gpio::B14;
	engineConfiguration->injectionPins[2] = Gpio::B12;
	engineConfiguration->injectionPins[3] = Gpio::B13;

	engineConfiguration->ignitionPins[0] = Gpio::E2;
	engineConfiguration->ignitionPins[1] = Gpio::E3;
	engineConfiguration->ignitionPins[2] = Gpio::C13;
	engineConfiguration->ignitionPins[3] = Gpio::E7;

	engineConfiguration->idle.solenoidPin = Gpio::D10;

	engineConfiguration->tachOutputPin = Gpio::E8;
	engineConfiguration->fuelPumpPin = Gpio::E11;
	engineConfiguration->fanPin = Gpio::E9;
	engineConfiguration->acRelayPin = Gpio::C7;
	engineConfiguration->launchActivatePin = Gpio::B8;

	// Analog Pin
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_3;
	engineConfiguration->afr.hwChannel = EFI_ADC_8;
	engineConfiguration->vbattAdcChannel = EFI_ADC_4;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_2;
	engineConfiguration->clt.adcChannel = EFI_ADC_1;
	engineConfiguration->iat.adcChannel = EFI_ADC_0;
	engineConfiguration->acSwitch = Gpio::C5;
}

static void setBoard_ua4c_pinout() {
	engineConfiguration->injectionPins[0] = Gpio::B15;
	engineConfiguration->injectionPins[1] = Gpio::D8;
	engineConfiguration->injectionPins[2] = Gpio::D9;
	engineConfiguration->injectionPins[3] = Gpio::D10;

	engineConfiguration->ignitionPins[0] = Gpio::E15;
	engineConfiguration->ignitionPins[1] = Gpio::E4;
	engineConfiguration->ignitionPins[2] = Gpio::D13;
	engineConfiguration->ignitionPins[3] = Gpio::E5;


	engineConfiguration->tachOutputPin = Gpio::C9;
	engineConfiguration->fuelPumpPin = Gpio::C8;
	engineConfiguration->fanPin = Gpio::A15;
	engineConfiguration->acRelayPin = Gpio::B7;
	engineConfiguration->launchActivatePin = Gpio::E14;

	// Analog Pin
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_0;
	engineConfiguration->afr.hwChannel = EFI_ADC_1;
	engineConfiguration->vbattAdcChannel = EFI_ADC_2;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_3;
	engineConfiguration->clt.adcChannel = EFI_ADC_4;
	engineConfiguration->iat.adcChannel = EFI_ADC_5;
	engineConfiguration->acSwitch = Gpio::B0;
}

/*PUBLIC_API_WEAK*/ void boardTsAction(uint16_t index) {
	if (index == 0) {
		setBoard_04_pinout();
	}
	else if (index == 1) {
		setBoard_ua4c_pinout();
	}
	writeToFlashNow();
	onApplyPreset();
}