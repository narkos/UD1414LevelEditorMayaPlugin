#include "Plugin.h"

MeshInfo outMeshData(std::string name)
{
	// Find mesh node in Dag
	MStatus			status;
	MString			_name(name.c_str());
	MSelectionList	sList;
	MDagPath		dagPath;

	if (MGlobal::getSelectionListByName(_name, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kMesh))
		{
			MGlobal::displayInfo("Mesh found: " + dagPath.fullPathName());
		}
	}

	MFnMesh			mNode(dagPath.node(), &status);
	MItMeshPolygon	polyIterator(dagPath.node(), &status);
	MeshInfo		outMesh;
	//MeshData		outMesh;
	
	// Variable declaration for mesh analysis
	const float*	vertices = mNode.getRawPoints(&status);
	const float*	normals = mNode.getRawNormals(&status);
	MFloatArray		uArray;
	MFloatArray		vArray;
	mNode.getUVs(uArray, vArray);

	MIntArray		triCount;
	MIntArray		triVerts;
	mNode.getTriangles(triCount, triVerts);
	MIntArray		triNorIndices;
	MIntArray		triUVIndices;
	
	int				totTris = 0;
	int				trisPerFace = 0;
	if (polyIterator.hasValidTriangulation())
	{
		//DO STUFF
		for (polyIterator.reset(); !polyIterator.isDone(); polyIterator.next())
		{

			polyIterator.numTriangles(trisPerFace);
			//totTris += trisPerFace;
			int uId0, uId1, uId2;
			cout << trisPerFace;
			if (trisPerFace == 1)
			{	
				triNorIndices.append(polyIterator.normalIndex(0, &status));
				triNorIndices.append(polyIterator.normalIndex(1, &status));
				triNorIndices.append(polyIterator.normalIndex(2, &status));

				polyIterator.getUVIndex(0, uId0);
				polyIterator.getUVIndex(1, uId1);
				polyIterator.getUVIndex(2, uId2);
				triUVIndices.append(uId0);
				triUVIndices.append(uId1);
				triUVIndices.append(uId2);
			}
			else
			{
				triNorIndices.append(polyIterator.normalIndex(0, &status));
				triNorIndices.append(polyIterator.normalIndex(1, &status));
				triNorIndices.append(polyIterator.normalIndex(3, &status));
				triNorIndices.append(polyIterator.normalIndex(3, &status));
				triNorIndices.append(polyIterator.normalIndex(1, &status));
				triNorIndices.append(polyIterator.normalIndex(2, &status));

				polyIterator.getUVIndex(0, uId0);
				polyIterator.getUVIndex(1, uId1);
				polyIterator.getUVIndex(3, uId2);
				triUVIndices.append(uId0);
				triUVIndices.append(uId1);
				triUVIndices.append(uId2);

				polyIterator.getUVIndex(3, uId0);
				polyIterator.getUVIndex(1, uId1);
				polyIterator.getUVIndex(2, uId2);
				triUVIndices.append(uId0);
				triUVIndices.append(uId1);
				triUVIndices.append(uId2);
				}
		}
	}

	if (mNode.parent(0).hasFn(MFn::kTransform))
	{
		MFnTransform mTrans(mNode.parent(0));
		outMesh.transformName = mTrans.fullPathName().asChar();
		MGlobal::displayInfo(outMesh.transformName.c_str());
	}

	outMesh.meshData.vertCount = mNode.numVertices();
	outMesh.meshData.normalCount = mNode.numNormals();
	outMesh.meshData.UVCount = mNode.numUVs();

	outMesh.meshData.vertices = vertices;
	outMesh.meshData.normals = normals;

	outMesh.meshData.triPerFace = new int[triCount.length()];
	triCount.get(outMesh.meshData.triPerFace);

	outMesh.meshData.uv = new float2[mNode.numUVs()];
	for (int i = 0; i < outMesh.meshData.UVCount; i++)
	{
		outMesh.meshData.uv[i][0] = uArray[i];
		outMesh.meshData.uv[i][1] = vArray[i];
	}

	outMesh.meshData.indCount = triVerts.length();
	outMesh.meshData.triCount = triCount.length();

	outMesh.meshData.triIndices = new int[outMesh.meshData.indCount];
	 triVerts.get(outMesh.meshData.triIndices);

	outMesh.meshData.norIndices = new int[triNorIndices.length()];
	triNorIndices.get(outMesh.meshData.norIndices);

	outMesh.meshData.UVIndices = new int[triUVIndices.length()];
	triUVIndices.get(outMesh.meshData.UVIndices);

	if (debug)
	{
		MGlobal::displayInfo("outMesh Name: " + MString(name.c_str()));
		MGlobal::displayInfo("outMesh Transform Name: " + MString(outMesh.transformName.c_str()));
		MGlobal::displayInfo("outMesh Vert/Nor/UV Count: " + MString() + outMesh.meshData.vertCount + " / " + MString() + outMesh.meshData.normalCount + " / " + MString() + outMesh.meshData.UVCount);
		MGlobal::displayInfo("outMesh Indices / Triangle Count: " + MString() + outMesh.meshData.indCount + " / " + MString() + outMesh.meshData.triCount);
		MString triFaceStr = " ( ";
		MString triIndStr = "";
		for (int i = 0; i < triCount.length(); i++)
		{

			if (i != triCount.length() - 1)
			{
				triFaceStr += MString() + outMesh.meshData.triPerFace[i] + " , ";
				//triIndStr += MString() + outMesh.triIndices[i] + "," + MString() + outMesh.norIndices[i] + "," + MString() + outMesh.UVIndices[i] + ")";
			}

			else
			{
				triFaceStr += MString() + outMesh.meshData.triPerFace[i];
				//triIndStr += MString() + outMesh.triIndices[i] + "," + MString() + outMesh.norIndices[i] + "," + MString() + outMesh.UVIndices[i] + ")";
			}

		}
		MGlobal::displayInfo("outMesh Tris per Polygon: " + triFaceStr + " )");
		for (int i = 0; i + 3 < outMesh.meshData.indCount; i += 3)
		{
			triIndStr += "(";
			triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i] + "," + MString() + outMesh.meshData.norIndices[i] + "," + MString() + outMesh.meshData.UVIndices[i] + ")");
			triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i + 1] + "," + MString() + outMesh.meshData.norIndices[i + 1] + "," + MString() + outMesh.meshData.UVIndices[i + 1] + ")");
			triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i + 2] + "," + MString() + outMesh.meshData.norIndices[i + 2] + "," + MString() + outMesh.meshData.UVIndices[i + 2] + ")");
			triIndStr += ")\n";
		}

		MGlobal::displayInfo("outMesh Indices per triangle: " + triIndStr);
	}
	
	return outMesh;
}

