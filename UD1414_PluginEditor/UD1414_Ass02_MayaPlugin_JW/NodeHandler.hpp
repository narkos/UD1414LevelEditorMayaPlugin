#pragma once
#ifndef NODEHANDLER_HPP
#define NODEHANDLER_HPP
#include "Includes.hpp"
//#include "MessageHandler.hpp"

namespace DoremiEditor
{
	namespace Plugin
	{
		class MessageHandler;
		class NodeHandler
		{
		private:

			/**
			Vectors for managing loaded objects
			*/
			std::vector<TransformInfo>m_transformVector;
			std::vector<MeshInfo>m_meshVector;
			std::vector<CameraInfo>m_cameraVector;
			std::vector<LightInfo>m_lightVector;
			std::vector<MaterialInfo>m_materialVector;

			/**
			Vector and queue for message handling
			*/
			std::vector<MessageInfo>m_msgVector;
			std::queue<MessageInfo>m_msgQueue;
			std::vector<std::string> m_msgTypeVector;

			MessageHandler* m_messageHandler;

		public:
			NodeHandler();
			~NodeHandler();

			/**
			Object of message handler class
			*/
			//MessageHandler m_messageHandler;

			/**
			AFFECTS: Transform
			Add node to storage vectors
			*/
			bool AddNodeTransform(std::string p_nodeName);
			/**
			AFFECTS: Mesh
			Add node to storage vectors
			*/
			bool AddNodeMesh(std::string p_nodeName);
			/**
			AFFECTS: Cameras
			Add node to storage vectors
			*/
			bool AddNodeCamera(std::string p_nodeName);
			/**
			AFFECTS: Lights
			Add node to storage vectors
			*/
			bool AddNodeLight(std::string p_nodeName);
			/**
			AFFECTS: Materials
			Add node to storage vectors
			*/
			bool AddNodeMaterial(std::string p_nodeName);

			bool AddMessage(std::string p_nodeName, int p_messageType, int p_nodeType, std::string p_otherName = nullptr);

			bool RemoveMessage(std::string p_nodeName, int p_messageType, int p_nodeType);

			std::string getParentName(MObject& p_node);

			bool RenameNode(std::string p_oldName, std::string p_newName, int p_nodeType);

			bool ReparentNode(std::string p_nodeName, std::string p_newParent, std::string p_oldParent);

		};
	}
}


#endif
