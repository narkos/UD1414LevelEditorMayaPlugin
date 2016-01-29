#include "Plugin.h"

EXPORT MStatus initializePlugin(MObject obj)
{
	using namespace DoremiEditor::Plugin;
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
	


	return MS::kSuccess;
}
