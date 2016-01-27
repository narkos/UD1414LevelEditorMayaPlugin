#pragma once
#include "LoaderPlugin.hpp"

#define NT_PLUGIN
#define REQUIRE_IOSTREAM
#define EXPORT __declspec(dllexport)
#include <maya/MFnPlugin.h>


//class OpenFileMaps;
//class CloseFileMaps;
//class AddAttribute;



//std::vector<std::string> msgTypeVector;
//
//	FileMapping fileMap;
//
//	M3dView modelPanel;
//	MDagPath activeCamera;
//
//	OpenFileMaps someFunction();
//
//
//	bool debug;
//	MCallbackId _CBid;
//	MCallbackIdArray _CBidArray;
//	std::vector<MeshInfo> meshVector;
//	std::vector<TransformInfo> transVector;
//	std::vector<CameraInfo> camVector;
//	std::vector<LightInfo> lightVector;
//	std::vector<MaterialInfo> materialVector;
//	std::vector<MessageInfo> msgVector;
//	std::queue<MessageInfo> msgQueue;
//	//std::map<std::string, std::pair<std::string, std::string>> attributesList;
//	
//	struct Attribute
//	{
//		Attribute(std::string p_name, std::string p_type, std::string p_value): name(p_name) , type(p_type) , value(p_value)
//		{
//
//		}
//		std::string GetFullString()
//		{
//
//		}
//		std::string name;
//		std::string type;
//		std::string value;
//	};
//
//	std::vector<Attribute> m_attributeVector;
//
//	void cbReparent(MDagPath &child, MDagPath &parent, void *clientData);
//	void cbMeshAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
//	void cbMessageTimer(float elapsedTime, float lastTime, void *clientData);
//	void cbNewNode(MObject& node, void* clientData);
//	void cbTransformModified(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
//	void cbNameChange(MObject& node, const MString& str, void* clientData);
//	void cbMeshAttributeChange(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
//	void cbMaterialAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData);
//	void cbPreRemoveNode(MObject& node, void* clientData);
//	void mAddNode(char* name, int type, int vertCount = 0, char* childname = nullptr);
//	void mAddMessage(std::string name, int msgType, int nodeType, std::string oldName = "");
//	void loadScene();
//	bool deleteNode();
//	bool renameNode(MString newName, MString oldName, int type);
//
//	MeshInfo outMeshData(std::string name, bool getDynamicData = true);
//
//
//	void fFillAttributesList();
//	bool fAddAttributes(MFnTransform& inTrans);
//
//	void outTransFormData(MObject& obj);
//	void outMeshData(MObject& obj);
//	void outCameraData(MObject& obj);
//	void outLightData(MObject& obj);


