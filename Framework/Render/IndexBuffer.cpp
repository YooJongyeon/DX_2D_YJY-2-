#include "framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, UINT count)
{
    // Vertex 버퍼: Vertex
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(UINT) * count;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    // 정점 정보들을 담는 정점 버퍼
    DEVICE->CreateBuffer(&bd, &initData, _buffer.GetAddressOf());
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::IASet()
{
    DEVICE_CONTEXT->IASetIndexBuffer(_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}