TransformInfo outTransformData(std::string name)
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
			//MGlobal::displayInfo("Transform found: " + dagPath.fullPathName());
		}

	}

	MFnTransform mNode(dagPath.node(), &result);
	TransformInfo outTrans;
	if (result)
	{
		
		outTrans.parentName[0] = 0;

		std::string attName(mNode.fullPathName().asChar());
		MVector trans = mNode.getTranslation(MSpace::kPostTransform, &result);
		outTrans.transformData.translation[0] = trans.x;
		outTrans.transformData.translation[1] = trans.y;
		outTrans.transformData.translation[2] = trans.z;

		MEulerRotation rotation;
		mNode.getRotation(rotation);
		outTrans.transformData.rotation[0] = rotation.x;
		outTrans.transformData.rotation[1] = rotation.y;
		outTrans.transformData.rotation[2] = rotation.z;

		double scale[3];
		mNode.getScale(scale);
		outTrans.transformData.scale[0] = scale[0];
		outTrans.transformData.scale[1] = scale[1];
		outTrans.transformData.scale[2] = scale[2];

		outTrans.nodeName = attName;
		//outTrans.parentName = getParentName()

		/*MGlobal::displayInfo("TRANSFORM INNER DATA: " + MString(outTrans.nodeName.c_str()));
		MGlobal::displayInfo("Pos: " + MString() + trans.x + " " + MString() + trans.y + " " + MString() + trans.z);
		MGlobal::displayInfo("Rot: " + MString() + rotation.x + " " + MString() + rotation.y + " " + MString() + rotation.z);
		MGlobal::displayInfo("Sca: " + MString() + scale[0] + " " + MString() + scale[1] + " " + MString() + scale[2]);*/
		return outTrans;
	}
	return outTrans;
}

