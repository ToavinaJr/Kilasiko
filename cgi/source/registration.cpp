#include "../../include/User.hpp"
#include "../../include/UserManager.hpp"
#include "../../include/Handler.hpp"
#include "../../include/Controller.hpp"
#include "../../include/Renderer.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

int main() {
    bool validInput{false};
    std::map<std::string, std::string> data;
    std::string name, email, dob, birthday, password1, password2;

    /***************************** */

    auto handler    =  std::make_unique<Handler>();
    auto userManager =  std::make_unique<UserManager>("./users.txt");
    auto renderer = std::make_unique<Renderer>("Inscrivez vous", "style.css");

    /***************************** */

    // Tester si la formulaire est valide
    try {
        data = handler->getData();
    }
    catch(const std::exception& e) {
        validInput = false;
        std::cout << "<div>Formulaire invalide </div>";
    }

    /***************************** */

    // testser si le champ nom est nom vide
    try {
        name = data.at("name");
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>Nom Invalide </div>";
        validInput = false;
    }

    /***************************** */

    try {
        dob = data.at("dob");
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>Date de naissance invalid</div>";
        validInput = false;
    }

    /***************************** */

    try {
        email = data.at("email");
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>EMail invalid </div>";
        validInput = false;
    }
    
    /***************************** */

    try {
        password1 = data.at("password-1");
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>Password 1 manquant invalid </div>";
        validInput = false;
    }

    /***************************** */

    try {
        password2 = data.at("password-2");
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>Password 2 manquant </div>";
        validInput = false;
    }

    /***************************** */

    // Tester si les input sont valides
    auto controlerFormulaire = std::make_unique<Controller>();
    
    // Tester la validité des champs
    auto validDate = controlerFormulaire->isValidDate(dob);
    auto validEmail = controlerFormulaire->isValidEmail(email);
    auto valiPassword = password1 == password2;

    // Validité de la formulaire
    validInput = validDate && validEmail && valiPassword;

    std::cout << "<div style='flex flex-col'>";
    if (!validDate) {
        std::cout << "<div style='color: #f5f5f5;'>Date invalid </div>";
    }

    if (!validEmail)  {
        std::cout << "<div style='color: #f5f5f5;'> EMail invalid </div>";
    }

    if (!valiPassword) {
        std::cout << "<div style='color: #f5f5f5;'> Password invalid </div>";
    }

    try {
        if (validInput) {
            std::cout << R"(
                        <div>
                            <h1 style='color: #f5f5f5;'>Users bien enregistrée</h1>
                            <a href='/login' style='background-color: #F3A712;'> Se connecter maintenant</a>
                        <div>
            )";

            // Savoir le dernier id
            auto nextId = handler->generateId();

            // AJouter l'utilisateur
            userManager->addUser(nextId, name, email, dob, password1);
            userManager->saveUsers();
        }
        else {
            std::cout << "<a href='/' style='background-color: #F3A712;'>Revenir au formulaire</a>";
        }
        std::cout <<"</div>";
    }
    catch(const std::exception& e) {
        std::cerr << "Erreur caught : " << e.what();
    }

    return EXIT_SUCCESS;
}