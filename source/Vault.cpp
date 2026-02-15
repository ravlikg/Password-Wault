#include "Vault.hpp"
#include "XorCipher.hpp"
#include <string>
#include <memory>
#include <algorithm>
#include <fstream>

std::vector<PasswordEntry>::const_iterator Vault::findEntryIter(const std::string &service) const{
    return std::find_if(entries.begin(), entries.end(),
    [&service](const PasswordEntry& e){
        return e.getService() == service;
    }); 
}

Vault::Vault(std::unique_ptr<ICipher> cipher)
{
    if (cipher == nullptr) 
        throw std::invalid_argument("Cipher can't be nullptr");

    this->cipher = std::move(cipher);
}

void Vault::listAll() const{
    for(const auto& entry : entries){
        entry.display();
    }
}

void Vault::addEntry(
    const std::string& source,
    const std::string& login,
    const std::string& password,
    const std::string& master_key
) {
    auto entry = findEntryIter(source);
    if(entry != entries.end()){
        entries.erase(entry);
    }
    entries.emplace_back(source, login, password, master_key, *this->cipher);
}

void Vault::deleteEntry(const std::string &source){
    auto entry = findEntryIter(source);
    if(entry != entries.end()){
        entries.erase(entry);
    }
}

const PasswordEntry* Vault::findEntry(const std::string& service) const {
    auto it = findEntryIter(service);

    if(it != entries.end()){
        return &(*it);
    }

    return nullptr;
}

void Vault::saveToFile(const std::string& filename) const{
    std::ofstream file(filename);
    if (!file.is_open()) 
        throw std::runtime_error("Could not open file for writing");

    //mini costil must be changed when new cipher be added
    auto xor_ptr = dynamic_cast<XorCipher*>(cipher.get());

    for(const auto& entry : entries){
        std::string safe_pass = xor_ptr ? 
            xor_ptr->toHex(entry.getEncryptedPassword()) : 
            entry.getEncryptedPassword();

        file << entry.getService() << "|" 
             << entry.getLogin() << "|" 
             << safe_pass << "\n"; 
    }

    file.close();
}

void Vault::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) 
        return; // If the file doesn't exist, we simply return without throwing an error
    
    std::string line;
    auto xor_ptr = dynamic_cast<XorCipher*>(cipher.get());
    while (std::getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if(pos1 == std::string::npos || pos2 == std::string::npos) 
            continue; // Skip malformed lines

        std::string service = line.substr(0, pos1);
        std::string login = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string encrypted_password = xor_ptr->fromHex(line.substr(pos2 + 1));
        entries.emplace_back(service, login, encrypted_password);
    }
}

