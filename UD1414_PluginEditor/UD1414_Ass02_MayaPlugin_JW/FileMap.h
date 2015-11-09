#pragma once
#ifndef FILEMAP_H
#define FILEMAP_H

#include <Windows.h>
#include <ostream>
#include <iostream>

#include <maya/MGlobal.h>


enum MessageType { msgAdded = 1, msgEdited = 2, msgDeleted = 3, msgRenamed = 4 };
enum NodeType { nDefaultNode = 0, nMesh = 1, nTransform = 2, nCamera = 3, nLight = 4, nMaterial = 5 };


struct MessageHeader
{
	MessageHeader() {
	nodeType = 0;
	messageType = 0;
	byteSize = 0;
	bytePadding = 0;
}
int nodeType;
int messageType;
size_t byteSize;
size_t bytePadding;
};

struct MessageInfo
{
	std::string nodeName;
	int nodeType;
	int msgType;
};
struct TransformData
{
	float translation[3];
	float rotation[3];
	float scale[3];
};
struct TransformInfo
{
	std::string nodeName;
	std::string parentName;
	TransformData transformData;
	//
	//std::string parentName;
	//int childCount;
};

struct MeshData
{
	int vertCount;
	int normalCount;
	int UVCount;
	int indCount;
	int triCount;
	//int triCountTotal;
	const float* vertices;
	const float* normals;
	float2* uv;
	int* triIndices;
	int* norIndices;
	int* UVIndices;
	int* triPerFace;

	~MeshData() {
		//delete[] this->triPerFace;
	}
};
struct MeshInfo
{
	std::string nodeName;
	std::string transformName;
	MeshData meshData;
};

struct MeshMessage
{
	char nodeName[100];
	char transformName[100];
	MeshData *meshData;
};

struct CameraData
{

};
struct CameraInfo
{
	std::string nodeName;
	std::string transformName;
};
struct MaterialData
{

};
struct MaterialInfo
{
	
};
struct LightData
{

};
struct LightInfo
{
	std::string transformName;
	LightData lightData;
};

class Mutex {
private:
	HANDLE handle_;
public:
	Mutex(const char* name = "__my_mutex__")
	{
		handle_ = CreateMutex(nullptr, false, (LPWSTR)(name));
	}
	~Mutex()
	{
		ReleaseMutex(handle_);
	}
	void Create(const char* name = "__my_mutex__")
	{
		handle_ = CreateMutex(nullptr, false, (LPWSTR)(name));
	}
	void Lock(DWORD milliseconds = INFINITE)
	{
		WaitForSingleObject(handle_, milliseconds);
	}
	void Unlock()
	{
		ReleaseMutex(handle_);
	}
};

class FileMapping
{
public:
	FileMapping();
	~FileMapping();
	void CreateFileMaps();
	void SetFilemapInfoValues(size_t headPlacement, size_t tailPlacement, size_t nonAccessMemoryPlacement, size_t messageFileMapTotalSize);
	void GetFilemapInfoValues();

	MessageHeader createHeaderMesh(MessageInfo& msginfo, MeshInfo& minfo);
	MeshMessage createMessageMesh(MessageInfo& msginfo, MeshInfo &mInfo);
	size_t makeMultiple(size_t size, size_t multiple);
	bool tryWrite(MessageInfo& msg, MeshInfo& minfo);
	bool writeMesh(MessageHeader& hdr, MeshMessage& mdata, int config);
	int findWriteConfig(MessageHeader& hdr);


private:

	struct FilemapInfo {
		size_t head_ByteOffset; //offset in bytes from beginning of the shared memory
		size_t tail_ByteOffset; //offset in bytes from beginning of the shared memory
		size_t non_accessmemoryOffset; //memory in beginning of file thats no touchy, so that head and tail won't get to each other
									   //size_t totalConsumers;
		size_t messageFilemap_Size;

		FilemapInfo() {
			head_ByteOffset = 0;
			tail_ByteOffset = 0;
			non_accessmemoryOffset = 10;
			//totalConsumers = 0;
			messageFilemap_Size = 0; //storleken på filemapen med meddelanden
		}
	};

	FilemapInfo _fileMapInfo;
	HANDLE hMessageFileMap;
	LPVOID mMessageData;
	unsigned int mSize;
	HANDLE hInfoFileMap;
	LPVOID mInfoData;
	unsigned int mInfoSize = 256;
	size_t localHead = 0;
	size_t localTail = 0;
	Mutex mutexInfo;

	size_t memoryPadding;
	bool headerFit;
	size_t _headerSize;

	MessageHeader messageHeader;
	

					   //har kvar vissa av dessa structsen även om de är lite onödiga då alla värden i vissa redan ligger i en full struct, men vill hålla det cleant med namngivning :-)
	struct TransformMessage {
		char parentName[100];
		TransformData transformData;
	};
	struct CameraMessage {
		char transformName[100];
		CameraData cameraData;
	};
	
	struct MaterialMessage { //namnet på den ligger i headern sen
		MaterialData materialData;
	};
	struct LightMessage {
		//ljusvärden
		char transformName[100];
		LightData lightdata;
	};

	TransformMessage *transformMessage;
	CameraMessage *cameraMessage;
	MeshMessage *meshMessage;
	MaterialMessage *materialMessage;
	LightMessage *lightMessage;

};


#endif