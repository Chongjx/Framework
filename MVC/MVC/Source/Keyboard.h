#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
private:
	bool keys[256];
public:
	Keyboard(void);
	~Keyboard(void);

	void Init(void);
	bool SwitchKeyStatus(unsigned short key);
	bool setKeyStatus(unsigned short key, bool status);
	bool getKeyStatus(unsigned short key);
	bool IsKeyPressed(unsigned short key);
};

#endif