#define IMGUI_DEFINE_MATH_OPERATORS
#include "DevConsole.hpp"
#include "GUI.hpp"
#include "Main.hpp"
#include "../Includes.hpp"
#include "../../Modules/Mods/TAS.hpp"
#include "../../Modules/Mods/FakeSpectator.hpp"
#include "../../ImGui/hashes.hpp"
#include <windows.h>			                                                 
#include <algorithm>
#include <atomic>
#include <cctype>
#include <unordered_map>
#include <unordered_set>

                                                                                
                                                            
extern ImVec4 g_RedThemeColor;

namespace KingConsole
{
	namespace
	{
		constexpr size_t kMaxLogEntries = 6000;
		constexpr size_t kMaxHistory = 128;
		constexpr int kMaxSuggestionsShown = 12;

		                                                                      
		                                                                       
		                                                                      
		                                                                      
		                                                           
		std::mutex PendingMutex;
		std::vector<LogEntry> Pending;

		std::deque<LogEntry> Log;
		std::map<std::string, bool> Categories;		                        
		bool LevelEnabled[8] = { true, true, true, true, true, true, true, true };
		std::vector<int> Filtered;					                   
		bool FilterDirty = true;

		char SearchBuffer[128] = "";
		bool AutoScroll = true;
		bool ScrollToBottom = false;				                                                  
		bool ShowTimestamps = true;
		bool ShowCategories = true;
		bool WrapLines = false;

		                                                                      
		bool WindowOpen = false;
		bool FocusInputNextFrame = false;

		char InputBuffer[512] = "";
		std::vector<std::string> History;
		int HistoryPos = -1;							                    

		std::vector<int> Suggestions;					                        
		int SuggestionIndex = 0;
		bool SuggestionNavigated = false;
		bool SuggestionsDismissed = false;
		bool InputActiveLastFrame = false;				                              
		size_t LastSuggestCommandCount = 0;				                                 

		                                                                      
		struct Registered
		{
			std::string Usage;
			std::string Description;
			CommandHandler Handler;
		};

		std::mutex RegistryMutex;
		std::map<std::string, Registered> Registry;		                          
		std::map<std::string, std::string> RegistryNames;                               

		std::mutex StagingMutex;
		std::vector<CommandInfo> Staging;				                            
		std::atomic<bool> StagingReady{ false };
		std::atomic<bool> RefreshInFlight{ false };

