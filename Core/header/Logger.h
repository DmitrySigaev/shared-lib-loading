#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <sstream>
#include <memory>

#define class_name() typeid(this).name()


using namespace std;

class Logger {

private:

    static shared_ptr<Logger> logger;

    void log(string, string, string);

public:
    static void init();

    static void info(string, string = "NULL");

    static void error(string, exception *, string = "NULL");

};

#endif //_LOGGER_H