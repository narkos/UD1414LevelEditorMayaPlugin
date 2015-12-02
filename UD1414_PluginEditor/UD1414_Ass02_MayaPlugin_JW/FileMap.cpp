#include "FileMap.h"


FileMapping::FileMapping()
{
	//mutexInfo.Unlock();
	_headerSize = sizeof(MessageHeader);
	headerFit;
}

FileMapping::~FileMapping()
{
	//mutexInfo.Unlock();

	std::string str;
	bool m = UnmapViewOfFile((LPCVOID)mMessageData);
	/*str = GetLastErrorAsString();
	MGlobal::displayInfo("Last Error: " + MString(str.c_str()));*/
	if (GetLastError() != 0)
	{
		MGlobal::displayInfo("Error");
	}
	if (m!=0) 
		MGlobal::displayInfo("Filemap closed");
	m = CloseHandle(hMessageFileMap);
	/*str = GetLastErrorAsString();
	MGlobal::displayInfo("Last Error: " + MString(str.c_str()));*/
	if (GetLastError() != 0)
	{
		MGlobal::displayInfo("Error");
	}
	if (m != 0)
		MGlobal::displayInfo("Filemap closed");
	

	bool n = UnmapViewOfFile((LPCVOID)mInfoData);
	/*str = GetLastErrorAsString();
	MGlobal::displayInfo("Last Error: " + MString(str.c_str()));*/
	if (GetLastError() != 0)
	{
		MGlobal::displayInfo("Error");
	}
	if (n != 0)
		MGlobal::displayInfo("InfoFilemap closed");
	n = CloseHandle(hInfoFileMap);
	/*str = GetLastErrorAsString();
	MGlobal::displayInfo("Last Error: " + MString(str.c_str()));*/
	if (GetLastError() != 0)
	{
		MGlobal::displayInfo("Error");
	}
	if (n != 0)
		MGlobal::displayInfo("InfoFilemap closed");

	
}

void FileMapping::CreateFileMaps()
{
	mInfoSize = 1 << 6;
	//info filemapen
	hInfoFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		(DWORD)0,
		mInfoSize,
		(LPCWSTR) "infoFileMap"); 

	mInfoData = MapViewOfFile(hInfoFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	//MGlobal::displayInfo("mInfoSize: " + MString() + mInfoSize);
	mutexInfo.Create("__info_Mutex__");
	
	//SetFilemapInfoValues(0, 0, 0, mSize); //storar de i filemapen oxå! sätt negativa värden om man inte vill nått värde ska ändras :)

	if (hInfoFileMap == NULL) {
		MGlobal::displayInfo("Couldn't create infofilemap");
	}
	//FilemapInfo fmInfo;
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MGlobal::displayInfo("Infofilemap exists, you get a handle to it!");
		GetFilemapInfoValues();
	}
	else { //first, sätter de första värdena på filemapinfon
		MGlobal::displayInfo("Creating new infofilemap, JAG SKA INTE VARA FÖRST :'(");
		//GetFilemapInfoValues();
		SetFilemapInfoValues(0, 0, 256, 4096);
	}
	memoryPadding = fileMapInfo.non_accessmemoryOffset;
	
	//mSize = 2048; //denna ska hämtas
	hMessageFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		(DWORD)0,
		mSize,
		(LPCWSTR) "messageFileMap");

	mMessageData = MapViewOfFile(hMessageFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	if (hMessageFileMap == NULL) {
		MGlobal::displayInfo("Couldn't create filemap");
	}
	else if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MGlobal::displayInfo("Filemap exists, you get a handle to it!");

	}
	else {
	
		MGlobal::displayInfo("Creating new filemap");
	}


	MGlobal::displayInfo("FileMapSize: " + MString() + mSize +" "+ MString()+fileMapInfo.non_accessmemoryOffset);
}

void FileMapping::GetFilemapInfoValues()
{
	while (mutexInfo.Lock(1000) == false) Sleep(10);
	memcpy(&fileMapInfo, (unsigned char*)mInfoData, sizeof(FilemapInfo)); //får inget värde!!!!!!! default värdet är fortfarande kvar
	mSize = fileMapInfo.messageFilemap_Size;
	MGlobal::displayInfo("MessageFMMemorySize: " + MString() + fileMapInfo.messageFilemap_Size);
	MGlobal::displayInfo("Nonaccess: " + MString()+fileMapInfo.non_accessmemoryOffset);
	mutexInfo.Unlock();
}

