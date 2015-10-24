#include "Plugin.h"

MeshData outMeshData(std::string name)
{
	MString _name(name.c_str());
	MSelectionList sList;
	MDagPath dagPath;
	if (MGlobal::getSelectionListByName(_name, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kMesh))
		{
			MGlobal::displayInfo("Mesh found: " + dagPath.fullPathName());
		}
		
	}

	MFnMesh mNode(dagPath.node());
	MeshData outMesh;
	
	if (mNode.parent(0).hasFn(MFn::kTransform))
	{
		MFnTransform mTrans(mNode.parent(0));
		outMesh.transformName = mTrans.fullPathName().asChar();
		MGlobal::displayInfo(outMesh.transformName.c_str());
	}
	

	MStatus result;
	////MFnMesh mNode((obj), &result);
	if (result)
	{
		//DO STUFF
		//MPointArray vertices;
		MFloatPointArray vertices;
		MFloatVectorArray normals;
		MFloatArray uArray;
		MFloatArray vArray;

		MIntArray vertexCountPerPoly;
		MIntArray vertList;
		mNode.getVertices(vertexCountPerPoly, vertList);

		MIntArray normalIndices;
		MIntArray normalPerPoly;
		mNode.getNormalIds(normalIndices, normalPerPoly);

		MIntArray triCount;
		MIntArray triVerts;
		mNode.getTriangleOffsets(triCount, triVerts);

		mNode.getPoints(vertices, MSpace::kPreTransform);
		mNode.getNormals(normals, MSpace::kPreTransform);
		mNode.getUVs(uArray, vArray);
		
		int numUVs = mNode.numUVs();
		

		outMesh.vertCount = vertices.length();
		outMesh.normalCount = normals.length();
		outMesh.UVCount = numUVs;
		outMesh.triCount = triVerts.length();
		outMesh.indCount = vertList.length();

		outMesh.indices = new int[outMesh.indCount];
		for (int i = 0; i < outMesh.indCount; i++)
		{
			outMesh.indices[i] = vertList[i];
		}
		outMesh.triIndices = new int[outMesh.triCount];
		for (int i = 0; i < outMesh.triCount; i++)
		{
			outMesh.triIndices[i] = triVerts[i];
		}
		outMesh.norIndices = new int[outMesh.normalCount];
		for (int i = 0; i < outMesh.normalCount; i++)
		{
			outMesh.norIndices[i] = normalPerPoly[i];
		}
		outMesh.UVIndices = new int[outMesh.UVCount];
		for (int i = 0; i < outMesh.UVCount; i++)
		{
			outMesh.UVIndices[i] = i;
		}
		MStatus st;
		outMesh.vertices = mNode.getRawPoints(&st);
		if (st)
		{
			int rawsize = outMesh.vertCount *3;
			MGlobal::displayInfo("RAW SIZE "+MString() + rawsize);
			for (int i = 0; i < rawsize; i++)
			{
				MGlobal::displayInfo(MString() + outMesh.vertices[i]);
			}
		}
		

		delete[] outMesh.indices;
		delete[] outMesh.triIndices;
		delete[] outMesh.norIndices;
		delete[] outMesh.UVIndices;

		//for()

		if (debug)
		{

			MGlobal::displayInfo("\nNew Mesh node path: " + mNode.fullPathName() + "\n");
			MGlobal::displayInfo("Normal Indicies: " + MString() + normalPerPoly.length());
			MGlobal::displayInfo("Triangle Count: " + MString() + triVerts.length());
			MGlobal::displayInfo("UV count:" + MString() + numUVs);
			MGlobal::displayInfo("Number of vertices: " + MString() + vertices.length());
			MGlobal::displayInfo("Number of vertIndicies: " + MString() + vertList.length());
			for (int i = 0; i < vertices.length(); i++)
			{
				MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
				MGlobal::displayInfo("v: " + MString() + vertices[i].x + ", " + MString() + vertices[i].y + ", " + MString() + vertices[i].z);

			}
			for (int i = 0; i < normals.length(); i++)
			{
				MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
				MGlobal::displayInfo("n: " + MString() + normals[i].x + ", " + MString() + normals[i].y + ", " + MString() + normals[i].z);
			}
			for (int i = 0; i < uArray.length(); i++)
			{
				MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
				MGlobal::displayInfo("uv: " + MString() + uArray[i] + ", " + MString() + vArray[i]);
			}
			for (int i = 0; i < triCount.length(); i++)
			{
				MGlobal::displayInfo("Tri ID:" + MString() + triCount[i] + " ( " + MString() + triVerts[i]);
			}
		}
	}
	return outMesh;
}

