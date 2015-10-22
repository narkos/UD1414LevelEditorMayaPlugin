#include "Plugin.h"



void cb_transformChanged(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	if(msg & MNodeMessage::AttributeMessage::kAttributeSet)
	//if (plug_1.node().hasFn(MFn::kTransform))
	{
		MStatus result;
		MFnTransform transform(plug_1.node());
		//MString att(plug_1.node());
		MGlobal::displayInfo(MString(plug_1.info().asChar()));
		std::string attName(plug_1.info().asChar());
		if (attName.find("translate") != std::string::npos)
		{
			MVector trans = transform.getTranslation(MSpace::kPostTransform, &result);
			MGlobal::displayInfo("NODE: " + transform.fullPathName() + " Translation changed: (" + MString() + trans.x + " , " + MString() + trans.y + " , " + MString() + trans.z + ")");
		}
		else if (attName.find("rotate") != std::string::npos)
		{
			MEulerRotation rotation;
			transform.getRotation(rotation);
			MGlobal::displayInfo("NODE: " + transform.fullPathName() + " Scaling changed: (" + MString() + rotation.x + " , " + MString() + rotation.y +" , " + MString() + rotation.z + ")");
			
		}
		else if (attName.find("scale") != std::string::npos)
		{
			double scale[3];
			transform.getScale(scale);
			MGlobal::displayInfo("NODE: " + transform.fullPathName() + "Scale changed: (" + MString() + scale[0] + " , " + MString() + scale[1] + " , " + MString() + scale[2] + ")");
		}
	}
	
}

void cb_meshAttributeChanged(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	// Standard string for use with find() function
	std::string plugName(plug_1.name().asChar());

	if (plugName.find("doubleSided") != std::string::npos && MNodeMessage::AttributeMessage::kAttributeSet )
	{
		//MGlobal::displayInfo(MString(plug_1.name().asChar()));
		MStatus result;
		MFnMesh mNode(plug_1.node(), &result);

		
		if (result)
		{
		
			MGlobal::displayInfo("\nNew Mesh node path: " + mNode.fullPathName() + "\n");
			//DO STUFF
			MPointArray vertices;
			MFloatVectorArray normals;
			MFloatArray uArray;
			MFloatArray vArray;
			mNode.getPoints(vertices, MSpace::kPostTransform);
			mNode.getNormals(normals, MSpace::kPostTransform);
			mNode.getUVs(uArray, vArray);
			//if (mNode.getPoints(vertices, MSpace::kWorld) == MS::kSuccess)
			//{
				MGlobal::displayInfo("Number of vertices: " + MString() + vertices.length());
				for (int i = 0; i < vertices.length(); i++)
				{
					MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
					MGlobal::displayInfo("v: " +MString() + vertices[i].x + ", " + MString() + vertices[i].y + ", " + MString() + vertices[i].z);
					MGlobal::displayInfo("n: " + MString() + normals[i].x + ", " + MString() + normals[i].y + ", " + MString() + normals[i].z);
					MGlobal::displayInfo("uv: " + MString() + uArray[i] + ", " + MString() + vArray[i]);
				}
				MGlobal::displayInfo("\n\n");
				MessageInfo temp;
				temp.msgType = 3;
				temp.nodeType = mesh;
				temp.nodeName = mNode.fullPathName();
				_meshVector.push_back(temp);
			//}
				
		}
		
	}
	
	MObject ob(plug_1.node());
	
	if (plugName.find("pnts") != std::string::npos  && plugName.find("[") != std::string::npos)
	{
		//MGlobal::displayInfo(plugName.c_str());
		std::size_t lIndex = plug_1.logicalIndex();
		//MGlobal::displayInfo(MString() + lIndex);
		std::string asdf(plug_1.node().apiTypeStr());
		if (asdf.find("kMesh") != std::string::npos)
		{
			MGlobal::displayInfo(plug_1.node().apiTypeStr());
			MFnMesh mesh(plug_1.node());
			
			MPointArray verts;
			mesh.getPoints(verts, MSpace::kPostTransform);
			MGlobal::displayInfo(mesh.fullPathName() + " Vertex[" + MString()+lIndex + "] moved ( " +MString()+verts[lIndex].	x + ", " + MString() + verts[lIndex].y + ", " + MString() + verts[lIndex].z +" )");

		}
	}

}