CameraInfo outCameraData(std::string name)
{
	MStatus result;
	MString cname(name.c_str());
	MSelectionList sList;
	MDagPath dagPath;
	CameraInfo outCam;
	if (MGlobal::getSelectionListByName(cname, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kCamera))
		{
			MGlobal::displayInfo("Camera found: " + dagPath.fullPathName());
			MFnCamera mNode(dagPath.node(), &result);
			MFloatMatrix projMtx(mNode.projectionMatrix());
			//MGlobal::displayInfo(MString() + projMtx);
			MPoint pos = mNode.eyePoint(MSpace::Space::kWorld);
			MFloatVector dir = mNode.viewDirection(MSpace::Space::kWorld);
			MFloatVector up = mNode.upDirection(MSpace::Space::kWorld);
			MFloatVector right = mNode.rightDirection(MSpace::Space::kWorld);
			MGlobal::displayInfo("Pos(" + MString() + pos.x + " , " + MString() + pos.y + " , " + MString() + pos.z + ")");
			MGlobal::displayInfo("Dir(" + MString() + dir.x + " , " + MString() + dir.y + " , " + MString() + dir.z + ")");
			MGlobal::displayInfo("Up(" + MString() + up.x + " , " + MString() + up.y + " , " + MString() + up.z + ")");
			bool isOrtho = mNode.isOrtho();
			double fov = mNode.horizontalFieldOfView();
			MGlobal::displayInfo("Fov: " + MString() + fov);
			MGlobal::displayInfo("Orthographic: " + MString() + isOrtho);
			
			outCam.camData.isOrtho = isOrtho;
			outCam.camData.hAngle = fov;
			for (int i = 0; i < 3; i++)
			{
				outCam.camData.rightVector[i] = right[i];
				outCam.camData.target[i] = dir[i];
				outCam.camData.upVector[i] = up[i];
			}
		}

	}


	return outCam;
}

LightInfo outLightData(std::string name)
{
	MStatus result;
	MString lName(name.c_str());
	MSelectionList sList;
	MDagPath dagPath;
	LightInfo outLight;
	MGlobal::displayInfo(MString() + outLight.lightData.colorDiffuse[1]);
	if (MGlobal::getSelectionListByName(lName, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kLight))
		{
			MFnLight baseLight(dagPath);
			
			// Get diffuse color data
			MColor diffColor = baseLight.color();
			float RGBColor[3];
			diffColor.get(MColor::MColorType::kRGB, RGBColor[0], RGBColor[1], RGBColor[2]);
			std::copy(RGBColor, RGBColor+3, outLight.lightData.colorDiffuse);
			MGlobal::displayInfo("Light Color Diffuse: " + MString() + outLight.lightData.colorDiffuse[0] + " " + MString() + outLight.lightData.colorDiffuse[1] + " " + MString() + outLight.lightData.colorDiffuse[2]);
			//Get light intensity
			outLight.lightData.intensity = baseLight.intensity();
			MGlobal::displayInfo("Light intensity: " + MString() + outLight.lightData.intensity);


			if (dagPath.hasFn(MFn::kDirectionalLight))
			{
				outLight.lightData.type = 1;
				MFnDirectionalLight dLight(dagPath); // Don't think this is necessary dude to probably all relevant data exist within MFnLight
				MFloatVector dir(baseLight.lightDirection(0, MSpace::kWorld, &result));
				outLight.lightData.direction[0] = dir.x;
				outLight.lightData.direction[1] = dir.y;
				outLight.lightData.direction[2] = dir.z;
				if(result)
					MGlobal::displayInfo("Light direction: " + MString() + dir.x + " " + MString() + dir.y + " " + MString() + dir.z);
			}
			else if (dagPath.hasFn(MFn::kSpotLight))
			{
				outLight.lightData.type = 2;
				MFnSpotLight sLight(dagPath);
				outLight.lightData.decayType =	sLight.decayRate();
				outLight.lightData.coneAngle =	sLight.coneAngle();
				outLight.lightData.penumAgle =	sLight.penumbraAngle();
				outLight.lightData.dropOff =	sLight.dropOff();

				MFloatVector dir(baseLight.lightDirection(0, MSpace::kWorld, &result));
				outLight.lightData.direction[0] = dir.x;
				outLight.lightData.direction[1] = dir.y;
				outLight.lightData.direction[2] = dir.z;
			}
			else if (dagPath.hasFn(MFn::kPointLight))
			{
				outLight.lightData.type = 3;
				MFnPointLight pLight(dagPath);
				outLight.lightData.decayType = pLight.decayRate();
			}
		}
	}
	return outLight;
}

