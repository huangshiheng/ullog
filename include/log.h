/*
 * @Descripttion: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-06-03 17:06:44
 * @LastEditTime: 2022-06-05 13:56:11
 */
#pragma once

#include <unordered_map>

namespace mylog {
    struct LogFile {
        LogFile() { }
        int fd;
        int level;
    };

    class Loger {
    public:
        Loger() { };
        bool load_conf(std::string file_name);
        static Loger& get_instance();
        int write_log(const std::string& define, const char * format, ... );
        void set_syslevel(int level) {
            syslevel = level;
        }
    private:
        std::unordered_map<std::string, LogFile*> logfile;
        int syslevel;
    };
}

/*
LOG_FILE: .log
LOF_LEVEL: 4
LOG_DEFINE: NOTICE,DEBUG

LOG_WF_FILE:
LOF_WF_LEVEL: 4
LOG_WF_DEFINE: WARNING,FAIL
*/

