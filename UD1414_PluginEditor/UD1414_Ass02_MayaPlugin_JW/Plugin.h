#pragma once

// some definitions for the DLL to play nice with Maya
#define NT_PLUGIN
#define REQUIRE_IOSTREAM
#define EXPORT __declspec(dllexport)

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include <maya/MEvent.h>
#include <maya/MFnPlugin.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTransform.h>
#include <maya/MFloatPointArray.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include <maya/MEulerRotation.h>
#include <maya/MVector.h>
#include <maya/MItDag.h>
#include <maya/MFnCamera.h>
#include <maya/M3dView.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MPlugArray.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnLambertShader.h>
#include <maya/MFnBlinnShader.h>
#include <maya/MFnPhongShader.h>
#include <maya/MImage.h>
#include <maya/MFnPointLight.h>
#include <maya/MSelectionList.h>
#include <maya/MItDependencyNodes.h>

// Wrappers
#include <maya/MGlobal.h>
#include <maya/MCallbackIdArray.h>

// Messages
#include <maya/MMessage.h>
#include <maya/MTimerMessage.h>
#include <maya/MDGMessage.h>
#include <maya/MEventMessage.h>
#include <maya/MPolyMessage.h>
#include <maya/MNodeMessage.h>
#include <maya/MDagPath.h>
#include <maya/MDagMessage.h>
#include <maya/MUiMessage.h>
#include <maya/MModelMessage.h>
#include <maya/MCameraSetMessage.h>

// Commands
#include <maya/MPxCommand.h>

// Libraries to link from Maya
// This can be also done in the properties setting for the project.
#pragma comment(lib,"Foundation.lib")
#pragma comment(lib,"OpenMaya.lib")
#pragma comment(lib,"OpenMayaUI.lib")


	enum MessageType { msgAdded = 1, msgEdited = 2, msgDeleted = 3, msgRenamed = 4};
	enum NodeType { nDefaultNode = 0, nMesh = 1, nTransform = 2, nCamera = 3, nLight = 4 , nMaterial = 5};




	struct MessageInfo
	{
		std::string nodeName;
		int msgType;
		int nodeType;
	};


	struct CameraInfo
	{
		std::string nodeName;
		std::string transformName;
	};

	struct MeshInfo
	{
		std::string nodeName;
		//std::string transformName;
		int vertCount;
	};

	struct MeshData
	{
		std::string transformName;
		int vertCount;
		int normalCount;
		int UVCount;
		int indCount;
		int triCount;
		int* indices;
		int* triIndices;
		int* norIndices;
		int* UVIndices;
		const float* vertices;
		const float* normals;
		float2* uv;
	};
	struct TransInfo
	{
		std::string nodeName;
		//std::string parentName;
		int childCount;
	};
	struct TransData
	{
		std::string parentName;
		float translation[3];
		float rotation[3];
		float scale[3];
		//kanske number of children?
	};


	bool debug;
	MCallbackId _CBid;
	MCallbackIdArray _CBidArray;
	std::vector<MeshInfo> _meshVector;
	std::vector<TransInfo> _transVector;
	std::vector<CameraInfo> _camVector;	
	std::vector<MessageInfo> _msgVector;
	std::queue<MessageInfo> _msgQueue;
	void cbMeshAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
	void cbMessageTimer(float elapsedTime, float lastTime, void *clientData);
	void cbNewNode(MObject& node, void* clientData);
	void cbTransformModified(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
	void cbNameChange(MObject& node, const MString& str, void* clientData);

	void mAddNode(char* name, int type, int vertCount = 0, char* childname = nullptr);

	void loadScene();

	void outTransFormData(MObject& obj);
	void outMeshData(MObject& obj);
	void outCameraData(MObject& obj);
	void outLightData(MObject& obj);


