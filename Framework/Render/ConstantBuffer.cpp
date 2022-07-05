#include "framework.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(void* data, UINT count)
	: _data(data)
	, _count(count)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	// D3D11_USAGE_DEFAULT : GPU���� �ϰ� ���� ����
	// D3D11_USAGE_IMMUTABLE :GPU���� �б⸸ ����
	// D3D11_USAGE_DYNAMIC :CPU ���� ���� ���� , GPU�б� ����
	// D3D11-USAGE- STAGING : GPU����  GPU�� �̵� (�б⸸ ����)
	bd.ByteWidth = count;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	DEVICE->CreateBuffer(&bd, nullptr, _buffer.GetAddressOf());
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Update()
{
	DEVICE_CONTEXT->Map(_buffer.Get(),0 , D3D11_MAP_WRITE_DISCARD, 0 , &_subResource);
	memcpy(_subResource.pData, _data, _count);
	DEVICE_CONTEXT->Unmap(_buffer.Get(), 0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
	DEVICE_CONTEXT->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
	Update();
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
	DEVICE_CONTEXT->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
	Update();
}