TransData outTransformData(std::string name)
{
	MStatus result;
	MString _name(name.c_str());
	MSelectionList sList;
	MDagPath dagPath;
	if (MGlobal::getSelectionListByName(_name, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kTransform))
		{
			MGlobal::displayInfo("Transform found: " + dagPath.fullPathName());
		}

	}

	MFnTransform mNode(dagPath.node());
	TransData outTrans;
	outTrans.parentName = nullptr;
	
	//MString att(plug_1.node());
	MGlobal::displayInfo(MString(mNode.fullPathName()) + MString() +mNode.childCount());
	std::string attName(mNode.fullPathName().asChar());
	if (attName.find("translate") != std::string::npos)
	{

		MVector trans = mNode.getTranslation(MSpace::kPostTransform, &result);
		MGlobal::displayInfo("NODE: " + mNode.fullPathName() + " Translation changed: (" + MString() + trans.x + " , " + MString() + trans.y + " , " + MString() + trans.z + ")");
		outTrans.translation[0] = trans.x;
		outTrans.translation[1] = trans.y;
		outTrans.translation[2] = trans.z;
	}
	else if (attName.find("rotate") != std::string::npos)
	{
		MEulerRotation rotation;
		mNode.getRotation(rotation);
		MGlobal::displayInfo("NODE: " + mNode.fullPathName() + " Scaling changed: (" + MString() + rotation.x + " , " + MString() + rotation.y + " , " + MString() + rotation.z + ")");
		outTrans.rotation[0] = rotation.x;
		outTrans.rotation[1] = rotation.y;
		outTrans.rotation[2] = rotation.z;
	}
	else if (attName.find("scale") != std::string::npos)
	{
		double scale[3];
		mNode.getScale(scale);
		MGlobal::displayInfo("NODE: " + mNode.fullPathName() + "Scale changed: (" + MString() + scale[0] + " , " + MString() + scale[1] + " , " + MString() + scale[2] + ")");
		outTrans.scale[0] = scale[0];
		outTrans.scale[1] = scale[1];
		outTrans.scale[2] = scale[2];
	}
	return outTrans;
}


