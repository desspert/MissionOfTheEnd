#pragma once
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"      
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include <unordered_map>
#define SE SoundManager::get()

//class SoundManager
//{
//private:
//	std::unordered_map<std::string, ci::audio::SamplePlayerNodeRef> sound;
//	ci::audio::GainNodeRef gain;
//	ci::audio::Context* ctx;
//public:
//	ci::audio::BufferPlayerNodeRef buffer_player;
//	ci::audio::FilePlayerNodeRef file_player;
//	SoundManager() {};
//	~SoundManager() {};
//
//	void set(std::string name, std::string path)
//	{
//		
//	}
//	void setBufferPlayer(std::string key_, std::string filepath_) {
//
//		if (sound.find(key_) == sound.end()) {
//			if (sound.find(key_) == sound.end()) {
//				ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));
//				buffer_player->loadBuffer(source);
//				sound[key_] = buffer_player;
//			}
//		}
//	}
//
//	void setfilePlayer(std::string key_, std::string filepath_) {
//
//		if (sound.find(key_) == sound.end()) {
//			if (sound.find(key_) == sound.end()) {
//				ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));
//				file_player->setSourceFile(source);
//				sound[key_] = file_player;
//			}
//		}
//	}
//
//	void setup() {
//
//
//
//		// サウンド機能を有効にする
//		ctx = ci::audio::master();
//		ctx->enable();
//		
//
//		
//		// 再生用のノードを生成
//		buffer_player = ctx->makeNode(new ci::audio::BufferPlayerNode());
//		file_player = ctx->makeNode(new ci::audio::FilePlayerNode());
//		// 音量調整用のノードを生成
//		gain = ctx->makeNode(new ci::audio::GainNode());
//
//		// 用意したノードを連結
//		buffer_player >> gain >> ctx->getOutput();
//		file_player >> gain >> ctx->getOutput();
//	
//	}
//
//	ci::audio::SamplePlayerNodeRef getSound(std::string name) {
//		return sound[name];
//	}
//
//	
//
//	static SoundManager& get() {
//		static SoundManager se;
//		return se;
//	}
//};


class Sound {
public:

	ci::audio::SamplePlayerNodeRef player_node;

	ci::audio::GainNodeRef gain;

	Sound(ci::audio::SamplePlayerNodeRef node_, ci::audio::Context* ctx_) {
		gain = ctx_->makeNode(new ci::audio::GainNode());

		player_node = node_;
		gain->setValue(1.0f);

		player_node >> gain >> ctx_->getOutput();
	}

	void add(ci::audio::SamplePlayerNodeRef node_) {
		player_node = node_;
	}


public:

	void start() {
		player_node->start();
	}
	void stop() {
		player_node->stop();
	}
	void disable() {
		player_node->disable();
	}
	bool isEnabled() {
		return player_node->isEnabled();
	}
	void setLoopEnabled(bool is_loop_) {
		player_node->setLoopEnabled(is_loop_);
	}

	void setGain(float value_) {
		gain->setValue(value_);
	}
};

class SoundManager {
public:

	static SoundManager& get()
	{
		static SoundManager soundmanager;
		return soundmanager;
	}

	SoundManager() {
		ctx = ci::audio::master();
		ctx->enable();
	}

	void setup() {
		

	}

	std::shared_ptr<Sound> find(const std::string& key_)
	{
		if (sound.find(key_) == sound.end())
			assert(!"Not sound name");
		return sound.find(key_)->second;
	}
	void registerFilePlayerNode(std::string key_, std::string filepath_) {
		
		if (sound.find(key_) == sound.end()) {
			ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

			ci::audio::FilePlayerNodeRef fileplayer = ctx->makeNode(new ci::audio::FilePlayerNode());
			fileplayer->setSourceFile(source);

			sound.insert(std::make_pair(key_, std::make_shared<Sound>(Sound(fileplayer, ctx))));
		}
	}

	void registerBufferPlayerNode(std::string key_, std::string filepath_) {
		if (sound.find(key_) == sound.end()) {
			ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset(filepath_));

			ci::audio::BufferPlayerNodeRef bufferplayer = ctx->makeNode(new ci::audio::BufferPlayerNode());
			bufferplayer->loadBuffer(source);

			sound.insert(std::make_pair(key_, std::make_shared<Sound>(Sound(bufferplayer, ctx))));
		}
	}

	void allStop() {
		for (auto& it : sound)
		{
			it.second->stop();
		}
	}
	void allCrear() {
		sound.clear();
	}

private:

	// 少しずつ読み込むやつがfileplayer
	// 一気に読み込むやつがbufferplayer

	std::map<std::string, std::shared_ptr<Sound>> sound;
	std::unordered_map<std::string, std::string> keys;
	ci::audio::Context* ctx;

};
