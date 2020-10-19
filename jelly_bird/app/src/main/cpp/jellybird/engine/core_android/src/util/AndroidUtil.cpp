#include "../../include/AndroidUtil.h"

const unsigned int AndroidUtil::BUFFER_SIZE = 200;

bool AndroidUtil::loadFileFromAssets(android_app* app, const std::string & path, std::string & result) {
    AAsset * file = AAssetManager_open(app->activity->assetManager, path.c_str(), AASSET_MODE_BUFFER);
    if(!file) {
        return false;
    }
    size_t fileLength = AAsset_getLength(file);
    char * fileContent = new char[fileLength + 1]; // +1 for the extra '\0' at the end
    char buffer[BUFFER_SIZE];

    int readResult, read = 0;
    while((readResult = AAsset_read(file, buffer, BUFFER_SIZE)) > 0){
        for(int i = 0; i < readResult; ++i) {
            fileContent[read + i] = buffer[i];
        }
        read += readResult;
    }
    if(readResult < 0) {
        AAsset_close(file);
        delete[] fileContent;
        return false;
    }
    // For safety you can add a 0 terminating character at the end of your file ...
    fileContent[fileLength] = '\0';
    result = std::string(fileContent);
    delete[] fileContent;
    AAsset_close(file);
    return true;
}


unsigned char *
AndroidUtil::loadImageFromAssets(android_app* app, char const * filename, int * x, int * y, int * channels_in_file,
                                 int desired_channels, bool flipOnLoad) {
    Util::util_stbi_set_flip_vertically_on_load(flipOnLoad);
    AAsset * file = AAssetManager_open(app->activity->assetManager, filename, AASSET_MODE_BUFFER);
    if(!file) {
        return nullptr;
    }
    size_t fileLength = AAsset_getLength(file);
    auto fileContent = new unsigned char[fileLength];
    unsigned char buffer[BUFFER_SIZE];

    int readResult, read = 0;
    while((readResult = AAsset_read(file, buffer, BUFFER_SIZE)) > 0){
        for(int i = 0; i < readResult; ++i) {
            fileContent[read + i] = buffer[i];
        }
        read += readResult;
    }
    if(readResult < 0) {
        AAsset_close(file);
        delete[] fileContent;
        return nullptr;
    }


    unsigned char * imageData = Util::util_stbi_load_from_memory(fileContent, fileLength, x, y,
                                                                 channels_in_file,
                                                                 desired_channels);
    if(!imageData) {
        AAsset_close(file);
        delete[] fileContent;
        return nullptr;
    }
    delete[] fileContent;
    AAsset_close(file);
    return imageData;
}