void oldMeshData(std::string name)
{
	MString _name(name.c_str());
	MSelectionList sList;
	MDagPath dagPath;
	if (MGlobal::getSelectionListByName(_name, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kMesh))
		{
			MGlobal::displayInfo("Mesh found: " + dagPath.fullPathName());
		}
		else return;
	}

	MFnMesh mNode(dagPath.node());



	MStatus result;
	////MFnMesh mNode((obj), &result);
	if (result)
	{
		//DO STUFF
		MPointArray vertices;
		MFloatVectorArray normals;
		MFloatArray uArray;
		MFloatArray vArray;

		MIntArray vertexCountPerPoly;
		MIntArray vertList;
		mNode.getVertices(vertexCountPerPoly, vertList);

		MIntArray normalIndices;
		MIntArray normalPerPoly;
		mNode.getNormalIds(normalIndices, normalPerPoly);

		MIntArray triCount;
		MIntArray triVerts;
		mNode.getTriangleOffsets(triCount, triVerts);

		mNode.getPoints(vertices, MSpace::kPreTransform);
		mNode.getNormals(normals, MSpace::kPreTransform);
		mNode.getUVs(uArray, vArray);

		//int numUVs = mNode.numUVs;

		MIntArray indices;
		//for()




		if (debug)
		{

			MGlobal::displayInfo("\nNew Mesh node path: " + mNode.fullPathName() + "\n");
			MGlobal::displayInfo("Normal Indicies: " + MString() + normalPerPoly.length());
			MGlobal::displayInfo("Triangle Count: " + MString() + triVerts.length());
//			MGlobal::displayInfo("UV count:" + MString() + numUVs);
			MGlobal::displayInfo("Number of vertices: " + MString() + vertices.length());
			MGlobal::displayInfo("Number of vertIndicies: " + MString() + vertList.length());
			for (int i = 0; i < vertices.length(); i++)
			{
				MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
				MGlobal::displayInfo("v: " + MString() + vertices[i].x + ", " + MString() + vertices[i].y + ", " + MString() + vertices[i].z);

			}
			for (int i = 0; i < normals.length(); i++)
			{
				MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
				MGlobal::displayInfo("n: " + MString() + normals[i].x + ", " + MString() + normals[i].y + ", " + MString() + normals[i].z);
			}
			for (int i = 0; i < uArray.length(); i++)
			{
				MGlobal::displayInfo(MString() + (int)(i + 1) + ".");
				MGlobal::displayInfo("uv: " + MString() + uArray[i] + ", " + MString() + vArray[i]);
			}
			for (int i = 0; i < triCount.length(); i++)
			{
				MGlobal::displayInfo("Tri ID:" + MString() + triCount[i] + " ( " + MString() + triVerts[i]);
			}
		}
	}
}

void mAddMessage(std::string name, int msgType, int nodeType)
{
	bool exists = false;
	if (_msgVector.size() > 0)
	{
		for(std::vector<MessageInfo>::size_type i = 0; i != _msgVector.size(); i++)
			{
				std::string tmp = _msgVector.at(i).nodeName;
				if (strcmp(name.c_str(), tmp.c_str()) == 0)
				{
					if (_msgVector.at(i).msgType == msgType)
					{
						exists = true;
						MGlobal::displayWarning("Message" + MString(name.c_str()) + "already exists!");
					}
					
				}
			}
	}
	if (!exists)
	{
		MessageInfo tMsg{ name, msgType, nodeType };
		_msgVector.push_back(tMsg);
		_msgQueue.push(tMsg);
	}
}

void mAddNode(std::string name, int type, int vertCount = 0, char* childname=nullptr)
{
	if (!name.empty())
	{
		bool exists = false;
		//std::string nodename = name.asChar();
		if (type == nMesh)
		{
			if (_meshVector.size() > 0)
			{
				for (std::vector<MeshInfo>::size_type i = 0; i != _meshVector.size(); i++)
				{
					std::string tmp = _meshVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						MGlobal::displayWarning("Mesh " + MString(name.c_str()) + " already exists!");
					}
				}
			}
			if (!exists)
			{
				MeshInfo mesh{ name, vertCount };
				_meshVector.push_back(mesh);
				mAddMessage(name, msgAdded, nMesh);
				MGlobal::displayInfo("Added mesh: " + MString(name.c_str()) + "with " + MString() + vertCount + " vertices.");
			}
		}
		else if (type == nTransform)
		{
			if (_transVector.size() > 0)
			{
				for (std::vector<TransInfo>::size_type i = 0; i != _transVector.size(); i++)
				{
					std::string tmp = _transVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						MGlobal::displayWarning("Transform " + MString(name.c_str()) + " already exists!");
					}
				}
			}
			if (!exists)
			{
				mAddMessage(name, msgAdded, nTransform);
				TransInfo trans{ name, vertCount };
				_transVector.push_back(trans);
				MGlobal::displayInfo("Added transform: " + MString(name.c_str()));
			}
		}
		else if (type == nCamera)
		{
			if (_camVector.size() > 0)
			{
				for (std::vector<CameraInfo>::size_type i = 0; i != _camVector.size(); i++)
				{
					std::string tmp = _camVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						MGlobal::displayWarning("Camera " + MString(name.c_str()) + " already exists!");
					}
				}
			}
			if (!exists)
			{
				MString mName(name.c_str());
				MDagPath dagPath;
				MSelectionList sList;
				if (MGlobal::getSelectionListByName(mName, sList))
				{
					sList.getDagPath(0, dagPath);
					MFnDagNode dagNode(dagPath);
					if (dagNode.parent(0).hasFn(MFn::kTransform))
					{
						MFnTransform trans(dagNode.parent(0));
						CameraInfo cam {name, trans.fullPathName().asChar()};
						_camVector.push_back(cam);
						MGlobal::displayInfo("Added camera: " + MString(name.c_str()));
						mAddMessage(name, msgAdded, nCamera);
					}
				}
				
			}

		}
		else if (type == nLight)
		{

		}
	}
	
}

void cbMeshAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	// Validates new mesh
	// Standard string for use with find() function
	std::string plugName(plug_1.name().asChar());
	if (plugName.find("doubleSided") != std::string::npos && MNodeMessage::AttributeMessage::kAttributeSet )
	{

		MStatus result;
		MFnMesh mNode(plug_1.node(), &result);
		if (result )
		{	//DO STUFF
			MString myCommand = "setAttr -e " + mNode.name() + ".quadSplit 0";
			MGlobal::executeCommandOnIdle(myCommand);


			MPointArray vertices;
			mNode.getPoints(vertices, MSpace::kPreTransform);
			std::string tmpName = mNode.fullPathName().asChar();
			mAddNode(tmpName.c_str(), nMesh, vertices.length());
		}
	}
	//Finds changes to vertex positions
	if (plugName.find("pnts") != std::string::npos  && plugName.find("[") != std::string::npos)
	{
		std::size_t lIndex = plug_1.logicalIndex();	
		std::string apiStr(plug_1.node().apiTypeStr());
		if (apiStr.find("kMesh") != std::string::npos)
		{
			MGlobal::displayInfo(plug_1.node().apiTypeStr());
			MFnMesh mesh(plug_1.node());
			std::string tmpname = mesh.fullPathName().asChar();
			mAddMessage(tmpname, msgEdited, NodeType::nMesh);
			
			if (debug)
			{
				MPointArray verts;
				mesh.getPoints(verts, MSpace::kPostTransform);
			}
			
		}
	}
}

void cbEvalAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeEval)
	{
		MGlobal::displayInfo(plug_1.info().asChar());
		MMessage::removeCallback(MPolyMessage::currentCallbackId());
	}
}

void cbPolyChanged(MObject& node, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
	{
		MStatus stat;
		MFnMesh mesh(node, &stat);
		if (stat == MS::kSuccess)
			MGlobal::displayInfo("( " + mesh.fullPathName() + " )MESH TOPOLOGY CHANGED");
		mAddMessage(mesh.fullPathName().asChar(), msgEdited, nMesh);
		_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbEvalAttribute));
	}
}


void cbNameChange(MObject& node, const MString& str, void* clientData)
{

	if (node.hasFn(MFn::kMesh))
	{
		MFnMesh mesh(node);
		std::string newNameStr = mesh.fullPathName().asChar();
		//std::string oldNameStr = str.asChar();
		for (std::vector<MeshInfo>::size_type i = 0; i != _meshVector.size(); i++)
		{
			std::string oldTemp = _meshVector.at(i).nodeName;
			if (strcmp(newNameStr.c_str(), oldTemp.c_str()))
			{
				_meshVector.at(i).nodeName = mesh.fullPathName().asChar();
				mAddMessage(_meshVector.at(i).nodeName, msgRenamed, NodeType::nMesh);
				MGlobal::displayInfo("Mesh name: " + str+ " changed to: " + (MString)mesh.name());
				break;
			}
		}
		
		//MMessage::removeCallback(MMessage::currentCallbackId());
	}
	else if (node.hasFn(MFn::kTransform) == true)
	{
		bool hasShapes = false;
		MFnTransform trans(node);
		for (int i = 0; i < trans.childCount(); i++)
		{
			MObject child = trans.child(i);
			if (child.hasFn(MFn::kMesh))
			{
				hasShapes = true;
			}
			if(child.hasFn(MFn::kCamera))
			{
				hasShapes = true;
			}
		}
		if(hasShapes)
			MGlobal::displayInfo("Transform name changed to: " + (MString)trans.name());
	}


}

