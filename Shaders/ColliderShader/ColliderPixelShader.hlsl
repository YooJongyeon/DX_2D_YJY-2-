cbuffer Color :register(b0)
{
	float4 color;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	
};

// SV_TARGET : �׸� ��... �츮���״� �ĸ����
float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}