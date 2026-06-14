#include <LoggerScope.hpp>

#include <string_view>
#include <Logger.hpp>

TachiTools::Logger::LoggerScope::LoggerScope(const std::string_view moduleName, const std::string_view subModuleName)
{
    Logger::enterModule(moduleName);
    Logger::enterSubmodule(subModuleName);
}

TachiTools::Logger::LoggerScope::~LoggerScope()
{
    Logger::exitSubmodule();
    Logger::exitModule();
}