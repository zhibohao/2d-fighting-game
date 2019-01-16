#pragma once
class PlayerState
{
public:
	PlayerState(int state);
	~PlayerState();

private:
	int m_numberFrame;
	bool m_control;
	int m_wait;
	int m_duration[20];

public:
	void SetNumberFrame(int numberFrame) { m_numberFrame = numberFrame; };
	void SetWait(int wait) { m_wait = wait; };
	void SetDuration(int duration[20]);
	void SetControl(bool control) { m_control = control; };

	int GetNumberFrame() { return m_numberFrame; };
	bool GetControl() { return m_control; };
	int GetDuration(int currentFrame) { return m_duration[currentFrame]; };
	int GetWait() { return m_wait; };
};

