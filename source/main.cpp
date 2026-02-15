#include <iostream>
#include <memory>
#include "Vault.hpp"
#include "XorCipher.hpp"

void showMenu() {
    std::cout << "\n--- VAULT TERMINAL ---" << std::endl;
    std::cout << "1. Add/Update password" << std::endl;
    std::cout << "2. Search & Decrypt" << std::endl;
    std::cout << "3. Delete entry" << std::endl;
    std::cout << "4. List all services" << std::endl;
    std::cout << "5. Save & Exit" << std::endl;
    std::cout << "Choice: ";
}

int main() {
    auto cipher = std::make_unique<XorCipher>();
    Vault vault(std::move(cipher));
    
    const std::string db_name = "data.db";
    vault.loadFromFile(db_name);

    int choice;
    while (true) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 5) {
            vault.saveToFile(db_name);
            std::cout << "Changes saved to " << db_name << ". Goodbye!" << std::endl;
            break;
        }

        switch (choice) {
            case 1: {
                std::string s, l, p, m;
                std::cout << "Service: "; std::cin >> s;
                std::cout << "Login: ";   std::cin >> l;
                std::cout << "Password: "; std::cin >> p;
                std::cout << "Master Key: "; std::cin >> m;
                vault.addEntry(s, l, p, m);
                break;
            }
            case 2: {
                std::string s, m;
                std::cout << "Service name: "; std::cin >> s;
                const auto* entry = vault.findEntry(s);
                if (entry) {
                    entry->display();
                    std::cout << "Enter Master Key: "; std::cin >> m;
                    XorCipher temp_cipher;
                    std::cout << ">> Password: " << entry->getDecryptedPassword(temp_cipher, m) << std::endl;
                } else {
                    std::cout << "Not found." << std::endl;
                }
                break;
            }
            case 3: {
                std::string s;
                std::cout << "Service to delete: "; std::cin >> s;
                vault.deleteEntry(s);
                std::cout << "Done." << std::endl;
                break;
            }
            case 4: {
                vault.listAll();
                break;
            }
            default: {
                std::cout << "Invalid choice." << std::endl;
                break;
            }
        }
    }
    return 0;
}