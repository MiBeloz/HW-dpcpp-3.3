#pragma once

#include <string>
#include <iostream>
#include <fstream>


enum class Type {
    warning,
    error,
    fatalError,
    unknownMessage
};

class LogMessage {
public:
    LogMessage() : nextLogMessage(nullptr) {}

    LogMessage* setNextLogMessage(LogMessage* logMessage) noexcept {
        nextLogMessage = logMessage;
        return nextLogMessage;
    }

    virtual const std::string message() const {
        if (nextLogMessage) {
            return nextLogMessage->message();
        }
        return {};
    }

private:
    LogMessage* nextLogMessage;
};

class LogMessageWarning : public LogMessage {
public:
    Type type() const noexcept { return m_type; }
    const std::string message() const override { 
        if (type() == Type::warning) {
            return "Warning!";
        }
        else {
            return LogMessage::message();
        }
    }

private:
    Type m_type = Type::warning;
};

class LogMessageError : public LogMessage {
public:
    LogMessageError(const std::string& filename) : m_filename(filename) {}

    Type type() const noexcept { return m_type; }
    const std::string message() const override {
        if (type() == Type::error) {
            std::fstream ofile;
            ofile.open(m_filename, std::fstream::app);

            if (ofile.is_open()) {
                ofile << "Error" << std::endl;
            }
            ofile.close();

            return "Ошибка записана в файл '" + m_filename + "'.";
        }
        else {
            return LogMessage::message();
        }
    }

private:
    std::string m_filename;
    Type m_type = Type::error;
};

class LogMessageFatalError : public LogMessage {
public:
    Type type() const noexcept { return m_type; }
    const std::string message() const override {
        if (type() == Type::fatalError) {
            std::cout << "Исключение!" << std::endl;
            throw "Fatal Error!";
        }
        else {
            return LogMessage::message();
        }
    }

private:
    Type m_type = Type::fatalError;
};

class LogMessageUnknownMessage : public LogMessage {
public:
    Type type() const noexcept { return m_type; }
    const std::string message() const override {
        if (type() == Type::unknownMessage) {
            std::cout << "Исключение!" << std::endl;
            throw "Unknown Message!";
        }
        else {
            return LogMessage::message();
        }
    }

private:
    Type m_type = Type::unknownMessage;
};
