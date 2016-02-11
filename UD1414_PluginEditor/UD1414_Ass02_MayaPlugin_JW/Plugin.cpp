#include "Plugin.h"
#include "Commands.h"

// OUT DATA FUNCTIONS
void fFillAttributesList()
{
	m_attributeVector.push_back(Attribute("drmRender", "bool", "1"));
	m_attributeVector.push_back(Attribute("drmBBox", "bool", "0"));
	m_attributeVector.push_back(Attribute("drmCollidable", "bool", "1"));	
	m_attributeVector.push_back(Attribute("drmInteractable", "bool", "0"));
    m_attributeVector.push_back(Attribute("drmCheckPointID", "long", "-1"));
    m_attributeVector.push_back(Attribute("drmSpawnPointID", "long", "-1"));
    m_attributeVector.push_back(Attribute("drmLevelStartEnd", "long", "0"));
    m_attributeVector.push_back(Attribute("drmAIground", "bool", "0"));

    m_attributeVector.push_back(Attribute("drmFrequencyAffected", "bool", "0"));
	m_attributeVector.push_back(Attribute("drmInteractableStartPos", "double3", "0 0 0"));
	m_attributeVector.push_back(Attribute("drmInteractableEndPos", "double3", "0 0 0"));
	m_attributeVector.push_back(Attribute("drmInteractableOffset", "double2", "0 0"));
	m_attributeVector.push_back(Attribute("drmInteractableStartSpeed", "double", "0"));
	m_attributeVector.push_back(Attribute("drmInteractableEndSpeed", "double", "0"));
	/*m_attributeVector.push_back(Attribute("drmInteractIntervalX", "\"float\"", "0"));
	m_attributeVector.push_back(Attribute("drmInteractIntervalY", "\"float\"", "0"));
	m_attributeVector.push_back(Attribute("drmInteractIntevalZ", "\"float\"", "0"));*/
	m_attributeVector.push_back(Attribute("drmIsPotentialFieldCollidable", "bool", "1"));
	m_attributeVector.push_back(Attribute("drmPotentialFieldID", "long", "-1"));
	m_attributeVector.push_back(Attribute("drmPotentialFieldNeighbour1", "long", "-1"));
	m_attributeVector.push_back(Attribute("drmPotentialFieldNeighbour2", "long", "-1"));
	m_attributeVector.push_back(Attribute("drmPotentialFieldNeighbour3", "long", "-1"));
	m_attributeVector.push_back(Attribute("drmPotentialFieldNeighbour4", "long", "-1"));
	m_attributeVector.push_back(Attribute("drmPotentialFieldNeighbour5", "long", "-1"));

	m_attributeVector.push_back(Attribute("drmIsSpawner", "bool", "0"));
	m_attributeVector.push_back(Attribute("drmSpawnsMax", "long", "1"));
	m_attributeVector.push_back(Attribute("drmSpawnsMaxAlive", "long", "1"));
	m_attributeVector.push_back(Attribute("drmSpawnTypeBlueprint", "long", "-1"));
    m_attributeVector.push_back(Attribute("drmSpawnFrequency", "double", "0"));

    m_attributeVector.push_back(Attribute("drmIsStatic", "bool", "1"));
    m_attributeVector.push_back(Attribute("drmPhysicsType", "long", "-1"));
	
	m_attributeVector.push_back(Attribute("drmTypeBlueprint", "long", "0"));
	m_attributeVector.push_back(Attribute("drmIsDangerous", "bool", "0"));
}

