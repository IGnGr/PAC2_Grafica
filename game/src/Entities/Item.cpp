#include "Item.h"

Item::Item(Vector2 position, Texture2D sprite, ItemType itemType)
{
	m_position = position;
	m_itemType = itemType;
	m_sprite = sprite;
}

Rectangle Item::GetHitbox()
{
	return { m_position.x - m_sprite.width / 2 , m_position.y - m_sprite.height, (float) m_sprite.width ,  (float) m_sprite.height };
}

void Item::Draw(void)
{
	if(m_enabled)
		DrawTexture(m_sprite, m_position.x - m_sprite.width / 2, m_position.y - m_sprite.height, WHITE);
}

ItemType Item::GetType(void)
{
	return m_itemType;
}

void Item::Disable(void)
{
	m_enabled = false;
}

bool Item::isEnabled(void)
{
	return m_enabled;
}

