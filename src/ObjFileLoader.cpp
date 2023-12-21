#include "ObjFileLoader.hpp"

ObjFileLoader::ObjFileLoader(const char * path){

    // load text from .obj file
    std::ifstream file(path);

    while(file.is_open()){
        std::string line;
        while( getline(file,line)){
            std::vector<float> newCoords;
            // v, vn, or vt
            if(line[0] == 'v'){
                // normals
                if(line[1] == 'n'){
                    newCoords = parseCoords(line.substr(3, line.npos));
                    m_normals.push_back(glm::vec3(newCoords[0], newCoords[1], newCoords[2]));
                 //   std::cout << newCoords[0] << " " << newCoords[1] << " " << newCoords[2] << std::endl;
                // textures
                }else if(line[1] == 't'){
                    newCoords = parseCoords(line.substr(3, line.npos));
                    m_uvs.push_back(glm::vec2(newCoords[0], newCoords[1]));
                // vertices
                }else{
                    newCoords = parseCoords(line.substr(2, line.npos));
                    m_vertices.push_back(glm::vec3(newCoords[0], newCoords[1], newCoords[2]));
                }
            // indices
            }else if(line[0] == 'f'){
                std::stringstream strStream(line.substr(2, line.npos));
                std::string str, vi, ni, ti;
                uint pos, pos1, pos2, start = 0;
                // process three triangles
                while(strStream >> str){
                    // find location of each slash
                    pos1 = str.find("/");
                    pos2 = str.find("/", pos1 + 1);
                    // get length of texture index
                    std::size_t length = pos2 - (pos1 + 1);

                    // extract indices
                    vi = str.substr(start, pos1);
                    ti = str.substr(pos1 + 1, length);
                    ni = str.substr(pos2 + 1);

                     // convert to int
                    int newVertex(atoi(vi.c_str()));
                    int newNormal(atoi(ni.c_str()));
                    int newTexture(atoi(ti.c_str()));
                    if(newVertex <= 0 || newNormal <= 0){
                        std::cout << "Model.cpp: Sorry, parser is unable to read this format!\n";
                        exit(1);
                    }else{
                        vertexIndices.push_back(newVertex - 1);
                        normalIndices.push_back(newNormal - 1);
                        uvIndices.push_back(newTexture - 1);
                    }
            }
            // load materials file
            }else if(line.substr(0, 6).compare("mtllib") == 0){
                mtlFile = line.substr(7);
            }
        }
        file.close();
    }
}

ObjFileLoader::~ObjFileLoader(){}


inline std::vector<float> ObjFileLoader::parseCoords(std::string line){
    std::string pos;
    std::stringstream strStream(line);
    std::vector<float> newPos;
 
    while (getline(strStream, pos, ' ')){
        newPos.push_back(std::stof(pos));
    }
        return newPos;

}