MaterialInfo outMaterialData(std::string name)
{
	return MaterialInfo();
}

std::string getParentName(MPlug& plug)
{
	MPlug p = plug;
	if (p.parent().asMObject().hasFn(MFn::kTransform))
	{
		MFnTransform tr(plug.parent());
		return tr.fullPathName().asChar();
	}
	else
		return "";
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
		MessageInfo tMsg{ name, nodeType,msgType };
		_msgVector.push_back(tMsg);
		_msgQueue.push(tMsg);
	}
}

void mAddNode(std::string name, std::string parentName, int type, int vertCount = 0, char* childname=nullptr)
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
				MeshInfo mesh{ name, parentName };
				_meshVector.push_back(mesh);
				mAddMessage(name, msgAdded, nMesh);
				MGlobal::displayInfo("Added mesh: " + MString(name.c_str()) + "with " + MString() + vertCount + " vertices.");
			}
		}
		else if (type == nTransform)
		{
			if (_transVector.size() > 0)
			{
				for (std::vector<TransformInfo>::size_type i = 0; i != _transVector.size(); i++)
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
				TransformInfo trans{ name};
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
			if (_lightVector.size() > 0)
				for (std::vector<LightInfo>::size_type i = 0; i != _lightVector.size(); i++)
				{

				}
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
			std::string parentname = getParentName(plug_1);
			std::string tmpName = mNode.fullPathName().asChar();
			mAddNode(tmpName.c_str(), parentname.c_str(), nMesh, vertices.length());
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
				MGlobal::displayInfo("VERTS VERTS VERTS");
				MPointArray verts;
				mesh.getPoints(verts, MSpace::kPostTransform);
			}
			
		}
	}
}

void cbLightAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	MFnLight light(plug_1.node());

	MString lightName(light.fullPathName());
	outLightData(lightName.asChar());
	/*else
	{ }*/
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

void cbCamAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	MGlobal::displayInfo("--------------- cam attribute");
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

			mAddNode(trans.fullPathName().asChar(), "", nTransform);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbTransformModified));
			_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));

			MFnTransform trans(node);
			int pcount = trans.parentCount();
			MFnTransform parent(trans.parent(0));
			MGlobal::displayInfo("Transform parent: " + parent.fullPathName() + MString()+ pcount);
		}
	}
	if (node.hasFn(MFn::kLight))
	{
		MGlobal::displayInfo("Light created");
		
		MFnLight light(node);
		//outLightData(light.fullPathName().asChar());
		if (node.hasFn(MFn::kDirectionalLight))
		{
			MGlobal::displayInfo("Directional");
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbLightAttribute));
		}
		else if (node.hasFn(MFn::kSpotLight))
		{
			MGlobal::displayInfo("Spot");
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbLightAttribute));
		}
		else if (node.hasFn(MFn::kPointLight))
		{
			MGlobal::displayInfo("Point");
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbLightAttribute));
		}
	}
	if (node.apiType() == MFn::kLambert)
	{
		MGlobal::displayInfo("Material added");
	}
}
void cbMessageTimer(float elapsedTime, float lastTime, void *clientData)
{
	//MGlobal::displayInfo("BEEP " + MString() + _CBidArray.length() + " CALLBACKS");
	_msgVector.clear();
	int msgCount = _msgQueue.size();
	MGlobal::displayInfo("--- MESSAGE UPDATE (" +MString()+msgCount +" Messages) ------------------------");
	bool run = true;
	int msgID = 0;
	while (!_msgQueue.empty() && run == true)
	{
		
		MGlobal::displayInfo("\n****** MESSAGE START (ID: " + MString() + msgID + ") **********************");
		switch (_msgQueue.front().nodeType)
		{
		case(NodeType::nMesh) :
		{
			MeshInfo outMesh = outMeshData(_msgQueue.front().nodeName);
			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) ("+msgTypeVector[_msgQueue.front().msgType].c_str()+" Mesh)");
			if (fileMap.tryWriteMesh(_msgQueue.front(), outMesh) == true)
			{
				
				delete[] outMesh.meshData.uv;
				delete[] outMesh.meshData.triIndices;
				delete[] outMesh.meshData.norIndices;
				delete[] outMesh.meshData.UVIndices;
				delete[] outMesh.meshData.triPerFace;
				//delete[] outMesh.vertices;
				MGlobal::displayInfo("* WOW EN VERTEX: " + MString() + fileMap.test[4]);
				MGlobal::displayInfo("*** MESSAGE Result( " + MString(_msgQueue.front().nodeName.c_str()) + " ): Success");
				delete[] fileMap.test;
				_msgQueue.pop();
			}
			else
			{
				MGlobal::displayInfo("*** Message result(" + MString(_msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
				run = false;
			}
			//MGlobal::displayInfo("-------------------------------------------------");
			break;
		}
		case(NodeType::nTransform) :
		{
			TransformInfo outTrans = outTransformData(_msgQueue.front().nodeName);
			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[_msgQueue.front().msgType].c_str() + " Transform)");

			if (fileMap.tryWriteTransform(_msgQueue.front(), outTrans) == true)
				{
				//#if defined(DEBUG) || defined(_DEBUG)
					MGlobal::displayInfo("*** MESSAGE Result( " + MString(_msgQueue.front().nodeName.c_str()) + " ): Success");
				//#endif
					_msgQueue.pop();
				}
				else
				{
					MGlobal::displayInfo("*** Message result(" + MString(_msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
					run = false;
				}
								
				break;

			break;
		}
		case(NodeType::nCamera) :
		{
			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[_msgQueue.front().msgType].c_str() + " Camera)");
		

			_msgQueue.pop();
			break;
		}
		case(NodeType::nLight) :
		{
			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[_msgQueue.front().msgType].c_str() + " Light)");

			_msgQueue.pop();
			break;
		}
		case(NodeType::nMaterial) :
		{
			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[_msgQueue.front().msgType].c_str() + " Material)");
			_msgQueue.pop();
			break;
		}
		}
		msgID++;
		MGlobal::displayInfo("*** MESSAGE STOP *************************");
	}
								  //	switch (_msgQueue.front().msgType)
								  //	{

								  //	case (MessageType::msgAdded) :
								  //		if (_msgQueue.front().nodeType == nMesh)
								  //		{
								  //			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) (New Mesh)");
								  //			MeshInfo  outMesh = outMeshData(_msgQueue.front().nodeName);
								  //			if (fileMap.tryWriteMesh(_msgQueue.front(), outMesh) == true)
								  //			{
								  //				delete[] outMesh.meshData.uv;
								  //				delete[] outMesh.meshData.triIndices;
								  //				delete[] outMesh.meshData.norIndices;
								  //				delete[] outMesh.meshData.UVIndices;
								  //				delete[] outMesh.meshData.triPerFace;
								  //				//delete[] outMesh.vertices;
								  //				_msgQueue.pop();
								  //			}
								  //			//fileMap.createHeaderMesh(_msgQueue.front(),outMesh);
								  //			break;
								  //		}
								  //		else if(_msgQueue.front().nodeType == nTransform)
								  //		{
								  //			MGlobal::displayInfo("*** MESSAGE: ( " + MString(_msgQueue.front().nodeName.c_str()) + " ) (New Transform)");
								  //			TransformInfo outTrans = outTransformData(_msgQueue.front().nodeName);
								  //			if (fileMap.tryWriteTransform(_msgQueue.front(), outTrans) == true)
								  //			{
								  //			#if defined(DEBUG) || defined(_DEBUG)
								  //				MGlobal::displayInfo("*** MESSAGE Result( " + MString(_msgQueue.front().nodeName.c_str()) + " ): Success");
								  //			#endif
								  //				_msgQueue.pop();
								  //			}
								  //			else
								  //			{
								  //				MGlobal::displayInfo("*** Message result(" + MString(_msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
								  //				run = false;
								  //			}
								  //				
								  //			break;
								  //		}
								  //		else if (_msgQueue.front().nodeType == nCamera)
								  //		{
								  //			MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (New Camera)");
								  //			_msgQueue.pop();
								  //		}
								  //		
								  //		
								  //		break;
								  //	case (MessageType::msgEdited) :
								  //		if (_msgQueue.front().nodeType == nMesh)
								  //		{
								  //			MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Mesh Edited)");
								  //			_msgQueue.pop();
								  //		}
								  //		else if (_msgQueue.front().nodeType == nTransform)
								  //		{
								  //			MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Transform Edited)");
								  //			outTransformData(_msgQueue.front().nodeName);
								  //			_msgQueue.pop();
								  //		}
								  //		break;
								  //	case (MessageType::msgDeleted) :
								  //		if (_msgQueue.front().nodeType == nMesh)
								  //		{
								  //			MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Mesh Deleted)");
								  //			_msgQueue.pop();
								  //		}
								  //		else if (_msgQueue.front().nodeType == nTransform)
								  //		{
								  //			MGlobal::displayInfo("MESSAGE: " + MString(_msgQueue.front().nodeName.c_str()) + " (Transform Deleted)");
								  //			_msgQueue.pop();
								  //		}
								  //		break;
								  //	case (MessageType::msgRenamed) :
								  //		_msgQueue.pop();
								  //		break;
								  //	}
								  //	msgID++;
								  //	MGlobal::displayInfo("*** MESSAGE STOP *************************");
								  //	//_msgQueue.pop();
								  //}
}

