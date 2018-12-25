#pragma once

class CMouseSpy
{
private:
	std::thread m_th;
	std::atomic_uint64_t m_error;

public:	
	static CMouseSpy& GetInstance();

	BOOL Run(HINSTANCE);
	void Stop();

	CMouseSpy(const CMouseSpy&) = delete;
	CMouseSpy& operator=(const CMouseSpy&) = delete;

private:
	CMouseSpy() = default;
	~CMouseSpy() = default;

	void ThFunc(HINSTANCE);
	BOOL MessageLoop(HINSTANCE);
	
};