void cbRemovedNode(MObject& node, void* clientData)
{
	/*MFnDependencyNode n(node);
	MGlobal::displayInfo(n.name() + " Node deleted");*/
	
}
void cbPreRemoveNode(MObject& node, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
	{
		MFnMesh mesh(node);
		
		for (int i = 0; i < _meshVector.size(); i++)
		{
			std::string tmp = _meshVector.at(i).nodeName;
			std::string ntmp = mesh.fullPathName().asChar();
			//MGlobal::displayInfo(MString(ntmp.c_str()) + " ___ " + MString(tmp.c_str()));
			if (tmp.find(ntmp) != std::string::npos)
			{
				//MGlobal::displayInfo(mesh.fullPathName() + " Node deleted MESH");
				_meshVector.pop_back();
				mAddMessage(mesh.fullPathName().asChar(), msgDeleted, nMesh);
			}
		}
	}
	if (node.hasFn(MFn::kTransform))
	{
		MFnTransform trans(node);
		for (int i = 0; i < _transVector.size(); i++)
		{
			std::string tmp = _transVector.at(i).nodeName;
			std::string ntmp = trans.fullPathName().asChar();
			//MGlobal::displayInfo(MString(ntmp.c_str()) + " ___ " + MString(tmp.c_str()));
			if (tmp.find(ntmp) != std::string::npos)
			{
				//MGlobal::displayInfo(trans.fullPathName() + " Node deleted TRANSFORM");
				_transVector.pop_back();
				mAddMessage(trans.fullPathName().asChar(), msgDeleted, nTransform);
			}
		}
	}
	_CBidArray.remove(MNodeMessage::currentCallbackId());

}
void cbTransformModified(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	if (msg & MNodeMessage::AttributeMessage::kAttributeSet)
		//if (plug_1.node().hasFn(MFn::kTransform))
	{
		bool d = false;
		MStatus result;
		MFnTransform transform(plug_1.node());
		//MString att(plug_1.node());
		//MGlobal::displayInfo(MString(plug_1.info().asChar()));
		std::string attName(plug_1.info().asChar());
		if (d)
		{
			if (attName.find("translate") != std::string::npos)
			{
				MVector trans = transform.getTranslation(MSpace::kPostTransform, &result);
				MGlobal::displayInfo("NODE: " + transform.fullPathName() + " Translation changed: (" + MString() + trans.x + " , " + MString() + trans.y + " , " + MString() + trans.z + ")");
			}
			else if (attName.find("rotate") != std::string::npos)
			{
				MEulerRotation rotation;
				transform.getRotation(rotation);
				MGlobal::displayInfo("NODE: " + transform.fullPathName() + " Rotation changed: (" + MString() + rotation.x + " , " + MString() + rotation.y + " , " + MString() + rotation.z + ")");

			}
			else if (attName.find("scale") != std::string::npos)
			{
				double scale[3];
				transform.getScale(scale);
				MGlobal::displayInfo("NODE: " + transform.fullPathName() + "Scale changed: (" + MString() + scale[0] + " , " + MString() + scale[1] + " , " + MString() + scale[2] + ")");
			}
		}
	
		mAddMessage(transform.fullPathName().asChar(), msgEdited, nTransform);
	}
}
void cbNewNode(MObject& node, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
			{
				_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbMeshAttribute));
				_CBidArray.append(MPolyMessage::addPolyTopologyChangedCallback(node, cbPolyChanged));
				_CBidArray.append(MDGMessage::addNodeRemovedCallback(cbRemovedNode, "dependNode"));
				_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			}
		if (node.hasFn(MFn::kTransform))
		{
			MFnTransform trans(node);
			if (trans.childCount() > 0)
			{
				mAddNode(trans.fullPathName().asChar(), nTransform);
				_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbTransformModified));
				_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));

				MFnTransform trans(node);
				int pcount = trans.parentCount();
				MFnTransform parent(trans.parent(0));
				MGlobal::displayInfo("Transform parent: " + parent.fullPathName() + MString()+ pcount);
			}
			
		}
}
void cbMessageTimer(float elapsedTime, float lastTime, void *clientData)
{
	//MGlobal::displayInfo("BEEP " + MString() + _CBidArray.length() + " CALLBACKS");
	_msgVector.clear();
	MGlobal::displayInfo("--- MESSAGE UPDATE ------------------------------");
	while (!_msgQueue.empty())
	{
		switch (_msgQueue.front().msgType)
		{

		case (MessageType::msgAdded) :
			if (_msgQueue.front().nodeType == nMesh)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (New Mesh)");
				outMeshData(_msgQueue.front().nodeName);
			}
			else if(_msgQueue.front().nodeType == nTransform)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (New Transform)");
				TransData trans = outTransformData(_msgQueue.front().nodeName);
			}
			else if (_msgQueue.front().nodeType == nCamera)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (New Camera)");
			}
			
			
			break;

		case (MessageType::msgEdited) :
			if (_msgQueue.front().nodeType == nMesh)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Mesh Edited)");
			}
			else if (_msgQueue.front().nodeType == nTransform)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Transform Edited)");
			}
			break;
		case (MessageType::msgDeleted) :
			if (_msgQueue.front().nodeType == nMesh)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Mesh Deleted)");
			}
			else if (_msgQueue.front().nodeType == nTransform)
			{
				MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Transform Deleted)");
			}
			break;
		case (MessageType::msgRenamed) :
			break;
		}
		_msgQueue.pop();
	}
	MGlobal::displayInfo("-------------------------------------------------");

}

