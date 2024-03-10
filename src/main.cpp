#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;

void uncolorBG(CCLayer* layer) {
	int i = 0;
	bool done = false;
	while (i < layer->getChildrenCount()) {
		auto node = getChildOfType<CCSprite>(layer, i);

		if (auto textureProtocol = typeinfo_cast<CCTextureProtocol*>(node)) {
			if (auto texture = textureProtocol->getTexture()) {
				auto* cachedTextures = CCTextureCache::sharedTextureCache()->m_pTextures;
				for (auto [key, obj] : CCDictionaryExt<std::string, CCTexture2D*>(cachedTextures)) {
					if (obj == texture) {
						if (key.ends_with("GJ_gradientBG.png") || key.ends_with("GJ_gradientBG-hd.png"))
							node->setColor({255, 255, 255});
							done = true;

						break;
					}
				}
				if (done) break;
			}
		}

		i++;
	}
}

class $modify(CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};

class $modify(LevelBrowserLayer) {
	bool init(GJSearchObject* p0) {
		if (!LevelBrowserLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};

class $modify(LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};

class $modify(LevelListLayer) {
	bool init(GJLevelList* p0) {
		if (!LevelListLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};

class $modify(LeaderboardsLayer) {
	bool init(LeaderboardState p0) {
		if (!LeaderboardsLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};

class $modify(EditLevelLayer) {
	bool init(GJGameLevel* p0) {
		if (!EditLevelLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);

		return true;
	}
};