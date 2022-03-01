#pragma once
class SendBuffer
{
public:
	SendBuffer(int32 buffserSize);
	~SendBuffer();

	BYTE*	Buffer() { return _buffer.data(); }
	int32	WriteSize() { return _writeSize; }
	int32	Capacity() { return static_cast<int32>(_buffer.size()); }

	void CopyData(void* data, int32 len);
private:
	vector<BYTE>	_buffer;
	int32			_writeSize = 0;
};

class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
	enum
	{
		SEND_BUFFER_CHUNK_SIZE = 0x1000
	};
public:
	SendBufferChunk();
	~SendBufferChunk();

	void Reset();
	SendBufferRef Open(uint32 allocSize);
	void Close(uint32 writeSize);
	bool IsOpen() { return _open; }
	BYTE* Buffer() { return &_buffer[_usedSize]; }
	uint32	FreeSize() { return static_cast<uint32>(_buffer.size()) - _usedSize; }

private:
	array<BYTE, SEND_BUFFER_CHUNK_SIZE>	_buffer = {};
	bool _open = false;
	uint32 _usedSize = 0;
};

class SendBufferManager
{
public:
	SendBufferChunkRef	Open(uint32 size);

private:
	SendBufferChunkRef	Pop();
	void				Push(SendBufferChunkRef buffer);

	static void			PushGlobal(SendBufferChunk* buffer);
private:
	USE_LOCK;
	vector<SendBufferChunkRef>	_sendBufferChunks;
};