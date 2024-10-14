#pragma once

#include <string>

class User
{
    public:
        User(const std::string& _id, const std::string &name, const std::string &email, const std::string& birthday, const std::string &password);
        
        // Les mutateurs 
        void setName(const std::string &name);
        void setEmail(const std::string &email);
        void setPassword(const std::string &password);
        void setBirthday(const std::string& birthday);
        void setId(const std::string& _id);
        
        // Les accesseurs
        std::string getEmail() const;
        std::string getName() const;
        std::string getPassword() const;
        std::string getBirthday() const;
        std::string getId() const;
        
        // L'operateur d'égalité
        bool operator== (const User& user)const;
        void printHTML()const;

    private:
        std::string id;
        std::string name;
        std::string email;
        std::string birthday;
        std::string password;
};