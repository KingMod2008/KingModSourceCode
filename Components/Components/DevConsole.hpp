#pragma once
#include "../Component.hpp"
#include "../../ImGui/imgui.h"
#include <deque>
#include <vector>
#include <mutex>

                                            
  
              
                                                                          
                                                                           
                                                                         
                                                                           
                                                                            
                                                                      
                                                                             
                                                                               
                                                                         
                                                                            
                                                                 
namespace KingConsole
{
	enum class LogLevel : uint8_t
	{
		Info,
		Success,
		Warning,
		Error,
		Notify,
		Debug,
		Command,	                        
		Result		                                            
	};

	                                                                         
	                                                    
	enum class CommandSource : uint8_t
	{
		KingMod,	                         
		Exec,		                           
		Engine		                                                  
	};

	struct LogEntry
	{
		std::string Time;		             
		std::string Category;	                                               
		std::string Text;		                                    
		LogLevel Level;
	};

	struct CommandInfo
	{
		std::string Name;		                
		std::string LowerName;	            
		std::string Signature;	                                  
		std::string Description;
		CommandSource Source;
	};

	using CommandHandler = std::function<void(const std::vector<std::string>& args)>;

	                                                                          
	                                                                     
	                                                                
	void Push(const std::string& text, LogLevel level);
	void Clear();

	                                                                          
	                                                                           
	void RegisterCommand(const std::string& name, const std::string& usage, const std::string& description, CommandHandler handler);

	                                                                          
	                                                                
	void Execute(const std::string& line);

	                                                                        
	                                                                
	void RefreshCommands();

	                                                                          
	bool IsOpen();
	void SetOpen(bool bOpen);
	void Toggle();
	void Render();
}
