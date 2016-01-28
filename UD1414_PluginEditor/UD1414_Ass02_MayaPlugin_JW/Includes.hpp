#pragma once
#ifndef INCLUDES_HPP
#define INCLUDES_HPP



// Maya 

// some definitions for the DLL to play nice with Maya


#include <stdlib.h>
#include <iostream>
#include <string>

#include <queue>
//#include <map>

#include <maya/MEvent.h>

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
//#include "FileMap.h"

// Commands
#include <maya/MPxCommand.h>

// Libraries to link from Maya
// This can be also done in the properties setting for the project.
#pragma comment(lib,"Foundation.lib")
#pragma comment(lib,"OpenMaya.lib")
#pragma comment(lib,"OpenMayaUI.lib")


// Std and windows Includes
#include <Windows.h>
#include <ostream>
#include <iostream>
#include <vector>
#include <maya/MGlobal.h>
#include <vector>



#include "PluginStructs.hpp"


#endif