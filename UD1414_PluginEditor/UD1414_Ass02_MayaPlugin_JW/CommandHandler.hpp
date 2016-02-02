#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#pragma once
#include "Includes.hpp"

namespace DoremiEditor
{
	namespace Plugin
	{
		class Commands
		{
			class TestCommand : public MPxCommand
			{
			public:
				TestCommand();
				virtual ~TestCommand();
				MStatus doIt(const MArgList& args);
				static void* creator();
			private:

			};



		};


	}
}





#endif