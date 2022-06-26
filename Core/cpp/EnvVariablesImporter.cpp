#include "EnvVariablesImporter.h"

#define ENVIRONMENT_VARIABLE_NAME "okkoenv"


shared_ptr<map<string, string>> EnvVariablesImporter::variables = nullptr;

void EnvVariablesImporter::load(const string &configDirPath) {
    if (!getenv(ENVIRONMENT_VARIABLE_NAME)){
        Logger::info("Variable " + std::string(ENVIRONMENT_VARIABLE_NAME) + " should be specified via environment variable or parameter");
        exit(1);
    }
    string envName = getenv(ENVIRONMENT_VARIABLE_NAME);
    load(configDirPath, envName);
}

void EnvVariablesImporter::load(const string &configDirPath, const string &envName) {
    // init map
    variables = make_shared<map<string, string>>();

    // file paths
    string defaultConfigPath = configDirPath + "app.property";
    string extraConfigPath = configDirPath + "app-" + envName + ".property";
    Logger::info("Loading env variables from files: " + defaultConfigPath + " " + extraConfigPath);

    load_from_file(defaultConfigPath);
    load_from_file(extraConfigPath);
}

void EnvVariablesImporter::load_from_file(const string &filename) {
    ifstream configFileStream;
    configFileStream.open(filename, ios_base::in);

    if (!configFileStream.good()) {
        throw invalid_argument(string("Something went wrong with file ") + filename +
                               " . Does it exists?");
    }


    for (string line; getline(configFileStream, line);) {
        // remove ' '
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

        // make it a stream
        istringstream is_line(line);

        //read key until '='
        string key;
        if (getline(is_line, key, '=')) {
            string value;

            // read value after '="
            if (getline(is_line, value))

                // set key value pair
                EnvVariablesImporter::variables->insert_or_assign(key, value);
        }
    }

    configFileStream.close();
}

string EnvVariablesImporter::get_string(const string &key) {
    try {
        return EnvVariablesImporter::variables->at(key);
    }
    catch (out_of_range &e) {
        throw invalid_argument(string("Value \"") + key + "\" does not exists");
    }
}

int EnvVariablesImporter::get_int(const string &key) {
    try {
        return stoi(EnvVariablesImporter::variables->at(key));
    }
    catch (out_of_range &e) {
        throw invalid_argument(string("Value \"") + key + "\" does not exists");
    }
}

string EnvVariablesImporter::get_all_values_as_string() {
    stringstream out;
    for (const auto &pair: *variables) {
        out << pair.first << " : " << pair.second << endl;
    }
    return out.str();
}
