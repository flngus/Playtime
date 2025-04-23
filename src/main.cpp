#include "layer/PlaytimeLayer.h"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/StatsLayer.hpp>

class $modify(StatsLayerExt, StatsLayer) {
	virtual void customSetup() {
		StatsLayer::customSetup();

		auto playtime = CCMenuItemExt::createSpriteExtraWithFrameName(
			"GJ_timeIcon_001.png", 1.25f, [](CCMenuItem*) {
				PlaytimeLayer::create()->show();
			}
		);
		playtime->setID("playtime-button"_spr);

		if (auto menu = this->m_buttonMenu) { //paranoic test
			auto back = menu->getChildByType(0);
			if (!back) return;
			//add btn
			menu->addChild(playtime);
			//set layout if there is no one already
			if (not menu->getLayout()) {
				//fix point up to aaa... back btn?
				menu->setPositionY(menu->getPositionY() + (back->getContentHeight() / 2));
				menu->setAnchorPoint(CCPointMake(0.5f, 1.f));
				menu->setLayout(
					ColumnLayout::create()
					->setAxisAlignment(AxisAlignment::End)
					->setAxisReverse(true)
				);
			}
			else menu->updateLayout();

		}
	}
};