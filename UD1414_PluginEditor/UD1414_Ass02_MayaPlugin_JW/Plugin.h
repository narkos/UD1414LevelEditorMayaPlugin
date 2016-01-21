#pragma once

// some definitions for the DLL to play nice with Maya
#define NT_PLUGIN
#define REQUIRE_IOSTREAM
#define EXPORT __declspec(dllexport)

#include <stdlib.h>
#include <iostream>
#include <string>

#include <queue>
//#include <map>

#include <maya/MEvent.h>
#include <maya/MFnPlugin.h>
#include <maya/MFnMesh.h>
#include <maya/MFnTransform.h>
#include <maya/MFloatPointArray.h>
#include <maya/MPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MPoint.h>
#include <maya/MMatrix.h>
#include <maya/MFloatMatrix.h>
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
#include <maya/MFnDirectionalLight.h>
#include <maya/MFnSpotLight.h>
#include <maya/MFnPointLight.h>
#include <maya/M3dView.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MMatrix.h>
#include <maya/MItMeshFaceVertex.h>
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
#include <maya/MLockMessage.h>

//#include "Commands.h"
#include "FileMap.h"

// Commands
#include <maya/MPxCommand.h>

// Libraries to link from Maya
// This can be also done in the properties setting for the project.
#pragma comment(lib,"Foundation.lib")
#pragma comment(lib,"OpenMaya.lib")
#pragma comment(lib,"OpenMayaUI.lib")


class OpenFileMaps;
class CloseFileMaps;
class AddAttribute;


std::vector<std::string> msgTypeVector;

	FileMapping fileMap;

	M3dView modelPanel;
	MDagPath activeCamera;

	OpenFileMaps someFunction();


	bool debug;
	MCallbackId _CBid;
	MCallbackIdArray _CBidArray;
	std::vector<MeshInfo> meshVector;
	std::vector<TransformInfo> transVector;
	std::vector<CameraInfo> camVector;
	std::vector<LightInfo> lightVector;
	std::vector<MaterialInfo> materialVector;
	std::vector<MessageInfo> msgVector;
	std::queue<MessageInfo> msgQueue;
	//std::map<std::string, std::pair<std::string, std::string>> attributesList;
	
	struct Attribute
	{
		Attribute(std::string p_name, std::string p_type, std::string p_value): name(p_name) , type(p_type) , value(p_value)
		{

		}
		std::string GetFullString()
		{

		}
		std::string name;
		std::string type;
		std::string value;
	};

	std::vector<Attribute> m_attributeVector;

	void cbReparent(MDagPath &child, MDagPath &parent, void *clientData);
	void cbMeshAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
	void cbMessageTimer(float elapsedTime, float lastTime, void *clientData);
	void cbNewNode(MObject& node, void* clientData);
	void cbTransformModified(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
	void cbNameChange(MObject& node, const MString& str, void* clientData);
	void cbMeshAttributeChange(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
	void cbMaterialAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
	void cbPreRemoveNode(MObject& node, void* clientData);
	void mAddNode(char* name, int type, int vertCount = 0, char* childname = nullptr);
	void mAddMessage(std::string name, int msgType, int nodeType, std::string oldName = "");
	void loadScene();
	bool deleteNode();
	bool renameNode(MString newName, MString oldName, int type);

	MeshInfo outMeshData(std::string name, bool getDynamicData = true);


	void fFillAttributesList();
	bool fAddAttributes(MFnTransform& inTrans);

	void outTransFormData(MObject& obj);
	void outMeshData(MObject& obj);
	void outCameraData(MObject& obj);
	void outLightData(MObject& obj);


