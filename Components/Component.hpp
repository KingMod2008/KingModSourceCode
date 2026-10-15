#pragma once
#include "../pch.hpp"
#include "../Extensions/Includes.hpp"

                                                                                   
class Component
{
private:
	std::string Name;
	std::string FormattedName;
	std::string Description;

public:
	Component(const std::string& name, const std::string& description);
	virtual ~Component();

public:                                                                                   
	virtual void OnCreate();
	virtual void OnDestroy();

public:
	std::string GetName() const;
	std::string GetNameFormatted() const;
	std::string GetDescription() const;
};