#include "framework.h"
#include "Action.h"

Action::Action(vector<Clip> clips, Type type, float speed)
	:_clips(clips)
	,_repeatType(type)
	, _speed(speed)
{
}

Action::~Action()
{
}

void Action::Update()
{
	if (!_isPlay)
		return;

	_time += DELTA_TIME;

	if (_time > _speed)
	{
		_time = 0.0f;

		switch (_repeatType)
		{
		case Action::END:
		{
			_curClipNum++;
			if (_curClipNum >= _clips.size())
				Stop();
		}
		break;
		case Action::LOOP:
		{
			_curClipNum++;
			if (_curClipNum >= _clips.size())
				_curClipNum %= _clips.size();
		}
		break;
		case Action::PINPONG:
		{
			if (_isReverse)
			{
				_curClipNum--;
				if (_curClipNum <= 0)
					_isReverse = true;
			}
			else
			{
				_curClipNum++;
				if (_curClipNum >= _clips.size() - 1)
					_isReverse = false;
			}
		}
		break;
		default:
			break;
		}
	}
}

void Action::Play()
{
	_isPlay = true;
	_isReverse = false;
	_curClipNum = 0;
	_time = 0.0f;
}

void Action::Pause()
{
	_isPlay = false;
}

void Action::Stop()
{
	_isPlay = false;
	_curClipNum = 0;
	if (_endEvent)
		_endEvent();
	
}
