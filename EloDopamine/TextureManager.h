#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>
#include <d3d11.h>


class TextureManager {
private:
	std::unordered_map<std::string, ID3D11ShaderResourceView*> textures;
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

public:
	bool LoadTexture(std::string name, const char* filename);
	ID3D11ShaderResourceView* GetTexture(std::string  name);

};
inline extern std::unique_ptr<TextureManager> textureManager = std::make_unique<TextureManager>();
