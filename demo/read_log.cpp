/*
 * @Descripttion: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-06-03 19:10:42
 * @LastEditTime: 2022-07-17 10:42:07
 */

#include <iostream>
#include "log.h"
#include <thread>

int main() {

    mylog::Loger loger = mylog::Loger::get_instance();
    if(!loger.load_conf("log.conf")) {
        std::cout << "log cong init failed" << std::endl;
    }
    loger.set_syslevel(4);
    loger.write_log("FAIL", "Hello %s\n", "World");

    std::thread th1([&](){
        loger = mylog::Loger::get_instance();
        loger.set_syslevel(4);
        if(!loger.load_conf("log.conf")) {
            std::cout << "log cong init failed" << std::endl;
        }
        for (int i = 0; i < 10000; ++i) {
            loger.write_log("FAIL", "Hello %s\n", "Huangshiheng");
        }
    });

    std::thread th2([&](){
        loger = mylog::Loger::get_instance();
        loger.set_syslevel(4);
        if(!loger.load_conf("log.conf")) {
            std::cout << "log cong init failed" << std::endl;
        }
        for (int i = 0; i < 10000; ++i) {
            loger.write_log("FAIL", "Hello %s\n", "Huang");
        }
    });

    std::thread th3([&](){
        loger = mylog::Loger::get_instance();
        loger.set_syslevel(4);
        if(!loger.load_conf("log.conf")) {
            std::cout << "log cong init failed" << std::endl;
        }
        for (int i = 0; i < 10000; ++i) {
            loger.write_log("FAIL", "Hello %s\n", "Code");
        }
    });

    th3.join();
    th2.join();
    th1.join();

    return 0;
}
