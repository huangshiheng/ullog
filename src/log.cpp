/*
 * @Descripttion: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-06-03 16:52:26
 * @LastEditTime: 2022-06-05 17:56:18
 */
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>

#include "../include/log.h"

namespace mylog {
    
    struct LogF {
        LogF() { }
        std::string file;
        int level;
        std::vector<std::string> define;
    };
    static void process_logf(const std::string& subkey, LogF* lf, std::string& val) {
        //std::cout << "process_logf " << subkey << " " << val << std::endl;
        if(subkey == "FILE") {
            lf->file = val;
        } else if(subkey == "LEVEL") {
            lf->level = stoi(val);
        } else if(subkey == "DEFINE") {
            std::string s = "";
            for (int i = 0; i < val.length(); i++) {
                if(val[i] == ',') {
                    lf->define.push_back(s);
                    s = "";
                } else {
                    s += val[i];
                }
            }
            lf->define.push_back(s);
        }
    }

    bool Loger::load_conf(std::string file_name) {
        std::fstream f(file_name);
        std::string line;
        std::unordered_map<std::string, LogF*> logf;
        std::vector<std::string> vstr {"FILE", "LEVEL", "DEFINE"};
        while(getline(f,line)) {
            if(line.length() == 0) {
                continue;
            }
            int pos = line.find(":");
            if(pos == line.npos) {
                std::cout << "log conf file parse failed" << std::endl;
                return false;
            }
            std::string key = line.substr(0, pos);
            std::string val = line.substr(pos + 1);
            for(std::string& s : vstr) {
                int pos1 = key.find(s);
                if(pos1 == key.npos) {
                    continue;
                }
                std::string subkey = key.substr(0, pos1);
                if(logf.find(subkey) != logf.end()) {
                    LogF* lf = logf[subkey];
                    process_logf(key.substr(pos1), lf, val);
                } else {
                    LogF* lf = new LogF();
                    process_logf(key.substr(pos1), lf, val);
                    logf[subkey] = lf;
                }
                break;
            }
        }

        for (auto it = logf.begin(); it != logf.end(); it++) {
            LogF* lf = it->second;
            if(lf == nullptr) {
                continue;
            }
            int fd = open(lf->file.c_str(), O_CREAT | O_RDWR | O_APPEND);
            if(fd == -1) {
                std::cout << "create log file " << lf->file << " failed" << std::endl;
                return false;
            }
            std::vector<std::string>& vs = lf->define; 
            for_each(vs.begin(), vs.end(), [&](std::string& s) {
                LogFile* lgf = new LogFile();
                lgf->fd = fd;
                lgf->level = lf->level;
                logfile[s] = lgf;
            });
        }
        return true;
    }

    Loger& Loger::get_instance() {
        static Loger loger;
        return loger;
    }

    int Loger::write_log(const std::string& define, const char * format, ... ) {
        if(logfile.find(define) == logfile.end()) {
            std::cout << "log file " << define << " is not exit" << std::endl;
            return -1;
        }
        LogFile* lf = logfile[define];
        if(lf->level > syslevel) {
            std::cout << "syslevel: " << syslevel << " log level: " << lf->level << std::endl;
            return -1;
        }
        char buff[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(buff, sizeof(buff), format, args);
        va_end(args);
        return write(lf->fd, buff, strlen(buff));
    }
}