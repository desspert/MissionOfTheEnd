#pragma once
#include "cinder/gl/Texture.h"      
#include "cinder/imageIo.h"         
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <unordered_map>


#define TEX TextureManager::get()

class TextureManager
{
private:
	std::unordered_map<std::string, ci::gl::Texture> texture;
public:
	TextureManager() {};
	~TextureManager() {};
	void set(std::string name, std::string path)
	{
		if (texture.find(name) == texture.end()) {
			texture[name] = ci::loadImage(ci::app::loadAsset(path));
		}
	}

	ci::gl::Texture get(std::string name) {
		return texture[name];
	}

	static TextureManager& get() {
		static TextureManager tex;
		return tex;
	}
};