		std::vector<CommandInfo> Commands;				                     
		bool CommandsRequested = false;
		int ExecCount = 0;
		int EngineCount = 0;

		                                                                      
		std::string Lower(std::string s)
		{
			std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(::tolower(c)); });
			return s;
		}

		std::string Trim(const std::string& s)
		{
			const size_t first = s.find_first_not_of(" \t\r\n");
			if (first == std::string::npos)
				return "";
			const size_t last = s.find_last_not_of(" \t\r\n");
			return s.substr(first, last - first + 1);
		}

		std::vector<std::string> Tokenize(const std::string& line)
		{
			std::vector<std::string> out;
			std::string current;
			bool inQuotes = false;
			for (const char c : line)
			{
				if (c == '"') { inQuotes = !inQuotes; continue; }
				if (!inQuotes && (c == ' ' || c == '\t'))
				{
					if (!current.empty()) { out.push_back(current); current.clear(); }
					continue;
				}
				current += c;
			}
			if (!current.empty())
				out.push_back(current);
			return out;
		}

		                                                                        
		                                                                         
		                                                                          
		                                                                        
		void SplitCategory(const std::string& text, std::string& outCategory, std::string& outMessage)
		{
			if (!text.empty() && text[0] == '[')
			{
				const size_t close = text.find(']');
				if (close != std::string::npos && close > 1 && close <= 48)
				{
					const std::string inside = text.substr(1, close - 1);
					                                                           
					if (inside.find(':') == std::string::npos &&
						inside.find_first_not_of("0123456789") != std::string::npos)
					{
						outCategory = inside;
						size_t start = close + 1;
						while (start < text.size() && text[start] == ' ')
							++start;
						outMessage = text.substr(start);
						return;
					}
				}
			}

			outCategory = "KingMod";
			outMessage = text;
		}

		ImVec4 LevelColor(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Success: return ImVec4(0.42f, 0.85f, 0.48f, 1.00f);
			case LogLevel::Warning: return ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
			case LogLevel::Error:   return ImVec4(1.00f, 0.38f, 0.38f, 1.00f);
			case LogLevel::Notify:  return ImVec4(0.42f, 0.72f, 1.00f, 1.00f);
			case LogLevel::Debug:   return ImVec4(0.85f, 0.55f, 0.95f, 1.00f);
			case LogLevel::Command: return ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			case LogLevel::Result:  return ImVec4(0.70f, 0.74f, 0.80f, 1.00f);
			default:                return ImVec4(0.82f, 0.85f, 0.90f, 1.00f);
			}
		}

		const char* LevelTag(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Success: return "OK";
			case LogLevel::Warning: return "WARN";
			case LogLevel::Error:   return "ERR";
			case LogLevel::Notify:  return "NOTE";
			case LogLevel::Debug:   return "DBG";
			case LogLevel::Command: return "CMD";
			case LogLevel::Result:  return "<<";
			default:                return "INFO";
			}
		}

		                                                                         
		                                    
		ImVec4 CategoryColor(const std::string& category)
		{
			uint32_t hash = 2166136261u;
			for (const char c : category)
			{
				hash ^= static_cast<uint8_t>(c);
				hash *= 16777619u;
			}
			const float hue = static_cast<float>(hash % 360u) / 360.0f;
			return (ImVec4)ImColor::HSV(hue, 0.45f, 1.00f);
		}

		ImVec4 SourceColor(CommandSource source)
		{
			switch (source)
			{
			case CommandSource::KingMod: return ImVec4(0.42f, 0.85f, 0.48f, 1.00f);
			case CommandSource::Exec:    return ImVec4(0.42f, 0.72f, 1.00f, 1.00f);
			default:                     return ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
			}
		}

		const char* SourceTag(CommandSource source)
		{
			switch (source)
			{
			case CommandSource::KingMod: return "kingmod";
			case CommandSource::Exec:    return "exec";
			default:                     return "engine";
			}
		}

		ImFont* MonoFont()
		{
			return GUIComponent::FontKingMono ? GUIComponent::FontKingMono : ImGui::GetFont();
		}

		                                                                       
		void DrainPending()
		{
			std::vector<LogEntry> incoming;
			{
				std::lock_guard<std::mutex> lock(PendingMutex);
				if (Pending.empty())
					return;
				incoming.swap(Pending);
			}

			for (LogEntry& entry : incoming)
			{
				if (Categories.find(entry.Category) == Categories.end())
					Categories[entry.Category] = true;
				Log.push_back(std::move(entry));
			}

			while (Log.size() > kMaxLogEntries)
				Log.pop_front();

			FilterDirty = true;
			                                                                        
			                                                               
			if (AutoScroll)
				ScrollToBottom = true;
		}

		bool PassesFilter(const LogEntry& entry)
		{
			if (!LevelEnabled[static_cast<size_t>(entry.Level)])
				return false;

			const auto it = Categories.find(entry.Category);
			if (it != Categories.end() && !it->second)
				return false;

			if (SearchBuffer[0] != '\0')
			{
				const std::string needle = Lower(SearchBuffer);
				if (Lower(entry.Text).find(needle) == std::string::npos &&
					Lower(entry.Category).find(needle) == std::string::npos)
					return false;
			}

			return true;
		}

		void RebuildFilter()
		{
			Filtered.clear();
			Filtered.reserve(Log.size());
			for (size_t i = 0; i < Log.size(); ++i)
			{
				if (PassesFilter(Log[i]))
					Filtered.push_back(static_cast<int>(i));
			}
			FilterDirty = false;
		}

		                                                                       
		                                                                      
		                                                                    
		                                                                  
		                                                                      
		                                                                     
		                                                                     
		bool IsReadableRange(const void* address, size_t byteCount)
		{
			if (!address || byteCount == 0)
				return false;

			MEMORY_BASIC_INFORMATION mbi{};
			if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi))
				return false;

			const DWORD protection = mbi.Protect & 0xFF;
			if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_GUARD) != 0 || protection == PAGE_NOACCESS)
				return false;

			const auto begin = reinterpret_cast<uintptr_t>(address);
			const auto end = begin + byteCount;
			const auto regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
			return end >= begin && end <= regionEnd;
		}

		                                                                       
		                                                                    
		bool IsCallableObject(const void* object)
		{
			if (!IsReadableRange(object, sizeof(void*)))
				return false;
			const void* vtable = *reinterpret_cast<const void* const*>(object);
			return IsReadableRange(vtable, sizeof(void*) * 68);
		}

		enum class ConsoleTarget { PlayerController, DefaultActor, Viewport };

		                                                                     
		                                                                         
		                                                                       
		bool RunConsoleCommand(void* object, ConsoleTarget target, const std::string& command, std::string& outReply)
		{
			const FString cmd = Format::ToFString(command);
			switch (target)
			{
			case ConsoleTarget::PlayerController:
				outReply = static_cast<APlayerController*>(object)->ConsoleCommand(cmd, false).ToString();
				return true;
			case ConsoleTarget::DefaultActor:
				outReply = static_cast<AActor*>(object)->ConsoleCommand(cmd, false).ToString();
				return true;
			case ConsoleTarget::Viewport:
				outReply = static_cast<UGameViewportClient*>(object)->ConsoleCommand(cmd).ToString();
				return true;
			}
			return false;
		}

		                                                                         
		                                                                      
		                                                                         
		bool SafeConsoleCommand(void* object, ConsoleTarget target, const std::string& command, std::string& outReply)
		{
			__try
			{
				return RunConsoleCommand(object, target, command, outReply);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				return false;
			}
		}

		                                                               
		                                                                  
		                                                                  
		                                                                      
		                                                                        
		std::string DispatchToGame(const std::string& command, bool& outSent)
		{
			outSent = false;
			std::string reply;

			                                                                   
			                               
			if (APlayerController* controller = Instances.IAPlayerController())
			{
				if (IsCallableObject(controller) &&
					SafeConsoleCommand(controller, ConsoleTarget::PlayerController, command, reply))
				{
					outSent = true;
					return reply;
				}
			}

			                                                                  
			                                                            
			if (AActor* actor = Instances.GetDefaultInstanceOf<AActor>())
			{
				if (IsCallableObject(actor) &&
					SafeConsoleCommand(actor, ConsoleTarget::DefaultActor, command, reply))
				{
					outSent = true;
					return reply;
				}
			}

			                                          
			if (UGameViewportClient* viewport = Instances.IUGameViewportClient())
			{
				if (IsCallableObject(viewport) &&
					SafeConsoleCommand(viewport, ConsoleTarget::Viewport, command, reply))
				{
					outSent = true;
					return reply;
				}
			}

			return "";
		}

		                                                                       
		void AddCommand(std::vector<CommandInfo>& out, std::unordered_set<std::string>& seen,
			const std::string& name, const std::string& signature,
			const std::string& description, CommandSource source)
		{
			if (name.empty())
				return;

			const std::string key = Lower(name);
			if (!seen.insert(key).second)
				return;

			CommandInfo info;
			info.Name = name;
			info.LowerName = key;
			info.Signature = signature.empty() ? name : signature;
			info.Description = description;
			info.Source = source;
			out.push_back(std::move(info));
		}

		                                                                           
		                                                                         
		                                                             
		std::string BuildExecSignature(UFunction* function, const std::string& name)
		{
			std::string signature = name;

			for (UField* field = function->Children; field; field = field->Next)
			{
				if (!field->IsA<UProperty>())
					continue;

				UProperty* property = static_cast<UProperty*>(field);
				if (!(property->PropertyFlags & CPF_Parm))
					continue;
				if (property->PropertyFlags & CPF_ReturnParm)
					continue;

				const std::string parmName = property->GetName();
				if (parmName.empty())
					continue;

				if (property->PropertyFlags & CPF_OptionalParm)
					signature += " [" + parmName + "]";
				else
					signature += " <" + parmName + ">";
			}

			return signature;
		}

		void BuildCommandListOnGameThread()
		{
			std::vector<CommandInfo> built;
			std::unordered_set<std::string> seen;
			int execCount = 0;
			int engineCount = 0;

			                                   
			{
				std::lock_guard<std::mutex> lock(RegistryMutex);
				for (const auto& pair : Registry)
				{
					const std::string& display = RegistryNames.count(pair.first) ? RegistryNames.at(pair.first) : pair.first;
					const std::string signature = pair.second.Usage.empty() ? display : display + " " + pair.second.Usage;
					AddCommand(built, seen, display, signature, pair.second.Description, CommandSource::KingMod);
				}
			}

			                                                                    
			                                                                     
			if (TArray<UObject*>* objects = UObject::GObjObjects())
			{
				UClass* functionClass = UFunction::StaticClass();
				const int32_t count = objects->size();

				for (int32_t i = 0; i < count; ++i)
				{
					UObject* object = objects->at(i);
					if (!object || !object->Class)
						continue;
					                                                                 
					                                                            
					if (functionClass ? (object->Class != functionClass) : !object->IsA<UFunction>())
						continue;

					UFunction* function = static_cast<UFunction*>(object);
					if (!(function->FunctionFlags & FUNC_Exec))
						continue;

					const std::string name = function->GetName();
					if (name.empty())
						continue;

					const std::string owner = function->Outer ? function->Outer->GetName() : "";
					AddCommand(built, seen, name, BuildExecSignature(function, name),
						owner.empty() ? "exec function" : owner, CommandSource::Exec);
					++execCount;
				}
			}

			                                                                 
			                                                                   
			                                                          
			if (UConsole* console = Instances.GetInstanceOf<UConsole>())
			{
				try
				{
					if (!console->bIsRuntimeAutoCompleteUpToDate)
						console->BuildRuntimeAutoCompleteList(false);
				}
				catch (...) {}

				TArray<FAutoCompleteCommand>* lists[] = {
					&console->NativeAutoCompleteList,
					&console->ManualAutoCompleteList,
					&console->AutoCompleteList
				};

				for (TArray<FAutoCompleteCommand>* list : lists)
				{
					if (!list)
						continue;

					const int32_t count = list->size();
					for (int32_t i = 0; i < count; ++i)
					{
						const FAutoCompleteCommand& entry = list->at(i);
						const std::string signature = Trim(entry.Command.ToString());
						if (signature.empty())
							continue;

						const std::vector<std::string> tokens = Tokenize(signature);
						if (tokens.empty())
							continue;

						AddCommand(built, seen, tokens[0], signature, entry.Desc.ToString(), CommandSource::Engine);
						++engineCount;
					}
				}
			}

			std::sort(built.begin(), built.end(), [](const CommandInfo& a, const CommandInfo& b)
			{
				if (a.Source != b.Source)
					return a.Source < b.Source;	                     
				return a.LowerName < b.LowerName;
			});

			{
				std::lock_guard<std::mutex> lock(StagingMutex);
				Staging = std::move(built);
				ExecCount = execCount;
				EngineCount = engineCount;
			}
			StagingReady.store(true, std::memory_order_release);
			RefreshInFlight.store(false, std::memory_order_release);

			Console.Write("[KingConsole] Discovered " + std::to_string(execCount) + " exec functions and " +
				std::to_string(engineCount) + " engine autocomplete entries.", TextColors::LightGreen);
		}

		void AdoptStagedCommands()
		{
			if (!StagingReady.load(std::memory_order_acquire))
				return;

			std::lock_guard<std::mutex> lock(StagingMutex);
			Commands = std::move(Staging);
			Staging.clear();
			StagingReady.store(false, std::memory_order_release);
		}

		                                                                        
		void RecomputeSuggestions()
		{
			Suggestions.clear();
			SuggestionIndex = 0;
			SuggestionNavigated = false;

			const std::string line(InputBuffer);
			                                                                    
			                                                           
			if (line.empty() || line.find_first_of(" \t") != std::string::npos)
				return;

			const std::string needle = Lower(line);

			                                               
			for (size_t i = 0; i < Commands.size(); ++i)
			{
				if (Commands[i].LowerName.rfind(needle, 0) == 0)
					Suggestions.push_back(static_cast<int>(i));
			}
			for (size_t i = 0; i < Commands.size(); ++i)
			{
				if (Commands[i].LowerName.rfind(needle, 0) != 0 &&
					Commands[i].LowerName.find(needle) != std::string::npos)
					Suggestions.push_back(static_cast<int>(i));
			}
		}

		bool SuggestionsVisible()
		{
			return !SuggestionsDismissed && !Suggestions.empty();
		}

		                                                                      
		                                                                   
		std::string CurrentSuggestionReplacement()
		{
			if (!SuggestionsVisible())
				return "";

			const int index = Suggestions[std::clamp(SuggestionIndex, 0, static_cast<int>(Suggestions.size()) - 1)];
			const CommandInfo& command = Commands[index];
			std::string replacement = command.Name;
			if (command.Signature.size() > command.Name.size())
				replacement += " ";
			return replacement;
		}

		                                                                        
		                                                                     
		                                                                      
		                                                                        
		void AcceptSuggestion()
		{
			const std::string replacement = CurrentSuggestionReplacement();
			if (replacement.empty())
				return;

			snprintf(InputBuffer, sizeof(InputBuffer), "%s", replacement.c_str());
			Suggestions.clear();
			SuggestionNavigated = false;
			FocusInputNextFrame = true;
		}

		int InputCallback(ImGuiInputTextCallbackData* data)
		{
			switch (data->EventFlag)
			{
			case ImGuiInputTextFlags_CallbackCompletion:
			{
				                                                              
				                                                             
				if (SuggestionsVisible())
				{
					const std::string replacement = CurrentSuggestionReplacement();
					data->DeleteChars(0, data->BufTextLen);
					data->InsertChars(0, replacement.c_str());
					Suggestions.clear();
					SuggestionNavigated = false;
				}
				break;
			}

			case ImGuiInputTextFlags_CallbackHistory:
			{
				                                                                 
				                                                                   
				if (SuggestionsVisible())
				{
					const int last = static_cast<int>(Suggestions.size()) - 1;
					if (data->EventKey == ImGuiKey_UpArrow)
						SuggestionIndex = (SuggestionIndex <= 0) ? last : SuggestionIndex - 1;
					else if (data->EventKey == ImGuiKey_DownArrow)
						SuggestionIndex = (SuggestionIndex >= last) ? 0 : SuggestionIndex + 1;
					SuggestionNavigated = true;
					break;
				}

				if (History.empty())
					break;

				const int previous = HistoryPos;
				if (data->EventKey == ImGuiKey_UpArrow)
					HistoryPos = (HistoryPos == -1) ? static_cast<int>(History.size()) - 1 : (std::max)(HistoryPos - 1, 0);
				else if (data->EventKey == ImGuiKey_DownArrow)
				{
					if (HistoryPos != -1 && ++HistoryPos >= static_cast<int>(History.size()))
						HistoryPos = -1;
				}

				if (previous != HistoryPos)
				{
					const std::string text = (HistoryPos >= 0) ? History[HistoryPos] : "";
					data->DeleteChars(0, data->BufTextLen);
					data->InsertChars(0, text.c_str());
					Suggestions.clear();
				}
				break;
			}

			case ImGuiInputTextFlags_CallbackEdit:
			{
				HistoryPos = -1;
				SuggestionsDismissed = false;
				RecomputeSuggestions();
				break;
			}

			default:
				break;
			}

			return 0;
		}

		                                                                       
		void PrintCommandList(const std::string& filter, size_t limit)
		{
			const std::string needle = Lower(filter);
			size_t shown = 0;
			size_t matched = 0;

			for (const CommandInfo& command : Commands)
			{
				if (!needle.empty() && command.LowerName.find(needle) == std::string::npos &&
					Lower(command.Description).find(needle) == std::string::npos)
					continue;

				++matched;
				if (shown >= limit)
					continue;

				std::string line = "  " + command.Signature;
				if (!command.Description.empty())
					line += "   -- " + command.Description;
				Push("[KingConsole] " + line, LogLevel::Result);
				++shown;
			}

			if (matched > shown)
				Push("[KingConsole] ... " + std::to_string(matched - shown) + " more (narrow the filter or use the search box)", LogLevel::Notify);
			if (matched == 0)
				Push("[KingConsole] No command matches \"" + filter + "\".", LogLevel::Warning);
		}

		                                                                         
		                                                                         
		int ParseIntOr(const std::vector<std::string>& args, size_t index, int fallback)
		{
			if (index >= args.size())
				return fallback;
			try { return std::stoi(args[index]); }
			catch (...) { return fallback; }
		}

		                                                                       
		                                                                     
		float ParseFloatOr(const std::vector<std::string>& args, size_t index, float fallback)
		{
			if (index >= args.size())
				return fallback;
			try { return std::stof(args[index]); }
			catch (...) { return fallback; }
		}

		                                                                          
		                                                                       
		                                                                        
		                                                                    
		                                                               
		ACar_TA* GetLocalCar()
		{
			ULocalPlayer* localPlayer = Instances.IULocalPlayer();
			if (!IsCallableObject(localPlayer))
				return nullptr;
			auto* controller = localPlayer->Actor;
			if (!IsCallableObject(controller))
				return nullptr;
			auto* pri = controller->PlayerReplicationInfo;
			if (!IsCallableObject(pri))
				return nullptr;
			ACar_TA* car = static_cast<APRI_TA*>(pri)->Car;
			if (!IsCallableObject(car))
				return nullptr;
			return car;
		}

		                                                                         
		                                                                           
		ABall_TA* GetLiveBall()
		{
			ABall_TA* ball = Instances.GetInstanceOf<ABall_TA>();
			return IsCallableObject(ball) ? ball : nullptr;
		}

		                                                                       
		                                                                         
		                                                                        
		                                                                       
		void QueueEquipToSlot(int productId, int expectedSlot, std::string label)
		{
			MainComponent::Execute([productId, expectedSlot, label]
			{
				Items.EnsureItemsLoaded();
				int slot = -1;
				std::string category;
				for (const GameItem& gi : Items.allItems)
					if (gi.id == productId) { slot = gi.slotIndex; category = gi.category; break; }
				if (slot < 0)
				{
					Push("[KingConsole] " + label + ": product " + std::to_string(productId) + " is not in the item database.", LogLevel::Error);
					return;
				}
				if (expectedSlot >= 0 && slot != expectedSlot)
					Push("[KingConsole] " + label + ": product " + std::to_string(productId) + " is a \"" + category + "\" (slot " + std::to_string(slot) + "), equipping it there.", LogLevel::Warning);
				const bool ok = Items.EquipProductToSlot(productId, slot);
				Push(ok ? ("[KingConsole] Equipped " + std::to_string(productId) + " (" + category + ") to slot " + std::to_string(slot))
					    : ("[KingConsole] Failed to equip " + std::to_string(productId) + " to slot " + std::to_string(slot)),
					ok ? LogLevel::Success : LogLevel::Error);
			});
		}

		                                                                            
		                                                                           
		                                                                          
		enum class FindKind { Function, Class, AnyObject };
		void QueueFind(FindKind kind, std::string needle)
		{
			MainComponent::Execute([kind, needle]
			{
				const std::string low = Lower(needle);
				const char* what = kind == FindKind::Function ? "function"
					             : kind == FindKind::Class    ? "class" : "object";
				size_t shown = 0, matched = 0;
				if (TArray<UObject*>* objects = UObject::GObjObjects())
				{
					UClass* filter = kind == FindKind::Function ? UFunction::StaticClass()
						           : kind == FindKind::Class    ? UClass::StaticClass() : nullptr;
					const int32_t count = objects->size();
					for (int32_t i = 0; i < count; ++i)
					{
						UObject* object = objects->at(i);
						if (!object || !object->Class)
							continue;
						if (filter && object->Class != filter)
							continue;
						if (Lower(object->GetName()).find(low) == std::string::npos)
							continue;
						++matched;
						if (shown < 60)
						{
							Push("[KingConsole]   " + object->GetFullName(), LogLevel::Result);
							++shown;
						}
					}
				}
				if (matched == 0)
					Push("[KingConsole] No " + std::string(what) + " matches \"" + needle + "\".", LogLevel::Warning);
				else if (matched > shown)
					Push("[KingConsole] ... " + std::to_string(matched - shown) + " more (showing first " + std::to_string(shown) + ").", LogLevel::Notify);
				else
					Push("[KingConsole] " + std::to_string(matched) + " " + what + (matched == 1 ? "" : "s") + " matched.", LogLevel::Notify);
			});
		}

		void RegisterBuiltins()
		{
			static bool registered = false;
			if (registered)
				return;
			registered = true;

			RegisterCommand("help", "[filter]", "List available commands, optionally filtered.",
				[](const std::vector<std::string>& args)
			{
				const std::string filter = args.empty() ? "" : args[0];
				Push("[KingConsole] " + std::to_string(Commands.size()) + " commands known. Type a name and press Tab to complete.", LogLevel::Notify);
				PrintCommandList(filter, 60);
			});

			RegisterCommand("commands", "[filter]", "Dump every discovered command into the log.",
				[](const std::vector<std::string>& args)
			{
				PrintCommandList(args.empty() ? "" : args[0], 4000);
			});

			RegisterCommand("clear", "", "Clear the console log.",
				[](const std::vector<std::string>&) { Clear(); });

			RegisterCommand("refresh", "", "Re-scan the game for exec functions and autocomplete entries.",
				[](const std::vector<std::string>&) { RefreshCommands(); });

			                                                                        
			                                                                        
			                                                                       
			                                                          
			const auto registerTasBind = [](const std::string& name, const std::string& desc)
			{
				RegisterCommand(name, "", desc,
					[name](const std::vector<std::string>&)
				{
					MainComponent::Execute([name]
					{
						KingTAS::ExecuteBind(name);
						Push("[KingTAS] " + KingTAS::GetStatus(), LogLevel::Notify);
					});
				});
			};
			registerTasBind("tas_start",         "TAS: start replaying the loaded TAS (records if it has no frames).");
			registerTasBind("tas_stop",          "TAS: stop replaying/recording (a new recording stays pending).");
			registerTasBind("tas_update",        "TAS: commit the pending recording as the active branch.");
			registerTasBind("tas_stopandupdate", "TAS: stop and immediately commit the recording.");
			registerTasBind("tas_changespeed",   "TAS: toggle world speed between replay and record speed.");

			                                                                        
			                                                                         
			                                                                         
			                                                                
			RegisterCommand("fakespectator", "[on|off]",
				"Toggle the experimental fake spectator PRI (default off; may crash the host).",
				[](const std::vector<std::string>& args)
			{
				bool enable = !FakeSpectator::IsEnabled();
				if (!args.empty())
				{
					const std::string& a = args[0];
					enable = (a == "1" || a == "on" || a == "true" || a == "enable");
				}
				MainComponent::Execute([enable]
				{
					FakeSpectator::SetEnabled(enable);
				});
				Push(std::string("[FakeSpectator] ") + (enable ? "enabled" : "disabled") +
					" (takes effect on the next match start).", LogLevel::Notify);
			});

			RegisterCommand("echo", "<text...>", "Print text back into the log.",
				[](const std::vector<std::string>& args)
			{
				std::string joined;
				for (const std::string& arg : args)
				{
					if (!joined.empty()) joined += " ";
					joined += arg;
				}
				Push("[KingConsole] " + joined, LogLevel::Result);
			});

			RegisterCommand("features", "", "List every feature that has logged this session.",
				[](const std::vector<std::string>&)
			{
				Push("[KingConsole] " + std::to_string(Categories.size()) + " features seen:", LogLevel::Notify);
				for (const auto& pair : Categories)
					Push("[KingConsole]   " + pair.first + (pair.second ? "" : "  (hidden)"), LogLevel::Result);
			});

			                                                                   
			                                                                    
			                                                                   
			                                     
			RegisterCommand("spawn_item", "<productId> [quality] [paint] [cert] [series]",
				"Spawn an inventory product by ID (optionally painted / certified).",
				[](const std::vector<std::string>& args)
			{
				const int productId = ParseIntOr(args, 0, -1);
				if (productId < 0)
				{
					Push("[KingConsole] Usage: spawn_item <productId> [quality] [paint] [cert] [series]", LogLevel::Warning);
					return;
				}
				const int quality = ParseIntOr(args, 1, 0);
				const int paint   = ParseIntOr(args, 2, 0);
				const int cert    = ParseIntOr(args, 3, 15);	            
				const int series  = ParseIntOr(args, 4, 0);
				MainComponent::Execute([=] { Items.CreateAndSpawnProduct(productId, quality, paint, cert, series); });
				Push("[KingConsole] Spawning product " + std::to_string(productId) + "...", LogLevel::Success);
			});

			RegisterCommand("spawn_credits", "<amount> [tournament]",
				"Spawn credits; pass a non-zero second arg for tournament credits.",
				[](const std::vector<std::string>& args)
			{
				const int amount = ParseIntOr(args, 0, 0);
				if (amount <= 0)
				{
					Push("[KingConsole] Usage: spawn_credits <amount> [tournament]", LogLevel::Warning);
					return;
				}
				const bool tournament = ParseIntOr(args, 1, 0) != 0;
				MainComponent::Execute([=] { Items.SpawnCredits(amount, tournament, "", true); });
				Push("[KingConsole] Spawning " + std::to_string(amount) + (tournament ? " tournament credits..." : " credits..."), LogLevel::Success);
			});

			RegisterCommand("equip", "<productId> [slot]",
				"Locally equip a product to a loadout slot (slot auto-detected if omitted).",
				[](const std::vector<std::string>& args)
			{
				const int productId = ParseIntOr(args, 0, -1);
				if (productId < 0)
				{
					Push("[KingConsole] Usage: equip <productId> [slot]", LogLevel::Warning);
					return;
				}
				const int requestedSlot = ParseIntOr(args, 1, -1);
				MainComponent::Execute([=]
				{
					int slot = requestedSlot;
					if (slot < 0)
					{
						Items.EnsureItemsLoaded();
						for (const GameItem& gi : Items.allItems)
							if (gi.id == productId) { slot = gi.slotIndex; break; }
					}
					if (slot < 0)
					{
						Push("[KingConsole] equip: could not resolve a slot for product " + std::to_string(productId) + " (pass one explicitly).", LogLevel::Error);
						return;
					}
					const bool ok = Items.EquipProductToSlot(productId, slot);
					Push(ok ? ("[KingConsole] Equipped product " + std::to_string(productId) + " to slot " + std::to_string(slot))
						    : ("[KingConsole] Failed to equip product " + std::to_string(productId)),
						ok ? LogLevel::Success : LogLevel::Error);
				});
			});

			RegisterCommand("find_item", "<text...>",
				"Search the item database; prints matching product IDs and names.",
				[](const std::vector<std::string>& args)
			{
				std::string needle;
				for (const std::string& a : args) { if (!needle.empty()) needle += " "; needle += a; }
				if (needle.empty())
				{
					Push("[KingConsole] Usage: find_item <text>", LogLevel::Warning);
					return;
				}
				MainComponent::Execute([needle]
				{
					Items.EnsureItemsLoaded();
					const std::string low = Lower(needle);
					size_t shown = 0, matched = 0;
					for (const GameItem& gi : Items.allItems)
					{
						if (Lower(gi.displayName).find(low) == std::string::npos &&
							Lower(gi.internalName).find(low) == std::string::npos)
							continue;
						++matched;
						if (shown < 60)
						{
							Push("[KingConsole]   " + std::to_string(gi.id) + "  " + gi.displayName + "  [" + gi.category + "]", LogLevel::Result);
							++shown;
						}
					}
					if (matched == 0)
						Push("[KingConsole] No item matches \"" + needle + "\".", LogLevel::Warning);
					else if (matched > shown)
						Push("[KingConsole] ... " + std::to_string(matched - shown) + " more.", LogLevel::Notify);
				});
			});

			RegisterCommand("spawn_title", "<titleId> [series]",
				"Spawn a title product by numeric ID.",
				[](const std::vector<std::string>& args)
			{
				const int titleId = ParseIntOr(args, 0, -1);
				if (titleId < 0)
				{
					Push("[KingConsole] Usage: spawn_title <titleId> [series]", LogLevel::Warning);
					return;
				}
				const int series = ParseIntOr(args, 1, 0);
				MainComponent::Execute([=] { Titles.SpawnTitle(titleId, series, 0, true, "", false); });
				Push("[KingConsole] Spawning title " + std::to_string(titleId) + "...", LogLevel::Success);
			});

			RegisterCommand("find_title", "<text...>",
				"Search the title database; prints matching title IDs and names.",
				[](const std::vector<std::string>& args)
			{
				std::string needle;
				for (const std::string& a : args) { if (!needle.empty()) needle += " "; needle += a; }
				if (needle.empty())
				{
					Push("[KingConsole] Usage: find_title <text>", LogLevel::Warning);
					return;
				}
				MainComponent::Execute([needle]
				{
					Titles.EnsureTitlesLoaded();
					const std::string low = Lower(needle);
					size_t shown = 0, matched = 0;
					for (const GameTitle& gt : Titles.allTitles)
					{
						if (Lower(gt.displayName).find(low) == std::string::npos &&
							Lower(gt.internalName).find(low) == std::string::npos)
							continue;
						++matched;
						if (shown < 60)
						{
							Push("[KingConsole]   " + std::to_string(gt.id) + "  " + gt.displayName + "  [" + gt.category + "]", LogLevel::Result);
							++shown;
						}
					}
					if (matched == 0)
						Push("[KingConsole] No title matches \"" + needle + "\".", LogLevel::Warning);
					else if (matched > shown)
						Push("[KingConsole] ... " + std::to_string(matched - shown) + " more.", LogLevel::Notify);
				});
			});

			RegisterCommand("workshop_load", "<path-to-.upk-or-.udk>",
				"Load a Workshop / custom map by full file path via the native loader.",
				[](const std::vector<std::string>& args)
			{
				std::string path;
				for (const std::string& a : args) { if (!path.empty()) path += " "; path += a; }
				                                                           
				if (path.size() >= 2 && (path.front() == '"' || path.front() == '\'') && path.back() == path.front())
					path = path.substr(1, path.size() - 2);
				if (path.empty())
				{
					Push("[KingConsole] Usage: workshop_load <path to .upk or .udk>", LogLevel::Warning);
					return;
				}
				MainComponent::Execute([path]
				{
					snprintf(GameEventHookModule::WorkshopMapPath, sizeof(GameEventHookModule::WorkshopMapPath), "%s", path.c_str());
					GameEventHookModule::LoadWorkshopMap();
				});
				Push("[KingConsole] Loading Workshop map: " + path, LogLevel::Success);
			});

			                                                                  
			                                                                     
			                                                                   
			RegisterCommand("tp", "<x> <y> <z>",
				"Teleport your car to a world position (keeps facing, stops motion).",
				[](const std::vector<std::string>& args)
			{
				if (args.size() < 3)
				{
					Push("[KingConsole] Usage: tp <x> <y> <z>", LogLevel::Warning);
					return;
				}
				const float x = ParseFloatOr(args, 0, 0.0f);
				const float y = ParseFloatOr(args, 1, 0.0f);
				const float z = ParseFloatOr(args, 2, 100.0f);
				MainComponent::Execute([=]
				{
					ACar_TA* car = GetLocalCar();
					if (!car)
					{
						Push("[KingConsole] tp: no live car -- join a match and get in a car first.", LogLevel::Error);
						return;
					}
					car->SetLocationAndRotation(FVector{ x, y, z }, car->Rotation);
					car->Velocity = FVector{ 0.0f, 0.0f, 0.0f };
					Push("[KingConsole] Teleported car to (" + std::to_string((int)x) + ", " + std::to_string((int)y) + ", " + std::to_string((int)z) + ").", LogLevel::Success);
				});
			});

			RegisterCommand("car_vel", "<x> <y> <z>",
				"Set your car's linear velocity in unreal units per second.",
				[](const std::vector<std::string>& args)
			{
				if (args.size() < 3)
				{
					Push("[KingConsole] Usage: car_vel <x> <y> <z>", LogLevel::Warning);
					return;
				}
				const float x = ParseFloatOr(args, 0, 0.0f);
				const float y = ParseFloatOr(args, 1, 0.0f);
				const float z = ParseFloatOr(args, 2, 0.0f);
				MainComponent::Execute([=]
				{
					ACar_TA* car = GetLocalCar();
					if (!car)
					{
						Push("[KingConsole] car_vel: no live car.", LogLevel::Error);
						return;
					}
					car->Velocity = FVector{ x, y, z };
					Push("[KingConsole] Car velocity set.", LogLevel::Success);
				});
			});

			RegisterCommand("ball_tp", "<x> <y> <z>",
				"Teleport the ball to a world position (stops its motion).",
				[](const std::vector<std::string>& args)
			{
				if (args.size() < 3)
				{
					Push("[KingConsole] Usage: ball_tp <x> <y> <z>", LogLevel::Warning);
					return;
				}
				const float x = ParseFloatOr(args, 0, 0.0f);
				const float y = ParseFloatOr(args, 1, 0.0f);
				const float z = ParseFloatOr(args, 2, 100.0f);
				MainComponent::Execute([=]
				{
					ABall_TA* ball = GetLiveBall();
					if (!ball)
					{
						Push("[KingConsole] ball_tp: no live ball.", LogLevel::Error);
						return;
					}
					ball->SetLocationAndRotation(FVector{ x, y, z }, ball->Rotation);
					ball->Velocity = FVector{ 0.0f, 0.0f, 0.0f };
					Push("[KingConsole] Teleported ball to (" + std::to_string((int)x) + ", " + std::to_string((int)y) + ", " + std::to_string((int)z) + ").", LogLevel::Success);
				});
			});

			RegisterCommand("ball_vel", "<x> <y> <z>",
				"Set the ball's linear velocity in unreal units per second.",
				[](const std::vector<std::string>& args)
			{
				if (args.size() < 3)
				{
					Push("[KingConsole] Usage: ball_vel <x> <y> <z>", LogLevel::Warning);
					return;
				}
				const float x = ParseFloatOr(args, 0, 0.0f);
				const float y = ParseFloatOr(args, 1, 0.0f);
				const float z = ParseFloatOr(args, 2, 0.0f);
				MainComponent::Execute([=]
				{
					ABall_TA* ball = GetLiveBall();
					if (!ball)
					{
						Push("[KingConsole] ball_vel: no live ball.", LogLevel::Error);
						return;
					}
					ball->Velocity = FVector{ x, y, z };
					Push("[KingConsole] Ball velocity set.", LogLevel::Success);
				});
			});

			RegisterCommand("boost", "<0-100>",
				"Set your car's boost tank to a percentage.",
				[](const std::vector<std::string>& args)
			{
				if (args.empty())
				{
					Push("[KingConsole] Usage: boost <0-100>", LogLevel::Warning);
					return;
				}
				float pct = ParseFloatOr(args, 0, 100.0f);
				if (pct < 0.0f) pct = 0.0f;
				if (pct > 100.0f) pct = 100.0f;
				MainComponent::Execute([pct]
				{
					ACar_TA* car = GetLocalCar();
					if (!car)
					{
						Push("[KingConsole] boost: no live car.", LogLevel::Error);
						return;
					}
					auto* boost = car->BoostComponent;
					if (!IsCallableObject(boost))
					{
						Push("[KingConsole] boost: this car has no boost component.", LogLevel::Error);
						return;
					}
					boost->SetBoostAmount(pct / 100.0f);
					Push("[KingConsole] Boost set to " + std::to_string((int)pct) + "%.", LogLevel::Success);
				});
			});

			RegisterCommand("boost_inf", "<0|1>",
				"Toggle unlimited boost on your car.",
				[](const std::vector<std::string>& args)
			{
				const bool on = ParseIntOr(args, 0, 1) != 0;
				MainComponent::Execute([on]
				{
					ACar_TA* car = GetLocalCar();
					if (!car)
					{
						Push("[KingConsole] boost_inf: no live car.", LogLevel::Error);
						return;
					}
					auto* boost = car->BoostComponent;
					if (!IsCallableObject(boost))
					{
						Push("[KingConsole] boost_inf: this car has no boost component.", LogLevel::Error);
						return;
					}
					boost->SetUnlimitedBoost(on);
					if (on)
						boost->SetBoostAmount(1.0f);
					Push(std::string("[KingConsole] Unlimited boost ") + (on ? "ON." : "OFF."), LogLevel::Success);
				});
			});

			                                                                   
			RegisterCommand("body", "<productId>", "Equip a car body by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: body <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 0, "body"); });

			RegisterCommand("decal", "<productId>", "Equip a decal by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: decal <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 1, "decal"); });

			RegisterCommand("wheels", "<productId>", "Equip wheels by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: wheels <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 2, "wheels"); });

			RegisterCommand("boost_item", "<productId>", "Equip a boost cosmetic by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: boost_item <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 3, "boost"); });

			RegisterCommand("antenna", "<productId>", "Equip an antenna by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: antenna <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 4, "antenna"); });

			RegisterCommand("topper", "<productId>", "Equip a topper/hat by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: topper <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 5, "topper"); });

			RegisterCommand("paint", "<productId>", "Equip a paint finish by product ID.",
				[](const std::vector<std::string>& args)
			{ const int id = ParseIntOr(args, 0, -1); if (id < 0) { Push("[KingConsole] Usage: paint <productId>", LogLevel::Warning); return; } QueueEquipToSlot(id, 6, "paint"); });

			                                                                  
			RegisterCommand("find_function", "<text...>",
				"Search every loaded SDK UFunction by name (prints full names).",
				[](const std::vector<std::string>& args)
			{
				std::string needle;
				for (const std::string& a : args) { if (!needle.empty()) needle += " "; needle += a; }
				if (needle.empty()) { Push("[KingConsole] Usage: find_function <text>", LogLevel::Warning); return; }
				QueueFind(FindKind::Function, needle);
			});

			RegisterCommand("find_class", "<text...>",
				"Search every loaded SDK UClass by name (prints full names).",
				[](const std::vector<std::string>& args)
			{
				std::string needle;
				for (const std::string& a : args) { if (!needle.empty()) needle += " "; needle += a; }
				if (needle.empty()) { Push("[KingConsole] Usage: find_class <text>", LogLevel::Warning); return; }
				QueueFind(FindKind::Class, needle);
			});

			RegisterCommand("find_object", "<text...>",
				"Search ALL live objects by name (heavy scan; prints full names).",
				[](const std::vector<std::string>& args)
			{
				std::string needle;
				for (const std::string& a : args) { if (!needle.empty()) needle += " "; needle += a; }
				if (needle.empty()) { Push("[KingConsole] Usage: find_object <text>", LogLevel::Warning); return; }
				QueueFind(FindKind::AnyObject, needle);
			});

			                                                                   
			RegisterCommand("funclog", "<on|off|stream|clear> [filter]",
				"Log SDK function calls: 'on' lists each unique function once, "
				"'stream' shows every call, both accept a name filter.",
				[](const std::vector<std::string>& args)
			{
				if (args.empty())
				{
					Push(std::string("[KingConsole] Function logger is ") + (EventsComponent::IsFunctionLogEnabled() ? "ON" : "OFF") + ". Usage: funclog <on|off|stream|clear> [filter]", LogLevel::Notify);
					return;
				}
				const std::string sub = Lower(args[0]);
				std::string rest;
				for (size_t i = 1; i < args.size(); ++i) { if (!rest.empty()) rest += " "; rest += args[i]; }

				if (sub == "off" || sub == "stop" || sub == "0")
				{
					EventsComponent::SetFunctionLog(false, false, "");
					Push("[KingConsole] Function logger OFF.", LogLevel::Notify);
				}
				else if (sub == "clear")
				{
					EventsComponent::ClearFunctionLogSeen();
					Push("[KingConsole] Function logger reset -- unique names will list again.", LogLevel::Notify);
				}
				else if (sub == "stream")
				{
					EventsComponent::SetFunctionLog(true, true, rest);
					Push("[KingConsole] Function logger STREAMING" + (rest.empty() ? std::string(" (every call -- heavy, add a filter!)") : (" filter=\"" + rest + "\"")) + ". Run 'funclog off' to stop.", LogLevel::Warning);
				}
				else
				{
					                                                             
					const std::string filter = (sub == "on" || sub == "1")
						? rest
						: (rest.empty() ? args[0] : args[0] + " " + rest);
			EventsComponent::SetFunctionLog(true, false, filter);
				Push("[KingConsole] Function logger ON, each unique function once" + (filter.empty() ? std::string("") : (", filter=\"" + filter + "\"")) + ". Run 'funclog off' to stop.", LogLevel::Success);
			}
		});

		                                                                        
		                                  
		                                                      
		                                                                             
		                                                                         
		                                            
		RegisterCommand("spawn_bot", "<name> [team] [skill]",
			"Spawn a bot with a custom name. Team 0=Orange/1=Blue. Skill 0=Intro..4=Unfair.",
			[](const std::vector<std::string>& args)
		{
			if (args.empty())
			{
				Push("[KingConsole] Usage: spawn_bot <name> [team] [skill]", LogLevel::Warning);
				return;
			}

			std::string botName = args[0];
			const int team = ParseIntOr(args, 1, 255);
			const int skill = ParseIntOr(args, 2, 4);

			MainComponent::Execute([botName, team, skill]
			{
				AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
				if (!IsCallableObject(ge))
				{
					Push("[KingConsole] spawn_bot: not in a match.", LogLevel::Error);
					return;
				}

				URLBot_Util_TA* util = URLBot_Util_TA::GetInstance();
				if (!IsCallableObject(util))
				{
					Push("[KingConsole] spawn_bot: RLBot_Util not available.", LogLevel::Error);
					return;
				}

				FString fName = Format::ToFString(botName);
				uint8_t uTeam = (team == 0 || team == 1) ? static_cast<uint8_t>(team) : 255;
				float skillFloat = 0.0f;
				switch (skill)
				{
				case 0: skillFloat = 0.0f; break;
				case 1: skillFloat = 0.25f; break;
				case 2: skillFloat = 0.5f; break;
				case 3: skillFloat = 0.75f; break;
				default: skillFloat = 1.0f; break;
				}

				FBotLoadout emptyLoadout{};
				emptyLoadout.PrimaryColor = FColor{ 255, 255, 255, 255 };
				emptyLoadout.SecondaryColor = FColor{ 255, 255, 255, 255 };

				AAIController_TA* bot = util->eventSpawnClassicBot(
					ge, fName, uTeam, skillFloat, emptyLoadout);

				if (IsCallableObject(bot))
				{
					std::string skillName;
					switch (skill)
					{
					case 0: skillName = "Intro"; break;
					case 1: skillName = "Easy"; break;
					case 2: skillName = "Medium"; break;
					case 3: skillName = "Hard"; break;
					default: skillName = "Unfair"; break;
					}
					Push("[KingConsole] Spawned bot \"" + botName + "\" team=" +
						(uTeam == 0 ? "Orange" : uTeam == 1 ? "Blue" : "Auto") +
						" skill=" + skillName + ".", LogLevel::Success);
				}
				else
				{
					Push("[KingConsole] spawn_bot: failed to spawn bot (game may not support it here).", LogLevel::Error);
				}
			});
		});

		                    
		                                                                                     
		                                               
		RegisterCommand("remove_bot", "<name>",
			"Remove a bot by name (partial match, case-insensitive).",
			[](const std::vector<std::string>& args)
		{
			if (args.empty())
			{
				Push("[KingConsole] Usage: remove_bot <name>", LogLevel::Warning);
				return;
			}

			std::string needle = args[0];
			const std::string needleLower = Lower(needle);

			MainComponent::Execute([needleLower]
			{
				AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
				if (!IsCallableObject(ge) || !ge->AIManager || !IsCallableObject(ge->AIManager))
				{
					Push("[KingConsole] remove_bot: not in a match or no AI manager.", LogLevel::Error);
					return;
				}

				AAIManager_TA* aiMgr = ge->AIManager;
				bool removed = false;
				std::string removedName;

				                                                                                     
				TArray<AAIController_TA*> botsCopy = aiMgr->Bots;

				for (int i = 0; i < botsCopy.size(); ++i)
				{
					AAIController_TA* bot = botsCopy[i];
					if (!IsCallableObject(bot))
						continue;

					APRI_TA* pri = static_cast<APRI_TA*>(bot->PlayerReplicationInfo);
					if (!IsCallableObject(pri))
						continue;

					std::string botPriName = pri->PlayerName.ToString();
					if (Lower(botPriName).find(needleLower) != std::string::npos)
					{
						aiMgr->RemoveBot(bot);
						                                                      
						                                  
						if (bot->Pawn && !bot->Pawn->bDeleteMe)
							bot->Pawn->Destroy();
						if (!bot->bDeleteMe)
							bot->Destroy();
						removed = true;
						removedName = botPriName;
						break;
					}
				}

				if (removed)
					Push("[KingConsole] Removed bot \"" + removedName + "\".", LogLevel::Success);
				else
					Push("[KingConsole] remove_bot: no bot matching \"" + needleLower + "\".", LogLevel::Warning);
			});
		});

		              
		                                              
		RegisterCommand("remove_bots", "",
			"Remove all bots from the current match.",
			[](const std::vector<std::string>&)
		{
			MainComponent::Execute([]
			{
				AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
				if (!IsCallableObject(ge) || !ge->AIManager || !IsCallableObject(ge->AIManager))
				{
					Push("[KingConsole] remove_bots: not in a match or no AI manager.", LogLevel::Error);
					return;
				}

				AAIManager_TA* aiMgr = ge->AIManager;
				                                                                   
				std::vector<AAIController_TA*> toRemove;
				for (int i = 0; i < aiMgr->Bots.size(); ++i)
				{
					AAIController_TA* bot = aiMgr->Bots[i];
					if (IsCallableObject(bot))
						toRemove.push_back(bot);
				}

				int count = 0;
				for (AAIController_TA* bot : toRemove)
				{
					aiMgr->RemoveBot(bot);
					                                                      
					                                  
					if (bot->Pawn && !bot->Pawn->bDeleteMe)
						bot->Pawn->Destroy();
					if (!bot->bDeleteMe)
						bot->Destroy();
					++count;
				}

				Push("[KingConsole] Removed " + std::to_string(count) + " bot(s).", LogLevel::Success);
			});
		});

		                  
		                                                                    
		                                                           
		                                                          
		RegisterCommand("bot_skill", "<0-4>",
			"Set bot skill level. 0=Intro 1=Easy 2=Medium 3=Hard 4=Unfair.",
			[](const std::vector<std::string>& args)
		{
			const int skill = ParseIntOr(args, 0, -1);
			if (skill < 0 || skill > 4)
			{
				Push("[KingConsole] Usage: bot_skill <0-4>  (0=Intro, 1=Easy, 2=Medium, 3=Hard, 4=Unfair)", LogLevel::Warning);
				return;
			}

			MainComponent::Execute([skill]
			{
				AGameEvent_Soccar_TA* ge = GameEventHookModule::CurrentGameEvent;
				if (!IsCallableObject(ge))
				{
					Push("[KingConsole] bot_skill: not in a match.", LogLevel::Error);
					return;
				}

				if (!ge->BotConfig || !IsCallableObject(ge->BotConfig))
				{
					Push("[KingConsole] bot_skill: BotConfig not available.", LogLevel::Error);
					return;
				}

				float skillFloat = 0.0f;
				std::string skillName;
				switch (skill)
				{
				case 0: skillFloat = 0.0f; skillName = "Intro"; break;
				case 1: skillFloat = 0.25f; skillName = "Easy"; break;
				case 2: skillFloat = 0.5f; skillName = "Medium"; break;
				case 3: skillFloat = 0.75f; skillName = "Hard"; break;
				case 4: skillFloat = 1.0f; skillName = "Unfair"; break;
				}

				                                                       
				                                          
				for (int i = 0; i < 5; ++i)
					ge->BotConfig->Skills[i] = skillFloat;

				                                                        
				if (ge->AIManager && IsCallableObject(ge->AIManager))
				{
					AAIManager_TA* aiMgr = ge->AIManager;
					for (int i = 0; i < aiMgr->Bots.size(); ++i)
					{
						AAIController_TA* bot = aiMgr->Bots[i];
						if (!IsCallableObject(bot))
							continue;

						                                                
						                                             
						                                               
					}
				}

				Push("[KingConsole] Bot skill set to " + skillName + " (" +
					std::to_string((int)(skillFloat * 100)) + "%). " +
					std::to_string(ge->AIManager ? ge->AIManager->Bots.size() : 0) +
					" active bot(s) updated.", LogLevel::Success);
			});
		});
	}
	}

	                                                                           
	void Push(const std::string& text, LogLevel level)
	{
		LogEntry entry;
		entry.Time = ConsoleComponent::GetTimestamp(false).substr(1, 8);
		entry.Level = level;
		SplitCategory(text, entry.Category, entry.Text);

		std::lock_guard<std::mutex> lock(PendingMutex);
		if (Pending.size() > kMaxLogEntries)		                               
			Pending.erase(Pending.begin(), Pending.begin() + Pending.size() / 2);
		Pending.push_back(std::move(entry));
	}

	void Clear()
	{
		{
			std::lock_guard<std::mutex> lock(PendingMutex);
			Pending.clear();
		}
		Log.clear();
		Filtered.clear();
		FilterDirty = true;
	}

	void RegisterCommand(const std::string& name, const std::string& usage, const std::string& description, CommandHandler handler)
	{
		if (name.empty() || !handler)
			return;

		const std::string key = Lower(name);
		{
			std::lock_guard<std::mutex> lock(RegistryMutex);
			Registry[key] = Registered{ usage, description, std::move(handler) };
			RegistryNames[key] = name;
		}

		                                                                     
		                        
		CommandInfo info;
		info.Name = name;
		info.LowerName = key;
		info.Signature = usage.empty() ? name : name + " " + usage;
		info.Description = description;
		info.Source = CommandSource::KingMod;

		const auto existing = std::find_if(Commands.begin(), Commands.end(),
			[&key](const CommandInfo& c) { return c.LowerName == key; });
		if (existing == Commands.end())
			Commands.insert(Commands.begin(), std::move(info));
		else
			*existing = std::move(info);
	}

	void RefreshCommands()
	{
		if (RefreshInFlight.exchange(true, std::memory_order_acq_rel))
			return;

		                                                                         
		                                                                  
		MainComponent::Execute([] { BuildCommandListOnGameThread(); });
	}

	void Execute(const std::string& line)
	{
		const std::string trimmed = Trim(line);
		if (trimmed.empty())
			return;

		Push("[KingConsole] > " + trimmed, LogLevel::Command);

		if (History.empty() || History.back() != trimmed)
			History.push_back(trimmed);
		while (History.size() > kMaxHistory)
			History.erase(History.begin());
		HistoryPos = -1;

		const std::vector<std::string> tokens = Tokenize(trimmed);
		if (tokens.empty())
			return;

		CommandHandler handler;
		{
			std::lock_guard<std::mutex> lock(RegistryMutex);
			const auto it = Registry.find(Lower(tokens[0]));
			if (it != Registry.end())
				handler = it->second.Handler;
		}

		if (handler)
		{
			const std::vector<std::string> args(tokens.begin() + 1, tokens.end());
			try
			{
				handler(args);
			}
			catch (const std::exception& e)
			{
				Push("[KingConsole] Command threw: " + std::string(e.what()), LogLevel::Error);
			}
			catch (...)
			{
				Push("[KingConsole] Command threw an unknown exception.", LogLevel::Error);
			}
			return;
		}

		                                                       
		MainComponent::Execute([trimmed]
		{
			bool sent = false;
			const std::string reply = DispatchToGame(trimmed, sent);

			if (!sent)
			{
				Push("[KingConsole] No console target available yet (not in a game?).", LogLevel::Error);
				return;
			}

			const std::string trimmedReply = Trim(reply);
			if (!trimmedReply.empty())
			{
				                                                          
				size_t start = 0;
				while (start < trimmedReply.size())
				{
					size_t end = trimmedReply.find('\n', start);
					if (end == std::string::npos)
						end = trimmedReply.size();
					const std::string part = Trim(trimmedReply.substr(start, end - start));
					if (!part.empty())
						Push("[KingConsole] " + part, LogLevel::Result);
					start = end + 1;
				}
			}
		});
	}

	bool IsOpen()
	{
		return WindowOpen;
	}

	void SetOpen(bool bOpen)
	{
		if (WindowOpen == bOpen)
			return;

		WindowOpen = bOpen;
		if (WindowOpen)
			FocusInputNextFrame = true;
	}

	void Toggle()
	{
		SetOpen(!WindowOpen);
	}

	                                                                           
	void Render()
	{
		RegisterBuiltins();
		AdoptStagedCommands();
		DrainPending();

		if (!WindowOpen)
			return;

		if (!CommandsRequested)
		{
			CommandsRequested = true;
			RefreshCommands();
		}

		                                                                       
		                                                                       
		                                                   
		if (ExecCount == 0 && !RefreshInFlight.load(std::memory_order_acquire))
		{
			static int retryCountdown = 90;			                               
			if (--retryCountdown <= 0)
			{
				retryCountdown = 90;
				RefreshCommands();
			}
		}

		if (FilterDirty)
			RebuildFilter();

		const ImVec4 accent = g_RedThemeColor;

		ImGui::SetNextWindowSize(ImVec2(920.0f, 480.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(520.0f, 260.0f), ImVec2(FLT_MAX, FLT_MAX));
		ImGui::SetNextWindowBgAlpha(0.96f);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.055f, 0.057f, 0.070f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.085f, 0.088f, 0.105f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.10f, 0.105f, 0.125f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(accent.x, accent.y, accent.z, 0.35f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

		bool open = WindowOpen;
		if (!ImGui::Begin(ICON_FA_TERMINAL " KingMod Console", &open, ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
			ImGui::PopStyleVar(3);
			ImGui::PopStyleColor(4);
			WindowOpen = open;
			return;
		}
		WindowOpen = open;

		                                                                      
		                                                                        
		                                                                 

		                                                                       
		                                                                         
		                                                                       
		                                                                      
		const ImGuiStyle& style = ImGui::GetStyle();
		const float inputPadY = 16.0f;										                    
		const float inputReserve = ImGui::GetFontSize() + inputPadY * 2.0f + style.ItemSpacing.y * 2.0f + 8.0f;

		const float suggRowH = ImGui::GetTextLineHeightWithSpacing() + 2.0f;
		bool showSuggest = SuggestionsVisible() && InputActiveLastFrame;
		int  suggShown = showSuggest ? (std::min)(static_cast<int>(Suggestions.size()), kMaxSuggestionsShown) : 0;

		                                                                    
		const float availForLog = ImGui::GetContentRegionAvail().y;
		const float maxSuggH = (availForLog - inputReserve) * 0.6f;
		const int   spaceRows = (maxSuggH > suggRowH) ? static_cast<int>(maxSuggH / suggRowH) : 0;
		suggShown = (std::min)(suggShown, spaceRows);
		if (suggShown <= 0)
			showSuggest = false;
		const float suggReserve = showSuggest ? (suggRowH * suggShown + 10.0f) : 0.0f;

		                                                                       
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.030f, 0.032f, 0.040f, 1.00f));
		ImGui::BeginChild("KingConsoleLog", ImVec2(0.0f, -(inputReserve + suggReserve)), true,
			WrapLines ? 0 : ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::PushFont(MonoFont());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 1.0f));

		ImGuiListClipper clipper;
		clipper.Begin(static_cast<int>(Filtered.size()));
		while (clipper.Step())
		{
			for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
			{
				if (row < 0 || row >= static_cast<int>(Filtered.size()))
					continue;

				const LogEntry& entry = Log[Filtered[row]];

				if (ShowTimestamps)
				{
					ImGui::TextColored(ImVec4(0.40f, 0.43f, 0.50f, 1.00f), "%s", entry.Time.c_str());
					ImGui::SameLine();
				}

				ImGui::PushStyleColor(ImGuiCol_Text, LevelColor(entry.Level));
				ImGui::Text("%-4s", LevelTag(entry.Level));
				ImGui::PopStyleColor();
				ImGui::SameLine();

				if (ShowCategories)
				{
					ImGui::TextColored(CategoryColor(entry.Category), "%s", entry.Category.c_str());
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(0.35f, 0.37f, 0.44f, 1.00f), "|");
					ImGui::SameLine();
				}

				ImGui::PushStyleColor(ImGuiCol_Text, LevelColor(entry.Level));
				if (WrapLines)
					ImGui::TextWrapped("%s", entry.Text.c_str());
				else
					ImGui::TextUnformatted(entry.Text.c_str());
				ImGui::PopStyleColor();
			}
		}
		clipper.End();

		ImGui::PopStyleVar();
		ImGui::PopFont();

		                                                                          
		                                                                       
		if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
			ImGui::SetScrollHereY(1.0f);
		ScrollToBottom = false;

		ImGui::EndChild();
		ImGui::PopStyleColor();

		                                                                       
		                                                                       
		                                                                
		if (showSuggest)
		{
			if (SuggestionIndex < 0)
				SuggestionIndex = 0;
			if (SuggestionIndex >= static_cast<int>(Suggestions.size()))
				SuggestionIndex = static_cast<int>(Suggestions.size()) - 1;

			int first = 0;
			if (SuggestionIndex >= suggShown)
				first = SuggestionIndex - suggShown + 1;

			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.10f, 0.11f, 0.14f, 1.00f));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(accent.x, accent.y, accent.z, 0.55f));
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6.0f, 4.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
			ImGui::BeginChild("KingConsoleSuggest", ImVec2(0.0f, suggReserve), true, ImGuiWindowFlags_NoScrollbar);
			ImGui::PushFont(MonoFont());

			ImDrawList* draw = ImGui::GetWindowDrawList();
			ImFont* font = ImGui::GetFont();
			const float fontSize = ImGui::GetFontSize();

			for (int i = 0; i < suggShown; ++i)
			{
				const int sidx = first + i;
				if (sidx < 0 || sidx >= static_cast<int>(Suggestions.size()))
					break;

				const CommandInfo& command = Commands[Suggestions[sidx]];

				ImGui::PushID(sidx);
				const bool selected = (sidx == SuggestionIndex);
				if (ImGui::Selectable("##row", selected, 0, ImVec2(0.0f, suggRowH)))
				{
					SuggestionIndex = sidx;
					AcceptSuggestion();
				}
				if (ImGui::IsItemHovered())
					SuggestionIndex = sidx;

				                                                              
				const ImVec2 rmin = ImGui::GetItemRectMin();
				const ImVec2 rmax = ImGui::GetItemRectMax();
				const float ty = rmin.y + (suggRowH - fontSize) * 0.5f;

				float x = rmin.x + 8.0f;
				draw->AddText(font, fontSize, ImVec2(x, ty),
					ImGui::GetColorU32(ImVec4(0.94f, 0.96f, 1.00f, 1.00f)), command.Signature.c_str());

				const float sigW = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, command.Signature.c_str()).x;
				x += sigW + 12.0f;
				draw->AddText(font, fontSize * 0.85f, ImVec2(x, ty + 1.0f),
					ImGui::GetColorU32(SourceColor(command.Source)), SourceTag(command.Source));

				if (!command.Description.empty())
				{
					const float tagW = font->CalcTextSizeA(fontSize * 0.85f, FLT_MAX, 0.0f, SourceTag(command.Source)).x;
					x += tagW + 12.0f;
					if (x < rmax.x - 10.0f)
						draw->AddText(font, fontSize * 0.85f, ImVec2(x, ty + 1.0f),
							IM_COL32(140, 146, 160, 255), command.Description.c_str());
				}
				ImGui::PopID();
			}

			ImGui::PopFont();
			ImGui::EndChild();
			ImGui::PopStyleVar(3);
			ImGui::PopStyleColor(2);
		}

		                                                                       
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f, inputPadY));

		ImGui::AlignTextToFramePadding();
		ImGui::TextColored(accent, ">");
		ImGui::SameLine();

		if (FocusInputNextFrame)
		{
			ImGui::SetKeyboardFocusHere();
			FocusInputNextFrame = false;
		}

		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
		ImGui::PushFont(MonoFont());
		const bool submitted = ImGui::InputText("##KingConsoleInput", InputBuffer, sizeof(InputBuffer),
			ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion |
			ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackEdit,
			[](ImGuiInputTextCallbackData* data) { return InputCallback(data); });
		ImGui::PopFont();

		InputActiveLastFrame = ImGui::IsItemActive();
		ImGui::PopStyleVar();

		if (submitted)
		{
			                                                                       
			if (SuggestionsVisible() && SuggestionNavigated)
			{
				AcceptSuggestion();
			}
			else
			{
				Execute(InputBuffer);
				InputBuffer[0] = '\0';
				Suggestions.clear();
				ScrollToBottom = true;		                                     
			}
			FocusInputNextFrame = true;
		}

		                                                                    
		                                               
		if (InputActiveLastFrame && InputBuffer[0] != '\0' && !SuggestionsDismissed &&
			Commands.size() != LastSuggestCommandCount)
		{
			LastSuggestCommandCount = Commands.size();
			RecomputeSuggestions();
		}

		                                                                   
		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && ImGui::IsKeyPressed(ImGuiKey_Escape, false))
		{
			if (SuggestionsVisible())
				SuggestionsDismissed = true;
			else
				WindowOpen = false;
		}

		ImGui::End();
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(4);
	}
}

