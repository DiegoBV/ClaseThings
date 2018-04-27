#pragma once
#include <Windows.h>
#include <XInput.h>
#include "BaseHID.h"

struct CONTROLER_STATE {
	XINPUT_STATE State;
	XINPUT_STATE OffState;
	DWORD dwResult;
	XINPUT_VIBRATION vibration;
};
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the +/- 32767 range.   This is a reasonable default value but can be altered if needed.
class HIDXBox : public BaseHID
{
private:
	CONTROLER_STATE XBox;
public:
	HIDXBox() {};
	~HIDXBox() {};
	HIDXBox(float t) :BaseHID(t) {};
	bool LeeMando();
	void EscribeMando();
	void update();
	void Mando2HID();
};

