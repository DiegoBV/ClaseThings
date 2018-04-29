#include "HIDXbox.h"

bool HIDXBox::LeeMando()
{
	XBox.dwResult = XInputGetState(0, &XBox.State); //estado del mando

	if (XBox.dwResult == ERROR_SUCCESS) {
		return true;
	}
	else {
		return false;
	}
}

void HIDXBox::EscribeMando()
{
	XBox.vibration.wLeftMotorSpeed = (WORD)(fLeftVibration * MAXUINT16);
	XBox.vibration.wRightMotorSpeed = (WORD)(fRightVibration * MAXUINT16);
	XInputSetState(0, &XBox.vibration);
}

void HIDXBox::Mando2HID()
{
	wButtons = XBox.State.Gamepad.wButtons;
	fLeftTrigger = (float)XBox.State.Gamepad.bLeftTrigger / (float)MAXBYTE;
	fRightTrigger = (float)XBox.State.Gamepad.bRightTrigger / (float)MAXBYTE;
	
	//deadZone
	if (XBox.State.Gamepad.sThumbLX > INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbLX -= INPUT_DEADZONE;
	}
	else if (XBox.State.Gamepad.sThumbLX < -INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbLX += INPUT_DEADZONE;
	}
	else {
		XBox.State.Gamepad.sThumbLX = 0;
	}

	if (XBox.State.Gamepad.sThumbLY > INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbLY -= INPUT_DEADZONE;
	}
	else if (XBox.State.Gamepad.sThumbLY < -INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbLY += INPUT_DEADZONE;
	}
	else {
		XBox.State.Gamepad.sThumbLY = 0;
	}

	if (XBox.State.Gamepad.sThumbRX > INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbRX -= INPUT_DEADZONE;
	}
	else if (XBox.State.Gamepad.sThumbRX < -INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbRX += INPUT_DEADZONE;
	}
	else {
		XBox.State.Gamepad.sThumbRX = 0;
	}

	if (XBox.State.Gamepad.sThumbRY > INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbRY -= INPUT_DEADZONE;
	}
	else if (XBox.State.Gamepad.sThumbRY < -INPUT_DEADZONE) {
		XBox.State.Gamepad.sThumbRY += INPUT_DEADZONE;
	}
	else {
		XBox.State.Gamepad.sThumbRY = 0;
	}

	float aux1 = (float)XBox.State.Gamepad.sThumbLX;
	float aux2 = (float)MAXUINT16 - INPUT_DEADZONE;
	float res = aux1 / aux2;
	fThumbLX = res;

	aux1 = (float)XBox.State.Gamepad.sThumbLY;
	res = aux1 / aux2;
	fThumbLY = res;

	aux1 = (float)XBox.State.Gamepad.sThumbRX;
	res = aux1 / aux2;
	fThumbRX = res;

	aux1 = (float)XBox.State.Gamepad.sThumbRY;
	res = aux1 / aux2;
	fThumbRY = res;
}

void HIDXBox::update() {
	if (LeeMando()) {
		XBox.OffState = XBox.State;
	}
}
