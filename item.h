#pragma once

namespace item {
	enum ItemType {
		Hemlet = 1,
		Armor,
		Shield,
		Ring,
		Belt,
		Boots,
		Weapon
	};

	enum CharacterStats {
		Strength = 1,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma,
		ArmorClass,
		AttackBonus,
		DamageBonus
	};

	class Item {
		public:
			Item();
			Item(const int&, const int&, const int&);
			int GetEnchantmentBonus();
			CharacterStats GetEnchantmentType();
		private:
			int enchantmentBonus;
			ItemType itemType;
			CharacterStats enchantmentType;
	};
}
