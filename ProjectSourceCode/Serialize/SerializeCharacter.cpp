#include "SerializeCharacter.h"

bool serializecharacter::SaveCharacter(Character::Character* t_character, const std::string& t_path = "")
{
    if (t_character == nullptr) {
        return false;
    }
    //Copy data from t_character into a record
    CharacterRecord record;
    record.name = t_character->Name();
    record.id = t_character->ID();
    //copy ability scores
    for (int i{ 0 }; i < 6; i++) {
        record.ability_scores.at(i) = t_character->Ability_Score_Natural(i, 0);
    }
    //copy levels
    for (int i{ 0 }; i < 12; i++) {
        record.level.at(i) = t_character->Levels((Character::Character_Class)i);
    }
    record.max_hit_points = t_character->Max_Hit_Points();
    record.hit_points = t_character->Hit_Points();
    //copy inventory item IDs
    for (auto i : t_character->Inventory().GetAllItems()) {
        record.inventory_item_ids.push_back(i.GetItemId());
    }
    //copy equipped item IDs
    for (int i{ 0 }; i < 8; i++) {
        try {
            AbstractComponent* currentWornItems = t_character->GetWornItems();
            std::vector<AbstractComponent*> itemDecoratorList = currentWornItems->GetDecoratorList();

            for (int i = 0; i < (int)itemDecoratorList.size(); ++i)
            {
                Item* decoratorItem = dynamic_cast<Item*>(itemDecoratorList.at(i));
                auto item_id = decoratorItem->GetItemId();
                record.equipped_item_ids.push_back(item_id);
            }


            // const item::Item* item_ptr = t_character->Equipped_Items((Character::Equipment_Slots)i);
            // if (item_ptr != nullptr) {
            //     auto item_id = const_cast<item::Item*>(item_ptr)->GetItemId();
            //     record.equipped_item_ids.push_back(item_id);
            // }
        }
        catch (std::exception e) {

        }
    }
    //Save inventory
    std::string currentPath = std::filesystem::current_path().string();

    std::ostringstream fullURI;
    fullURI << currentPath << t_path << "\\InventoryItemsCharacter_" << std::to_string(record.id) << ".csv";
    std::vector<Item*> inventoryVector;

    /*for (auto i : t_character->Inventory().GetAllItems()) {
        item::Item* saved_item = &i;
        inventoryVector.push_back(saved_item);
    }*/
    for (int i{ 0 }; i < t_character->Inventory().GetAllItems().size(); i++) {
        inventoryVector.push_back(&t_character->Inventory().GetAllItems().at(i));
    }
    record.inventory_container_path = fullURI.str();

    if (t_character->Inventory().GetCapacity() > 0)
        serializeItem::SaveItems(fullURI.str(), inventoryVector);
    record.inventory_container_id = t_character->Inventory().GetItemId();

    record.isPlayerControlled = t_character->GetIsPlayerControlled();

    CharacterActionStrategy* actionStrategy = t_character->GetActionStrategy();
    if (record.isPlayerControlled) {
        record.actionStrategy = Character::HUMAN_PLAYER_STRATEGY_NAME;
    }
    else if (dynamic_cast<HumanPlayerStrategy*>(actionStrategy) == nullptr && dynamic_cast<AggressorStrategy*>(actionStrategy) == nullptr) {
        record.actionStrategy = Character::FRIENDLY_STRATEGY_NAME;
    }
    else {
        record.actionStrategy = Character::AGGRESSOR_STRATEGY_NAME;
    }

    //opening file

    std::string filename = t_path + "Character_" + std::to_string(record.id) + ".csv";
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error! Could not open " << filename << std::endl;
        return false;
    }

    outfile << "ID," << record.id << std::endl;
    outfile << "Name," << record.name << std::endl;
    outfile << "Ability_scores(Str_Dex_Con_Int_Wis_Cha),";
    for (int i{ 0 }; i < record.ability_scores.size(); i++) {
        outfile << record.ability_scores[i] << ",";
    }
    outfile << std::endl;
    outfile << "Levels(Barb_Bard_Cler_Drui_Figh_Monk_Pala_Rang_Rogu_Sorc_Warl_Wizr),";
    for (int i{ 0 }; i < record.level.size(); i++) {
        outfile << record.level[i] << ",";
    }
    outfile << std::endl;
    outfile << "Max_HP," << record.max_hit_points << std::endl;
    outfile << "Current_HP," << record.hit_points << std::endl;
    outfile << "Inventroy_Item_IDs,";
    for (int i{ 0 }; i < record.inventory_item_ids.size(); i++) {
        outfile << record.inventory_item_ids[i] << ",";
    }
    outfile << std::endl;
    outfile << "Equipped_Item_IDs,";
    for (int i{ 0 }; i < record.equipped_item_ids.size(); i++) {
        outfile << record.equipped_item_ids[i] << ",";
    }
    outfile << std::endl;
    outfile << "Inventory_Container_Path," << record.inventory_container_path;
    outfile << std::endl;
    outfile << "Inventory_Container_ID," << record.inventory_container_id;
    outfile << std::endl;

    outfile << "isPlayerControlled," << record.isPlayerControlled;
    outfile << std::endl;
    outfile << "actionStrategy," << record.actionStrategy;

    //Closing file
    outfile.close();

    return true;
}

