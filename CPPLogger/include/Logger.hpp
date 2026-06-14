#pragma once

#include <string>
#include <format>

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
            if (sizeof...(args) == 0)
            {
                Logger::logSimple(level, message, this.m_moduleName);
            }
            else
            {
                std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
                Logger::logSimple(level, formattedMessage, this.m_moduleName);
            }
        }

        template<typename ... Args>
        static void log(const Logger::Level level, const std::string_view subHeader, const std::string_view message, Args&& ... args)
        {
            std::string header = std::format("{}/{}", this.m_moduleName, subHeader);
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
        static void log(const Logger::Level level, const std::string_view customHeader, const std::string_view subHeader, const std::string_view message, Args&& ... args)
        {
            std::string header = std::format("{}/{}", customHeader, subHeader);
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

    private:
        static void logSimple(const Level level, const std::string_view message, const std::string_view header);
        static std::string returnCurrentTimeDate(const std::string_view format);
        static std::string makeColor(const ConsoleColor color, const bool background, const bool bright);
        static void logConsole(const Level level, const std::string_view message, const std::string_view realTime, const std::string_view header);
        static void logFile(const Level level, const std::string_view message, const std::string_view realTime, const std::string_view header);

        static std::string m_fileName;
        static std::string m_moduleName;
        static bool m_printToFile;
        static bool m_overrideFile;
        static bool m_openedFile;
        static bool m_saveTimedCopy;
        static std::string m_timedCopyName;
        static Level m_minimumPrintLevel;
        static Level m_minimumFileLevel;
    };
};