bool fAddAttributes(MFnTransform& inTrans)
{
	for (std::vector<Attribute>::size_type i = 0; i != m_attributeVector.size(); i++)
	{
		MStatus res;
		MPlug testPlug = inTrans.findPlug(MString(m_attributeVector[i].name.c_str()), &res);
		if (res)
		{
			//FileMapping::printInfo("BBox exists!");
			if (!testPlug.isKeyable())
			{
				MString myCommand2 = "setAttr -e -keyable true " + inTrans.fullPathName() + "."+MString(m_attributeVector[i].name.c_str());
				MGlobal::executeCommandOnIdle(myCommand2);
			}
		}
		else
		{
			if (m_attributeVector[i].type.find("3") != std::string::npos)
			{
				MString myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "\" -at " + MString(m_attributeVector[i].type.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "X\" -at double -p " + MString(m_attributeVector[i].name.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "Y\" -at double -p " + MString(m_attributeVector[i].name.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "Z\" -at double -p " + MString(m_attributeVector[i].name.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "setAttr -type double3 " + inTrans.fullPathName() +"."+m_attributeVector[i].name.c_str()+ " " + m_attributeVector[i].value.c_str();
				MGlobal::executeCommandOnIdle(myCommand);
				
			}
			else if (m_attributeVector[i].type.find("2") != std::string::npos)
			{
				MString myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "\" -at " + MString(m_attributeVector[i].type.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "X\" -at double -p " + MString(m_attributeVector[i].name.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "Y\" -at double -p " + MString(m_attributeVector[i].name.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				myCommand = "setAttr -type double2 " + inTrans.fullPathName() + "." + m_attributeVector[i].name.c_str() + " " + m_attributeVector[i].value.c_str();
				MGlobal::executeCommandOnIdle(myCommand);

			}
			else
			{
				MString myCommand = "addAttr -ln \"" + MString(m_attributeVector[i].name.c_str()) + "\" -at " + MString(m_attributeVector[i].type.c_str()) + " -dv " + MString(m_attributeVector[i].value.c_str()) + " " + inTrans.fullPathName();
				MGlobal::executeCommandOnIdle(myCommand);
				MString myCommand2 = "setAttr -e -keyable true " + inTrans.fullPathName() + "." + MString(m_attributeVector[i].name.c_str());
				MGlobal::executeCommandOnIdle(myCommand2);
			}
			//FileMapping::printInfo("BBox does NOT exist!");
			
		}
	}
	return true;
}

MeshInfo outMeshData(std::string name, bool getDynamicData)
{
	// Find mesh node in Dag
	MStatus			result;
	MString			_name(name.c_str());
	MSelectionList	sList;
	MDagPath		dagPath;

	if (MGlobal::getSelectionListByName(_name, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kMesh))
		{
			FileMapping::printInfo("Mesh found: " + dagPath.fullPathName());
		}
	}

	MFnMesh			mNode(dagPath.node(), &result);
	MItMeshPolygon	polyIterator(dagPath.node(), &result);
	MeshInfo		outMesh;

	// Variable declaration for mesh analysis
	const float*	vertices = mNode.getRawPoints(&result);
	const float*	normals = mNode.getRawNormals(&result);
	MFloatArray		uArray;
	MFloatArray		vArray;
	mNode.getUVs(uArray, vArray);

	MIntArray		triCount;
	MIntArray		triVerts;
	mNode.getTriangles(triCount, triVerts);
	MIntArray		triNorIndices;
	MIntArray		triUVIndices;

	int				totTris = 0;
	int				triCountThisPoly = 0;
	if (polyIterator.hasValidTriangulation())
	{
		//DO STUFF
		for (polyIterator.reset(); !polyIterator.isDone(); polyIterator.next())
		{

			polyIterator.numTriangles(triCountThisPoly);
			int uId0, uId1, uId2;
			cout << triCountThisPoly;
			if (triCountThisPoly == 1)
			{
				triNorIndices.append(polyIterator.normalIndex(0, &result));
				triNorIndices.append(polyIterator.normalIndex(1, &result));
				triNorIndices.append(polyIterator.normalIndex(2, &result));

				polyIterator.getUVIndex(0, uId0);
				polyIterator.getUVIndex(1, uId1);
				polyIterator.getUVIndex(2, uId2);
				triUVIndices.append(uId0);
				triUVIndices.append(uId1);
				triUVIndices.append(uId2);
			}
			else
			{
				unsigned int faceindex = polyIterator.index();
				MIntArray fNormals;
				mNode.getFaceNormalIds(faceindex, fNormals);
				for (int i = 0; i < fNormals.length(); i++)
				{
					//FileMapping::printInfo("FACE NORMALS " + MString() + fNormals[i]);
				}

				MObject face(polyIterator.currentItem());
				//MItMeshFaceVertex faceIterator(dagPath, face, &result);
				//int o = 0;
				//while (!faceIterator.isDone())
				//{
				//	//FileMapping::printInfo("WOW " + MString() + o + " UH " + MString() + faceIterator.faceId());
				//	o++;
				//	faceIterator.next();

				//}
				MIntArray indList;
				MIntArray locInd;
				polyIterator.getVertices(locInd);
				/*for (int i = 0; i < locInd.length(); i++)
				{

				}*/
				MPointArray vList;

				int numTriangles;

				MIntArray vIndList;

				polyIterator.getTriangles(vList, indList, MSpace::kWorld);
				polyIterator.getVertices(vIndList);
				bool firstIteration = true;
				int firstValue;
				int lastValue;
				int vertsThisFace = locInd.length();
				int midValue = vertsThisFace - 1;
				//FileMapping::printInfo("LENGTH " + MString() + vertsThisFace);
				if (triCountThisPoly > 2)
				{
					for (int i = 0; i < triCountThisPoly; i++)
					{

						if (firstIteration)
						{
							triNorIndices.append(polyIterator.normalIndex(0, &result));
							triNorIndices.append(polyIterator.normalIndex(1, &result));
							triNorIndices.append(polyIterator.normalIndex(midValue - 2, &result));

							polyIterator.getUVIndex(0, uId0);
							polyIterator.getUVIndex(1, uId1);
							polyIterator.getUVIndex(midValue, uId2);
							triUVIndices.append(uId0);
							triUVIndices.append(uId1);
							triUVIndices.append(uId2);

							firstValue = 1;
							lastValue = midValue;
							firstIteration = false;
						}
						else if (triCountThisPoly == 2)
						{
							triNorIndices.append(polyIterator.normalIndex(lastValue, &result));
							triNorIndices.append(polyIterator.normalIndex(firstValue, &result));
							triNorIndices.append(polyIterator.normalIndex(3, &result));

							polyIterator.getUVIndex(lastValue, uId0);
							polyIterator.getUVIndex(firstValue, uId1);
							polyIterator.getUVIndex(2, uId2);
							triUVIndices.append(uId0);
							triUVIndices.append(uId1);
							triUVIndices.append(uId2);

						}
						else
						{
							if (lastValue - 1 >= 0)
							{
								if (lastValue - 1 != midValue)
								{
									lastValue--;
								}
								else if (lastValue - 2 >= 0)
								{
									lastValue -= 2;
								}
								else
								{
									lastValue = midValue + 1;
								}
							}
							else
							{
								lastValue = midValue + 1;
							}
							triNorIndices.append(polyIterator.normalIndex(firstValue, &result));
							triNorIndices.append(polyIterator.normalIndex(lastValue, &result));
							triNorIndices.append(polyIterator.normalIndex(midValue - 2, &result));
							if (lastValue - 1 >= 0)
							{
								if (lastValue - 1 != midValue)
								{
									lastValue--;
								}
								else if (lastValue - 2 >= 0)
								{
									lastValue -= 2;
								}
								else
								{
									lastValue = midValue + 1;
								}
							}
							else
							{
								lastValue = midValue + 1;
							}
							polyIterator.getUVIndex(firstValue, uId0);
							polyIterator.getUVIndex(lastValue, uId1);
							polyIterator.getUVIndex(midValue, uId2);
							triUVIndices.append(uId0);
							triUVIndices.append(uId1);
							triUVIndices.append(uId2);

							firstValue = lastValue;
							lastValue -= 2;
							//lastValue = i + 1;
						}
						//midValue += 2;
						//MGlobal::displayInfo("VERT ID: " + MString() + vIndList[i] +" "+ MString()+polyIterator.index());
					}
				}
				else
				{
					triNorIndices.append(polyIterator.normalIndex(0, &result));
					triNorIndices.append(polyIterator.normalIndex(1, &result));
					triNorIndices.append(polyIterator.normalIndex(3, &result));
					triNorIndices.append(polyIterator.normalIndex(3, &result));
					triNorIndices.append(polyIterator.normalIndex(1, &result));
					triNorIndices.append(polyIterator.normalIndex(2, &result));

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
	}

	if (mNode.parent(0).hasFn(MFn::kTransform))
	{
		outMesh.transformCount = mNode.parentCount();
		for (int i = 0; i < outMesh.transformCount; i++)
		{
			MFnTransform mTrans(mNode.parent(i), &result);
			if (!result)
			{
				FileMapping::printError(MString(name.c_str()) + " parent not found!");
			}
			else
			{
				outMesh.transformName.push_back(mTrans.fullPathName().asChar()) ;
				FileMapping::printInfo("Parent " +MString()+i+": " + outMesh.transformName[i].c_str());
			}
		}
	
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

	// Prints general mesh data
	if (true)
	{
		FileMapping::printInfo("outMesh Name: " + MString(name.c_str()));
		//FileMapping::printInfo("outMesh Transform Name: " + MString(outMesh.transformName.c_str()));
		FileMapping::printInfo("outMesh Vert/Nor/UV Count: " + MString() + outMesh.meshData.vertCount + " / " + MString() + outMesh.meshData.normalCount + " / " + MString() + outMesh.meshData.UVCount);
		FileMapping::printInfo("outMesh Indices / Triangle Count: " + MString() + outMesh.meshData.indCount + " / " + MString() + triUVIndices.length() + " / " + MString() + totTris);
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
		FileMapping::printInfo("outMesh Tris per Polygon: " + triFaceStr + " )");

		// Prints vertex data
		bool dbug2 = false;
		MString iDataStr = "";
		if (dbug2)
		{

			for (int i = 0; i + 3 < outMesh.meshData.indCount; i += 3)
			{
				triIndStr += "(";
				triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i] + "," + MString() + outMesh.meshData.norIndices[i] + "," + MString() + outMesh.meshData.UVIndices[i] + ")");
				triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i + 1] + "," + MString() + outMesh.meshData.norIndices[i + 1] + "," + MString() + outMesh.meshData.UVIndices[i + 1] + ")");
				triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i + 2] + "," + MString() + outMesh.meshData.norIndices[i + 2] + "," + MString() + outMesh.meshData.UVIndices[i + 2] + ")");

				triIndStr += ")\n";
			}


			/*for (int i = 0; i < outMesh.meshData.normalCount*3; i+=3)
			{
			iDataStr += "Pos ";
			iDataStr += "(" + MString() + outMesh.meshData.vertices[i] + " , ";
			iDataStr += MString() + outMesh.meshData.vertices[i+1] + " , ";
			iDataStr += MString() + outMesh.meshData.vertices[i+2] + ")";

			iDataStr += "Nor ";
			iDataStr += "(" + MString() + outMesh.meshData.normals[i] + " , ";
			iDataStr += MString() + outMesh.meshData.normals[i + 1] + " , ";
			iDataStr += MString() + outMesh.meshData.normals[i + 2] +")";

			iDataStr += "UV ";
			iDataStr += "(" + MString() + outMesh.meshData.uv[i][0] + " , ";
			iDataStr += MString() + outMesh.meshData.uv[i][1] + ")\n";
			}*/

		}
		FileMapping::printInfo("outMesh Indices per triangle: " + triIndStr);
		if (dbug2)FileMapping::printInfo(iDataStr);

	}
	MObjectArray connectedShaders;
	MIntArray shaderIndices;
	mNode.getConnectedShaders(0, connectedShaders, shaderIndices);
	MFnDependencyNode shaderGroup(connectedShaders[0]);
	MPlug plug = shaderGroup.findPlug("surfaceShader");
	MPlugArray connections;
	plug.connectedTo(connections, true, false);
	int matindex = -1;
	for (uint i = 0; i < connections.length(); i++)
	{
		if (connections[i].node().hasFn(MFn::kLambert))
		{
			matindex = i;
			if (debug) FileMapping::printInfo("Num of connections " + MString() + connections.length() + MString() + connections[i].name().asChar() + MString() + shaderGroup.name().asChar());
		}
	}
	if (matindex >= 0)
	{
		MFnDependencyNode mat(connections[matindex].node());
		FileMapping::printInfo(mat.name().asChar());
		outMesh.materialName = mat.name().asChar();
	}
	else
	{
		outMesh.materialName = "ERROR NONE";
	}

	outMesh.meshID = 5;
	outMesh.materialID = 8;
	if (debug) FileMapping::printInfo("MAT MESH ID: " + MString() + outMesh.meshID + " " + MString() + outMesh.materialID + outMesh.materialName.c_str());
	FileMapping::printInfo("MESH INDEX COUNTS(V,N,UV): " + MString() + outMesh.meshData.indCount + " " + MString() + triNorIndices.length() + " " + MString() + triUVIndices.length());

	FileMapping::printError("\n\nPARENT COUNT: " + MString() + mNode.parentCount());

	return outMesh;
}

TransformInfo outTransformData(std::string name)
{
	MStatus result;
	MString _name(name.c_str());
	MSelectionList sList;
	MDagPath dagPath;
	TransformInfo outTrans;
	if (MGlobal::getSelectionListByName(_name, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kTransform))
		{
			MTransformationMatrix trMtx = dagPath.inclusiveMatrix(&result);
			MVector transM = trMtx.getTranslation(MSpace::kTransform, &result);
			double rotsM[4];
			trMtx.getRotationQuaternion(rotsM[0], rotsM[1], rotsM[2], rotsM[3]);
			double scaleM[3];
			trMtx.getScale(scaleM, MSpace::kTransform);



			MFnTransform mNode(dagPath.node(), &result);
			TransformInfo outTrans;

			if (result)
			{
				if (mNode.parent(0).hasFn(MFn::kTransform))
				{
					MFnTransform parent(mNode.parent(0), &result);
					if (!result)
					{
						FileMapping::printWarning(MString(name.c_str()) + " parent not found!");
					}
					else
					{
						outTrans.parentName = parent.fullPathName().asChar();
					}
				}
				else
				{
					outTrans.parentName[0] = 0;
				}


				std::string attName(mNode.fullPathName().asChar());
				if (strcmp(attName.c_str(), name.c_str()) != 0)
				{
					FileMapping::printError("NAME CHANGED ON TRANSFORM");
					cbNameChange(dagPath.node(), MString(name.c_str()), nullptr);
				}


				MVector trans = mNode.getTranslation(MSpace::kTransform, &result);
				outTrans.transformData.translation[0] = transM.x;
				outTrans.transformData.translation[1] = transM.y;
				outTrans.transformData.translation[2] = transM.z;
				/*		outTrans.transformData.translation[0] = trans.x;
						outTrans.transformData.translation[1] = trans.y;
						outTrans.transformData.translation[2] = trans.z;*/

				double rots[4];
				mNode.getRotationQuaternion(rots[0], rots[1], rots[2], rots[3], MSpace::kTransform);
				outTrans.transformData.rotation[0] = rotsM[0] * -1.0f;
				outTrans.transformData.rotation[1] = rotsM[1] * -1.0f;
				outTrans.transformData.rotation[2] = rotsM[2] * -1.0f;
				outTrans.transformData.rotation[3] = rotsM[3] * -1.0f;
				/*outTrans.transformData.rotation[0] = rots[0];
				outTrans.transformData.rotation[1] = rots[1];
				outTrans.transformData.rotation[2] = rots[2];
				outTrans.transformData.rotation[3] = rots[3];*/

				double scale[3];
				mNode.getScale(scale);
				outTrans.transformData.scale[0] = scaleM[0];
				outTrans.transformData.scale[1] = scaleM[1];
				outTrans.transformData.scale[2] = scaleM[2];
				/*outTrans.transformData.scale[0] = scale[0];
				outTrans.transformData.scale[1] = scale[1];
				outTrans.transformData.scale[2] = scale[2];*/

				outTrans.nodeName = attName;

				if (debug)
				{
					FileMapping::printInfo("TRANSFORM INNER DATA: " + MString(outTrans.nodeName.c_str()) + " par" + MString(outTrans.parentName.c_str()));
					FileMapping::printInfo("Translation(ACC): " + MString() + transM.x + " " + MString() + transM.y + " " + MString() + transM.z);
					FileMapping::printInfo("Rotation(ACC): " + MString() + rotsM[0] + " " + MString() + rotsM[1] + " " + MString() + rotsM[2] + " " + MString() + rotsM[3]);
					FileMapping::printInfo("Scale(ACC): " + MString() + scaleM[0] + " " + MString() + scaleM[1] + " " + MString() + scaleM[2]);
				}
				
				MPlug tempPlug = mNode.findPlug("drmRender");
				tempPlug.getValue(outTrans.transformData.attributes.isRendered);
				tempPlug = mNode.findPlug("drmBBox");
				tempPlug.getValue(outTrans.transformData.attributes.isBBox);
				tempPlug = mNode.findPlug("drmCollidable");
				tempPlug.getValue(outTrans.transformData.attributes.isCollider);
                tempPlug = mNode.findPlug("drmInteractable");
                tempPlug.getValue(outTrans.transformData.attributes.isInteractable);
                tempPlug = mNode.findPlug("drmCheckPointID");
                tempPlug.getValue(outTrans.transformData.attributes.checkPointID);
                tempPlug = mNode.findPlug("drmSpawnPointID");
                tempPlug.getValue(outTrans.transformData.attributes.spawnPointID);
                tempPlug = mNode.findPlug("drmLevelStartEnd");
                tempPlug.getValue(outTrans.transformData.attributes.startOrEndPoint);
				tempPlug = mNode.findPlug("drmAIground");
				tempPlug.getValue(outTrans.transformData.attributes.isAIground);
				
                tempPlug = mNode.findPlug("drmFrequencyAffected");
                tempPlug.getValue(outTrans.transformData.attributes.frequencyAffected);

				tempPlug = mNode.findPlug("drmInteractableStartPosX");
				tempPlug.getValue(outTrans.transformData.attributes.interactableStartPos[0]);
				tempPlug = mNode.findPlug("drmInteractableStartPosY");
				tempPlug.getValue(outTrans.transformData.attributes.interactableStartPos[1]);
				tempPlug = mNode.findPlug("drmInteractableStartPosZ");
				tempPlug.getValue(outTrans.transformData.attributes.interactableStartPos[2]);
				tempPlug = mNode.findPlug("drmInteractableEndPosX");
				tempPlug.getValue(outTrans.transformData.attributes.interactableEndPos[0]);
				tempPlug = mNode.findPlug("drmInteractableEndPosY");
				tempPlug.getValue(outTrans.transformData.attributes.interactableEndPos[1]);
				tempPlug = mNode.findPlug("drmInteractableEndPosZ");
				tempPlug.getValue(outTrans.transformData.attributes.interactableEndPos[2]);
				tempPlug = mNode.findPlug("drmInteractableOffsetX");
				tempPlug.getValue(outTrans.transformData.attributes.interactableOffset[0]);
				tempPlug = mNode.findPlug("drmInteractableOffsetY");
				tempPlug.getValue(outTrans.transformData.attributes.interactableOffset[1]);

				tempPlug = mNode.findPlug("drmIsPotentialFieldCollidable");
				tempPlug.getValue(outTrans.transformData.attributes.isPotentialFieldCollidable);
				tempPlug = mNode.findPlug("drmPotentialFieldID");
				tempPlug.getValue(outTrans.transformData.attributes.potentialFieldID);
				tempPlug = mNode.findPlug("drmPotentialFieldNeighbour1");
				tempPlug.getValue(outTrans.transformData.attributes.potentialFieldNeighbour1);
				tempPlug = mNode.findPlug("drmPotentialFieldNeighbour2");
				tempPlug.getValue(outTrans.transformData.attributes.potentialFieldNeighbour2);
				tempPlug = mNode.findPlug("drmPotentialFieldNeighbour3");
				tempPlug.getValue(outTrans.transformData.attributes.potentialFieldNeighbour3);
				tempPlug = mNode.findPlug("drmPotentialFieldNeighbour4");
				tempPlug.getValue(outTrans.transformData.attributes.potentialFieldNeighbour4);
				tempPlug = mNode.findPlug("drmPotentialFieldNeighbour5");
				tempPlug.getValue(outTrans.transformData.attributes.potentialFieldNeighbour5);

				tempPlug = mNode.findPlug("drmIsSpawner");
				tempPlug.getValue(outTrans.transformData.attributes.isSpawner);
				tempPlug = mNode.findPlug("drmSpawnsMax");
				tempPlug.getValue(outTrans.transformData.attributes.spawnMax);
				tempPlug = mNode.findPlug("drmSpawnsMaxAlive");
				tempPlug.getValue(outTrans.transformData.attributes.spawnMaxAlive);
				tempPlug = mNode.findPlug("drmSpawnTypeBlueprint");
				tempPlug.getValue(outTrans.transformData.attributes.spawnTypeBlueprint);                
                tempPlug = mNode.findPlug("drmSpawnFrequency");
                tempPlug.getValue(outTrans.transformData.attributes.spawnFrequency);

				tempPlug = mNode.findPlug("drmIsStatic");
				tempPlug.getValue(outTrans.transformData.attributes.isStatic);
				tempPlug = mNode.findPlug("drmPhysicsType");
				tempPlug.getValue(outTrans.transformData.attributes.physicsType);

				tempPlug = mNode.findPlug("drmTypeBlueprint");
				tempPlug.getValue(outTrans.transformData.attributes.typeBlueprint);	
				tempPlug = mNode.findPlug("drmIsDangerous");
				tempPlug.getValue(outTrans.transformData.attributes.isDangerous);

				//m_attributeVector[0].nam
				return outTrans;
			}

		}
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
			if (debug) FileMapping::printInfo("Camera found: " + dagPath.fullPathName());
			MFnCamera mNode(dagPath.node(), &result);

			// Get the node's parent
			if (mNode.parent(0).hasFn(MFn::kTransform))
			{
				MFnTransform parent(mNode.parent(0), &result);
				if (!result)
				{
					FileMapping::printError(MString(name.c_str()) + " parent not found!");
				}
				else
				{
					outCam.transformName = parent.fullPathName().asChar();
				}
			}

			MFloatMatrix projMtx(mNode.projectionMatrix());
			MPoint pos = mNode.eyePoint(MSpace::Space::kPostTransform);
			MFloatVector dir = mNode.viewDirection(MSpace::Space::kPostTransform);
			MFloatVector up = mNode.upDirection(MSpace::Space::kPostTransform);
			MFloatVector right = mNode.rightDirection(MSpace::Space::kPostTransform);

			bool isOrtho = mNode.isOrtho();
			//double fov = mNode.horizontalFieldOfView();
			double fov = mNode.verticalFieldOfView();


			outCam.camData.isOrtho = isOrtho;
			if (isOrtho)
			{
				outCam.camData.hAngle = mNode.orthoWidth();
			}
			else
			{
				outCam.camData.hAngle = fov;
			}
			for (int i = 0; i < 3; i++)
			{
				outCam.camData.rightVector[i] = right[i];
				outCam.camData.target[i] = dir[i];
				outCam.camData.upVector[i] = up[i];
			}

			if (debug)
			{
				FileMapping::printInfo("Pos(" + MString() + pos.x + " , " + MString() + pos.y + " , " + MString() + pos.z + ")");
				FileMapping::printInfo("Dir(" + MString() + dir.x + " , " + MString() + dir.y + " , " + MString() + dir.z + ")");
				FileMapping::printInfo("Up(" + MString() + up.x + " , " + MString() + up.y + " , " + MString() + up.z + ")");
				FileMapping::printInfo("Orthographic: " + MString() + isOrtho);
				FileMapping::printInfo("Horizontal fov / Orthographic width: " + MString() + outCam.camData.hAngle);
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
	FileMapping::printInfo(MString() + outLight.lightData.colorDiffuse[1]);
	if (MGlobal::getSelectionListByName(lName, sList))
	{
		sList.getDagPath(0, dagPath);
		if (dagPath.hasFn(MFn::kLight))
		{
			MFnLight baseLight(dagPath);
			if (baseLight.parent(0).hasFn(MFn::kTransform))
			{
				MFnTransform trans(baseLight.parent(0), &result);
				if (!result)
				{
					FileMapping::printError(MString(name.c_str()) + " parent not found!");
				}
				outLight.transformName = trans.fullPathName().asChar();
			}

			// Get diffuse color data
			MColor diffColor = baseLight.color();
			float RGBColor[3];
			diffColor.get(MColor::MColorType::kRGB, RGBColor[0], RGBColor[1], RGBColor[2]);
			std::copy(RGBColor, RGBColor + 3, outLight.lightData.colorDiffuse);
			if (debug) FileMapping::printInfo("Light Color Diffuse: " + MString() + outLight.lightData.colorDiffuse[0] + " " + MString() + outLight.lightData.colorDiffuse[1] + " " + MString() + outLight.lightData.colorDiffuse[2]);
			//Get light intensity
			outLight.lightData.intensity = baseLight.intensity();
			if (debug) FileMapping::printInfo("Light intensity: " + MString() + outLight.lightData.intensity);


			if (dagPath.hasFn(MFn::kDirectionalLight))
			{
				outLight.lightData.type = 1;
				MFnDirectionalLight dLight(dagPath); // Don't think this is necessary dude to probably all relevant data exist within MFnLight
				MFloatVector dir(baseLight.lightDirection(0, MSpace::kWorld, &result));
				outLight.lightData.direction[0] = dir.x;
				outLight.lightData.direction[1] = dir.y;
				outLight.lightData.direction[2] = dir.z;
				if (debug && result) FileMapping::printInfo("Light direction: " + MString() + dir.x + " " + MString() + dir.y + " " + MString() + dir.z);
			}
			else if (dagPath.hasFn(MFn::kSpotLight))
			{
				outLight.lightData.type = 2;
				MFnSpotLight sLight(dagPath);
				outLight.lightData.decayType = sLight.decayRate();
				outLight.lightData.coneAngle = sLight.coneAngle();
				outLight.lightData.penumAgle = sLight.penumbraAngle();
				outLight.lightData.dropOff = sLight.dropOff();

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
	MString mName(name.c_str());
	MDagPath dagPath;
	MSelectionList sList;
	MaterialInfo outMat;
	MStatus status;
	if (MGlobal::getSelectionListByName(mName, sList))
	{
		MObject obj;
		sList.getDependNode(0, obj);
		MFnDependencyNode mat(obj);
		// FileMapping::printInfo(depNode.name().asChar());
		MPlug plg = mat.findPlug("diffuse", &status);
		if (status)
		{
			float val;
			plg.getValue(val);
			FileMapping::printInfo(MString() + val);
			outMat.data.diffuse = val;
		}
		plg = mat.findPlug("color", &status);
		if (status)
		{
			if (plg.isConnected())
			{
				MPlugArray plgArray;
				plg.connectedTo(plgArray, true, false);
				for (int i = 0; i < plgArray.length(); i++)
				{
					if (plgArray[i].node().apiType() == MFn::kFileTexture)
					{
						MFnDependencyNode texture(plgArray[i].node());
						plg = texture.findPlug("fileTextureName", &status);
						if (status)
						{
							MString name = plg.asString();
							if (name.length() < 1)
							{
								FileMapping::printWarning(mat.name() + " TEXTURE PATH NOT SET");
								outMat.diffuseTexturePath[0] = 0;
							}
							else if (name.length() < 100)
							{
								FileMapping::printInfo(mat.name() + " FOUND TEXTURE MAP " + name);
								outMat.diffuseTexturePath = name.asChar();
								// outMat.diffuseTexturePath[name.length()] = 0;
								outMat.data.mapMasks |= (int)bitmask::COLORMAP;
								FileMapping::printInfo(outMat.diffuseTexturePath.c_str());
							}
							else
							{
								FileMapping::printError(mat.name() + "File texture path name too long");
							}
						}
					}
				}
			}
			else
			{
				outMat.diffuseTexturePath[0] = 0;
				plg = mat.findPlug("colorR", &status);
				if (status) plg.getValue(outMat.data.color[0]);
				plg = mat.findPlug("colorG", &status);
				if (status) plg.getValue(outMat.data.color[1]);
				plg = mat.findPlug("colorB", &status);
				if (status) plg.getValue(outMat.data.color[2]);
			}
		}
		plg = mat.findPlug("incandescence", &status);
		if (status)
		{
			if (plg.isConnected())
			{
				MPlugArray plgArray;
				plg.connectedTo(plgArray, true, false);
				for (int i = 0; i < plgArray.length(); ++i)
				{
					if (plgArray[i].node().apiType() == MFn::kFileTexture)
					{
						MFnDependencyNode glowTexture(plgArray[i].node());
						plg = glowTexture.findPlug("fileTextureName", &status);
						MString name = plg.asString();
						if (name.length() < 1)
						{
							FileMapping::printWarning(mat.name() + "TEXTURE PATH NOT SET");
							outMat.glowTexturePath[0] = 0;
						}
						else if (name.length() < 100)
						{
							FileMapping::printInfo(mat.name() + " FOUND GLOW MAP " + name);
							outMat.glowTexturePath = name.asChar();
							FileMapping::printInfo(outMat.glowTexturePath.c_str());
							outMat.data.mapMasks |= (int)bitmask::GLOWMAP;
						}
						else
						{
							FileMapping::printError(mat.name() + "Glow texture path name too long");
						}
					}
				}
			}
		}


		plg = mat.findPlug("specularColor", &status);
		if (status)
		{
			if (plg.isConnected())
			{
				if (debug) FileMapping::printInfo("IS CONNECTED");
			}
			else
			{
				plg = mat.findPlug("specularColorR", &status);
				if (status) plg.getValue(outMat.data.specColor[0]);
				plg = mat.findPlug("specularColorG", &status);
				if (status) plg.getValue(outMat.data.specColor[1]);
				plg = mat.findPlug("specularColorB", &status);
				if (status) plg.getValue(outMat.data.specColor[2]);
			}
		}
		plg = mat.findPlug("cosinePower", &status);
		if (status)
		{
			plg.getValue(outMat.data.specCosine);
		}
		plg = mat.findPlug("eccentricity", &status);
		if (status)
		{
			plg.getValue(outMat.data.specEccentricity);
		}
		plg = mat.findPlug("specularRollOff", &status);
		if (status)
		{
			plg.getValue(outMat.data.specRollOff);
		}


		if (debug)
		{
			FileMapping::printInfo("Color: " + MString() + outMat.data.color[0]);
			FileMapping::printInfo("Specular color: ");
			FileMapping::printInfo("Cosine Power: " + MString() + outMat.data.specCosine);
			FileMapping::printInfo("Eccentricity: " + MString() + outMat.data.specEccentricity);
			FileMapping::printInfo("Specular Roll Off: " + MString() + outMat.data.specRollOff);
		}

		/*int mask = 0;
		if ((mask & (int)bitmask::COLORMAP))
		{
		FileMapping::printInfo("BITS "+MString()+mask);
		}
		mask |= (int)bitmask::SPECULARMAP;
		if((mask & ((int)bitmask::SPECULARMAP | (int)bitmask::COLORMAP)) == ((int)bitmask::SPECULARMAP | (int)bitmask::COLORMAP))
		{
		FileMapping::printInfo("BITS2 " + MString() + mask);
		}

		int removeMask = (int)bitmask::COLORMAP;
		removeMask &= mask;
		mask ^= removeMask;
		if ((mask & ((int)bitmask::SPECULARMAP | (int)bitmask::COLORMAP)) == ((int)bitmask::SPECULARMAP | (int)bitmask::COLORMAP))
		{
		FileMapping::printInfo("WRONG " + MString() + mask);
		}
		if ((mask &(int)bitmask::SPECULARMAP) == (int)bitmask::SPECULARMAP)
		{
		FileMapping::printInfo("RIGHT " + MString() + mask);
		}

		plg = mat.findPlug("ambient");*/
	}
	return outMat;
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

// MESSAGE AND NODE HANDLERS
void mAddMessage(std::string name, int msgType, int nodeType, std::string oldName)
{
	bool exists = false;
	bool addToVector = false;
	MessageInfo msgInfo{ name, nodeType, msgType, oldName };
	if (msgVector.size() > 0)
	{
		for (std::vector<MessageInfo>::size_type i = 0; i != msgVector.size(); i++)
		{
			std::string tmp = msgVector.at(i).nodeName;
			if (strcmp(name.c_str(), tmp.c_str()) == 0)
			{
				//If a message of this type already exists in the queue OR if a msgAdded is already in queue, no new message should be added.
				if (msgVector.at(i).msgType == msgType || msgVector.at(i).msgType == msgAdded)
				{
					if (msgType != msgSwitched)
					{
						exists = true;
						if (debug) FileMapping::printWarning("Message" + MString(name.c_str()) + "already exists!");
					}
				}
				else if (msgVector.at(i).msgType == msgSwitched && msgType == msgSwitched)
				{
					msgVector.at(i).nodeName = name;
					exists = true;
				}
			}
		}
	}
	//std::string oldN = "";
	if (msgType == MessageType::msgRenamed)
	{
		FileMapping::printInfo("\n****** MESSAGE Start (Node Rename: " + MString(name.c_str()) + ")");
		RenameDeleteInfo msg{ name, oldName };
		if (fileMap.tryWriteRenameDelete(msgInfo, msg))
		{
			FileMapping::printInfo("****** MESSAGE Result (Node Renamed: " + MString(name.c_str()) + ")) Success!");
		}
		else
		{
			FileMapping::printInfo("****** MESSAGE Result (Node Renamed: " + MString(name.c_str()) + ") Failed (Adding to queue)");
			addToVector = true;
		}

	}
	else if (msgType == MessageType::msgDeleted)
	{
		FileMapping::printInfo("\n****** MESSAGE Start (Node Deleted: " + MString(name.c_str()) + ")");
		RenameDeleteInfo msg{ name, oldName };
		if (fileMap.tryWriteRenameDelete(msgInfo, msg))
		{
			FileMapping::printInfo("****** MESSAGE Result (Node Deleted: " + MString(name.c_str()) + ")) Success!");
		}
		else
		{
			FileMapping::printInfo("****** MESSAGE Result (Node Deleted: " + MString(name.c_str()) + ") Failed (Adding to queue)");
			addToVector = true;
		}
	}
	else
	{
		switch (nodeType)
		{
		case(NodeType::nTransform) :
		{

			if (msgType == MessageType::msgAdded)
			{
				FileMapping::printInfo("\n****** MESSAGE Start (Transform Added: " + MString(name.c_str()) + ")");
				if (fileMap.tryWriteTransform(msgInfo, outTransformData(name)))
				{
					FileMapping::printInfo("****** MESSAGE Result (Transform Added: " + MString(name.c_str()) + ")) Success!");
				}
				else
				{
					FileMapping::printInfo("****** MESSAGE Result (Transform Added: " + MString(name.c_str()) + ") Failed (Adding to queue)");
					addToVector = true;
				}
			}
			else
			{
				addToVector = true;
			}
			break;
		}
		case(NodeType::nMesh) :
		{
			if (msgType == MessageType::msgAdded)
			{
				FileMapping::printInfo("\n****** MESSAGE Start (Mesh Added: " + MString(name.c_str()) + ")");
				if (fileMap.tryWriteMesh(msgInfo, outMeshData(name)))
				{
					FileMapping::printInfo("****** MESSAGE Result (Mesh Added: " + MString(name.c_str()) + ")) Success!");
				}
				else
				{
					FileMapping::printInfo("****** MESSAGE Result (Mesh Added: " + MString(name.c_str()) + ") Failed (Adding to queue)");
					addToVector = true;
				}
			}
			else
			{
				addToVector = true;
			}
			break;
		}
		case(NodeType::nCamera) :
		{
			if (msgType == MessageType::msgAdded)
			{
				FileMapping::printInfo("\n****** MESSAGE Start (Camera Added: " + MString(name.c_str()) + ")");
				if (fileMap.tryWriteCamera(msgInfo, outCameraData(name)))
				{
					FileMapping::printInfo("****** MESSAGE Result (Camera Added: " + MString(name.c_str()) + ")) Success!");
				}
				else
				{
					FileMapping::printInfo("****** MESSAGE Result (Camera Added: " + MString(name.c_str()) + ") Failed (Adding to queue)");
					addToVector = true;
				}
			}
			else
			{
				addToVector = true;
			}
			break;
		}
		case(NodeType::nMaterial) :
		{
			if (msgType == MessageType::msgAdded)
			{
				FileMapping::printInfo("\n****** MESSAGE Start (Material Added: " + MString(name.c_str()) + ")");
				if (fileMap.tryWriteMaterial(msgInfo, outMaterialData(name)))
				{
					FileMapping::printInfo("****** MESSAGE Result (Material Added: " + MString(name.c_str()) + ")) Success!");
				}
				else
				{
					FileMapping::printInfo("****** MESSAGE Result (Material Added: " + MString(name.c_str()) + ") Failed (Adding to queue)");
					addToVector = true;
				}
			}
			else
			{
				addToVector = true;
			}
			break;
		}
		case(NodeType::nLight) :
		{
			if (msgType == MessageType::msgAdded)
			{
				FileMapping::printInfo("\n****** MESSAGE Start (Light Added: " + MString(name.c_str()) + ")");
				if (fileMap.tryWriteLight(msgInfo, outLightData(name)))
				{
					FileMapping::printInfo("****** MESSAGE Result (Light Added: " + MString(name.c_str()) + ")) Success!");
				}
				else
				{
					FileMapping::printInfo("****** MESSAGE Result (Light Added: " + MString(name.c_str()) + ") Failed (Adding to queue)");
					addToVector = true;
				}
			}
			else
			{
				addToVector = true;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}


	if (!exists && addToVector == true)
	{
		MessageInfo tMsg{ name, nodeType,msgType, oldName };
		msgVector.push_back(tMsg);
		//msgQueue.push(tMsg);
	}
	//bool exists = false;
	//if (msgVector.size() > 0)
	//{
	//	for (std::vector<MessageInfo>::size_type i = 0; i != msgVector.size(); i++)
	//	{
	//		std::string tmp = msgVector.at(i).nodeName;
	//		if (strcmp(name.c_str(), tmp.c_str()) == 0)
	//		{
	//			//If a message of this type already exists in the queue OR if a msgAdded is already in queue, no new message should be added.
	//			if (msgVector.at(i).msgType == msgType || msgVector.at(i).msgType == msgAdded)
	//			{
	//				if (msgType != msgSwitched)
	//				{
	//					exists = true;
	//					FileMapping::printWarning("Message" + MString(name.c_str()) + "already exists!");
	//				}
	//			}
	//			else if (msgVector.at(i).msgType == msgSwitched && msgType == msgSwitched)
	//			{
	//				msgVector.at(i).nodeName = name;
	//				exists = true;
	//			}
	//		}
	//	}
	//}
	//std::string oldN = "";
	//if (msgType == MessageType::msgRenamed)
	//{
	//	oldN = oldName;
	//}
	//if (!exists)
	//{
	//	MessageInfo tMsg{ name, nodeType,msgType, oldN };
	//	msgVector.push_back(tMsg);
	//	//msgQueue.push(tMsg);
	//}
}
void mAddNode(std::string name, std::string parentName, int type, int extra = 0, char* childname = nullptr)
{
	
	if (!name.empty())
	{
		bool exists = false;
		//std::string nodename = name.asChar();
		if (type == nMesh)
		{
			if (meshVector.size() > 0)
			{
				for (std::vector<MeshInfo>::size_type i = 0; i != meshVector.size(); i++)
				{
					std::string tmp = meshVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						if (debug) FileMapping::printWarning("Mesh " + MString(name.c_str()) + " already exists!");
					}
				}
			}
			if (!exists)
			{
				std::vector<std::string>transName;
				transName.push_back(parentName);
				MeshInfo mesh{ name,1 ,transName, "" ,0,0 };
				meshVector.push_back(mesh);
				MessageInfo msginfo{ name, NodeType::nMesh, MessageType::msgAdded };
				mAddMessage(name, msgAdded, nMesh);
				if (debug) FileMapping::printInfo("Added mesh: " + MString(name.c_str()));
			}
		}
		else if (type == nTransform)
		{
			if (transVector.size() > 0)
			{
				for (std::vector<TransformInfo>::size_type i = 0; i != transVector.size(); i++)
				{
					std::string tmp = transVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						if (debug) FileMapping::printWarning("Transform " + MString(name.c_str()) + " already exists!");
					}
				}
			}
			if (!exists)
			{
				TransformInfo trans{ name };
				transVector.push_back(trans);
				MessageInfo msginfo{ name, NodeType::nTransform, MessageType::msgAdded };
				mAddMessage(name, msgAdded, nTransform);
				if (debug) FileMapping::printInfo("Added transform: " + MString(name.c_str()));
			}
		}
		else if (type == nCamera)
		{
			if (camVector.size() > 0)
			{
				for (std::vector<CameraInfo>::size_type i = 0; i != camVector.size(); i++)
				{
					std::string tmp = camVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						if (debug) FileMapping::printWarning("Camera " + MString(name.c_str()) + " already exists!");
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
						CameraInfo cam{ name, trans.fullPathName().asChar() };
						camVector.push_back(cam);
						if (debug) FileMapping::printInfo("Added camera: " + MString(name.c_str()));
						mAddMessage(name, msgAdded, nCamera);
					}
				}

			}

		}
		else if (type == nLight)
		{
			
			if (lightVector.size() > 0)
			{
				for (std::vector<LightInfo>::size_type i = 0; i != lightVector.size(); i++)
				{
					//FileMapping::printInfo("VECTOR SIZE: " + MString() + lightVector.size() + " " + MString(name.c_str()));

					std::string tmp = lightVector.at(i).nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						FileMapping::printWarning("Light " + MString(name.c_str()) + " already exists!");
					}
					//FileMapping::printInfo("VECTOR SIZE: " + MString() + lightVector.size());
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
						LightInfo light{ name, trans.fullPathName().asChar() };
						lightVector.push_back(light);
						if (true) FileMapping::printInfo("Added light: " + MString(name.c_str()) + "  " + MString()+lightVector.size());
						mAddMessage(name, msgAdded, nLight);
					}
				}
			}
		}
		else if (type == nMaterial)
		{
			if (lightVector.size() > 0)
			{
				for (std::vector<MaterialInfo>::size_type i = 0; i != materialVector.size(); i++)
				{
					std::string tmp = materialVector[i].nodeName;
					if (strcmp(name.c_str(), tmp.c_str()) == 0)
					{
						exists = true;
						if (debug) FileMapping::printWarning("Material " + MString(name.c_str()) + " already exists!");
					}
				}
			}
			if (!exists)
			{
				MaterialInfo material{ name,"", "","","",extra };
				materialVector.push_back(material);
				if (debug) FileMapping::printInfo("Added material: " + MString(name.c_str()));
				mAddMessage(name, msgAdded, nMaterial);
			}
		}
	}

}

bool removeFromQueue(std::string name)
{
	std::string nName = name;
	for (std::vector<MessageInfo>::size_type i = 0; i < msgVector.size(); i++)
	{
		if (strcmp(name.c_str(), msgVector[i].nodeName.c_str()) == 0)
		{
			FileMapping::printInfo("Removed message for: " + MString(msgVector[i].nodeName.c_str()));
			msgVector.erase(msgVector.begin() + i);
		}
	}
	return true;
}
// CALLBACKS
void cbMeshAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	// Validates new mesh
	// Standard string for use with find() function
	std::string plugName(plug_1.name().asChar());
	if (plugName.find("doubleSided") != std::string::npos && MNodeMessage::AttributeMessage::kAttributeSet)
	{
		MStatus result;
		MFnMesh mNode(plug_1.node(), &result);
		if (result)
		{	//DO STUFF
			MString myCommand = "setAttr -e " + mNode.name() + ".quadSplit 0";
			MGlobal::executeCommandOnIdle(myCommand);
			std::string parentname = getParentName(plug_1);
			std::string tmpName = mNode.fullPathName().asChar();
			mAddNode(tmpName.c_str(), parentname.c_str(), nMesh);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(plug_1.node(), cbMeshAttributeChange));
			MMessage::removeCallback(MMessage::currentCallbackId());
		}
	}
}
void cbMeshAttributeChange(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	// Validates new mesh
	// Standard string for use with find() function
	MStatus status;
	MFnMesh mesh(plug_1.node(), &status);

	if (status)
	{
		std::string plugName(plug_1.name().asChar());
		std::string meshName(mesh.fullPathName().asChar());
		bool exists = false;
		for (std::vector<MeshInfo>::size_type i = 0; i < meshVector.size(); i++)
		{
			//FileMapping::printInfo(MString(plugName.c
			if (strcmp(meshName.c_str(), meshVector[i].nodeName.c_str()) == 0)
			{
				exists = true;
			}
		}
		if (exists)
		{
			//Finds changes to vertex positions
			if (plugName.find("pnts") != std::string::npos  && plugName.find("[") != std::string::npos)
			{
				mAddMessage(meshName, MessageType::msgEdited, NodeType::nMesh);

			}
			// Finds out if the material connected to this node has been replaced
			if (plug_2.node().apiType() == MFn::Type::kShadingEngine)
			{
				mAddMessage(mesh.fullPathName().asChar(), MessageType::msgEdited, NodeType::nMesh);
			}
		}
	}
}

void cbDuplication(void* clientData)
{
	FileMapping::printInfo("\n\n\n\n\n\n\n\n\nDUPLICADO POR FAVOR");
}
void cbInstancing(MObject &node, void *clientData)
{
	FileMapping::printInfo("\n\n\n\n\n\n\n\n\INSTANCIADO POR FAVOR\n");
}
void cbAddParent(MDagPath &child, MDagPath &parent, void *clientData)
{
	MString childPathName(child.fullPathName());
	MString parentPathName(parent.fullPathName());
	if (childPathName.length() > 0 && parentPathName.length() > 0)
	{
		if (child.hasFn(MFn::kTransform))
		{
			bool hasShapes = false;
			int numChild = child.childCount();
			if (numChild > 0)
			{
				for (int i = 0; i < numChild; i++)
				{
					if (child.child(i).hasFn(MFn::kMesh))
					{
						MFnMesh mesh(child.child(i));

						std::string t = "|";
						std::string nodeName = t + mesh.name().asChar();

						int oldStrLen = mesh.name().length();
						for (int i = 0; i < meshVector.size(); i++)
						{
							std::string oldTemp = meshVector.at(i).nodeName;
							std::string oldTemp2 = oldTemp;
							size_t strsize = oldTemp.find_last_of("|");
							std::string thisStr = oldTemp.erase(0, strsize);
							//FileMapping::printInfo("VECTOR NAME SPLIT: " + MString(thisStr.c_str()));

							if (strcmp(nodeName.c_str(), thisStr.c_str()) == 0)
							{
								//FileMapping::printInfo("FOUND NODE IN VECTOR : " + MString(nodeName.c_str()) + " " + MString(thisStr.c_str()) + " " + MString(oldTemp.c_str()));
								meshVector[i].nodeName = mesh.fullPathName().asChar();
								//transVector[i].parentName
								mAddMessage(meshVector[i].nodeName, msgRenamed, NodeType::nMesh, oldTemp2);
								for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
								{
									if (strspn(oldTemp2.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
									{
										if (msgVector[o].nodeType == NodeType::nMesh)
										{
											msgVector[o].nodeName = meshVector[i].nodeName;
										}
									}
								}
								i = meshVector.size();
							}
						}
						hasShapes = true;
					}
					else if (child.child(i).hasFn(MFn::kLight))
					{
						MFnLight light(child.child(i));
						hasShapes = true;
					}
					else if (child.child(i).hasFn(MFn::kCamera))
					{
						MFnCamera camera(child.child(i));
						hasShapes = true;
					}

				}
			}

			MFnTransform trans(child.node());

			if (hasShapes)
			{
				//std::string oldStr = str.asChar();
				std::string t = "|";
				std::string nodeName = t + trans.name().asChar();
				//FileMapping::printInfo("THIS NODE NAME: " + MString(nodeName.c_str()));
				int oldStrLen = trans.name().length();
				for (int i = 0; i < transVector.size(); i++)
				{
					std::string oldTemp = transVector.at(i).nodeName;
					std::string oldTemp2 = oldTemp;
					size_t strsize = oldTemp.find_last_of("|");
					std::string thisStr = oldTemp.erase(0, strsize);
					//FileMapping::printInfo("VECTOR NAME SPLIT: " + MString(thisStr.c_str()));

					if (strcmp(nodeName.c_str(), thisStr.c_str()) == 0)
					{
						//FileMapping::printInfo("FOUND NODE IN VECTOR : " + MString(nodeName.c_str()) + " " + MString(thisStr.c_str()) + " " + MString(oldTemp.c_str()));
						transVector[i].nodeName = childPathName.asChar();
						transVector[i].parentName = parent.fullPathName().asChar();
						//transVector[i].parentName
						mAddMessage(transVector[i].nodeName, msgRenamed, NodeType::nTransform, oldTemp2);
						for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
						{
							if (strspn(oldTemp2.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
							{
								if (msgVector[o].nodeType == NodeType::nTransform)
								{
									msgVector[o].nodeName = transVector[i].nodeName;
								}
							}
						}
						i = transVector.size();
					}
				}
			}
		}
		if (debug) FileMapping::printInfo("REPARENT (CHILD -> PARENT)" + child.fullPathName() + " -> " + parent.fullPathName() + " ");
	}

}
void cbRemoveParent(MDagPath &child, MDagPath &parent, void *clientData)
{
	MString childPathName(child.fullPathName());
	MString parentPathName(parent.fullPathName());
	if (childPathName.length() > 0)
	{
		if (child.hasFn(MFn::kTransform))
		{
			bool hasShapes = false;
			int numChild = child.childCount();
			if (numChild > 0)
			{
				for (int i = 0; i < numChild; i++)
				{
					if (child.child(i).hasFn(MFn::kMesh))
					{
						MFnMesh mesh(child.child(i));

						std::string t = "|";
						std::string nodeName = t + mesh.name().asChar();
						int oldStrLen = mesh.name().length();
						for (int i = 0; i < meshVector.size(); i++)
						{
							std::string oldTemp = meshVector.at(i).nodeName;
							std::string oldTemp2 = oldTemp;
							size_t strsize = oldTemp.find_last_of("|");
							std::string thisStr = oldTemp.erase(0, strsize);

							if (strcmp(nodeName.c_str(), thisStr.c_str()) == 0)
							{
								//FileMapping::printInfo("FOUND NODE IN VECTOR : " + MString(nodeName.c_str()) + " " + MString(thisStr.c_str()) + " " + MString(oldTemp.c_str()));

								meshVector[i].nodeName = mesh.fullPathName().asChar();

								mAddMessage(meshVector[i].nodeName, msgRenamed, NodeType::nMesh, oldTemp2);
								for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
								{
									if (strspn(oldTemp.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
									{
										if (msgVector[o].nodeType == NodeType::nMesh)
										{
											msgVector[o].nodeName = meshVector[i].nodeName;
										}
									}
								}
								i = meshVector.size();
							}
						}
						hasShapes = true;
					}
					else if (child.child(i).hasFn(MFn::kLight))
					{
						MFnLight light(child.child(i));
						hasShapes = true;
					}
					else if (child.child(i).hasFn(MFn::kCamera))
					{
						MFnCamera camera(child.child(i));
						hasShapes = true;
					}

				}
			}

			MFnTransform trans(child.node());

			if (hasShapes)
			{
				//std::string oldStr = str.asChar();
				std::string t = "|";
				std::string nodeName = t + trans.name().asChar();
				//FileMapping::printInfo("THIS NODE NAME: " + MString(nodeName.c_str()));
				int oldStrLen = trans.name().length();
				for (int i = 0; i < transVector.size(); i++)
				{
					std::string oldTemp = transVector.at(i).nodeName;
					std::string oldTemp2 = oldTemp;
					size_t strsize = oldTemp.find_last_of("|");
					std::string thisStr = oldTemp.erase(0, strsize);
					//FileMapping::printInfo("VECTOR NAME SPLIT: " + MString(thisStr.c_str()));

					if (strcmp(nodeName.c_str(), thisStr.c_str()) == 0)
					{
						//FileMapping::printInfo("FOUND NODE IN VECTOR : " + MString(nodeName.c_str()) + " " + MString(thisStr.c_str()) + " " + MString(oldTemp.c_str()));
						transVector[i].nodeName = childPathName.asChar();
						if (parent.fullPathName().length() > 0)
						{
							transVector[i].parentName = parent.fullPathName().asChar();
						}
						else
						{
							transVector[i].parentName = '0';
						}
						//transVector[i].parentName
						mAddMessage(transVector[i].nodeName, msgRenamed, NodeType::nTransform, oldTemp2);
						for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
						{
							if (strspn(oldTemp2.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
							{
								if (msgVector[o].nodeType == NodeType::nTransform)
								{
									msgVector[o].nodeName = transVector[i].nodeName;
								}
							}
						}
						i = transVector.size();
					}
				}
			}
		}

	}

}

void cbLightAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	MFnLight light(plug_1.node());
	bool sendMsg = false;
	std::string lightName(light.fullPathName().asChar());
	std::string plugName(plug_1.name().asChar());
	
	FileMapping::printInfo(MString(plugName.c_str()) + " nr " + MString() + msg);

	if (msg & MNodeMessage::AttributeMessage::kAttributeSet && msg != 2052)
	{
		
		//outLightData(lightName.asChar());
		MStatus result;
		if (plugName.find(".intensity") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".color") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".decayRate") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".coneAngle") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".dropOff") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".penumbraAngle") != std::string::npos)
		{
			sendMsg = true;

		}

		if (sendMsg)
		{
			//FileMapping::printInfo(MString(plugName.c_str()) + "    " + plug_1.node().apiTypeStr() + "  " + msg);
			mAddMessage(lightName, msgEdited, nLight);
		}
	}
}
void cbLightAdd(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	MFnLight light(plug_1.node());
	bool sendMsg = false;
	std::string lightName(light.fullPathName().asChar());
	std::string plugName(plug_1.name().asChar());

	//FileMapping::printInfo(MString(plugName.c_str()) + " nr " + MString() + msg);

	if (lightName.find("#") == std::string::npos && MNodeMessage::AttributeMessage::kAttributeSet)
	{
		//FileMapping::printInfo(MString(plugName.c_str()) + " nr " + MString() + msg);
		//FileMapping::printInfo(light.fullPathName());
		mAddNode(light.fullPathName().asChar(), "", nLight);

		_CBidArray.append(MNodeMessage::addAttributeChangedCallback(plug_1.node(), cbLightAttribute));
		_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(plug_1.node(), cbPreRemoveNode));
		_CBidArray.append(MNodeMessage::addNameChangedCallback(plug_1.node(), &cbNameChange));
		MMessage::removeCallback(MMessage::currentCallbackId());
		sendMsg = true;
	}
}
void cbMaterialAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	MFnDependencyNode mat(plug_1.node());

	std::string lightName(mat.name().asChar());
	std::string plugName(plug_1.name().asChar());


	if (msg & MNodeMessage::AttributeMessage::kAttributeSet && msg != 2052)
	{
		bool sendMsg = false;
		//outLightData(lightName.asChar());
		MStatus result;
		if (plugName.find(".diffuse") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".color") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".transparency") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".ambient") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".specularColor") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".eccentricity") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".specularRollOff") != std::string::npos)
		{
			sendMsg = true;
		}
		else if (plugName.find(".cosinePower") != std::string::npos)
		{
			sendMsg = true;
		}

		if (sendMsg)
		{
			if (debug) FileMapping::printInfo("MATERIAL CHANGE " + MString(plugName.c_str()));
			//outMaterialData(mat.name().asChar());
			mAddMessage(lightName, msgEdited, nMaterial);
		}
	}
}
void cbEvalAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	//FileMapping::printInfo("AFHDIFHIUDHFIADSHFIDSHIFSDHIFHSDIFHSIDHFISDHIFHSDIH" + MString()+msg);
	//std::string plugname(plug_1.name().asChar());
	//if (plugname.find("outMesh") == std::string::npos)
	//{
	//	FileMapping::printInfo("OUTMESH");
	//}
	//FileMapping::printInfo(plug_1.name().asChar() + MString("   ") + plug_2.name().asChar());
	if (msg & MNodeMessage::kIncomingDirection + MNodeMessage::AttributeMessage::kAttributeEval || msg & MNodeMessage::kIncomingDirection + MNodeMessage::AttributeMessage::kAttributeSet)
	{
		FileMapping::printInfo("EVAL");
		MMessage::removeCallback(MMessage::currentCallbackId());
	}
}
void cbPolyChanged(MObject& node, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
	{
		MStatus stat;
		MFnMesh mesh(node, &stat);
		if (stat == MS::kSuccess)
		{
			if (debug) FileMapping::printInfo("( " + mesh.fullPathName() + " )MESH TOPOLOGY CHANGED");
			mAddMessage(mesh.fullPathName().asChar(), msgEdited, nMesh);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbEvalAttribute));
		}
	}
}
void cbCamAttribute(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	std::string plgname = plug_1.name().asChar();
	if (plgname.find(".orthographicWidth"))
	{
		MFnCamera cam(plug_1.node());
		if (cam.isOrtho())
		{
			mAddMessage(cam.fullPathName().asChar(), MessageType::msgEdited, NodeType::nCamera);
		}
	}

}
void cbCameraPanel(const MString &str, MObject &node, void *clientData)
{
	if (node.hasFn(MFn::kCamera))
	{
		MFnCamera currCam(node);
		FileMapping::printInfo("Current Camera: " + str + " -> " + currCam.fullPathName());
		mAddMessage(currCam.fullPathName().asChar(), msgSwitched, nCamera);
	}
}
void cbNameChange(MObject& node, const MString& str, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
	{
		MFnMesh mesh(node);
		std::string newNameStr = mesh.fullPathName().asChar();
		std::string oldName;
		//std::string oldNameStr = str.asChar();
		for (std::vector<MeshInfo>::size_type i = 0; i != meshVector.size(); i++)
		{
			if (newNameStr.length() > 0)
			{
				std::string oldTemp = meshVector.at(i).nodeName;
				std::string oldStr = str.asChar();
				int oldStrLen = oldStr.length();
				if (strspn(oldStr.c_str(), meshVector[i].nodeName.c_str()) == oldStrLen)
					//if (strcmp(newNameStr.c_str(), oldTemp.c_str())==0)
				{
					meshVector.at(i).nodeName = mesh.fullPathName().asChar();
					//MessageInfo minfo{ oldTemp, NodeType::nMesh, MessageType::msgRenamed, oldTemp };
					RenameDeleteInfo renameInfo{ newNameStr, oldTemp };
					//if (!fileMap.tryWriteRenameDelete(minfo, renameInfo))
					//{
					mAddMessage(meshVector.at(i).nodeName, MessageType::msgRenamed, NodeType::nMesh, oldTemp);
					//}
					for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
					{
						if (strspn(oldStr.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
						{
							if (msgVector[o].nodeType == NodeType::nMesh)
							{
								msgVector[o].nodeName = newNameStr;
							}
						}
					}
					FileMapping::printInfo("Mesh name: " + str + " changed to: " + (MString)mesh.name() + " " + meshVector[i].nodeName.c_str());
					i = meshVector.size();
					break;
				}
			}
		}
	}
	else if (node.hasFn(MFn::kCamera))
	{
		MFnCamera cam(node);
		std::string newNameStr = cam.fullPathName().asChar();
		std::string oldName;
		//std::string oldNameStr = str.asChar();
		for (std::vector<CameraInfo>::size_type i = 0; i != camVector.size(); i++)
		{
			if (newNameStr.length() > 0)
			{
				std::string oldTemp = camVector.at(i).nodeName;
				std::string oldStr = str.asChar();
				int oldStrLen = oldStr.length();
				if (strspn(oldStr.c_str(), camVector[i].nodeName.c_str()) == oldStrLen)
				{
					camVector.at(i).nodeName = cam.fullPathName().asChar();
					//MessageInfo minfo{ oldTemp, NodeType::nMesh, MessageType::msgRenamed, oldTemp };
					RenameDeleteInfo renameInfo{ newNameStr, oldTemp };
					//if (!fileMap.tryWriteRenameDelete(minfo, renameInfo))
					//{
					mAddMessage(camVector.at(i).nodeName, MessageType::msgRenamed, NodeType::nCamera, oldTemp);
					//}
					for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
					{
						if (strspn(oldStr.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
						{
							if (msgVector[o].nodeType == NodeType::nCamera)
							{
								msgVector[o].nodeName = newNameStr;
							}
						}
					}
					FileMapping::printInfo("Camera name: " + str + " changed to: " + (MString)cam.name() + " " + camVector[i].nodeName.c_str());
					i = camVector.size();
					break;
				}
			}
		}
	}
	else if (node.hasFn(MFn::kLight))
	{
		MFnLight light(node);
		std::string newNameStr = light.fullPathName().asChar();
		std::string oldName;
		//std::string oldNameStr = str.asChar();
		for (std::vector<LightInfo>::size_type i = 0; i != lightVector.size(); i++)
		{
			if (newNameStr.length() > 0)
			{
				std::string oldTemp = lightVector.at(i).nodeName;
				std::string oldStr = str.asChar();
				int oldStrLen = oldStr.length();
				if (strspn(oldStr.c_str(), lightVector[i].nodeName.c_str()) == oldStrLen)
				{
					lightVector.at(i).nodeName = light.fullPathName().asChar();
					//MessageInfo minfo{ oldTemp, NodeType::nMesh, MessageType::msgRenamed, oldTemp };
					RenameDeleteInfo renameInfo{ newNameStr, oldTemp };
					//if (!fileMap.tryWriteRenameDelete(minfo, renameInfo))
					//{
					mAddMessage(lightVector.at(i).nodeName, MessageType::msgRenamed, NodeType::nLight, oldTemp);
					//}
					for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
					{
						if (strspn(oldStr.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
						{
							if (msgVector[o].nodeType == NodeType::nLight)
							{
								msgVector[o].nodeName = newNameStr;
							}
						}
					}
					FileMapping::printInfo("Light name: " + MString(oldStr.c_str()) + " changed to: " + (MString)light.name() + " " + lightVector[i].nodeName.c_str());
					i = camVector.size();
					break;
				}
			}
		}
	}
	else if (node.hasFn(MFn::kTransform) == true)
	{
		bool hasShapes = false;
		MFnTransform trans(node);
		std::string newNameStr = trans.fullPathName().asChar();
		int newNameLength = newNameStr.length();
		if (newNameStr.c_str()[newNameLength - 1] != '#')
		{
			for (int i = 0; i < trans.childCount(); i++)
			{
				if (newNameStr.length() > 0)
				{
					MObject child = trans.child(i);
					if (child.hasFn(MFn::kMesh))
					{
						hasShapes = true;
					}
					if (child.hasFn(MFn::kCamera))
					{
						hasShapes = true;
					}
					if (child.hasFn(MFn::kLight))
					{
						hasShapes = true;
					}
				}
			}
			if (hasShapes)
			{
				std::string oldStr = str.asChar();
				int oldStrLen = oldStr.length();
				for (int i = 0; i < transVector.size(); i++)
				{
					std::string oldTemp = transVector.at(i).nodeName;
					if (strspn(oldStr.c_str(), transVector[i].nodeName.c_str()) == oldStrLen)
					{
						transVector.at(i).nodeName = trans.fullPathName().asChar();
						//MessageInfo minfo{ oldTemp, NodeType::nTransform, MessageType::msgRenamed };
						RenameDeleteInfo renameInfo{ newNameStr, oldTemp };
						//if (!fileMap.tryWriteRenameDelete(minfo, renameInfo))
						//{
						mAddMessage(transVector.at(i).nodeName, msgRenamed, NodeType::nTransform, oldTemp);
						//}
						for (std::vector<MessageInfo>::size_type o = 0; o != msgVector.size(); o++)
						{
							if (strspn(oldStr.c_str(), msgVector[o].nodeName.c_str()) == oldStrLen)
							{
								if (msgVector[o].nodeType == NodeType::nTransform)
								{
									msgVector[o].nodeName = newNameStr;
								}
							}
						}
						FileMapping::printInfo("Transform name changed to: " + (MString)trans.name() + " from: " + str);
						// To exit for loop
						i = transVector.size();
						break;
					}
				}
			}
		}
		else
		{
			//if(debug) FileMapping::printError("# IDENTIFIER FAILED ( " + MString(newNameStr.c_str())+ ")");
		}
	}
}
void cbRemovedNode(MObject& node, void* clientData)
{
	/*MFnDependencyNode n(node);
	FileMapping::printInfo(n.name() + " Node deleted");*/
	//FileMapping::printInfo("REMOOOOOOOOOOOOOOOOOOOOOOOOVed");
}
void cbPreRemoveNode(MObject& node, void* clientData)
{
	if (node.hasFn(MFn::kMesh))
	{
		MFnMesh mesh(node);
		//FileMapping::printError("WOW????????????????");
		std::string ntmp = mesh.fullPathName().asChar();
		for (int i = 0; i < meshVector.size(); i++)
		{
			std::string tmp = meshVector.at(i).nodeName;
			if (tmp.find(ntmp) != std::string::npos)
			{
				FileMapping::printInfo(mesh.fullPathName() + " Node deleted MESH");
				meshVector.erase(meshVector.begin() + i);
				removeFromQueue(mesh.fullPathName().asChar());
				mAddMessage(ntmp, msgDeleted, nMesh);
			}
		}
	}
	else if (node.hasFn(MFn::kTransform))
	{
		MFnTransform trans(node);
		std::string ntmp = trans.fullPathName().asChar();
		for (int i = 0; i < transVector.size(); i++)
		{
			std::string tmp = transVector.at(i).nodeName;

			//FileMapping::printInfo(MString(ntmp.c_str()) + " ___ " + MString(tmp.c_str()));
			if (tmp.find(ntmp) != std::string::npos)
			{
				FileMapping::printInfo(trans.fullPathName() + " Node deleted TRANSFORM");
				transVector.erase(transVector.begin() + i);
				removeFromQueue(trans.fullPathName().asChar());
				mAddMessage(ntmp, msgDeleted, nTransform);
			}
		}
	}
	else if (node.hasFn(MFn::kCamera))
	{
		MFnCamera cam(node);
		std::string ntmp = cam.fullPathName().asChar();
		for (int i = 0; i < camVector.size(); i++)
		{
			std::string tmp = camVector.at(i).nodeName;

			//FileMapping::printInfo(MString(ntmp.c_str()) + " ___ " + MString(tmp.c_str()));
			if (tmp.find(ntmp) != std::string::npos)
			{
				FileMapping::printInfo(cam.fullPathName() + " Node deleted CAMERA");
				camVector.erase(camVector.begin() + i);
				removeFromQueue(cam.fullPathName().asChar());
				mAddMessage(ntmp, msgDeleted, nCamera);
			}
		}
	}
	else if (node.hasFn(MFn::kLight))
	{
		MFnLight light(node);
		std::string ntmp = light.fullPathName().asChar();
		for (int i = 0; i < lightVector.size(); i++)
		{
			std::string tmp = lightVector.at(i).nodeName;

			//FileMapping::printInfo(MString(ntmp.c_str()) + " ___ " + MString(tmp.c_str()));
			if (tmp.find(ntmp) != std::string::npos)
			{
				FileMapping::printInfo(MString(ntmp.c_str()) + " Node deleted LIGHT");
				lightVector.erase(lightVector.begin() + i);
				removeFromQueue(ntmp);
				mAddMessage(ntmp, msgDeleted, nLight);
			}
		}
	}
	else if (node.hasFn(MFn::kLambert))
	{
		MFnDependencyNode mat(node);
		std::string ntmp = mat.name().asChar();
		for (int i = 0; i < materialVector.size(); i++)
		{
			std::string tmp = materialVector.at(i).nodeName;
			//FileMapping::printInfo(MString(ntmp.c_str()) + " ___ " + MString(tmp.c_str()));
			if (tmp.find(ntmp) != std::string::npos)
			{
				FileMapping::printInfo(MString(ntmp.c_str()) + " Node deleted MATERIAL");
				materialVector.erase(materialVector.begin() + i);
				removeFromQueue(ntmp);
				mAddMessage(ntmp, msgDeleted, nMaterial);
			}
		}
	}
	_CBidArray.remove(MNodeMessage::currentCallbackId());
}
void cbTransformModified(MNodeMessage::AttributeMessage msg, MPlug& plug_1, MPlug& plug_2, void* clientData)
{
	//FileMapping::printInfo(MString(plug_1.info().asChar()));
	if (msg & MNodeMessage::AttributeMessage::kAttributeSet)
		//if (plug_1.node().hasFn(MFn::kTransform))
	{
		bool d = false;
		MStatus result;
		MFnTransform transform(plug_1.node());
		//MString att(plug_1.node());
		//FileMapping::printInfo(MString(plug_1.info().asChar()));
		std::string attName(plug_1.info().asChar());
		//FileMapping("PLG NAME")
		if (d)
		{
			if (attName.find("translate") != std::string::npos)
			{
				MVector trans = transform.getTranslation(MSpace::kPostTransform, &result);
				if (debug) FileMapping::printInfo("NODE: " + transform.fullPathName() + " Translation changed: (" + MString() + trans.x + " , " + MString() + trans.y + " , " + MString() + trans.z + ")");
			}
			else if (attName.find("rotate") != std::string::npos)
			{
				MEulerRotation rotation;
				transform.getRotation(rotation);
				if (debug) FileMapping::printInfo("NODE: " + transform.fullPathName() + " Rotation changed: (" + MString() + rotation.x + " , " + MString() + rotation.y + " , " + MString() + rotation.z + ")");

			}
			else if (attName.find("scale") != std::string::npos)
			{
				double scale[3];
				transform.getScale(scale);
				if (debug) FileMapping::printInfo("NODE: " + transform.fullPathName() + "Scale changed: (" + MString() + scale[0] + " , " + MString() + scale[1] + " , " + MString() + scale[2] + ")");
			}
		}
		mAddMessage(transform.fullPathName().asChar(), msgEdited, nTransform);
		// If this transform has another transform as a child, send a message to that too
		// TODO: Support more levels of parenting
		if (transform.childCount() > 0)
		{
			int numChild = transform.childCount();
			for (int i = 0; i < numChild; i++)
			{
				if (transform.child(i).hasFn(MFn::kTransform))
				{
					MFnTransform childTrans(transform.child(i));
					mAddMessage(childTrans.fullPathName().asChar(), msgEdited, nTransform);
				}
			}
		}
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
		_CBidArray.append(MModelMessage::addNodeAddedToModelCallback(node, cbInstancing));
	}
	if (node.hasFn(MFn::kTransform))
	{
		MFnTransform trans(node);
		if (trans.childCount() > 0)
		{

			mAddNode(trans.fullPathName().asChar(), "", nTransform);
			MDagPath dPath = trans.dagPath();
			fAddAttributes(trans);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbTransformModified));
			_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			//_CBidArray.append(MDagMessage::addParentAddedDagPathCallback(trans.dagPath(), cbReparent));
			//_CBidArray.append(MDagMessage::addParentAddedDagPathCallback(*dPath, cbReparent));
			

			int pcount = trans.parentCount();
			MFnTransform parent(trans.parent(0));
			if (pcount > 0)
			{
				if (debug) FileMapping::printInfo("Transform parent: " + parent.fullPathName() + MString() + pcount);
			}

		}
	}
	if (node.hasFn(MFn::kLight))
	{
		if (debug) FileMapping::printInfo("Light created");

		MFnLight light(node);
		//outLightData(light.fullPathName().asChar());
		if (node.hasFn(MFn::kDirectionalLight))
		{
			if (debug) FileMapping::printInfo("Directional");
			//mAddNode(light.fullPathName().asChar(), "", nLight);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbLightAdd));
			//_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			//_CBidArray.append(MNodeMessage::addNameChangedCallback(node, &cbNameChange));
		}
		else if (node.hasFn(MFn::kSpotLight))
		{
			if (debug) FileMapping::printInfo("Spot");
			//mAddNode(light.fullPathName().asChar(), "", nLight);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbLightAdd));
			//_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			//_CBidArray.append(MNodeMessage::addNameChangedCallback(node, &cbNameChange));
		}
		else if (node.hasFn(MFn::kPointLight))
		{
			if (debug) FileMapping::printInfo("Point");
			//mAddNode(light.fullPathName().asChar(), "", nLight);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbLightAdd));
			//_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			//_CBidArray.append(MNodeMessage::addNameChangedCallback(node, &cbNameChange));
		}
	}
	if (node.hasFn(MFn::kLambert))
	{
		MFnDependencyNode mat(node);
		if (node.apiType() == MFn::kLambert)
		{
			mAddNode(mat.name().asChar(), "", nMaterial, 1);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbMaterialAttribute));
			_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			_CBidArray.append(MNodeMessage::addNameChangedCallback(node, &cbNameChange));
			if (debug) FileMapping::printInfo("Material added (Lambert)");
		}
		else if (node.apiType() == MFn::kPhong)
		{
			mAddNode(mat.name().asChar(), "", nMaterial, 2);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbMaterialAttribute));
			_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			_CBidArray.append(MNodeMessage::addNameChangedCallback(node, &cbNameChange));
			if (debug) FileMapping::printInfo("Material added (Phong)");
		}
		else if (node.apiType() == MFn::kBlinn)
		{
			mAddNode(mat.name().asChar(), "", nMaterial, 3);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(node, cbMaterialAttribute));
			_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(node, cbPreRemoveNode));
			_CBidArray.append(MNodeMessage::addNameChangedCallback(node, &cbNameChange));
			if (debug) FileMapping::printInfo("Material added (Blinn)");
		}

	}
}


