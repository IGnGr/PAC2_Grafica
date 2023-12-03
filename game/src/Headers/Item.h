#pragma once

#include "raylib.h"

enum ItemType { BONUS1 = 0, BONUS2 = 1, BONUS3 = 2, PEACH = 3};


class Item
{


private:
	Vector2 m_position;
	Texture2D m_sprite;
	ItemType m_itemType;
	bool m_enabled;

public:
	Item();
	Item(Vector2 position, Texture2D sprite, ItemType itemType);
	Rectangle GetHitbox(void);
	void Draw(void);
	ItemType GetType(void);
	void Disable(void);
	bool isEnabled(void);
};

