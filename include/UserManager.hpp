#pragma once

#include <algorithm>
#include <vector>
#include <optional>
#include "User.hpp"

class UserManager {
    public:
        UserManager(const std::string& dbName);
        ~UserManager();

        // Fonctions pour ajouter une utilisateur
        bool addUser(const std::string& _id, const std::string &name, const std::string &email, const std::string& birthday, const std::string &password);
        bool addUser(const User& user);

        // FOnction pour rechercher un utilisateur
        bool findUser(const User& user) ;
        bool findUser(const std::string& id) ;
        
        // FOnction pour créer un utilisateur
        User createUser(const std::string& _id, const std::string &name, const std::string &email, const std::string& birthday, const std::string &password);
        User createUser(const std::string &name, const std::string &email, const std::string& birthday, const std::string &password);

        // Fonction pour effacer un user
        bool removeUser(const User& user);
        bool removeUser(const std::string& id);

        bool editUser(const std::string& id, const std::string& newName, const std::string& newEmail, const std::string& newBirthday) ;
        int  getNextId()const;
        bool loadUsers();
        void printHTML()const ;
        void displayUserTable();
        void saveUsers()const;

        inline std::string getDatabaseName() const { return database;}
        bool authenticateUser(const std::string& email, const std::string& password);
        std::vector<User> getUsers()const;
    private:
        std::vector<User> users; 
        std::string database;
};