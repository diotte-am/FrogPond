#include "Asset.hpp"


Asset::Asset(int a){ 
    m_assetType = AssetType(a);
}

void Asset::loadSphereData(std::string fileName, 
    std::string name, std::string parent, 
    glm::vec3 position, glm::vec3 scale, 
    float rotationIncrement, glm::vec3 rotAxis){
        m_fileName = fileName;
        m_name = name;
        m_parent = parent;
        m_position = position;
        m_scale = scale;
        m_rotAxis = rotAxis;
        m_rotInc = rotationIncrement;
}

void Asset::loadQuadData(std::string fileName, 
    std::string colorMap, std::string detailMap, 
    glm::vec3 position, glm::vec3 scale, 
    float rotationIncrement, glm::vec3 rotAxis){
        m_fileName = fileName;
        m_colorMap = colorMap;
        m_detailMap = detailMap;
        m_position = position;
        m_scale = scale;
        m_rotAxis = rotAxis;
        m_rotInc = rotationIncrement;
}



AssetType Asset::getAssetType(){
    return m_assetType;
}

std::string Asset::getName(){
    return m_name;
}

std::string Asset::getTextureFile(){
    return m_fileName;
}

Asset::~Asset(){

}