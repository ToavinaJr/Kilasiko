#include "../include/User.hpp"
#include "../include/UserManager.hpp"
#include "../include/Handler.hpp"

#include <fstream>
#include <memory>

/*************************** */

UserManager::UserManager(const std::string& dbName)  : database(dbName)
{
    loadUsers();
}

UserManager::~UserManager() {
    saveUsers();
}
/*************************** */

User UserManager::createUser(const std::string &name, const std::string &email, const std::string &birthday, const std::string &password) {
    auto handler = std::make_unique<Handler>();
    auto id = handler->generateId();
    auto user = User(id, name, email, birthday, password);
    
    return user;
}

/*************************** */

bool UserManager::loadUsers() {
    std::ifstream dbFile(database);

    if (dbFile.is_open()) {
        auto handler = std::make_unique<Handler>();
        std::string line;

        // Tant qu'il y a encore une line        
        while(std::getline(dbFile, line)) {
            // ter la ligne pour avoir toutes les données
            auto userData = handler->split(line, '|');

            // Les données dans la line extraite
            auto id = userData.at(0);
            auto name = userData.at(1);
            auto email = userData.at(2);
            auto birthday = userData.at(3);
            auto password = userData.at(4);
            
            auto user = User(id, name, email, birthday, password);
            if (!findUser(id)){
                users.emplace_back(id, name, email, birthday, password);
            }
        }

        dbFile.close();
        return true;
    }
    else {
        return false;
    }
}

/*************************** */

std::vector<User> UserManager::getUsers()const {
    return users;
}

/*************************** */

User UserManager::createUser(const std::string& id, const std::string &name, const std::string &email, const std::string& birthday, const std::string &password) {
    auto user = User(id, name, email, birthday, password);
    return user;
}

/*************************** */

bool UserManager::addUser(const std::string& id, const std::string &name, const std::string &email, const std::string& birthday, const std::string &password) {
    User user(id, name, email, birthday, password);
    // Tester si au moins un user a le meme id
    auto found = std::find(std::begin(users), std::end(users), user);
    
    if (found == users.end()) {
        users.emplace_back(id, name, email, birthday, password);
        return true;
    }

    return true;
}

/*************************** */

bool UserManager::addUser(const User& user) {
    users.push_back(user);

    // Tester si au moins un user a le meme id
    auto found = std::find(std::begin(users), std::end(users), user);
    
    if (found == users.end()) {
        users.emplace_back(user);

        return true;
    }

    return false;
}

/*************************** */

bool UserManager::findUser(const User& user) {
    // Tester si au moins un user a le meme id
    auto found = std::find(std::begin(users), std::end(users), user);

    return (found != users.end());
}

/*************************** */

bool UserManager::findUser(const std::string& id) {
    // Tester si au moins un user a le meme id
    auto found = std::find_if(std::begin(users), std::end(users), [id](const User& user) { return user.getId() == id;});

    return (found != users.end());
}

/*************************** */

bool UserManager::removeUser(const User& user) {
    for (const User& u : users)
        if (user == u)
            return true;

    return false;
}

/*************************** */

bool UserManager::removeUser(const std::string& id) {
    auto it = std::remove_if(users.begin(), users.end(), [id](const User& u) {
        return u.getId() == id;
    });
    if (it != users.end()) {
        users.erase(it, users.end());
        return true;
    }
    return false;
}


/*************************** */

void UserManager::printHTML()const {
    if (users.size() < 0) {
        std::cout << R"(
        )";
    }
    else {
        std::cout << "<h1>Voici toutes les utilisateurs </div>";
        for (const User& user : users)
            user.printHTML();
    }
}

/*************************** */

int UserManager::getNextId()const {
    return users.size();
}

/*************************** */

void UserManager::saveUsers()const {
    std::ofstream dbFile(database);
    
    if (dbFile.is_open()) {
        for (const User& user : users ) {
            dbFile  << user.getId() << "|" << user.getName() << "|" << user.getEmail() << "|" 
                    << user.getBirthday() << "|" << user.getPassword() << std::endl;
        }
        dbFile.close();
    }
    else {
        std::cout << "Ereur";
    }
}

bool UserManager::authenticateUser(const std::string& email, const std::string& password) {
    std::ifstream file(database);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string userEmail, userPassword;

        // Lire la ligne et séparer les valeurs par "|"
        int tokenIndex = 0;
        while (std::getline(ss, token, '|')) {
            if (tokenIndex == 2) {
                userEmail = token;  // Deuxième valeur : email
            }
            if (tokenIndex == 4) {
                userPassword = token;  // Dernière valeur : password
            }
            ++tokenIndex;
        }

        // Comparer l'email et le mot de passe
        if (userEmail == email && userPassword == password) {
            return true;  // Trouvé
        }
    }

    return false;  // Non trouvé
}

/************************ */

void UserManager::displayUserTable() {
    if (users.size() == 0) {
        std::cout << "<p style='color: white;'>La liste des utilisateur est vide</p>";
        return;
    }

    std::cout << "<table border='1'>\n";
    std::cout << "<thead>\n<tr style='background:#d69002;'>\n<th>ID</th>\n<th>Nom</th>\n<th>Email</th>\n<th>Date de Naissance</th>\n<th>Actions</th>\n</tr>\n</thead>\n<tbody>\n";

    for (const auto& user : users) {
        std::cout << "<tr style='color:#f5f5f5;'>\n";
        std::cout << "<td>" << user.getId() << "</td>\n";
        std::cout << "<td>" << user.getName() << "</td>\n";
        std::cout << "<td>" << user.getEmail() << "</td>\n";
        std::cout << "<td>" << user.getBirthday() << "</td>\n";
        std::cout << "<td style='display:flex'>"
                  << "  <a href='/listUsers.cgi?action=modif&id=" << user.getId() << "'>Modifier</a>  "
                  << "  <a href='/listUsers.cgi?action=suppr&id=" << user.getId() << "'>Supprimer</a>"
                  << "</td>\n";
        std::cout << "</tr>\n";
    }

    std::cout << "</tbody>\n</table>\n";
}

bool UserManager::editUser(const std::string& id, const std::string& newName, const std::string& newEmail, const std::string& newBirthday) {
    for (auto& user : users) {
        if (user.getId() == id) {
            user.setName(newName);
            user.setEmail(newEmail);
            user.setBirthday(newBirthday);
            return true;
        }
    }
    return false;
}
