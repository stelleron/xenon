#include "res/filesystem.hpp"
#include <fstream>
#include <sstream>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils/logger.hpp"
#include <stdlib.h>

namespace xenon {
    namespace filesystem {
        std::string currentWorkingDir = "";

        void set_dir(const std::string& dir) {
            if (!dir_exists(dir)) {
                ERROR("Filesystem: Directory does not exist!");
                exit(1);
            }
            currentWorkingDir = dir;
            if (dir[-1] != '/') {
                currentWorkingDir += '/';
            }
        }

        bool dir_exists(const std::string& dir) {
            struct stat buffer;
            stat(dir.c_str(), &buffer);
            if (buffer.st_mode & S_IFDIR) {
                return true;
            }
            else {
                return false;
            }
        }

        bool file_exists(const std::string& path) {
            struct stat buffer;
            stat(path.c_str(), &buffer);
            if (buffer.st_mode & S_IFREG) {
                return true;
            }
            else {
                return false;
            }
        }

        std::string load_file_str(const std::string& dir) {
            std::string path = currentWorkingDir;
            path += dir;
            if (!file_exists(path)) {
                ERROR("Filesystem: File does not exist!");
                exit(1);
            }
            std::ifstream fin(path, std::ios::in);
            std::stringstream buffer;
            buffer << fin.rdbuf() << '\0';
            return buffer.str();
        }

        char* load_file_text(const std::string& dir, size_t& fsize) {
            std::string path = currentWorkingDir;
            path += dir;
            if (!file_exists(path)) {
                ERROR("Filesystem: File does not exist!");
                exit(1);
            }
            std::string source = load_file_str(path);
            char* buffer = new char[source.size()];
            fsize = source.size() * sizeof(char);
            memcpy( buffer, source.c_str(), source.size() );
            return buffer;
        }

        unsigned char* load_file_data(const std::string& dir, size_t& fsize) {
            std::string path = currentWorkingDir;
            path += dir;
            if (!file_exists(path)) {
                ERROR("Filesystem: File does not exist!");
                exit(1);
            }
            FILE *file = fopen(path.c_str(), "rb");
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            fseek(file, 0, SEEK_SET);
            unsigned char* data = new unsigned char[size];
            unsigned int count = fread(data, 1, size, file);
            fsize = count;
            fclose(file);
            return data;
        }

        void unload_file_text(char* data) {
            delete[] data;
        }

        void unload_file_data(unsigned char* data) {
            delete[] data;
        }
        void save_file_str(const std::string& path, const std::string& data) {
            std::string fpath = currentWorkingDir;
            fpath += path;
            std::ofstream output(fpath, std::ios::out);
            output << data;
        }
        void save_file_text(const std::string& path, char* data) {
            std::string fpath = currentWorkingDir;
            fpath += path;
            std::ofstream output(fpath, std::ios::out);
            output << data;
        }
        void save_file_data(const std::string& path, unsigned char* data) {
            std::string fpath = currentWorkingDir;
            fpath += path;
            std::ofstream output(fpath, std::ios::out);
            output << data;
        }
        std::string get_file_extension(const std::string& path) {
            return path.substr(path.find_last_of(".") + 1);
        }
    }
}