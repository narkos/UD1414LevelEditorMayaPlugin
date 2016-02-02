#ifndef COMMANDS_H
#define COMMANDS_H
#pragma once
#include "Includes.hpp"

namespace DoremiEditor
{
	namespace Plugin
	{
		class NodeHandler;
		class CmdFilemapOnOff : public MPxCommand
		{
		public:
			CmdFilemapOnOff();
			virtual ~CmdFilemapOnOff();
			MStatus doIt(const MArgList& args);
			static void* creator();
		private:
			//NodeHandler* m_nodeHandler;
		};	
		
	}
}





#endif