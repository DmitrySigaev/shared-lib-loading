
#ifndef _ENVVARIABLESIMPORTER_H
#define _ENVVARIABLESIMPORTER_H

#include <iostream>
#include <map>
#include <fstream>
#include <memory>
#include <sstream>
#include <algorithm>

#include <Logger.h>

using namespace std;

class EnvVariablesImporter {
public:
    static void load(const string &configDirPath, const string &envName);

    static void load(const string &configDirPath);

    static string get_string(const string &key);

    static int get_int(const string &key);

    static string get_all_values_as_string();

private:
    static void load_from_file(const string &filename);

    static shared_ptr<map<string, string>> variables;

};

#endif // _ENVVARIABLESIMPORTER_H
