#pragma once

namespace DoremiEditor
{
	namespace Plugin
	{
		/**
		Forward declarations
		*/
		class MessageHandler;
		class NodeHandler;
		class FileMaps;
		class Commands;
		class MayaCallbacks;
		
		class ApplicationContext
		{
		public:
		
			static ApplicationContext& GetInstance()
			{
				static ApplicationContext applicationContext = ApplicationContext();
				return applicationContext;
			}


			MayaCallbacks* GetMayaCallbacks() const
			{
				return mayaCallbacks;
			}

			MayaCallbacks* mayaCallbacks;

		private:
			ApplicationContext();
			~ApplicationContext();
		};





	}
}