void cbMessageTimer(float elapsedTime, float lastTime, void *clientData)
{
	//MGlobal::displayInfo("BOOOOOOOOOOOOOOB");
	bool asdf = false;
	//MGlobal::displayInfo("WOWOWOWOWO");
	if (msgVector.size() > 0)
	{
		for (std::vector<MessageInfo>::size_type i = 0; i != msgVector.size(); i++)
		{
			msgQueue.push(msgVector[i]);
		}
	}
	msgVector.clear();
	if (fileMap.getStatus() == true)
	{
		int msgCount = msgQueue.size();
		FileMapping::printInfo("\n--- TIMED MESSAGE UPDATE (" + MString() + msgCount + " Messages) ------------------------");
		bool run = true;
		int msgID = 0;
		while (!msgQueue.empty() && run == true)
		{

			FileMapping::printInfo("\n****** MESSAGE START (ID: " + MString() + msgID + ") **********************");
			if (msgQueue.front().msgType == MessageType::msgDeleted)
			{
				if (fileMap.tryWriteRenameDelete(msgQueue.front(), RenameDeleteInfo{ msgQueue.front().nodeName,"" }) == true)
				{
					msgQueue.pop();
				}
			}
			else if (msgQueue.front().msgType == MessageType::msgRenamed)
			{
				if (fileMap.tryWriteRenameDelete(msgQueue.front(), RenameDeleteInfo{ msgQueue.front().nodeName,msgQueue.front().oldName }) == true)
				{
					msgQueue.pop();
				}
			}
			else
			{
				switch (msgQueue.front().nodeType)
				{
				case(NodeType::nMesh) :
				{
					MeshInfo outMesh = outMeshData(msgQueue.front().nodeName);
					FileMapping::printInfo("*** MESSAGE: ( " + MString(msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[msgQueue.front().msgType].c_str() + " Mesh)");
					if (fileMap.tryWriteMesh(msgQueue.front(), outMesh) == true)
					{
						/*delete[] outMesh.meshData.uv;
						delete[] outMesh.meshData.triIndices;
						delete[] outMesh.meshData.norIndices;
						delete[] outMesh.meshData.UVIndices;
						delete[] outMesh.meshData.triPerFace;*/
						FileMapping::printInfo("*** MESSAGE Result( " + MString(msgQueue.front().nodeName.c_str()) + " ): Success");
						msgQueue.pop();
					}
					else
					{
						FileMapping::printInfo("*** MESSAGE result(" + MString(msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
						run = false;
					}
					break;
				}
				case(NodeType::nTransform) :
				{
					TransformInfo outTrans = outTransformData(msgQueue.front().nodeName);
					FileMapping::printInfo("*** MESSAGE: ( " + MString(msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[msgQueue.front().msgType].c_str() + " Transform)");
					if (fileMap.tryWriteTransform(msgQueue.front(), outTrans) == true)
					{
						FileMapping::printInfo("*** MESSAGE Result( " + MString(msgQueue.front().nodeName.c_str()) + " ): Success");
						msgQueue.pop();
					}
					else
					{
						FileMapping::printInfo("*** MESSAGE result(" + MString(msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
						run = false;
					}
					break;
					break;
				}
				case(NodeType::nCamera) :
				{
					CameraInfo outCam = outCameraData(msgQueue.front().nodeName);
					FileMapping::printInfo("*** MESSAGE: ( " + MString(msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[msgQueue.front().msgType].c_str() + " Camera)");
					if (fileMap.tryWriteCamera(msgQueue.front(), outCam) == true)
					{
						FileMapping::printInfo("*** MESSAGE Result( " + MString(msgQueue.front().nodeName.c_str()) + " ): Success");
						msgQueue.pop();
					}
					else
					{
						FileMapping::printInfo("*** MESSAGE result(" + MString(msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
						run = false;
					}
					break;
				}
				case(NodeType::nLight) :
				{
					LightInfo outLight = outLightData(msgQueue.front().nodeName);
					FileMapping::printInfo("*** MESSAGE: ( " + MString(msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[msgQueue.front().msgType].c_str() + " Light)");
					if (fileMap.tryWriteLight(msgQueue.front(), outLight) == true)
					{
						FileMapping::printInfo("*** MESSAGE Result( " + MString(msgQueue.front().nodeName.c_str()) + " ): Success");
						msgQueue.pop();
					}
					else
					{
						FileMapping::printInfo("*** MESSAGE result(" + MString(msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
						run = false;
					}
					break;
				}
				case(NodeType::nMaterial) :
				{
					MaterialInfo outMat = outMaterialData(msgQueue.front().nodeName);
					FileMapping::printInfo("*** MESSAGE: ( " + MString(msgQueue.front().nodeName.c_str()) + " ) (" + msgTypeVector[msgQueue.front().msgType].c_str() + " Material)");
					if (fileMap.tryWriteMaterial(msgQueue.front(), outMat) == true)
					{
						FileMapping::printInfo("*** MESSAGE Result( " + MString(msgQueue.front().nodeName.c_str()) + " ): Success");
						msgQueue.pop();
					}
					else
					{
						FileMapping::printInfo("*** MESSAGE result(" + MString(msgQueue.front().nodeName.c_str()) + "): Failed (Leaving in queue)");
						run = false;
					}
					break;
				}
				}
			}
			msgID++;
			FileMapping::printInfo("*** MESSAGE STOP *************************");
		}

	}
	
}

void loadScene()
{
	MStatus stat;
	MItDependencyNodes itDep(MFn::kLambert);
	while (!itDep.isDone())
	{
		if (itDep.thisNode().apiType() == MFn::kLambert)
		{
			MFnDependencyNode mat(itDep.thisNode());
			//FileMapping::printInfo("Found Material " + MString() + mat.name().asChar());
			mAddNode(mat.name().asChar(), "", nMaterial, 1);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(itDep.thisNode(), cbMaterialAttribute));
		}
		else if (itDep.thisNode().apiType() == MFn::kPhong)
		{
			MFnDependencyNode mat(itDep.thisNode());
			//FileMapping::printInfo("Found Material " + MString() + mat.name().asChar());
			mAddNode(mat.name().asChar(), "", nMaterial, 2);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(itDep.thisNode(), cbMaterialAttribute));
		}
		else if (itDep.thisNode().apiType() == MFn::kBlinn)
		{
			MFnDependencyNode mat(itDep.thisNode());
			//FileMapping::printInfo("Found Material " + MString() + mat.name().asChar());
			mAddNode(mat.name().asChar(), "", nMaterial, 3);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(itDep.thisNode(), cbMaterialAttribute));
		}
		itDep.next();
	}


	MFn::Type filter = MFn::kTransform;
	MItDag itTrans(MItDag::kDepthFirst, filter, &stat);
	for (; !itTrans.isDone(); itTrans.next())
	{
		
		MDagPath transDagPath;
		stat = itTrans.getPath(transDagPath);
		MFnDagNode transDagNode(transDagPath, &stat);
		int childCount = transDagNode.childCount();
		if (childCount > 0)
		{
			MFnTransform trans(transDagPath.node());
			MObject obj(transDagPath.node());
			fAddAttributes(trans);
			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(obj, cbTransformModified));
			_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(obj, cbPreRemoveNode));
			int pcount = trans.parentCount();
			MFnTransform transParent(trans.parent(0));
			mAddNode(trans.fullPathName().asChar(), transParent.fullPathName().asChar(), NodeType::nTransform);
			for (int i = 0; i < childCount; i++)
			{
				MObject child(trans.child(i));
				if (child.hasFn(MFn::kMesh))
				{
					
					MFnMesh mesh(trans.child(i), &stat);
					if (mesh.isInstanced())
					{
						//FileMapping::printInfo("\n\n\n\n\n\n\nFOUND INSTANCE LOL");
					}
					FileMapping::printInfo("MESH VERTS " + MString() + mesh.numVertices());
					if (mesh.numVertices() > 0)
					{
						if (stat)
						{
							std::string name = mesh.fullPathName().asChar();
							if (name.find("SurfaceShape") == std::string::npos)
							{
								MString myCommand = "setAttr -e " + mesh.name() + ".quadSplit 0";
								MGlobal::executeCommandOnIdle(myCommand);
								//_CBidArray.append(MNodeMessage::addAttributeChangedCallback(child, cbMeshAttribute));
								_CBidArray.append(MNodeMessage::addAttributeChangedCallback(child, cbMeshAttributeChange));
								_CBidArray.append(MPolyMessage::addPolyTopologyChangedCallback(child, cbPolyChanged));
								_CBidArray.append(MDGMessage::addNodeRemovedCallback(cbRemovedNode, "dependNode"));
								_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(child, cbPreRemoveNode));
								mAddNode(mesh.fullPathName().asChar(), trans.fullPathName().asChar(), NodeType::nMesh);
							}

						}
					}


				}
				else if (child.hasFn(MFn::kCamera))
				{
					MFnCamera cam(child);
					_CBidArray.append(MNodeMessage::addAttributeChangedCallback(child, cbCamAttribute));
					mAddNode(cam.fullPathName().asChar(), trans.fullPathName().asChar(), NodeType::nCamera);
				}
				else if (child.hasFn(MFn::kLight))
				{
					if (child.hasFn(MFn::kDirectionalLight) || child.hasFn(MFn::kSpotLight) || child.hasFn(MFn::kPointLight))
					{
						MFnLight light(child);
						//FileMapping::printInfo("WOAOAOAWOAWDKOASKDOAS "+trans.fullPathName()+"  KDOASKDKOASKDASOKDOSAKDOSA\n\n"+light.fullPathName()+"\n");
						mAddNode(light.fullPathName().asChar(), trans.fullPathName().asChar(), nLight);
						
						_CBidArray.append(MNodeMessage::addAttributeChangedCallback(child, cbLightAttribute));
						_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(child, cbPreRemoveNode));
						_CBidArray.append(MNodeMessage::addNameChangedCallback(child, &cbNameChange));
					}
				}
				else if (child.hasFn(MFn::kTransform))
				{
					MFnTransform childTransform(child);
					_CBidArray.append(MNodeMessage::addAttributeChangedCallback(child, cbTransformModified));
					_CBidArray.append(MNodeMessage::addNodePreRemovalCallback(child, cbPreRemoveNode));

					mAddNode(childTransform.fullPathName().asChar(), trans.fullPathName().asChar(), NodeType::nTransform);
				}
				else
				{
					MFnDagNode dNode(trans.child(i));
					if (dNode.isInstanced())
					{
						//FileMapping::printInfo("\n\n\n\n\n\n\nFOUND INSTANCE LOL");
					}
				}
			}

		}
	}

	filter = MFn::kCamera;
	MItDag dagIt(MItDag::kDepthFirst, filter, &stat);

	//for (; !dagIt.isDone(); dagIt.next())
	//{
	//	MDagPath dagPath;
	//	stat = dagIt.getPath(dagPath);
	//	MFnDagNode dagNode(dagPath, &stat);
	//	std::string transname;
	//	if (dagPath.hasFn(MFn::kCamera))
	//	{
	//		
	//		_CBidArray.append(MNodeMessage::addAttributeChangedCallback(dagPath.node(), cbCamAttribute));
	//		outCameraData(dagPath.fullPathName().asChar());
	//		MObject parent = dagNode.parent(0);
	//		if (parent.hasFn(MFn::kTransform))
	//		{
	//			MFnTransform trans(parent);
	//			transname = trans.fullPathName().asChar();
	//			//mAddNode(trans.fullPathName().asChar(),"", nTransform);
	//			_CBidArray.append(MNodeMessage::addAttributeChangedCallback(parent, cbTransformModified));
	//		}
	//		mAddNode(dagPath.fullPathName().asChar(), transname.c_str(), nCamera);
	//	}
	//	
	//}
	stat = modelPanel.getCamera(activeCamera);

	FileMapping::printInfo("CURRENT CAMERA " + activeCamera.fullPathName());

	if (stat)
	{
		mAddMessage(activeCamera.fullPathName().asChar(), msgSwitched, nCamera);
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
	fFillAttributesList();
	//OpenFileMaps::fMap = &fileMap;
	//result = editorPlugin.registerCommand("execFileMaps", OpenFileMaps::creator);
	fileMap.CreateFileMaps(true);

	FileMapping::printInfo("Level Editor plugin loaded.\n");
	result = M3dView::getM3dViewFromModelPanel("modelPanel4", modelPanel);
	loadScene();
	debug = fileMap.debug;
	FileMapping::printInfo("debug:  " + MString() + debug);
	msgTypeVector.push_back("Invalid msg type");
	msgTypeVector.push_back("Added");
	msgTypeVector.push_back("Edited");
	msgTypeVector.push_back("Deleted");
	msgTypeVector.push_back("Renamed");
	msgTypeVector.push_back("Switched");


	//_CBidArray.append(MNodeMessage::addNameChangedCallback(MObject::kNullObj, &cbNameChange));
	_CBidArray.append(MDGMessage::addNodeAddedCallback(cbNewNode));
	_CBidArray.append(MTimerMessage::addTimerCallback(0.2f, &cbMessageTimer));
	_CBidArray.append(MUiMessage::addCameraChangedCallback("modelPanel4", cbCameraPanel));
	_CBidArray.append(MDagMessage::addParentAddedCallback(cbAddParent));
	_CBidArray.append(MDagMessage::addChildReorderedCallback(cbRemoveParent));
	_CBidArray.append(MModelMessage::addAfterDuplicateCallback(cbDuplication));

	return result;

}

EXPORT MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin(obj);

	FileMapping::printInfo("Level Editor plugin unloaded.");
	MMessage::removeCallbacks(_CBidArray);


	return MS::kSuccess;
}

//MeshInfo outMeshData(std::string name, bool getDynamicData)
//{
//	// Find mesh node in Dag
//	MStatus			result;
//	MString			_name(name.c_str());
//	MSelectionList	sList;
//	MDagPath		dagPath;
//
//	if (MGlobal::getSelectionListByName(_name, sList))
//	{
//		sList.getDagPath(0, dagPath);
//		if (dagPath.hasFn(MFn::kMesh))
//		{
//			FileMapping::printInfo("Mesh found: " + dagPath.fullPathName());
//		}
//	}
//
//	MFnMesh			mNode(dagPath.node(), &result);
//	MItMeshPolygon	polyIterator(dagPath.node(), &result);
//	MeshInfo		outMesh;
//	
//	// Variable declaration for mesh analysis
//	const float*	vertices = mNode.getRawPoints(&result);
//	const float*	normals = mNode.getRawNormals(&result);
//	MFloatArray		uArray;
//	MFloatArray		vArray;
//	mNode.getUVs(uArray, vArray);
//
//	MIntArray		triCount;
//	MIntArray		triVerts;
//	mNode.getTriangles(triCount, triVerts);
//	MIntArray		triNorIndices;
//	MIntArray		triUVIndices;
//	
//	MIntArray vCount, posIndices;
//	mNode.getVertices(vCount, posIndices);
//
//	MIntArray uvPerPoly, uvIndices;
//	mNode.getAssignedUVs(uvPerPoly, uvIndices);
//
//	MIntArray norPerPoly, norIndices;
//	mNode.getNormalIds(norPerPoly, norIndices);
//
//	MIntArray trisPerFaceOff, offsetIndices;
//	mNode.getTriangleOffsets(trisPerFaceOff, offsetIndices);
//
//	for (int i = 0; i < posIndices.length(); i++)
//	{
//
//	}
//
//	int				totTris = 0;
//	int				triCountThisPoly = 0;
//	
//
//	if (mNode.parent(0).hasFn(MFn::kTransform))
//	{
//		MFnTransform mTrans(mNode.parent(0), &result);
//		if (!result)
//		{
//			FileMapping::printError(MString(name.c_str()) + " parent not found!");
//		}
//		else
//		{
//			outMesh.transformName = mTrans.fullPathName().asChar();
//			FileMapping::printInfo(outMesh.transformName.c_str());
//		}
//	}
//
//	outMesh.meshData.vertCount = mNode.numVertices();
//	outMesh.meshData.normalCount = mNode.numNormals();
//	outMesh.meshData.UVCount = mNode.numUVs();
//
//	outMesh.meshData.vertices = vertices;
//	outMesh.meshData.normals = normals;
//
//	outMesh.meshData.triPerFace = new int[triCount.length()];
//	triCount.get(outMesh.meshData.triPerFace);
//
//	outMesh.meshData.uv = new float2[mNode.numUVs()];
//	for (int i = 0; i < outMesh.meshData.UVCount; i++)
//	{
//		outMesh.meshData.uv[i][0] = uArray[i];
//		outMesh.meshData.uv[i][1] = vArray[i];
//	}
//
//	outMesh.meshData.indCount = offsetIndices.length();
//	outMesh.meshData.triCount = triCount.length();
//
//	outMesh.meshData.triIndices = new int[outMesh.meshData.indCount];
//	 triVerts.get(outMesh.meshData.triIndices);
//
//	outMesh.meshData.norIndices = new int[norIndices.length()];
//	norIndices.get(outMesh.meshData.norIndices);
//	//triNorIndices.get(outMesh.meshData.norIndices);
//
//	outMesh.meshData.UVIndices = new int[uvIndices.length()];
//	uvIndices.get(outMesh.meshData.UVIndices);
//
//	// Prints general mesh data
//	if (true)
//	{
//		FileMapping::printInfo("outMesh Name: " + MString(name.c_str()));
//		FileMapping::printInfo("outMesh Transform Name: " + MString(outMesh.transformName.c_str()));
//		FileMapping::printInfo("outMesh Vert/Nor/UV Count: " + MString() + outMesh.meshData.vertCount + " / " + MString() + outMesh.meshData.normalCount + " / " + MString() + outMesh.meshData.UVCount);
//		FileMapping::printInfo("outMesh Indices / Triangle Count: " + MString() + outMesh.meshData.indCount + " / "+ MString() + triUVIndices.length() + " / " + MString() + totTris);
//		MString triFaceStr = " ( ";
//		MString triIndStr = "";
//		for (int i = 0; i < triCount.length(); i++)
//		{
//
//			if (i != triCount.length() - 1)
//			{
//				triFaceStr += MString() + outMesh.meshData.triPerFace[i] + " , ";
//				//triIndStr += MString() + outMesh.triIndices[i] + "," + MString() + outMesh.norIndices[i] + "," + MString() + outMesh.UVIndices[i] + ")";
//			}
//
//			else
//			{
//				triFaceStr += MString() + outMesh.meshData.triPerFace[i];
//				//triIndStr += MString() + outMesh.triIndices[i] + "," + MString() + outMesh.norIndices[i] + "," + MString() + outMesh.UVIndices[i] + ")";
//			}
//
//		}
//		FileMapping::printInfo("outMesh Tris per Polygon: " + triFaceStr + " )");
//		
//		// Prints vertex data
//		bool dbug2 = true;
//		MString iDataStr = "";
//		if (dbug2)
//		{
//			
//			for (int i = 0; i + 3 < outMesh.meshData.indCount; i += 3)
//			{
//				triIndStr += "(";
//				triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i] + "," + MString() + outMesh.meshData.norIndices[i] + "," + MString() + outMesh.meshData.UVIndices[i] + ")");
//				triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i + 1] + "," + MString() + outMesh.meshData.norIndices[i + 1] + "," + MString() + outMesh.meshData.UVIndices[i + 1] + ")");
//				triIndStr += ("(" + MString() + outMesh.meshData.triIndices[i + 2] + "," + MString() + outMesh.meshData.norIndices[i + 2] + "," + MString() + outMesh.meshData.UVIndices[i + 2] + ")");
//				
//				triIndStr += ")\n";
//			}
//
//
//			/*for (int i = 0; i < outMesh.meshData.normalCount*3; i+=3)
//			{
//				iDataStr += "Pos ";
//				iDataStr += "(" + MString() + outMesh.meshData.vertices[i] + " , ";
//				iDataStr += MString() + outMesh.meshData.vertices[i+1] + " , ";
//				iDataStr += MString() + outMesh.meshData.vertices[i+2] + ")";
//
//				iDataStr += "Nor ";
//				iDataStr += "(" + MString() + outMesh.meshData.normals[i] + " , ";
//				iDataStr += MString() + outMesh.meshData.normals[i + 1] + " , ";
//				iDataStr += MString() + outMesh.meshData.normals[i + 2] +")";
//
//				iDataStr += "UV ";
//				iDataStr += "(" + MString() + outMesh.meshData.uv[i][0] + " , ";
//				iDataStr += MString() + outMesh.meshData.uv[i][1] + ")\n";
//			}*/
//
//		}
//		FileMapping::printInfo("outMesh Indices per triangle: " + triIndStr);
//		if(dbug2)FileMapping::printInfo(iDataStr);
//		
//	}
//
//
//
//
//	MObjectArray connectedShaders;
//	MIntArray shaderIndices;
//	mNode.getConnectedShaders(0, connectedShaders, shaderIndices);
//	MFnDependencyNode shaderGroup(connectedShaders[0]);
//	MPlug plug = shaderGroup.findPlug("surfaceShader");
//	MPlugArray connections;
//	plug.connectedTo(connections, true, false);
//	int matindex = -1;
//	for (uint i = 0; i < connections.length(); i++)
//	{
//		if (connections[i].node().hasFn(MFn::kLambert))
//		{
//			matindex = i;
//			if(debug) FileMapping::printInfo("Num of connections "+MString()+connections.length() + MString()+connections[i].name().asChar()+ MString()+shaderGroup.name().asChar());
//		}
//	}
//	if (matindex >= 0)
//	{
//		MFnDependencyNode mat(connections[matindex].node());
//		FileMapping::printInfo(mat.name().asChar());
//		outMesh.materialName = mat.name().asChar();
//	}
//	else
//	{
//		outMesh.materialName = "ERROR NONE";
//	}
//	
//	outMesh.meshID = 5;
//	outMesh.materialID = 8;
//	if(debug) FileMapping::printInfo("MAT MESH ID: " + MString() + outMesh.meshID + " " + MString() + outMesh.materialID + outMesh.materialName.c_str());
//	FileMapping::printInfo("MESH INDEX COUNTS(V,N,UV): " + MString() + offsetIndices.length() + " " + MString() + norIndices.length() + " " + MString() + uvIndices.length());
// 	
//	
//	return outMesh;
//}