void FileMapping::SetFilemapInfoValues(size_t headPlacement, size_t tailPlacement, size_t nonAccessMemoryPlacement, size_t messageFileMapTotalSize) {
	while (mutexInfo.Lock(1000) == false) Sleep(10);
	memcpy(&fileMapInfo, (unsigned char*)mInfoData, sizeof(FilemapInfo));
	if (headPlacement >= 0)
		fileMapInfo.head_ByteOffset = headPlacement;
	if (tailPlacement >= 0)
		fileMapInfo.tail_ByteOffset = tailPlacement;
	if (nonAccessMemoryPlacement >= 0)
		fileMapInfo.non_accessmemoryOffset = nonAccessMemoryPlacement;
	if (messageFileMapTotalSize > 0)
		fileMapInfo.messageFilemap_Size = messageFileMapTotalSize;
	mSize = messageFileMapTotalSize;
	memcpy((unsigned char*)mInfoData, &fileMapInfo, sizeof(FilemapInfo));	
	mutexInfo.Unlock();
}


bool FileMapping::tryWriteTransform(MessageInfo& msg, TransformInfo& tinfo)
{
			MessageHeader mHeader = createHeaderTransform(msg, tinfo);
			int cfg = findWriteConfig(mHeader);
			if (cfg != 0)
			{
				if (writeTransform(mHeader, createMessageTransform(msg, tinfo), cfg) == true)
				{
					return true;
				}
			}
			else
			{
				return false;
			}
	return false;
}
bool FileMapping::tryWriteMesh(MessageInfo& msg, MeshInfo& minfo)
{
		/*MGlobal::displayInfo("FileMap Msg: Mesh Message found");
		MessageHeader mHeader = createHeaderMesh(msg, minfo);
		int cfg = findWriteConfig(mHeader);
		createMessageMesh(msg, minfo);*/

	return false;
}
bool FileMapping::tryWriteCamera(MessageInfo& msg, CameraInfo& cinfo)
{
	
		MGlobal::displayInfo("FileMap Msg: Mesh Message found");
		MessageHeader mHeader = createHeaderCamera(msg, cinfo);
		int cfg = findWriteConfig(mHeader);
		createMessageCamera(msg, cinfo);

	return false;
}
bool FileMapping::tryWriteMaterial(MessageInfo& msg, MaterialInfo& minfo)
{

		MGlobal::displayInfo("FileMap Msg: Mesh Message found");
		MessageHeader mHeader = createHeaderMaterial(msg, minfo);
		int cfg = findWriteConfig(mHeader);
		createMessageMaterial(msg, minfo);

	
	return false;
}
bool FileMapping::tryWriteLight(MessageInfo& msg, LightInfo& linfo)
{

		MGlobal::displayInfo("FileMap Msg: Mesh Message found");
		MessageHeader mHeader = createHeaderLight(msg, linfo);
		int cfg = findWriteConfig(mHeader);
		createMessageLight(msg, linfo);

	return false;
}

