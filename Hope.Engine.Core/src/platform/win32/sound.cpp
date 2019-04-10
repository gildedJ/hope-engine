#include "sound.h"


SoundSystem::SoundSystem()
{
	m_DirectSound = NULL;
	m_PrimaryBuffer = NULL;
	m_SecondaryBuffer1 = NULL;
}

SoundSystem::SoundSystem(const SoundSystem& other)
{

}

SoundSystem::~SoundSystem()
{

}


bool SoundSystem::Initialize(HWND window)
{
	bool result = InitializeDirectSound(window);
	if (!result) return false;

	//char *testWaveFile = (char*)"data/air_raid.wav";
	//result = LoadWaveFile(testWaveFile, &m_SecondaryBuffer1);
	//if (!result) return false;

	//result = PlayWaveFile();
	//if (!result) return false;

	return true;
}


void SoundSystem::Shutdown()
{
	ShutdownWaveFile(&m_SecondaryBuffer1);
	ShutdownDirectSound();
}

bool SoundSystem::InitializeDirectSound(HWND window)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_DirectSound, NULL))) return false;
	if (FAILED(m_DirectSound->SetCooperativeLevel(window, DSSCL_PRIORITY))) return false;

	DSBUFFERDESC bufferDesc = {};
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	if (FAILED(m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_PrimaryBuffer, NULL))) return false;

	WAVEFORMATEX waveFormat = {};
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	if (FAILED(m_PrimaryBuffer->SetFormat(&waveFormat))) return false;

	return true;
}

void SoundSystem::ShutdownDirectSound()
{
	if (m_PrimaryBuffer)
	{
		m_PrimaryBuffer->Release();
		m_PrimaryBuffer = NULL;
	}

	if (m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = NULL;
	}
}

bool SoundSystem::LoadWaveFile(char *filename, IDirectSoundBuffer8** secondaryBuffer)
{
	FILE* filePtr;
	int error = fopen_s(&filePtr, filename, "rb");
	if (error != 0) return false;

	WaveHeaderType waveFileHeader;
	size_t count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1) return false;

	if ((waveFileHeader.chunkId[0] != 'R')
		|| (waveFileHeader.chunkId[1] != 'I')
		|| (waveFileHeader.chunkId[2] != 'F')
		|| (waveFileHeader.chunkId[3] != 'F'))
		return false;
	if ((waveFileHeader.format[0] != 'W')
		|| (waveFileHeader.format[1] != 'A')
		|| (waveFileHeader.format[2] != 'V')
		|| (waveFileHeader.format[3] != 'E'))
		return false;

	if ((waveFileHeader.subChunkId[0] != 'f')
		|| (waveFileHeader.subChunkId[1] != 'm')
		|| (waveFileHeader.subChunkId[2] != 't')
		|| (waveFileHeader.subChunkId[3] != ' '))
		return false;

	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
		return false;

	WAVEFORMATEX waveFormat = {};
	waveFormat.wFormatTag = waveFileHeader.audioFormat;
	waveFormat.nSamplesPerSec = waveFileHeader.sampleRate;
	waveFormat.wBitsPerSample = waveFileHeader.bitsPerSample;
	waveFormat.nChannels = waveFileHeader.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	DSBUFFERDESC bufferDesc;
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer* tempBuffer;
	if (FAILED(m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL)))
		return false;

	if (FAILED(tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer)))
		return false;
	tempBuffer->Release();
	tempBuffer = NULL;

	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	unsigned char* waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData) return false;

	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize) return false;

	if (fclose(filePtr) != 0) return false;

	unsigned char *bufferPtr;
	unsigned long bufferSize;
	if (FAILED((*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0)))
		return false;

	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	if (FAILED((*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0)))
		return false;
	
	delete[] waveData;
	waveData = NULL;

	return true;
}

void SoundSystem::ShutdownWaveFile(IDirectSoundBuffer8** secondaryBuffer)
{
	if (*secondaryBuffer)
	{
		(*secondaryBuffer)->Release();
		*secondaryBuffer = NULL;
	}
}


bool SoundSystem::PlayWaveFile()
{
	if (FAILED(m_SecondaryBuffer1->SetCurrentPosition(0)))
		return false;

	if (FAILED(m_SecondaryBuffer1->SetVolume(DSBVOLUME_MAX)))
		return false;

	if (FAILED(m_SecondaryBuffer1->Play(0, 0, 0)))
		return false;

	return true;
}