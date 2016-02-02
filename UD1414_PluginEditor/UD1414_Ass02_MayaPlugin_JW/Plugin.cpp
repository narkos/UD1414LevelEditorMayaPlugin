#include "Plugin.h"
#include "ApplicationContext.hpp"
#include "CmdFilemapOnOff.hpp"
EXPORT MStatus initializePlugin(MObject obj)
{
	MGlobal::displayInfo("Bulten1");
	using namespace DoremiEditor::Plugin;
	//ApplicationContext::Startup();
	MGlobal::displayInfo("Bulten2");
	//Error Checking Variable
	MStatus result = MS::kSuccess;
	//LoaderPlugin mainPlugin;
	MFnPlugin editorPlugin(obj, "Level Editor", "1.0", "Any", &result);
	if (MFAIL(result))
	{
		CHECK_MSTATUS(result);
	}
	else
	{
		MGlobal::displayInfo("DRM Level Editor Plugin Loaded.");
	}
	
	//editorPlugin.registerCommand("drmToggleFilemaps", CmdFilemapOnOff::creator);

	//mainPlugin.m_callbackIDArray.append(MDGMessage::addNodeAddedCallback(mainPlugin.cbNewNode));
	//fFillAttributesList();
	//OpenFileMaps::fMap = &fileMap;
	//result = editorPlugin.registerCommand("execFileMaps", OpenFileMaps::creator);
	//fileMap.CreateFileMaps(true);
	
//	FileMapping::printInfo("Level Editor plugin loaded.\n");
	//result = M3dView::getM3dViewFromModelPanel("modelPanel4", modelPanel);
	//loadScene();
	//debug = fileMap.debug;
	//FileMapping::printInfo("debug:  " + MString() + debug);
	//ApplicationContext::GetInstance().GetNodeHandler().DoATestOfStuff(true);


	//_CBidArray.append(MNodeMessage::addNameChangedCallback(MObject::kNullObj, &cbNameChange));
	/*_CBidArray.append(MDGMessage::addNodeAddedCallback(cbNewNode));
	_CBidArray.append(MTimerMessage::addTimerCallback(0.2f, &cbMessageTimer));
	_CBidArray.append(MUiMessage::addCameraChangedCallback("modelPanel4", cbCameraPanel));
	_CBidArray.append(MDagMessage::addParentAddedCallback(cbAddParent));
	_CBidArray.append(MDagMessage::addChildReorderedCallback(cbRemoveParent));
	_CBidArray.append(MModelMessage::addAfterDuplicateCallback(cbDuplication));*/

	return result;

}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	MGlobal::displayInfo("Level Editor plugin unloaded.");

	using namespace DoremiEditor::Plugin;
	//plugin.deregisterCommand("drmToggleFilemaps");
	//ApplicationContext::Shutdown();
	
	return MS::kSuccess;
}
