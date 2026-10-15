#pragma once
#include "../pch.hpp"
#include "../Extensions/Includes.hpp"

                                      
class Module
{
private:
	std::string Name;				                
	std::string FormattedName;		                          
	std::string Description;		                       
	uint32_t AllowedStates;			                                               
	bool Initialized;				                                                                                

public:
	Module(const std::string& name, const std::string& description, uint32_t states);
	virtual ~Module();

public:
	std::string GetName() const;
	std::string GetNameFormatted() const;
	std::string GetDescription() const;
	uint32_t GetAllowedStates() const;
	bool IsAllowed() const;
	bool IsInitialized() const;
	void SetInitialized(bool bInitialized);
};