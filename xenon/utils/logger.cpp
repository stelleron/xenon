#include "utils/logger.hpp"
#include <iostream>

namespace xenon {
    // Disable log function
    void disabledCallback(const char* message) {

    }

    // Default log function
    void defaultLogCallback(const char* message) {
        std::cout << message << std::endl;
    }

    Logger::Logger() {
        message = "";
        #ifdef ENABLE_XENON_LOGGER
            useDefault();
        #else
            disable();
        #endif
    }

    void Logger::disable() {
        setLogCallback(disabledCallback);
        setErrorCallback(disabledCallback);
    }

    void Logger::useDefault() {
        setLogCallback(defaultLogCallback);
        setErrorCallback(defaultLogCallback);
    }

    void Logger::setLogCallback(std::function<void(const char*)> callback) {
        logCallback = callback;
    }

    void Logger::setErrorCallback(std::function<void(const char*)> callback) {
        errorCallback = callback;
    }

    Logger& Logger::operator<<(const std::string& message) {
        this->message += message;
        return *this;
    }

    Logger& Logger::operator<<(const char character) {
        this->message += character;
        return *this;
    }

    Logger& Logger::operator<<(const char* message) {
        this->message += message;
        return *this;
    }

    Logger& Logger::operator<<(const int num) {
        this->message += std::to_string(num);
        return *this;
    }

    Logger& Logger::operator<<(const float num) {
        this->message += std::to_string(num);
        return *this;
    }

    Logger& Logger::operator<<(const unsigned int num) {
        this->message += std::to_string(num);
        return *this;
    }

    Logger& Logger::operator<<(const unsigned long num) {
        this->message += std::to_string(num);
        return *this;
    }

    Logger& Logger::operator<<(const Vertex vertex) {
        this->message += "Position: (";
            this->message += std::to_string(vertex.pos.x);
            this->message += ", ";
            this->message += std::to_string(vertex.pos.y);
            this->message += ")\n";
        this->message += "Color: (";
            this->message += std::to_string(vertex.color.r);
            this->message += ", ";
            this->message += std::to_string(vertex.color.g);
            this->message += ", ";
            this->message += std::to_string(vertex.color.b);
            this->message += ", ";
            this->message += std::to_string(vertex.color.a);
            this->message += ")\n";
        this->message += "Tex Coords: (";
            this->message += std::to_string(vertex.texCoords.x);
            this->message += ", ";
            this->message += std::to_string(vertex.texCoords.y);
            this->message += ")\n";
        return *this;
    }

    Logger& Logger::operator<<(const Vector2 vec) {
        this->message += "(";
        this->message += std::to_string(vec.x);
        this->message += ", ";
        this->message += std::to_string(vec.y);
        this->message += ")";
        return *this;
    }

    Logger& Logger::operator<<(const Vector3 vec) {
        this->message += "(";
        this->message += std::to_string(vec.x);
        this->message += ", ";
        this->message += std::to_string(vec.y);
        this->message += ", ";
        this->message += std::to_string(vec.z);
        this->message += ")";
        return *this;
    }

    Logger& Logger::operator<<(const Vector4 vec) {
        this->message += "(";
        this->message += std::to_string(vec.x);
        this->message += ", ";
        this->message += std::to_string(vec.y);
        this->message += ", ";
        this->message += std::to_string(vec.z);
        this->message += ", ";
        this->message += std::to_string(vec.w);
        this->message += ")";
        return *this;
    }

    Logger& Logger::operator<<(const Rectangle rect) {
        this->message += "(";
        this->message += std::to_string(rect.pos.x);
        this->message += ", ";
        this->message += std::to_string(rect.pos.y);
        this->message += ", ";
        this->message += std::to_string(rect.width);
        this->message += ", ";
        this->message += std::to_string(rect.height);
        this->message += ")";
        return *this;
    }

    void Logger::operator<<(const EndLog end) {
        if (end.mType == Message)
            logCallback(message.c_str());
        else
            errorCallback(message.c_str());
        message = "";
    }

    // Internal logger
    Logger logger;
    EndLog end_message;
    EndLog end_error;
}