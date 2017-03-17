#include "Select.h"
using select_coroutine = boost::coroutines::coroutine<Select*>;
struct Select::_coroutine
{
	std::vector<CoroutineInfo>& c_info;
	select_coroutine::push_type startCoroutine;
	Select& parent;


	_coroutine(Select& parent) :
		startCoroutine(selectCoroutine), parent(parent), c_info(parent.c_info) {
		parent.time = 0;
	}
	void update(const float& delta_time)
	{
		parent.time -= delta_time;
		if (parent.time < 0)
		{
			startCoroutine(&parent);
			parent.time = parent.time;
		}

	}
	static void selectCoroutine(select_coroutine::pull_type & yield) {
		while (true)
		{
			//開始時
			while (yield().get()->is_start)
			{
				for (int i = 0; i < yield().get()->c_info.size(); i++)
				{
					yield().get()->time = yield().get()->c_info[i].time;
					yield().get()->c_info[i].callback();
					yield();
				}
				yield().get()->is_start = false;
				break;
			}
			//通常時
			while (true)
			{
				yield();
				if (yield().get()->ui.isGasya()) {
					yield().get()->c_info.clear();
					yield().get()->_m->gasyaMove();
					break;
				}
				if (yield().get()->ui.isEnd()) {
					yield().get()->c_info.clear();
					yield().get()->_m->end();
					break;
				}

			}
			//ガシャ中
			while (yield().get()->ui.isGasya())
			{
				for (int i = 0; i < yield().get()->c_info.size(); i++)
				{
					yield().get()->time = yield().get()->c_info[i].time;
					yield().get()->c_info[i].callback();
				}
				yield().get()->c_info.clear();
				if (yield().get()->gasya_production) {
					yield().get()->_m->gasyaProduction();
					yield().get()->ui.isGasya() = false;
					break;
				}
			}
			//ガシャ演出
			while (yield().get()->gasya_production)
			{
				for (int i = 0; i < yield().get()->c_info.size(); i++)
				{
					yield().get()->time = yield().get()->c_info[i].time;
					yield().get()->c_info[i].callback();
				}
				yield().get()->c_info.clear();

				break;
			}

			//ゲーム終了時
			while (yield().get()->ui.isEnd())
			{
				for (int i = 0; i < yield().get()->c_info.size(); i++)
				{
					yield().get()->time = yield().get()->c_info[i].time;
					yield().get()->c_info[i].callback();
				}
				break;
			}
		}
	}
	void setup()
	{
		start();
	}
	void start()
	{
		c_info.push_back(CoroutineInfo(1, [&]() {
			SE.find("SelectBGM")->start();
			SE.find("SelectBGM")->setLoopEnabled(true);
			c_Easing::apply(CAMERA.fade_out.a, 0, EasingFunction::Linear, 90);
			return;
		}));

	}
	void gasyaMove() {
		c_info.push_back(CoroutineInfo(0, [this]() {
			c_Easing::apply(CAMERA.fade_out.a, 1, EasingFunction::Linear, 30);
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<float> rand(0, 100);
			parent.releaseChara = rand(mt);
			PLAYERDATA.useCoin(5);
			return;
		}));
		c_info.push_back(CoroutineInfo(1, [&]() {
			parent.camera_pos.x = 1000;
			SE.registerBufferPlayerNode("GasyaSE1", "SE/gasya_se1.mp3");
			SE.registerBufferPlayerNode("GasyaSE2", "SE/gasya_se2.mp3");
			SE.registerBufferPlayerNode("GasyaSE3", "SE/shine4.mp3");
			SE.registerBufferPlayerNode("GasyaNormal", "SE/normal.mp3");
			SE.registerBufferPlayerNode("GasyaRare", "SE/rare.wav");
			SE.registerBufferPlayerNode("RareJingle", "SE/jingle1.mp3");
			selectCharacter();
			return;
		}));

		c_info.push_back(CoroutineInfo(1, [&]() {
			c_Easing::apply(CAMERA.fade_out.a, 0, EasingFunction::Linear, 60);
			return;
		}));
		c_info.push_back(CoroutineInfo(1, [&]() {
			ci::app::console() << static_cast<int>(parent.releaseChara) << std::endl;
			if (static_cast<int>(parent.releaseChara) < 30) {
				parent.ui.ui_data["GasyaBall"]->setColor(0.3f,0.3f,1,1);
				parent.ui.ui_data["GasyaBall"]->setActive(true);
				ANIMATION.animationAdd<GasyaSpawn>(ci::vec2(1300, 500), 1000);
				SE.find("GasyaRare")->start();
			}
			else {
				parent.ui.ui_data["GasyaBall"]->setColor(1,1, 1, 1);
				parent.ui.ui_data["GasyaBall"]->setActive(true);
				ANIMATION.animationAdd<GasyaSpawn>(ci::vec2(1300, 500), 1000);
				SE.find("GasyaNormal")->start();
			}
			
			return;
		}));

	}
	void gasyaProduction() {

		c_info.push_back(CoroutineInfo(0, [&]() {
			parent.ui.ui_data["GasyaBall"]->setActive(false);
			SE.find("GasyaSE1")->start();
			return;
		}));
		c_info.push_back(CoroutineInfo(0.3f, [&]() {
			SE.find("GasyaSE2")->start();
			return;
		}));

		c_info.push_back(CoroutineInfo(0.5f, [&]() {
			ANIMATION.animationAdd<Gasya>(ci::vec2(680, 0), ci::vec2(1280, 960));
			SE.find("GasyaSE3")->start();
			return;
		}));

		c_info.push_back(CoroutineInfo(0.5f, [&]() {
			CAMERA.fade_out = ci::vec4(1, 1, 1, 0);
			c_Easing::apply(CAMERA.fade_out.a, 1, EasingFunction::Linear, 30);
			return;
		}));
		c_info.push_back(CoroutineInfo(1.5f, [&]() {
			c_Easing::apply(CAMERA.fade_out.a, 0, EasingFunction::Linear, 70);
			SE.find("RareJingle")->start();
			ANIMATION.animationAdd<GasyaEnd>(ci::vec2(1300, 500), 1000);
			return;
		}));

		if (static_cast<int>(parent.releaseChara) >= 30) {
			c_info.push_back(CoroutineInfo(1, [&]() {
				parent.ui.ui_data["Star1"]->setActive(true);
				return;
			}));

			c_info.push_back(CoroutineInfo(0, [&]() {
				parent.ui.ui_data["GasyaChara"]->setActive(true);
				ANIMATION.animationAdd<GasyaEnd>(ci::vec2(1300, 500), 1000);
				return;
			}));
		}
		if (static_cast<int>(parent.releaseChara) < 30 &&
			static_cast<int>(parent.releaseChara) > 3) {
			c_info.push_back(CoroutineInfo(1, [&]() {
				parent.ui.ui_data["Star2"]->setActive(true);
				return;
			}));
			c_info.push_back(CoroutineInfo(0, [&]() {
				parent.ui.ui_data["GasyaChara"]->setActive(true);
				ANIMATION.animationAdd<GasyaEnd>(ci::vec2(1300, 500), 1000);
				return;
			}));
			c_info.push_back(CoroutineInfo(1, [&]() {
				parent.ui.ui_data["Star3"]->setActive(true);
				return;
			}));
		}
		if (static_cast<int>(parent.releaseChara) <= 3) {
			c_info.push_back(CoroutineInfo(1, [&]() {
				parent.ui.ui_data["Star1"]->setActive(true);
				return;
			}));

			c_info.push_back(CoroutineInfo(0, [&]() {
				parent.ui.ui_data["GasyaChara"]->setActive(true);
				ANIMATION.animationAdd<GasyaEnd>(ci::vec2(1300, 500), 1000);
				return;
			}));
			c_info.push_back(CoroutineInfo(1, [&]() {
				parent.ui.ui_data["Star2"]->setActive(true);
				return;
			}));
			c_info.push_back(CoroutineInfo(0, [&]() {
				parent.ui.ui_data["GasyaChara"]->setActive(true);
				ANIMATION.animationAdd<GasyaEnd>(ci::vec2(1300, 500), 1000);
				return;
			}));
			c_info.push_back(CoroutineInfo(1, [&]() {
				parent.ui.ui_data["Star3"]->setActive(true);
				return;
			}));
		}

		
		for (int i = 0; i < 2; i++) {
			c_info.push_back(CoroutineInfo(2, [&]() {
				ANIMATION.animationAdd<GasyaEnd>(ci::vec2(1300, 500), 1000);
				return;
			}));
		}
		
		c_info.push_back(CoroutineInfo(1, [this]() {
			CAMERA.fade_out = ci::vec4(0, 0, 0, 0);
			c_Easing::apply(CAMERA.fade_out.a, 1, EasingFunction::Linear, 30);
			parent.ui.ui_data["GasyaChara"]->setActive(false);
			parent.ui.ui_data["Star3"]->setActive(false);
			parent.ui.ui_data["Star2"]->setActive(false);
			parent.ui.ui_data["Star1"]->setActive(false);
			parent.ui.ui_data["GasyaBall"]->setActive(false);
			parent.gasya_production = false;
			return;
		}));

		c_info.push_back(CoroutineInfo(1, [this]() {
			parent.camera_pos.x = 0;
			return;
		}));

		c_info.push_back(CoroutineInfo(1, [this]() {
			c_Easing::apply(CAMERA.fade_out.a, 0, EasingFunction::Linear, 90);
			return;
		}));
		c_info.push_back(CoroutineInfo(1, [this]() {
			parent.pause = false;
			return;
		}));
	}
	void end()
	{
		c_info.push_back(CoroutineInfo(0, [&]() {
			c_Easing::apply(CAMERA.fade_out.a, 1, EasingFunction::Linear, 60);
			return;
		}));
		c_info.push_back(CoroutineInfo(1, [this]() {
			shift();
			return;
		}));

	}
	void selectCharacter() {
		Json::Value root_type;
		Json::Reader reader;
		if (reader.parse(loadString("SaveData/CharactersData.json"), root_type)) {
			int size = 0;
			int selected_chara = 0;
			if (static_cast<int>(parent.releaseChara) >= 30) {
				size = root_type["Star1"].size();
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_real_distribution<float> rand(0, size);
				selected_chara = rand(mt);

				auto it = root_type["Star1"].begin();
				for (int i = 0; i < selected_chara; i++) {
					it++;
				}
				saveChara(it);
				auto img_gasya = ci::loadImage(ci::app::loadAsset((*it)["TexturePath"].asString()));
				parent.ui.textures["GasyaChara"] = ci::gl::Texture2d::create(img_gasya);

				//PLAYERDATA.characters[(*it)["Name"].asString()].rare = (*it)["Rare"].asInt();

			}
			if (static_cast<int>(parent.releaseChara) < 30 &&
				static_cast<int>(parent.releaseChara) > 3) {
				size = root_type["Star2"].size();
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_real_distribution<float> rand(0, size);
				selected_chara = rand(mt);

				auto it = root_type["Star2"].begin();
				for (int i = 0; i < selected_chara; i++) {
					it++;
				}
				saveChara(it);
				auto img_gasya = ci::loadImage(ci::app::loadAsset((*it)["TexturePath"].asString()));
				parent.ui.textures["GasyaChara"] = ci::gl::Texture2d::create(img_gasya);
			}
			if (static_cast<int>(parent.releaseChara) <= 3) {
				size = root_type["Star3"].size();
				std::random_device rd;
				std::mt19937 mt(rd());
				std::uniform_real_distribution<float> rand(0, size);
				selected_chara = rand(mt);

				auto it = root_type["Star3"].begin();
				for (int i = 0; i < selected_chara; i++) {
					it++;
				}
				saveChara(it);
				auto img_gasya = ci::loadImage(ci::app::loadAsset((*it)["TexturePath"].asString()));
				parent.ui.textures["GasyaChara"] = ci::gl::Texture2d::create(img_gasya);
			}
		}
	}

	void saveChara(Json::ValueIterator& chara) {
		PLAYERDATA.root_type["Characters"][std::to_string(PLAYERDATA.root_type["Characters"].size()+1)] = (*chara);
		PLAYERDATA.Save();
	}

	void shift() {
		SE.allStop();
		SE.allCrear();
		SCENE.shift(SceneName::GAMEMAIN);
	}

};