// Write config return values
// 0: Can't write
// 1: Can write normally
// 2: Header fits before buffer end, but message will have to be moved to the beginning of the buffer
int FileMapping::findWriteConfig(MessageHeader& hdr)
{
	while (mutexInfo.Lock(1000) == false) Sleep(10);
	memcpy(&fileMapInfo, (unsigned char*)mInfoData, sizeof(FilemapInfo));

	localHead = fileMapInfo.head_ByteOffset;
	localTail = fileMapInfo.tail_ByteOffset;

	if (localHead >= localTail)
	{
		if (hdr.byteSize + hdr.bytePadding + localHead + memoryPadding <= mSize)
		{
			MGlobal::displayInfo("*   MSG Config (CAN WRITE NORMALLY)");
			return 1;
		}
		else if (localHead + sizeof(MessageHeader) <= mSize && makeMultiple(hdr.byteSize - sizeof(MessageHeader), 256)+ memoryPadding <=localTail)
		{
			MGlobal::displayInfo("*   MSG Config (CAN WRITE WITH SPLIT)");
			size_t tempTotal;
			tempTotal = makeMultiple(hdr.byteSize - sizeof(MessageHeader), 256);
			hdr.bytePadding = tempTotal - hdr.byteSize;
			return 2;
		}
	}
	else
	{
		if (hdr.byteSize + hdr.bytePadding + localHead + memoryPadding <= localTail)
		{
			MGlobal::displayInfo("*   MSG Config (CAN WRITE NORMALLY)");
			return 1;
		}
	}
	MGlobal::displayInfo("*   MSG Config (CANNOT WRITE)");
	MGlobal::displayInfo("*   HEAD POSITION: " + MString() + localHead + " TAIL POSISH: " +MString() + localTail);
	mutexInfo.Unlock();
	return 0;

}
bool FileMapping::writeTransform(MessageHeader& hdr, TransformMessage& tdata, int config)
{
	int cfg = config;
	/*MGlobal::displayInfo("TRANSFORM OUTER DATA: " + MString(tdata.nodeName));
	MGlobal::displayInfo("Pos: " + MString() + tdata.trData.translation[0] + " " + MString() + tdata.trData.translation[1] + " " + MString() + tdata.trData.translation[2]);
	MGlobal::displayInfo("Rot: " + MString() + tdata.trData.rotation[0] + " " + MString() + tdata.trData.rotation[1] + " " + MString() + tdata.trData.rotation[2]);
	MGlobal::displayInfo("Sca: " + MString() + tdata.trData.scale[0] + " " + MString() + tdata.trData.scale[1] + " " + MString() + tdata.trData.scale[2]);*/
	switch (cfg)
	{
	case 1:
		PrintFileMapInfo(false);
		memcpy((unsigned char*)mMessageData + localHead, &hdr, sizeof(MessageHeader));
		
		localHead +=sizeof(MessageHeader);
		memcpy((unsigned char*)mMessageData + localHead, &tdata, hdr.byteSize - sizeof(MessageHeader));

		localHead += hdr.byteSize+hdr.bytePadding - sizeof(MessageHeader);

		while (mutexInfo.Lock(1000) == false) Sleep(10);
		memcpy(&fileMapInfo, (unsigned char*)mInfoData, sizeof(FilemapInfo));
		if (localHead == mSize)
		{
			localHead = 0;
		}
		fileMapInfo.head_ByteOffset = localHead;
		memcpy((unsigned char*)mInfoData, &fileMapInfo, sizeof(FilemapInfo));
		mutexInfo.Unlock();
		PrintFileMapInfo(true);
		return true;
		break;

	case 2:
		PrintFileMapInfo(false);
		memcpy((unsigned char*)mMessageData + localHead, &hdr, sizeof(MessageHeader));
		localHead = 0;
		memcpy((unsigned char*)mMessageData, &tdata, hdr.byteSize - sizeof(MessageHeader));
		localHead += hdr.byteSize + hdr.bytePadding;

		while (mutexInfo.Lock(1000) == false) Sleep(10);
		memcpy(&fileMapInfo, (unsigned char*)mInfoData, sizeof(FilemapInfo));
		fileMapInfo.head_ByteOffset = localHead;
		memcpy((unsigned char*)mInfoData, &fileMapInfo, sizeof(FilemapInfo));
		mutexInfo.Unlock();
		PrintFileMapInfo(true);
		break;

	case 3:

		break;
	}



	return false;
}
bool FileMapping::writeMesh(MessageHeader& hdr, MeshMessage& mdata, int config)
{
	int cfg = config;
	switch (cfg)
	{
		case 1:
			memcpy((unsigned char*)mMessageData + localHead, &hdr, sizeof(MessageHeader));
			localHead += sizeof(MessageHeader);
			memcpy((unsigned char*)mMessageData + localHead, &mdata, hdr.byteSize - sizeof(MessageHeader));
			localHead += hdr.byteSize + hdr.bytePadding - sizeof(MessageHeader);
			fileMapInfo.head_ByteOffset = localHead;
			memcpy(mInfoData, &fileMapInfo, sizeof(FilemapInfo));

			break;

		case 2:

			break;

		case 3:

			break;
	}



	return false;
}
bool FileMapping::writeCamera(MessageHeader& hdr, CameraMessage& cdata, int config)
{
	int cfg = config;
	switch (cfg)
	{
	case 1:

		break;

	case 2:

		break;

	case 3:

		break;
	}



	return false;
}
bool FileMapping::writeMaterial(MessageHeader& hdr, MaterialMessage& mdata, int config)
{
	int cfg = config;
	switch (cfg)
	{
	case 1:

		break;

	case 2:

		break;

	case 3:

		break;
	}



	return false;
}
bool FileMapping::writeLight(MessageHeader& hdr, LightMessage& ldata, int config)
{
	int cfg = config;
	switch (cfg)
	{
	case 1:

		break;

	case 2:

		break;

	case 3:

		break;
	}



	return false;
}


