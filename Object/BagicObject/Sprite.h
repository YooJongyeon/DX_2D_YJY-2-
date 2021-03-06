#pragma once

class Sprite :public Quad
{
public:
	Sprite(wstring file, Vector2 maxFrame = Vector2{ 1,1 });
	~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateData() override;
	
	Vector2 GetHalfFrameSize();
	shared_ptr<FrameBuffer> GetFrameBuffer() { return _frameBuffer; }
	void SetFrameBuffer(int x, int y) { _frameBuffer->data.curFrame = { (float)x,(float)y }; }
private:
	Vector2 _maxFrame;
	shared_ptr<FrameBuffer> _frameBuffer;


		
};

