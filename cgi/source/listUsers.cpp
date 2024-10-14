#include "../../include/UserManager.hpp"
#include "../../include/Handler.hpp"
#include "../../include/Renderer.hpp"

#include <fstream>
#include <iostream>
#include <memory>

int main() {
    auto userManager =  std::make_unique<UserManager>("./users.txt");
    auto renderer = std::make_unique<Renderer>("Inscrivez vous", "style.css");
    auto loadingData = userManager->loadUsers();
    auto handler = std::make_unique<Handler>();

    std::map<std::string, std::string> data;

    try {
        if (loadingData) {
            data = handler->getData();
        }
        else {
            throw std::runtime_error("Erreur lors du chargement de la donnée ");
        }
    }
    catch(const std::exception& e) {
        std::cerr << "<div> " << e.what() <<" </div>";
    }

    std::string action, id;
    try {
        id = data.at("id");
    }
    catch(const std::exception& e) {
        std::cerr << "Action non trouvée " << e.what();
    }
    // Tester l'action
    try {
        action = data.at("action");
        if (action == "modif") {
            std::cout <<R"( <div>
            <form action="registration.cgi" method="get">
                <div class="input-group">
                    <label for="name">Nom d'utilisateur</label>
                    <input name="name" type="text" id="name" placeholder="Entrez votre nom d'utilisateur" required>
                </div>
                <div class="input-group">
                    <label for="email">Email</label>
                    <input type="email" id="email" placeholder="Entrez votre email" name="email" required>
                </div>
                <div class="input-group">
                    <label for="dob">Date de naissance</label>
                    <input type="date" id="dob" name="dob" required value="test">
                </div>
                <div class="input-group">
                    <label for="password">Mot de passe</label>
                    <input type="password" id="password-1" name="password-1" placeholder="Entrez votre mot de passe" required>
                </div>
                <div class="input-group">
                    <label for="confirm-password">Confirmer le mot de passe</label>
                    <input type="password" id="password-2" name="password-2" placeholder="Confirmez votre mot de passe" required>
                </div>
                <button type="submit" id="sign-up">Mettre à jour</button>
            </form>
            <a href="listUsers.cgi">Voir la liste</a></div>)";
        }
        if (action == "suppr") {
            userManager->removeUser(id);
        }
    }

    catch(const std::exception& e) {
        std::cerr << "Action non trouvée " << e.what();
    }


    return EXIT_SUCCESS;
}