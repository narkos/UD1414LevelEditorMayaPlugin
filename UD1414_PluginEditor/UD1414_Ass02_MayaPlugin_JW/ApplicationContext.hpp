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

			static void Startup();
			static void Shutdown();

			static ApplicationContext& GetInstance()
			{
				return *applicationContext;
			}

			MayaCallbacks* GetMayaCallbacks() const
			{
				return m_mayaCallbacks;
			}

			MessageHandler* GetMessageHandler() const
			{
				return m_messageHandler;
			}

			NodeHandler* GetNodeHandler() const
			{
				return m_nodeHandler;
			}

		private:
			ApplicationContext();
			~ApplicationContext();		
			ApplicationContext(ApplicationContext const&) = delete;
			void operator=(ApplicationContext const&) = delete;
			static ApplicationContext* applicationContext;

			MessageHandler* m_messageHandler;
			NodeHandler* m_nodeHandler;
			FileMaps* m_fileMaps;
			Commands* m_commands;
			MayaCallbacks* m_mayaCallbacks;
		};
	}
}