#include "FileMap.h"


FileMapping::FileMapping()
{
	_headerSize = sizeof(MessageHeader);
	headerFit;
}

FileMapping::~FileMapping()
{
	bool m = UnmapViewOfFile((LPCVOID)mMessageData);
	if (m!=0) 
		MGlobal::displayInfo("Filemap closed");
	m = CloseHandle(hMessageFileMap);
	if (m != 0)
		MGlobal::displayInfo("Filemap closed");
	

	bool n = UnmapViewOfFile((LPCVOID)mInfoData);
	if (n != 0)
		MGlobal::displayInfo("InfoFilemap closed");
	n = CloseHandle(hInfoFileMap);
	if (n != 0)
		MGlobal::displayInfo("InfoFilemap closed");

	
}

void FileMapping::CreateFileMaps()
{

	//info filemapen
	hInfoFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		(DWORD)0,
		mInfoSize,
		(LPCWSTR) "infoFileMap");

	//MGlobal::displayInfo("mInfoSize: " + MString() + mInfoSize);
	mutexInfo.Create("__info_Mutex__");

	mInfoData = MapViewOfFile(hInfoFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	//SetFilemapInfoValues(0, 0, 0, mSize); //storar de i filemapen oxå! sätt negativa värden om man inte vill nått värde ska ändras :)

	if (hInfoFileMap == NULL) {
		MGlobal::displayInfo("Couldn't create infofilemap");
	}
	//FilemapInfo fmInfo;
	else if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MGlobal::displayInfo("Infofilemap exists, you get a handle to it!");
		GetFilemapInfoValues();
	}
	else { //first, sätter de första värdena på filemapinfon
		MGlobal::displayInfo("Creating new infofilemap");
		SetFilemapInfoValues(0, 0, 256, 2048);
	}
	memoryPadding = _fileMapInfo.non_accessmemoryOffset;
	
	mSize = 256;
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


	MGlobal::displayInfo("FileMapSize: " + MString() + mSize +" "+ MString()+_fileMapInfo.non_accessmemoryOffset);
}

void FileMapping::GetFilemapInfoValues()
{
	mutexInfo.Lock();
	memcpy(&_fileMapInfo, mInfoData, sizeof(FilemapInfo));
	mutexInfo.Unlock();
}

void FileMapping::SetFilemapInfoValues(size_t headPlacement, size_t tailPlacement, size_t nonAccessMemoryPlacement, size_t messageFileMapTotalSize) {
	mutexInfo.Lock();
	memcpy(&_fileMapInfo, mInfoData, sizeof(FilemapInfo));
	if (headPlacement >= 0)
		_fileMapInfo.head_ByteOffset = headPlacement;
	if (tailPlacement >= 0)
		_fileMapInfo.tail_ByteOffset = tailPlacement;
	if (nonAccessMemoryPlacement >= 0)
		_fileMapInfo.non_accessmemoryOffset = nonAccessMemoryPlacement;
	if (messageFileMapTotalSize > 0)
		_fileMapInfo.messageFilemap_Size = messageFileMapTotalSize;

	memcpy(mInfoData, &_fileMapInfo, sizeof(FilemapInfo));	
	mutexInfo.Unlock();
}


bool FileMapping::tryWrite(MessageInfo& msg, MeshInfo& minfo)
{
	switch (msg.nodeType)
	{
	case NodeType::nMesh:
		MGlobal::displayInfo("WOOOOOOOOOOOH");
		MessageHeader mHeader = createHeaderMesh(msg, minfo);
		int cfg = findWriteConfig(mHeader);
		createMessageMesh(msg, minfo);
		
		break;

	//default:
	//	break;

	}
	return false;
}

//void FileMapping::findWriteConfig(bool& canWrite, bool& )
int FileMapping::findWriteConfig(MessageHeader& hdr)
{
	// Write config return values
	// 0: Can't write
	// 1: Can write normally
	// 2: Header fits before buffer end, but message will have to be moved to the beginning of the buffer
	memcpy(&_fileMapInfo, mInfoData, sizeof(FilemapInfo));

	localHead = _fileMapInfo.head_ByteOffset;
	localTail = _fileMapInfo.tail_ByteOffset;

	if (localHead >= localTail)
	{
		if (hdr.byteSize + hdr.bytePadding + localHead + memoryPadding <= mSize)
		{
			MGlobal::displayInfo("MSG Config (CAN WRITE NORMALLY)");
			return 1;
		}
		else if (localHead + sizeof(MessageHeader) <= mSize && hdr.byteSize + hdr.bytePadding + memoryPadding <=localTail)
		{
			MGlobal::displayInfo("MSG Config (CAN WRITE WITH SPLIT)");
			return 2;
		}
	}
	else
	{
		if (hdr.byteSize + hdr.bytePadding + localHead + memoryPadding <= localTail)
		{
			MGlobal::displayInfo("MSG Config (CAN WRITE NORMALLY)");
			return 1;
		}
	}
	MGlobal::displayInfo("MSG Config (CANNOT WRITE)");
	return 0;

}
bool FileMapping::writeMesh(MessageHeader& hdr, MeshMessage& mdata, int config)
{

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