#pragma once

#include <string>
#include <format>
#include <stack>

namespace TachiTools::Logger
{
    class Logger
    {
    public:
        enum class Level { Debug, Info, Warning, Error, Fatal };
        enum class ConsoleColor { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Reset = -1 };
        

        static void setup(const Level minimumPrintLevel = Level::Info, const Level minimumFileLevel = Level::Warning, const bool printToFile = false, const std::string fileName = "", const bool saveTimedCopy = true, const bool overrideFile = true, const std::string moduleName = "");

        template<typename ... Args>
        static void log(const Logger::Level level, const std::string_view message, Args&& ... args)
        {
            std::string header;
            if (!m_moduleName.empty() && !m_submoduleName.empty())
            {
                header = std::format("{}/{}", m_moduleName, m_submoduleName);
            }
            else if (!m_moduleName.empty())
            {
                header = std::format("{}", m_moduleName);
            }
            else
            {
                header = "";
            }
            if (sizeof...(args) == 0)
            {
                Logger::logSimple(level, message, header);
            }
            else
            {
                std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
                Logger::logSimple(level, formattedMessage, header);
            }
        }

        template<typename ... Args>
        static void log(const std::string_view customHeader, const std::string_view customSubHeader, const Logger::Level level, const std::string_view message, Args&& ... args)
        {
            std::string header;
            if (!customHeader.empty() && !customSubHeader.empty())
            {
                header = std::format("{}/{}", customHeader, customSubHeader);
            }
            else if (!customHeader.empty())
            {
                header = std::format("{}", customHeader);
            }
            else
            {
                header = "";
            }
            if (sizeof...(args) == 0)
            {
                Logger::logSimple(level, message, header);
            }
            else
            {
                std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
                Logger::logSimple(level, formattedMessage, header);
            }
        }

        static void enterModule(const std::string_view moduleName);
        static void exitModule();
        static void enterSubmodule(const std::string_view subModuleName);
        static void exitSubmodule();

    private:
        static void logSimple(const Level level, const std::string_view message, const std::string_view header);
        static std::string returnCurrentTimeDate(const std::string_view format);
        static std::string makeColor(const ConsoleColor color, const bool background, const bool bright);
        static void logConsole(const Level level, const std::string_view message, const std::string_view realTime, const std::string_view header);
        static void logFile(const Level level, const std::string_view message, const std::string_view realTime, const std::string_view header);

        static std::string m_fileName;
        static std::string m_moduleName;
        static std::string m_submoduleName;
        static std::stack<std::string> m_moduleStack;
        static std::stack<std::string> m_headerStack;
        static bool m_printToFile;
        static bool m_overrideFile;
        static bool m_openedFile;
        static bool m_saveTimedCopy;
        static std::string m_timedCopyName;
        static Level m_minimumPrintLevel;
        static Level m_minimumFileLevel;
    };
};