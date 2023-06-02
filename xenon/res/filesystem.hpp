#ifndef XENON_FILESYSTEM
    #define XENON_FILESYSTEM
    #include <string>
    namespace xenon {
        // Filesystem namespace
        namespace filesystem {
            // Set the working directory
            void set_dir(const std::string& dir);
            // Check if directory exists
            bool dir_exists(const std::string& dir);
            // Check if file exists
            bool file_exists(const std::string& dir);


            // File loading functions
            std::string load_file_str(const std::string& fpath); // Load it as a string instead
            char* load_file_text(const std::string& fpath, size_t& fsize); // Null terminates the file text
            unsigned char* load_file_data(const std::string& path, size_t& fsize);
            // File unloading functions
            void unload_file_text(char* data);
            void unload_file_data(unsigned char* data);
            // File saving functions
            void save_file_str(const std::string& path, const std::string& data);
            void save_file_text(const std::string& path, char* data);
            void save_file_data(const std::string& path, unsigned char* data);
            
            // Get file extension
            std::string get_file_extension(const std::string& path);
        };
    }
#endif