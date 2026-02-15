#pragma once

#include <string>
#include "ICipher.hpp"

class PasswordEntry{
private:
	std::string service_name;
	std::string login;
	std::string password;

public:
    PasswordEntry(
        const std::string& service_name, 
        const std::string& login, 
        const std::string& password, 
        const std::string& master_key, 
        const ICipher& cipher
    );

    PasswordEntry(
        const std::string& service_name, 
        const std::string& login, 
        const std::string& encrypted_password
    );

	void display() const;

	std::string getDecryptedPassword(
        const ICipher& cipher, 
        const std::string& master_key
        ) const;

    std::string getService() const {return service_name;}
    std::string getLogin() const {return login;}
    std::string getEncryptedPassword() const {return password;}
};
