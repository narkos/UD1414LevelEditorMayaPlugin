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
struct TransformMessage
{

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
struct CameraMessage
{

};
struct MaterialData
{

};
struct MaterialInfo
{
	
};
struct MaterialMessage
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
struct LightMessage
{

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

	MessageHeader createHeaderTransform(MessageInfo& msginfo, TransformInfo &tInfo);
	MessageHeader createHeaderMesh(MessageInfo& msginfo, MeshInfo& minfo);
	MessageHeader createHeaderCamera(MessageInfo& msginfo, CameraInfo& cInfo);
	MessageHeader createHeaderMaterial(MessageInfo& msginfo, MaterialInfo& mInfo);
	MessageHeader createHeaderLight(MessageInfo& msginfo, LightInfo& lInfo);
	
	MeshMessage createMessageMesh(MessageInfo& msginfo, MeshInfo &mInfo);
	TransformMessage createMessageTransform(MessageInfo& msginfo, TransformInfo &tInfo);
	CameraMessage createMessageCamera(MessageInfo& msginfo, CameraInfo& cInfo);
	MaterialMessage createMessageMaterial(MessageInfo& msginfo, MaterialInfo& mInfo);
	LightMessage createMessageLight(MessageInfo& msgInfo, LightInfo& lInfo);
	size_t makeMultiple(size_t size, size_t multiple);
	bool tryWriteTransform(MessageInfo& msg, TransformInfo& tinfo);
	bool tryWriteMesh(MessageInfo& msg, MeshInfo& minfo);
	bool tryWriteCamera(MessageInfo& msg, CameraInfo& cinfo);
	bool tryWriteMaterial(MessageInfo& msg, MaterialInfo& minfo);
	bool tryWriteLight(MessageInfo& msg, LightInfo& linfo);

	int findWriteConfig(MessageHeader& hdr);
	
	bool writeTransform(MessageHeader& hdr, TransformMessage& tdata, int config);
	bool writeMesh(MessageHeader& hdr, MeshMessage& mdata, int config);
	bool writeCamera(MessageHeader& hdr, CameraMessage& cdata, int config);
	bool writeMaterial(MessageHeader& hdr, MaterialMessage& mdata, int config);
	bool writeLight(MessageHeader& hdr, LightMessage& ldata, int config);

	std::string GetLastErrorAsString();




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

	FilemapInfo fileMapInfo;
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
	
	//TransformMessage *transformMessage;
	//CameraMessage *cameraMessage;
	//MeshMessage *meshMessage;
	//MaterialMessage *materialMessage;
	//LightMessage *lightMessage;

};


#endif