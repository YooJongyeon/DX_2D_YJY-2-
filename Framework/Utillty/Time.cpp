#include "framework.h"
#include "Time.h"

Time* Time::_instacne = nullptr;

Time::Time()
{

	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);
	
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

	_timeScale = 1.0f / (double)_periodFrequency;

}

Time::~Time()
{
}

void Time::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	_timeTickElased = (double)(_curTime - _lastTime) * _timeScale;
	if (_lockFPS != 0)
	{
		double temp = (1.0 / _lockFPS);
		while (_timeTickElased < temp)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_timeTickElased = (double)(_curTime - _lastTime) * _timeScale;
		}
	}
	// �� ������Ʈ�� ���İ� ���� ������ Ƚ��
	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _timeTickElased;
	_runTime += _timeTickElased;

	//1�ʸ��� �����ؾ� �Ǵ� ����
	if (_oneSecCount >= 1.0)
	{
		_frameRate = _frameCount;
		_oneSecCount = 0;
		_frameCount = 0;
	}
}
