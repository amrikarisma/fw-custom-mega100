#include "pch.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}

// board-specific configuration setup
void setBoardDefaultConfiguration() {


	engineConfiguration->triggerInputPins[0] = Gpio::D3;
	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;
	// engineConfiguration->injectionPins[0] = Gpio::B15;
	// engineConfiguration->injectionPins[1] = Gpio::B14;
	// engineConfiguration->injectionPins[2] = Gpio::B12;
	// engineConfiguration->injectionPins[3] = Gpio::B13;

	// engineConfiguration->ignitionPins[0] = Gpio::E2;
	// engineConfiguration->ignitionPins[1] = Gpio::E3;
	// engineConfiguration->ignitionPins[2] = Gpio::C13;
	// engineConfiguration->ignitionPins[3] = Gpio::E7;

	// engineConfiguration->idle.solenoidPin = Gpio::D10;

	// engineConfiguration->tachOutputPin = Gpio::E8;
	// engineConfiguration->fuelPumpPin = Gpio::E11;
	// engineConfiguration->fanPin = Gpio::E9;
	// engineConfiguration->acRelayPin = Gpio::C7;
	// engineConfiguration->launchActivatePin = Gpio::B8;

	// // Analog Pin
	// engineConfiguration->map.sensor.hwChannel = EFI_ADC_3;
	// engineConfiguration->afr.hwChannel = EFI_ADC_8;
	// engineConfiguration->vbattAdcChannel = EFI_ADC_4;
	// engineConfiguration->tps1_1AdcChannel = EFI_ADC_2;
	// engineConfiguration->clt.adcChannel = EFI_ADC_1;
	// engineConfiguration->iat.adcChannel = EFI_ADC_0;
	// engineConfiguration->acSwitch = Gpio::C5;


	// engineConfiguration->injectionPins[0] = Gpio::F13;
	// engineConfiguration->ignitionPins[0] = Gpio::E15;
	//	engineConfiguration->map.sensor.hwChannel = EFI_ADC_3;

//	engineConfiguration->clt.adcChannel = EFI_ADC_1;

//	engineConfiguration->iat.adcChannel = EFI_ADC_2;


    	// 5.6k high side/10k low side = 1.56 ratio divider
    	engineConfiguration->analogInputDividerCoefficient = 1.47f;

    	// 6.34k high side/ 1k low side
//    	engineConfiguration->vbattDividerCoeff = (6.34 + 1) / 1;

	engineConfiguration->adcVcc = 3.3f;

//	engineConfiguration->clt.config.bias_resistor = 2490;
//	engineConfiguration->iat.config.bias_resistor = 2490;


	// Battery sense on PA0
//	engineConfiguration->vbattAdcChannel = EFI_ADC_0;
}
