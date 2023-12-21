#include "AssetLibrary.hpp"
#include <string>

int const assetTotal = 4;
int const paramCount = 14;
std::string assets[assetTotal][paramCount] = {
    {"1", "./common/textures/nightskygen.ppm", 
        // name | parent
        "Person", "ROOT", 
        // position
        "246.0","35.0f","475.0f", 
        // scale
        "1","1","1", 
        // rotation
        "0", "0", "1", "0"},
    
    // night sky
    // asset type | texture    
    {"1", "./common/textures/nightskygen.ppm", 
        // name | parent
        "Sky", "Person", 
        // position
        "0","0","0", 
        // scale
        "512","512","512", 
        // rotation
        ".0001", "0", "1", "0"},

    // moon
    {"1", "./common/textures/moontexture1.ppm", "Moon", "ROOT", 
        "180", "120", "220", 
        "12","12","12", 
        "0.001", "0", "1", "0"},

    // terrain
    {"2", "./common/textures/pondheightmap.ppm",
        "./common/textures/pondcolormap.ppm", "./common/textures/detailmap.ppm",
        "-100", "-10", "0",
        "40", "200", "40",
        "0", "0", "1", "0"}

    };

AssetLibrary::AssetLibrary(){
    for(int i = 0; i < assetTotal; i++){
        AssetType type = AssetType(std::stoi(assets[i][0]));
        Asset* a = new Asset(type);
        
        switch(type){
        case 0:
            std::cout << "construct model"<< std::endl;
            break;
        case 1:
            a->loadSphereData(
                // filename
                assets[i][1], 
                // objectName
                assets[i][2], 
                // parent
                assets[i][3], 
                // position
                glm::vec3(std::stof(assets[i][4]), std::stof(assets[i][5]), std::stof(assets[i][6])), 
                // scale
                glm::vec3(std::stof(assets[i][7]), std::stof(assets[i][8]), std::stof(assets[i][9])), 
                // rotationIncrement
                std::stof(assets[i][10]), 
                // rotation axis
                glm::vec3(std::stof(assets[i][11]), std::stof(assets[i][12]), std::stof(assets[i][13])));
                m_assetList.push_back(a);
            break;
        case 2:
            a->loadQuadData(
                // texturefile
                assets[i][1],
                // color map
                assets[i][2],
                // detail map
                assets[i][3],
                // position
                glm::vec3(std::stof(assets[i][4]), std::stof(assets[i][5]), std::stof(assets[i][6])), 
                // scale
                glm::vec3(std::stof(assets[i][7]), std::stof(assets[i][8]), std::stof(assets[i][9])), 
                // rotationIncrement
                std::stof(assets[i][10]), 
                // rotation axis
                glm::vec3(std::stof(assets[i][11]), std::stof(assets[i][12]), std::stof(assets[i][13])));
            m_assetList.push_back(a);
            break;
        case 3:
            std::cout << "construct cube" << std::endl;
            break;
    }}
}

Asset* AssetLibrary::getAsset(int i){
    return m_assetList[i];
}



AssetLibrary::~AssetLibrary(){

}