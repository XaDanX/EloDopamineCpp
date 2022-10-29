#pragma once
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <memory>
#include <string>
#include <stdio.h>
#include <stdarg.h>

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif


enum LogLevel {
    Info,
    Warning,
    Error,
    Debug
};

class Logger { // TODO: Recode, its ghetto and using 2 streams but i need it for testing.
private:
    LogLevel level{LogLevel::Info};

    std::string TimeFormat() {
        
        return "[]: ";

    }

    std::string INFO =    "[INFO    ] ";
    std::string WARNING = "[WARNING ] ";
    std::string ERROR_T = "[ERROR   ] ";
    std::string DEBUG =   "[DEBUG   ] ";

public:
    void SetLevel(LogLevel l) {
        this->level = l;
    }
    void Info(const char* format, ...) {

        std::cout << (this->TimeFormat())
        << " "
        << (INFO)
        << (" >> ");
        va_list argptr;
        va_start(argptr, format);

        vprintf(format, argptr);

        va_end(argptr);
        std::cout << "\n";
    }
    void Warn(const char* format, ...) {
        if (level < LogLevel::Warning) return;
        std::cout << (this->TimeFormat())
                  << " "
                  << (WARNING)
                  << (" >> ");
        va_list argptr;
                va_start(argptr, format);

        vprintf(format, argptr);

                va_end(argptr);
        std::cout << "\n";
    }
    void Error(const char* format, ...) {
        if (level < LogLevel::Error) return;
        std::cout << (this->TimeFormat())
                  << " "
                  << (ERROR_T)
                  << (" >> ");
        va_list argptr;
                va_start(argptr, format);

        vprintf(format, argptr);

                va_end(argptr);
        std::cout << "\n";
    }
    void Debug(const char* format, ...) {
        if (level < LogLevel::Debug) return;
        std::cout << (this->TimeFormat())
                  << " "
                  << (DEBUG)
                  << (" >> ");
        va_list argptr;
                va_start(argptr, format);

        vprintf(format, argptr);

                va_end(argptr);
                std::cout << "\n";
    }


};
inline extern std::unique_ptr<Logger> logger = std::make_unique<Logger>();