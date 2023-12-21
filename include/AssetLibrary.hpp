#ifndef ASSETLIBRARY_HPP
#define ASSETLIBRARY_HPP

#include <vector>
#include <string>
#include <Asset.hpp>
#include <glad/glad.h>


class AssetLibrary{
    public:
        AssetLibrary();
        ~AssetLibrary();
        Asset* getAsset(int i);
        int assetCount(){ return m_assetList.size();};

    private:
        std::vector<Asset*> m_assetList;



};

#endif