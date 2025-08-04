#include "AudioSystem.h"
#include "../Core/StringHelper.h"

#include <fmod_errors.h>
#include <iostream>

namespace errera {
    /// <summary>
    /// 
    /// </summary>
    /// <param name="result"></param>
    /// <returns></returns>
    bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
        if (result != FMOD_OK) {
            std::cerr << FMOD_ErrorString(result) << std::endl;
            return false;
        }
        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    bool AudioSystem::Initialize() {
        FMOD_RESULT result = FMOD::System_Create(&_system);

        if (!CheckFMODResult(result)) return false;

        void* extradriverdata = nullptr;

        if (!CheckFMODResult(result)) return false;

        result = _system->init(32, FMOD_INIT_NORMAL, extradriverdata);

        return true;
    }

    /// <summary>
    /// 
    /// </summary>
    void AudioSystem::Shutdown() {
        CheckFMODResult(_system->release());
    }

    /// <summary>
    /// 
    /// </summary>
    void AudioSystem::Update() {
        CheckFMODResult(_system->update());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="name"></param>
    /// <returns></returns>
    bool AudioSystem::AddSound(const std::string& filename, const std::string& name) {
        std::string key = (name.empty()) ? filename : name;
        key = tolower(key);

        // Check if key exists in sounds map
        if (_sounds.find(key) != _sounds.end()) {
            std::cerr << "Audio System: Name Already Exists {" << key << "}" << std::endl;
            return false;
        }

        // Create sound from key
        FMOD::Sound* sound = nullptr;
        FMOD_RESULT result = _system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
        if (!CheckFMODResult(result)) return false;

        // Insert into map
        _sounds[key] = sound;

        return true;
    }

    bool AudioSystem::PlaySound(const std::string& name) {
        std::string key = name;
        key = tolower(key);

        // Check if sound exists
        if (_sounds.find(key) == _sounds.end()) {
            std::cerr << "Audio System: Name Doesn't Exist {" << key << "}" << std::endl;
            return false;
        }

        // Play sound from key
        FMOD_RESULT result = _system->playSound(_sounds[key], 0, false, nullptr);
        if (!CheckFMODResult(result)) return false;

        return true;
    }
}
