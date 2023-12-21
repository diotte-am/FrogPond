#ifndef ASSET_HPP
#define ASSET_HPP

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <string>
#include <iostream>


enum AssetType { MODEL, SPHERE, TEXTURED_QUAD, CUBE};

// this class is the factory that outputs types of objects
// types of objects:
class Asset{
    public:
        Asset(int a);
        ~Asset();
        AssetType getAssetType();
        std::string getTextureFile();

        std::string getName();
        std::string getParent() { return m_parent; };
        glm::vec3 getPosition() { return m_position; };
        glm::vec3 getScale() { return m_scale; };
        glm::vec3 getRotationAxis() { return m_rotAxis; };
        float getRotationIncrement() { return m_rotInc; };
        std::string getColorMap() { return m_colorMap; };
        std::string getDetailMap() { return m_detailMap; };

        void loadSphereData(std::string fileName, std::string name, 
        std::string parent, glm::vec3 position, 
        glm::vec3 scale, float rotationIncrement, glm::vec3 rotAxis);

        void loadQuadData(std::string fileName, std::string colorMap, 
        std::string detailMap, glm::vec3 position, 
        glm::vec3 scale, float rotationIncrement, glm::vec3 rotAxis);

        

    private:
        // common member variables
        glm::vec3 m_position, m_scale, m_rotAxis;
        float m_rotInc;
        AssetType m_assetType;
        std::string m_fileName;

        // sphere member variables
        std::string m_name;
        std::string m_parent;

        // quad member variables
        std::string m_colorMap;
        std::string m_detailMap;

        
    
};

#endif