MessageHeader FileMapping::createHeaderMesh(MessageInfo& msginfo, MeshInfo& minfo)
{
	size_t totalSize;
	size_t msgSize; 
	size_t padding;
	size_t infoSize;
	infoSize = 200 * sizeof(char);

	MeshInfo mInfo = minfo;

	msgSize =		mInfo.meshData.vertCount * sizeof(float);
	msgSize +=		mInfo.meshData.normalCount * sizeof(float);
	msgSize +=		2 * (mInfo.meshData.UVCount *sizeof(float));
	msgSize +=		3 * (mInfo.meshData.indCount * sizeof(int));
	msgSize +=		mInfo.meshData.triCount * sizeof(int);

	MGlobal::displayInfo(":: Info byte size: " + MString()+infoSize);
	MGlobal::displayInfo(":: Mesh data byte size: " + MString() + msgSize);
	MGlobal::displayInfo(":: Header byte size: " + MString() + _headerSize);
	msgSize += infoSize;
	msgSize += _headerSize;
	MGlobal::displayInfo(":: MESSAGE BYTE SIZE: " + MString() + msgSize);
	totalSize = makeMultiple(msgSize, 256);
	padding = totalSize - msgSize;
	MGlobal::displayInfo(":: Padding byte size: " + MString() + padding);
	MGlobal::displayInfo(":: TOTAL BYTE SIZE: " + MString() + totalSize);
	MGlobal::displayInfo(":: Node Name Length: " + MString(msginfo.nodeName.c_str()) + MString() + mInfo.nodeName.length());

	MessageHeader hdr;
	hdr.nodeType = msginfo.nodeType;
	hdr.messageType = msginfo.msgType;
	hdr.byteSize = msgSize;
	hdr.bytePadding = padding;

	return hdr;
	//return 0;
}
MessageHeader FileMapping::createHeaderTransform(MessageInfo& msginfo, TransformInfo &tInfo)
{
	size_t totalSize;
	size_t msgSize;
	size_t padding;
	size_t infoSize;
	//infoSize = 200 * sizeof(char);
	msgSize = sizeof(TransformMessage) + sizeof(MessageHeader);
	
	totalSize = makeMultiple(msgSize, 256);
	padding = totalSize - msgSize;
	 MGlobal::displayInfo("*   Transform Message Sizes(HDR,MSG,PDG,TOT): " + MString() + sizeof(TransformMessage) + " " + sizeof(MessageHeader)
		+ " " + MString() + padding + " " + MString() + totalSize);

	MessageHeader hdr;
	hdr.nodeType = msginfo.nodeType;
	hdr.messageType = msginfo.msgType;
	hdr.byteSize = msgSize;
	hdr.bytePadding = padding;

	return hdr;
	//return 0;
}
MessageHeader FileMapping::createHeaderCamera(MessageInfo& msginfo, CameraInfo& cInfo)
{
	size_t totalSize;
	size_t msgSize;
	size_t padding;
	size_t infoSize;
	infoSize = 200 * sizeof(char);

	MessageHeader hdr;
	hdr.nodeType = msginfo.nodeType;
	hdr.messageType = msginfo.msgType;
	hdr.byteSize = msgSize;
	hdr.bytePadding = padding;

	return hdr;
	//return 0;
}
MessageHeader FileMapping::createHeaderMaterial(MessageInfo& msginfo, MaterialInfo& mInfo)
{
	size_t totalSize;
	size_t msgSize;
	size_t padding;
	size_t infoSize;
	infoSize = 200 * sizeof(char);

	MessageHeader hdr;
	hdr.nodeType = msginfo.nodeType;
	hdr.messageType = msginfo.msgType;
	hdr.byteSize = msgSize;
	hdr.bytePadding = padding;

	return hdr;
	//return 0;
}
MessageHeader FileMapping::createHeaderLight(MessageInfo& msginfo, LightInfo& lInfo)
{
	size_t totalSize;
	size_t msgSize;
	size_t padding;
	size_t infoSize;
	infoSize = 200 * sizeof(char);

	MessageHeader hdr;
	hdr.nodeType = msginfo.nodeType;
	hdr.messageType = msginfo.msgType;
	hdr.byteSize = msgSize;
	hdr.bytePadding = padding;

	return hdr;
	//return 0;
}


