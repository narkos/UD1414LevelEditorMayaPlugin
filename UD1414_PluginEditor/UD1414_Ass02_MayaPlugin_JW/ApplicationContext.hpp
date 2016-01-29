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
				return m_mayaCallbacks;
			}

			MessageHandler* GetMessageHandler() const
			{
				return m_messageHandler;
			}


		private:
			ApplicationContext();
			~ApplicationContext();			
			
			MessageHandler* m_messageHandler;
			NodeHandler* m_nodeHandler;
			FileMaps* m_fileMaps;
			Commands* m_commands;
			MayaCallbacks* m_mayaCallbacks;
		};





	}
}