#include "Json.h"

#include <rapidjson/istreamwrapper.h>

namespace errera::json {
    bool Load(const std::string& filename, document_t& document) {
        // Read the file into a string
        std::string buffer;
        if (!file::ReadTextFile(filename, buffer)) {
            Logger::Error("Could not read file: {}", filename);
            return false;
        }

        // Convert the string into a json stream
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // Set the json document from the stream
        document.ParseStream(istream);
        // Check if the parse was successful
        if (!document.IsObject()) {
            Logger::Error("Could not parse Json: {}", filename);
            return false;
        }
        return true;
    }

    bool Read(const value_t& value, const std::string& name, int& data) {
        // Check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
            Logger::Error("Could not read Json value (int): {}", name);
            return false;
        }

        // Get the data
        data = value[name.c_str()].GetInt();
        return true;
    }

    bool Read(const value_t& value, const std::string& name, float& data) {
        // Check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat()) {
            Logger::Error("Could not read Json value (float): {}", name);
            return false;
        }

        // Get the data
        data = value[name.c_str()].GetFloat();
        return true;
    }

    bool Read(const value_t& value, const std::string& name, bool& data) {
        // Check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {
            Logger::Error("Could not read Json value (bool): {}", name);
            return false;
        }

        // Get the data
        data = value[name.c_str()].GetBool();
        return true;
    }

    bool Read(const value_t& value, const std::string& name, std::string& data) {
        // Check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
            Logger::Error("Could not read Json value (string): {}", name);
            return false;
        }

        // Get the data
        data = value[name.c_str()].GetString();
        return true;
    }

    bool Read(const value_t& value, const std::string& name, vec2& data) {
        // Check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {
            Logger::Error("Could not read Json value (vec2): {}", name);
            return false;
        }

        // Get json array object
        auto& array = value[name.c_str()];

        // Get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}", name);
                return false;
            }

            // Get the data
            data[i] = array[i].GetFloat();
        }
        return true;
    }

    bool Read(const value_t& value, const std::string& name, vec3& data) {
        // Check if the value has the "<name>" and is an array with 3 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3) {
            Logger::Error("Could not read Json value (vec3): {}", name);
            return false;
        }

        // Get json array object
        auto& array = value[name.c_str()];

        // Get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}", name);
                return false;
            }

            // Get the data
            data[i] = array[i].GetFloat();
        }
        return true;
    }

}