MeshMessage FileMapping::createMessageMesh(MessageInfo& msginfo, MeshInfo &mInfo)
{
	MeshMessage msg;

	int nodeNameLength = msginfo.nodeName.length();
	int transformNameLength = mInfo.transformName.length();
	if (nodeNameLength <= 100)
	{
		for (int i = 0; i < nodeNameLength; i++)
		{
			msg.nodeName[i] = msginfo.nodeName[i];
		}
		//msg.nodeName[nodeNameLength] = (char)"\0";
		msg.nodeName[nodeNameLength] = '\0';
	}
	else
	{
		MGlobal::displayError("Node name too long!");
	}
	if (transformNameLength <= 100)
	{
		for (int i = 0; i < transformNameLength; i++)
		{
			msg.transformName[i] = mInfo.transformName[i];
		}
		//msg.nodeName[nodeNameLength] = (char)"\0";
		msg.transformName[transformNameLength] = '\0';
	}
	else
	{
		MGlobal::displayError("Transform name too long!");
	}
	msg.meshData = &mInfo.meshData;
	MGlobal::displayInfo(MString() + msg.meshData->indCount);
	return msg;
}
TransformMessage FileMapping::createMessageTransform(MessageInfo& msginfo, TransformInfo &tInfo)
{
	TransformMessage outMsg;

	int nodeNameLength = msginfo.nodeName.length();
	int parentNameLength = tInfo.parentName.length();
	if (nodeNameLength <= 100)
	{
		for (int i = 0; i < nodeNameLength; i++)
		{
			outMsg.nodeName[i] = msginfo.nodeName[i];
		}
		//MGlobal::displayInfo("Node name added!");
		outMsg.nodeName[nodeNameLength] = '\0';
	}
	else
	{
		MGlobal::displayError("* Node name too long!");
	}
	if (parentNameLength <= 100)
	{
		for (int i = 0; i < parentNameLength; i++)
		{
			outMsg.parentName[i] = tInfo.parentName[i];
		}
		outMsg.parentName[parentNameLength] = '\0';
	}
	else
	{
		MGlobal::displayError("* Transform name too long!");
	}
	outMsg.trData = tInfo.transformData;
	//MGlobal::displayInfo(MString() + outMsg.meshData->indCount);

	return outMsg;
}
CameraMessage FileMapping::createMessageCamera(MessageInfo& msginfo, CameraInfo& cInfo)
{
	CameraMessage outMsg;
	return outMsg;
}
MaterialMessage FileMapping::createMessageMaterial(MessageInfo& msginfo, MaterialInfo& mInfo)
{
	MaterialMessage outMsg;
	return outMsg;
}
LightMessage FileMapping::createMessageLight(MessageInfo& msgInfo, LightInfo& lInfo)
{
	LightMessage outMsg;
	return outMsg;
}


size_t FileMapping::makeMultiple(size_t size, size_t multiple)
{
	size_t modValue;
	modValue = size % multiple;
	//std::cout << "\nModvalue: " << modValue << "\n";
	if (modValue == 0)
	{
		return size;
	}

	return size + multiple - modValue;
}

void FileMapping::PrintFileMapInfo(bool isPost)
{
	std::string str;
	if (isPost)
	{
		str = "POST";
	}
	else
	{
		str = "PRE";
	}
		
	MGlobal::displayInfo("* ! Infovalues " + MString(str.c_str()) + " message(HEAD, TAIL, NAM, SIZE): " +
		MString() + fileMapInfo.head_ByteOffset + " " + MString() + fileMapInfo.tail_ByteOffset + " " +
		MString() + fileMapInfo.non_accessmemoryOffset + " " + MString() + fileMapInfo.messageFilemap_Size);

	return;
}

std::string FileMapping::GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return std::string(); //No error message has been recorded

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}