void cbCameraChange(MObject &cameraSetNode, unsigned int multiIndex, MObject &oldCamera, MObject &newCamera, void *clientData)
{
	MGlobal::displayInfo("CAMERAAAAAAAAAAAAAAA");
}

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
		std::string transname;
		if (dagPath.hasFn(MFn::kCamera))
		{
			
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(dagPath.node(), cbCamAttribute));
			outCameraData(dagPath.fullPathName().asChar());
			MObject parent = dagNode.parent(0);
			if (parent.hasFn(MFn::kTransform))
			{
				//MGlobal::displayInfo("FOUND CAMERA LOL " + dagPath.fullPathName());
				MFnTransform trans(parent);
				transname = trans.fullPathName().asChar();
				mAddNode(trans.fullPathName().asChar(),"", nTransform);
				_CBidArray.append(MNodeMessage::addAttributeChangedCallback(parent, cbTransformModified));

				MString panel;
				_CBidArray.append(MCameraSetMessage::addCameraChangedCallback(cbCameraChange));
			}
			mAddNode(dagPath.fullPathName().asChar(), transname.c_str(), nCamera);
		}

	}
	filter = MFn::kLambert;
	MItDependencyNodes itDep(MFn::kLambert);
	//MItDag dagIt2(MItDag::kDepthFirst, filter, &stat);
	while(!itDep.isDone())
	{
		switch (itDep.item().apiType())
		{
		case MFn::kPhong:
		{
			MGlobal::displayInfo("Phong phong phong");
			break;
		}
		case MFn::kLambert:
		{
			MGlobal::displayInfo("Lambert lambert lambert");
			break;
		}
		case MFn::kBlinn:
		{
			MGlobal::displayInfo("Blinn blinn blinn");
			break;
		}
		default:
			break;
		}
		itDep.next();
	
	}


}
void cbCameraPanel(const MString &str, MObject &node, void *clientData)
{
	if (node.hasFn(MFn::kCamera))
	{
		MFnCamera currCam(node);
		MGlobal::displayInfo("Current Camera: " + currCam.fullPathName() );
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


	fileMap.CreateFileMaps();

	MGlobal::displayInfo("Level Editor plugin loaded.");
	loadScene();
	debug = true;

	msgTypeVector.push_back("woah");
	msgTypeVector.push_back("Added");
	msgTypeVector.push_back("Edited");
	msgTypeVector.push_back("Deleted");
	msgTypeVector.push_back("Renamed");


	_CBidArray.append(MNodeMessage::addNameChangedCallback(MObject::kNullObj, &cbNameChange));
	_CBidArray.append(MDGMessage::addNodeAddedCallback(cbNewNode));
	_CBidArray.append(MTimerMessage::addTimerCallback(5, &cbMessageTimer));	
	_CBidArray.append(MUiMessage::addCameraChangedCallback("modelPanel4", cbCameraPanel));
	_CBidArray.append(MUiMessage::addCameraChangedCallback("modelPanel1", cbCameraPanel));
	_CBidArray.append(MUiMessage::addCameraChangedCallback("modelPanel2", cbCameraPanel));	
	_CBidArray.append(MUiMessage::addCameraChangedCallback("modelPanel3", cbCameraPanel));
	

	return result;
	
}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);
	
	MGlobal::displayInfo("Level Editor plugin unloaded.");
	MMessage::removeCallbacks(_CBidArray);
	

	return MS::kSuccess;
}