void cbCameraChange(MObject &cameraSetNode, unsigned int multiIndex, MObject &oldCamera, MObject &newCamera, void *clientData)
{
	MGlobal::displayInfo("CAMERAAAAAAAAAAAAAAA");
}

//void cbCameraChange(const MString &str, MObject &node, void *clientData)
//{
//	MGlobal::displayInfo("CAMERAAAAAAAAAAAAAAA");
//}

void loadScene()
{
	MStatus stat;
	MFn::Type filter = MFn::kCamera;
	
	MItDag dagIt(MItDag::kDepthFirst, filter, &stat);
	
	for (; !dagIt.isDone(); dagIt.next())
	{
		MDagPath dagPath;
		stat = dagIt.getPath(dagPath);
		MFnDagNode dagNode(dagPath, &stat);
		
		if (dagPath.hasFn(MFn::kCamera))
		{
			MObject parent = dagNode.parent(0);
			if (parent.hasFn(MFn::kTransform))
			{
				//MGlobal::displayInfo("FOUND CAMERA LOL " + dagPath.fullPathName());
				MFnTransform trans(parent);
				mAddNode(trans.fullPathName().asChar(), nTransform);
				_CBidArray.append(MNodeMessage::addAttributeChangedCallback(parent, cbTransformModified));
				MString panel;
				_CBidArray.append(MCameraSetMessage::addCameraChangedCallback(cbCameraChange));
			}
			mAddNode(dagPath.fullPathName().asChar(), nCamera);
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
	loadScene();
	debug = true;

	_CBidArray.append(MNodeMessage::addNameChangedCallback(MObject::kNullObj, &cbNameChange));
	_CBidArray.append(MDGMessage::addNodeAddedCallback(cbNewNode));
	_CBidArray.append(MTimerMessage::addTimerCallback(5, &cbMessageTimer));	
	
	return result;
	
}



EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	
	MGlobal::displayInfo("Level Editor plugin unloaded.");
	MMessage::removeCallbacks(_CBidArray);
	

	return MS::kSuccess;
}