void cb_meshAttributeEvaluated(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	std::string plugName(plug_2.info().asChar());
	MString plugN(plug_2.info());
	if (msg & MNodeMessage::AttributeMessage::kAttributeEval)
	{
		MGlobal::displayInfo(plug_1.info().asChar());
	}
	//if(plugName.find("Translate") != std::string::npos)
	//{
	//	MGlobal::displayInfo("!!!!!!! EVAL");
	//	//MPolyMessage::removeCallback(MPolyMessage::currentCallbackId());
	//}
}

void cb_polyChanged(MObject& node, void* clientData)
{
	
	

}

void cb_meshCreated(MObject& node, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
	{
		_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cb_meshAttributeChanged));
		_CBidArray.append(MPolyMessage::addPolyTopologyChangedCallback(node, cb_polyChanged));		
		
	}
	if (node.hasFn(MFn::kTransform))
	{
		_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cb_transformChanged));
	}


}

void o_meshData(MFnMesh& node)
{
	MStatus result;
	//MFnMesh mNode(node, &result);
	//MFnMesh mNode = node;

	if (result)
	{

		MGlobal::displayInfo("\nNew Mesh node path: " + node.fullPathName() + "\n");
		//DO STUFF
		MPointArray vertices;
		MFloatVectorArray normals;
		MFloatArray uArray;
		MFloatArray vArray;
		node.getPoints(vertices, MSpace::kPostTransform);
		node.getNormals(normals, MSpace::kPostTransform);
		node.getUVs(uArray, vArray);
		//if (mNode.getPoints(vertices, MSpace::kWorld) == MS::kSuccess)
		//{
		MGlobal::displayInfo("Number of vertices: " + MString() + vertices.length());
		for (int i = 0; i < vertices.length(); i++)
		{
			MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
			MGlobal::displayInfo("v: " + MString() + vertices[i].x + ", " + MString() + vertices[i].y + ", " + MString() + vertices[i].z);
			MGlobal::displayInfo("n: " + MString() + normals[i].x + ", " + MString() + normals[i].y + ", " + MString() + normals[i].z);
			MGlobal::displayInfo("uv: " + MString() + uArray[i] + ", " + MString() + vArray[i]);
		}
		MGlobal::displayInfo("\n\n");

		//}
	}

}

void f_timeChanged(float elapsedTime, float lastTime, void *clientData)
{
	MGlobal::displayInfo("BEEP " + MString()+_CBidArray.length() + " CALLBACKS");
	int ml = _meshVector.size();
	for (int i = 0; i < ml; i++)
	{
		if (_meshVector[i].msgType == meshAdded)
		{
			
			MStatus status;
			MSelectionList slist;
			slist.add(_meshVector[i].nodeName);
			MDagPath d;
			slist.getDagPath(0, d);
			
			MGlobal::displayInfo("WOHOAAAAOHOHOHOHOHOH"  + d.fullPathName());
			MFnMesh m(d, &status);
			if (status)
			{
				o_meshData(m);
			}
			_meshVector[i].msgType = 0;
	
			MDagPath path();
			MGlobal::selectByName(_meshVector[i].nodeName);
		}
	}
}



EXPORT MStatus initializePlugin(MObject obj)
{
	//Error Checking Variable
	MStatus result = MS::kSuccess;

	MFnPlugin editorPlugin(obj, "Level Editor", "1.0", "Any", &result);
	if (MFAIL(result))
	{
		CHECK_MSTATUS(result);
	}

	MGlobal::displayInfo("Level Editor plugin loaded.");
	//MObject objecto = obj;
	debug = true;
	_CBidArray.append(MNodeMessage::addNameChangedCallback(MObject::kNullObj, &cbNameChange));
	_CBidArray.append(MDGMessage::addNodeAddedCallback(cbNewNode));
	_CBidArray.append(MTimerMessage::addTimerCallback(5, &cbMessageTimer));
	/*MStatus lel;
	_CBidArray.append(MNodeMessage::addAttributeChangedCallback(MObject::kNullObj, f_transformChanged, NULL, &lel));
	if (lel == MS::kSuccess)
	{
	MGlobal::displayInfo("Could be added bitch");
	}*/
	//_CBidArray.

	return result;

}



EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	MGlobal::displayInfo("Level Editor plugin unloaded.");
	MMessage::removeCallbacks(_CBidArray);


	return MS::kSuccess;
}