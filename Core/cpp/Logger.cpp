#include <Logger.h>

shared_ptr<Logger> Logger::logger = nullptr;

void Logger::log(string class_name, string type, string message) {
    time_t t = time(0);
    string current_time = ctime(&t);

    char mbstr[100];
    strftime(mbstr, sizeof(mbstr), "%d-%m-%Y %H:%M:%S", localtime(&t));
    stringstream out;
    out <<  mbstr << " " << type << " --- ["
        << class_name << "] "
        << message
        << endl;
    cerr << out.str();
}


void Logger::init() {
    logger = shared_ptr<Logger>(new Logger());
}

void Logger::info(string message, string producer) {
    logger->log(producer, "INFO", message);
}

void Logger::error(string message, exception *ex, string producer) {
    string error_message = ex->what();
    logger->log(producer, "WARN", "Error message: " + error_message + " ; Log message: " + message);
}