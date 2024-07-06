#include <exception>
#include <filesystem>

class ConfigJSONNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Config file is missing!";
    }
};

class ConfigFieldNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Config file is empty!";
    }
};

class NameFieldNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Name field is missing!";
    }
};

class VersionFieldNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Version field is missing!";
    }
};

class FilesFieldNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Files field is missing!";
    }
};

class RequestsJSONNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Request file is missing!";
    }
};

class RequestsFieldNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Request file is empty!";
    }
};

class AnswersJSONNotExistsException : std::exception {
public:
    const char * what() const noexcept override {
        return "Answers file is missing!";
    }
};

class FileNotExistsException : std::exception {
private:
    std::filesystem::path file_path;
public:
    FileNotExistsException(std::filesystem::path p) : file_path(p) {}
    const char * what() const noexcept override {
        std::string result = std::string("File \"") + std::filesystem::absolute(file_path).string() + std::string("\" is missing!");
        return result.c_str();
    }
};
