#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

// =====================
// Base Item class
// =====================
class Item {
protected:
    std::string name;
    std::string description;
    double cost;

public:
    Item(const std::string& itemName,
         const std::string& itemDescription,
         double itemCost)
        : name(itemName), description(itemDescription), cost(itemCost) {}

    virtual ~Item() = default;

    virtual void displayItem() const {
        std::cout << "Item Name: " << name << "\n"
                  << "Description: " << description << "\n"
                  << "Cost: " << cost << " Gold\n";
    }

    const std::string& getName() const { return name; }
    double getCost() const { return cost; }
};

// =====================
// Weapon
// =====================
class Weapon : public Item {
    double attackPower;

public:
    Weapon(const std::string& itemName,
           const std::string& itemDescription,
           double itemCost,
           double itemAttackPower)
        : Item(itemName, itemDescription, itemCost),
          attackPower(itemAttackPower) {}

    void displayItem() const override {
        Item::displayItem();
        std::cout << "Attack Power: " << attackPower << "\n";
    }
};

// =====================
// Consumable
// =====================
class Consumable : public Item {
    std::string effect;

public:
    Consumable(const std::string& itemName,
               const std::string& itemDescription,
               double itemCost,
               const std::string& itemEffect)
        : Item(itemName, itemDescription, itemCost),
          effect(itemEffect) {}

    void displayItem() const override {
        Item::displayItem();
        std::cout << "Effect: " << effect << "\n";
    }
};

// =====================
// Equipment
// =====================
class Equipment : public Item {
    std::string equipmentType;

public:
    Equipment(const std::string& itemName,
              const std::string& itemDescription,
              double itemCost,
              const std::string& type)
        : Item(itemName, itemDescription, itemCost),
          equipmentType(type) {}

    void displayItem() const override {
        Item::displayItem();
        std::cout << "Equipment Type: " << equipmentType << "\n";
    }
};

// =====================
// Utility Functions
// =====================
void displayShop(const std::vector<std::unique_ptr<Item>>& shopItems) {
    std::cout << "\nWelcome to the Item Shop\n";
    std::cout << "========================\n";
    for (const auto& item : shopItems) {
        item->displayItem();
        std::cout << "------------------------\n";
    }
}

void displayInventory() {
    std::ifstream file("inventory.txt");
    std::string line;

    std::cout << "\nYour Inventory:\n";
    if (!file.is_open()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    while (std::getline(file, line)) {
        std::cout << "- " << line << "\n";
    }
}

// =====================
// Main
// =====================
int main() {
    int gold = 100;
    int menuChoice = 0;

    std::fstream inventoryFile("inventory.txt", std::ios::app);

    std::cout << "Enter starting gold (default 100): ";
    std::cin >> gold;

    std::vector<std::unique_ptr<Item>> shopItems;

    shopItems.push_back(std::make_unique<Consumable>(
        "HealingPotion", "Restores 50 health points", 15.0, "Restore Health"));

    shopItems.push_back(std::make_unique<Weapon>(
        "SteelSword", "A sharp sword for attacking", 25.0, 50.0));

    shopItems.push_back(std::make_unique<Equipment>(
        "SteelHelmet", "Standard protective helmet", 40.0, "Armor"));

    shopItems.push_back(std::make_unique<Consumable>(
        "Apple", "Restores 25 health points", 10.0, "Restore Health"));

    displayShop(shopItems);

    bool shopping = true;

    while (shopping) {
        std::cout << "\n1) Buy Item\n"
                  << "2) View Inventory\n"
                  << "3) Exit Shop\n"
                  << "Choice: ";
        std::cin >> menuChoice;

        if (menuChoice == 1) {
            std::string choice;
            std::cout << "Enter item name: ";
            std::cin >> choice;

            bool found = false;
            for (const auto& item : shopItems) {
                if (item->getName() == choice) {
                    found = true;
                    if (gold >= item->getCost()) {
                        gold -= static_cast<int>(item->getCost());
                        inventoryFile << item->getName() << "\n";
                        std::cout << "Purchased! Gold remaining: " << gold << "\n";
                    } else {
                        std::cout << "Not enough gold.\n";
                    }
                    break;
                }
            }

            if (!found) {
                std::cout << "Item not found.\n";
            }
        }
        else if (menuChoice == 2) {
            displayInventory();
            std::cout << "Gold: " << gold << "\n";
        }
        else if (menuChoice == 3) {
            std::cout << "Thanks for visiting!\n";
            shopping = false;
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}
