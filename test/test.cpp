/*
 * @Descripttion: file content
 * @version: 
 * @Author: huangshiheng
 * @Date: 2022-06-03 18:26:32
 * @LastEditTime: 2022-06-05 17:51:10
 */
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

#include <fstream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;
class W {
    public:
    void write_log(const string& s, const char * format, ... ) {
        char buff[20];
        va_list args;
        va_start(args, format);
        vsnprintf(buff, sizeof(buff), format, args);
        va_end(args);
        //snprintf(buff, sizeof(buff), "Hello %s\n", "Woord");
        std::cout << buff << std::endl;
    }
};

int read_file() {   

    fstream     f("dictionary.txt");//创建一个fstream文件流对象
    vector<string>  words; //创建一个vector<string>对象
    string      line; //保存读入的每一行
    while(getline(f,line))//会自动把\n换行符去掉 
    {
        words.push_back(line);  
    }
    //dictionary.txt在csdn里面可以下载，里面有4万多个单词，相当于一个字典
    cout << "共有单词数目:" << words.size() << endl;
    return  0;

}

int write_file() {
    int fd = open("file.log", O_CREAT | O_RDWR | O_APPEND );
    if(fd == -1) {
        std::cout << "open file failed" << std::endl;
    }
    char buff[] = "Hello World";
    return write(fd ,buff, sizeof(buff));
}

int main() {
    //W w;
    //w.write_log("WARNING","Hello %s", "Woord");
    //read_file();
    write_file();
    return 0;
}