serializecharacter::CharacterRecord serializecharacter::LoadCharacter(const std::string& filename)
{

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error! Could not open file " << filename << std::endl;
        return {};
    }

    serializecharacter::CharacterRecord record;
    std::string line;

    while (std::getline(file, line)) {

        std::stringstream spliter(line);
        std::string field_key;
        std::string data;
        //Extract the field name
        std::getline(spliter, field_key, ',');
        if (field_key == "ID") {
            while (std::getline(spliter, data, ',')) {
                record.id = std::stoi(data);
            }
        }
        else if (field_key == "Name") {
            while (std::getline(spliter, data, ',')) {
                record.name = data;
            }
        }
        else if (field_key == "Ability_scores(Str_Dex_Con_Int_Wis_Cha)") {
            int ability_index = 0;
            while (std::getline(spliter, data, ',')) {
                record.ability_scores[ability_index] = std::stoi(data);
                ability_index++;
            }
        }
        else if (field_key == "Levels(Barb_Bard_Cler_Drui_Figh_Monk_Pala_Rang_Rogu_Sorc_Warl_Wizr)") {
            int class_index = 0;
            while (std::getline(spliter, data, ',')) {
                record.level[class_index] = std::stoi(data);
                class_index++;
            }
        }
        else if (field_key == "Max_HP") {
            while (std::getline(spliter, data, ',')) {
                record.max_hit_points = std::stoi(data);
            }
        }
        else if (field_key == "Current_HP") {
            while (std::getline(spliter, data, ',')) {
                record.hit_points = std::stoi(data);
            }

        }
        else if (field_key == "Inventroy_Item_IDs") {
            int inventory_index = 0;
            while (std::getline(spliter, data, ',')) {
                record.inventory_item_ids.push_back(std::stoi(data));
                inventory_index++;
            }
        }
        else if (field_key == "Equipped_Item_IDs") {
            int equipped_index = 0;
            while (std::getline(spliter, data, ',')) {
                record.equipped_item_ids.push_back(std::stoi(data));
                equipped_index++;
            }
        }
        else if (field_key == "Inventory_Container_Path") {
            while (std::getline(spliter, data, ',')) {
                record.inventory_container_path = data;
            }
        }
        else if (field_key == "Inventory_Container_ID") {
            while (std::getline(spliter, data, ',')) {
                record.inventory_container_id = std::stoi(data);
            }
        }
        else if (field_key == "isPlayerControlled") {
            while (std::getline(spliter, data, ',')) {
                record.isPlayerControlled = data == "true" ? true : false;
            }
        }
        else if (field_key == "actionStrategy") {
            while (std::getline(spliter, data, ',')) {
                record.actionStrategy = data;
            }
        }
    }

    file.close();
    return record;
}

std::string serializecharacter::FindCharacterFile(int id, std::filesystem::path t_path)
{
    std::string filename, temp;
    std::filesystem::path currentDir;
    if (t_path.empty()) {
        currentDir = std::filesystem::current_path();
    }
    else {
        currentDir = t_path;
    }
    for (const auto& entry : std::filesystem::directory_iterator(currentDir)) {
        temp = entry.path().filename().string();
        if (temp.find(std::to_string(id)) != std::string::npos && temp.find("Character_") != std::string::npos && !(temp.find("InventoryItemsCharacter_") != std::string::npos)) {
            filename = currentDir.string() + "\\" + temp;
        }
    }
    return filename;
}