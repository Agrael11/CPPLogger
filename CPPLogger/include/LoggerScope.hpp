#pragma once

#include <string_view>

namespace TachiTools::Logger
{
    class LoggerScope
    {
        public:
            LoggerScope(const std::string_view moduleName, const std::string_view subModuleName);
            ~LoggerScope();
    };
};