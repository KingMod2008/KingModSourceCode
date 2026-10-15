#include "Console.hpp"
#include "DevConsole.hpp"
#include <iostream>

                                                                            
                                                                             
static KingConsole::LogLevel LevelFromColor(TextColors color)
{
	switch (color)
	{
	case TextColors::Yellow:     return KingConsole::LogLevel::Warning;
	case TextColors::Red:        return KingConsole::LogLevel::Error;
	case TextColors::LightGreen: return KingConsole::LogLevel::Success;
	case TextColors::LightBlue:  return KingConsole::LogLevel::Notify;
	case TextColors::LightRed:   return KingConsole::LogLevel::Debug;
	default:                     return KingConsole::LogLevel::Info;
	}
}
ConsoleComponent::ConsoleComponent() : Component("Console", "Displays and manages the standard out stream.") { OnCreate(); }

ConsoleComponent::~ConsoleComponent() { OnDestroy(); }

void ConsoleComponent::OnCreate()
{
	OutputHandle = nullptr;
	OutputFile = nullptr;
	WriteToLog = true;
	WriteTimestamp = false;
}

void ConsoleComponent::OnDestroy()
{
	LogFile.close();

	if (OutputFile)
	{
		                
	}
}

void ConsoleComponent::Write(const std::string& text, TextColors textColor)
{
	WriteInternal(text, textColor);
}

void ConsoleComponent::WriteInternal(std::string text, TextColors textColor)
{
	                                                                            
	                                                                           
	                                       
	KingConsole::Push(text, LevelFromColor(textColor));

	SetTextColor(textColor);

	                                                                          
	if (WriteTimestamp)
	{
		std::string timestamp = GetTimestamp(true);
		text.reserve(text.length() + timestamp.length() + 1);
		text = std::move(timestamp) + std::move(text);
	}

	                                              
	if (OutputHandle)
	{
		                          
		text += '\n';

		                                                        
		WriteConsoleA(
			OutputHandle,
			text.c_str(),
			static_cast<DWORD>(text.length()),
			nullptr,
			nullptr
		);
	}
	else
	{
		                                                                 
		std::cout << text << std::endl;
	}
	                             

	if (WriteToLog && LogFile.is_open())
	{
		                                                               
		LogFile.write(text.c_str(), text.length());

		                                                 
		static int writeCount = 0;
		if (++writeCount % 10 == 0)
		{
			LogFile.flush();
		}
	}

	SetTextColor(TextColors::BrightWhite);
}

void ConsoleComponent::Warning(const std::string& text)
{
	WriteInternal(text, TextColors::Yellow);
}

void ConsoleComponent::Error(const std::string& text)
{
	WriteInternal(text, TextColors::Red);
}

void ConsoleComponent::Success(const std::string& text)
{
	WriteInternal(text, TextColors::LightGreen);
}

void ConsoleComponent::Notify(const std::string& text)
{
	WriteInternal(text, TextColors::LightBlue);
}

void ConsoleComponent::Debug(const std::string& text, const char* file, int line)
{
	                                                                       
	std::string debugMsg;
	size_t fileLen = strlen(file);
	size_t lineDigits = (line == 0) ? 1 : static_cast<size_t>(log10(abs(line)) + 1);
	debugMsg.reserve(fileLen + lineDigits + text.length() + 6);                             

	debugMsg = '[';
	debugMsg += file;
	debugMsg += "][";
	debugMsg += std::to_string(line);
	debugMsg += "] ";
	debugMsg += text;

	WriteInternal(std::move(debugMsg), TextColors::LightRed);
}

void ConsoleComponent::Debug(const class FString& text, const char* file, int line)
{
	                                                 
	const std::string& textStr = text.ToString();
	Debug(textStr, file, line);
}

void ConsoleComponent::Debug(const int& number, const char* file, int line)
{
	                                               
	std::string debugMsg;
	size_t fileLen = strlen(file);
	size_t lineDigits = (line == 0) ? 1 : static_cast<size_t>(log10(abs(line)) + 1);
	size_t numDigits = (number == 0) ? 1 : static_cast<size_t>(log10(abs(number)) + 1);
	if (number < 0) numDigits++;                          

	debugMsg.reserve(fileLen + lineDigits + numDigits + 6);

	debugMsg = '[';
	debugMsg += file;
	debugMsg += "][";
	debugMsg += std::to_string(line);
	debugMsg += "] ";
	debugMsg += std::to_string(number);

	WriteInternal(std::move(debugMsg), TextColors::LightRed);
}

void ConsoleComponent::Initialize(const std::filesystem::path& directory, const std::string& fileName)
{
	OutputHandle = nullptr;
	OutputFile = nullptr;
	WriteToLog = true;
	WriteTimestamp = true;

	                                                                               
	if (AllocConsole())
	{
		FILE* pNewStdout = nullptr;
		if (freopen_s(&pNewStdout, "CONOUT$", "w", stdout) == 0)
		{
			OutputFile = pNewStdout;
			HWND consoleWindow = GetConsoleWindow();
			if (consoleWindow)
			{
				ShowWindow(consoleWindow, SW_HIDE);
				SetForegroundWindow(consoleWindow);                          
			}
			OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTitle(L"KingMod Console");
		}
		else
		{
			                                              
			if (AttachConsole(ATTACH_PARENT_PROCESS))
			{
				OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			}
		}
	}

	if (WriteToLog)
	{
		LogFile.open(directory / fileName);
		                                                    
		LogFile.rdbuf()->pubsetbuf(nullptr, 8192);
	}

	Write(GetNameFormatted() + "Initialized!");
}

void ConsoleComponent::ToggleLogging(bool bWriteToLog)
{
	                                              
	if (!bWriteToLog && WriteToLog && LogFile.is_open())
	{
		LogFile.flush();
	}
	WriteToLog = bWriteToLog;
}

void ConsoleComponent::ToggleTimestamp(bool bWriteTimestamp)
{
	WriteTimestamp = bWriteTimestamp;
}

void ConsoleComponent::ToggleConsoleVisibility(bool bVisible)
{
	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow)
	{
		ShowWindow(consoleWindow, bVisible ? SW_SHOW : SW_HIDE);
	}
}

void ConsoleComponent::SetTextColor(TextColors textColor)
{
	if (OutputHandle)
	{
		SetConsoleTextAttribute(OutputHandle, static_cast<uint16_t>(textColor));
	}
}

std::string ConsoleComponent::GetTimestamp(const bool& bWithSpace)
{
	std::time_t time = std::time(nullptr);
	std::tm local;
	localtime_s(&local, &time);

	                                                              
	std::string result;
	result.reserve(12);                                    

	result = '[';

	                                 
	if (local.tm_hour < 10) result += '0';
	result += std::to_string(local.tm_hour);
	result += ':';

	if (local.tm_min < 10) result += '0';
	result += std::to_string(local.tm_min);
	result += ':';

	if (local.tm_sec < 10) result += '0';
	result += std::to_string(local.tm_sec);
	result += ']';

	if (bWithSpace) result += ' ';

	return result;
}

class ConsoleComponent Console {};