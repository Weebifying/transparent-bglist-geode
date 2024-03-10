#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

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

class $modify(CCDirector) {
	void willSwitchToScene(CCScene* scene) {
		CCDirector::willSwitchToScene(scene);

		if (getChildOfType<CCLayer>(scene, 0)) {
			if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(getChildOfType<CCLayer>(scene, 0));
		}
	}
};

class $modify(LevelSelectLayer) {
	void scrollLayerMoved(CCPoint p0) {
		LevelSelectLayer::scrollLayerMoved(p0);

		if (Mod::get()->getSettingValue<bool>("bg")) uncolorBG(this);
	}
};