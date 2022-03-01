#include "pch.h"
#include "SendBuffer.h"

SendBuffer::SendBuffer(int32 buffserSize)
{
	_buffer.resize(buffserSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* data, int32 len)
{
	ASSERT_CRASH(Capacity() >= len);
	::memcpy(_buffer.data(), data, len);
	_writeSize = len;
}

SendBufferChunk::SendBufferChunk()
{
}

SendBufferChunk::~SendBufferChunk()
{
}

void SendBufferChunk::Reset()
{
	_open = false;
	_usedSize = 0;
}

SendBufferRef SendBufferChunk::Open(uint32 allocSize)
{
	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK_SIZE);
	ASSERT_CRASH(_open == false);

	if (allocSize > FreeSize())
		return nullptr;

	_open = true;
	return ObjectPool<SendBuffer>::MakeShared(shared_from_this(), Buffer(), allocSize);
}

void SendBufferChunk::Close(uint32 writeSize)
{
}


SendBufferChunkRef SendBufferManager::Open(uint32 size)
{
	if (LSendBufferChunk == nullptr)
		LSendBufferChunk = Pop(); // WRITE_LOCK

	ASSERT_CRASH(LSendBufferChunk->IsOpen() == false);

	// 다 썼으면 버리고 새거로 교체
	if (LSendBufferChunk->FreeSize() < size)
	{
		LSendBufferChunk = Pop();	// WRITE_LOCK
		LSendBufferChunk->Reset();
	}

	return LSendBufferChunk->Open(size);
}

SendBufferChunkRef SendBufferManager::Pop()
{
	WRITE_LOCK;
	if(_sendBufferChunks.emplace() == false)
	{
		SendBufferChunkRef sendBufferChunk = _sendBufferChunks.back();
		_sendBufferChunks.pop_back();

	}
	return SendBufferChunkRef(xnew<SendBufferChunk>(), PushGlobal);
}

void SendBufferManager::Push(SendBufferChunkRef buffer)
{
	WRITE_LOCK;
	_sendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* buffer)
{
	GSendBufferManager->Push(SendBufferChunkRef(buffer, PushGlobal));
}