#pragma once
#ifndef PLUGINSTRUCTS_HPP
#define PLUGINSTRUCTS_HPP
#include <string>


enum class MessageType
{
	msgAdded = 1,
	msgEdited = 2,
	msgDeleted = 3,
	msgRenamed = 4,
	msgSwitched = 5
};
enum class NodeType
{
	nDefaultNode = 0,
	nMesh = 1,
	nTransform = 2,
	nCamera = 3,
	nLight = 4,
	nMaterial = 5
};
enum class bitmask : int
{
	COLORMAP = 0x01,
	GLOWMAP = 0x02,
	SPECMAP = 0x04,
	BUMPMAP = 0x08
};

struct MessageHeader
{
	MessageHeader()
	{
		nodeType = 0;
		messageType = 0;
		msgConfig = 0;
		byteTotal = 0;
		byteSize = 0;
		bytePadding = 0;
	}
	int nodeType;
	int messageType;
	int msgConfig;
	size_t byteTotal;
	size_t byteSize;
	size_t bytePadding;
};
struct MessageInfo
{
	std::string nodeName;
	int nodeType;
	int msgType;
	std::string oldName;
};
struct RenameDeleteInfo
{
	std::string nodeName1;
	std::string nodeName2;
};
struct RenameDeleteMessage
{
	char nodeName1[100];
	char nodeName2[100];
};


struct TransformData
{
	float translation[3];
	float rotation[4];
	float scale[3];
};
struct TransformInfo
{
	std::string nodeName;
	std::string parentName; // om ingen parent sätt till 0 första bokstav fuck off.
	TransformData transformData;
};
struct TransformMessage
{
	char nodeName[100];
	char parentName[100];
	TransformData trData;
};
struct MeshData
{
	int vertCount;
	int normalCount;
	int UVCount;
	int indCount;
	int triCount;
	// int triCountTotal;
	const float* vertices;
	const float* normals;
	float2* uv;
	int* triIndices;
	int* norIndices;
	int* UVIndices;
	int* triPerFace;

	~MeshData()
	{
		// delete[] this->triPerFace;
	}
};
struct MeshInfo
{
	std::string nodeName;
	std::string transformName;
	std::string materialName;
	int meshID;
	int materialID;
	MeshData meshData;
};
struct MeshMessage
{
	char nodeName[100];
	char transformName[100];
	char materialName[100];
	int meshID;
	int materialID;
	MeshData meshData;
};
struct CameraData
{
	int isOrtho;
	float target[3];
	float upVector[3];
	float rightVector[3];
	float hAngle;
};
struct CameraInfo
{
	std::string nodeName;
	std::string transformName;
	CameraData camData;
};
struct CameraMessage
{
	char nodeName[100];
	char transformName[100];
	CameraData camData;
};
struct MaterialData
{
	MaterialData()
	{
		mapMasks = 0;
		diffuse = 0;
		color[0] = color[1] = color[2] = 0.0f;
		ambColor[0] = ambColor[1] = ambColor[2] = 0.0f;
		specColor[0] = specColor[1] = specColor[2] = 0.0f;
		specCosine = specEccentricity = specRollOff = 0;
	}
	int mapMasks;
	float diffuse;
	float color[3];
	float ambColor[3];
	float specColor[3];
	float specCosine;
	float specEccentricity;
	float specRollOff;
};
struct MaterialInfo
{
	std::string nodeName;
	std::string diffuseTexturePath;
	std::string glowTexturePath;
	std::string specTexturePath;
	std::string bumpTexturePath;
	int type;
	MaterialData matData;
};
struct MaterialMessage
{
	char nodeName[100];
	char diffuseTexturePath[100];
	char glowTexturePath[100];
	char specTexturePath[100];
	char bumpTexturePath[100];
	int type;
	MaterialData matData;
};
struct LightData
{
	LightData()
	{
		type = 0;
		decayType = 0;
		intensity = 0;
		colorDiffuse[0] = colorDiffuse[1] = colorDiffuse[2] = 0.5f;
		direction[0] = direction[1] = direction[2] = 0.0f;
		dropOff = 1.0f;
		coneAngle = 0.0f;
		penumAgle = 0.0f;
	}
	int type; // 0 = def, 1 = dir, 2 = spot, 3 = point
	int decayType; // 0 = none, 1 = linear, 2 = quadratic (l/d**v)
	float intensity;
	float colorDiffuse[3];
	float direction[3];
	float dropOff;
	float coneAngle;
	float penumAgle;
};
struct LightInfo
{
	std::string nodeName;
	std::string transformName;
	LightData lightData;
};
struct LightMessage
{
	char nodeName[100];
	char transformName[100];
	LightData lightData;
};



#endif