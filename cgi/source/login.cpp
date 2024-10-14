#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "../../include/Handler.hpp"
#include "../../include/User.hpp"
#include "../../include/UserManager.hpp"
#include "../../include/Renderer.hpp"

int main() {
    auto handler    =  std::make_unique<Handler>();
    auto userManager =  std::make_unique<UserManager>("./users.txt");
    auto renderer = std::make_unique<Renderer>("Connectez vous", "style.css");

    std::map<std::string, std::string> data;
    std::string inputEmail, inputPassword, line, session_token="zaez";

    bool validInput{false};

    // Tester si la formulaire est valide
    try {
        data = handler->getData();
    }
    catch(const std::exception& e) {
        validInput = false;
        std::cerr << "<div>Formulaire invalide </div>" << e.what();
    }

    try {
        inputEmail = data.at("email");
        validInput = false;
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>L'email est incorrecte </div>";
        validInput = false;
    }

    try {
        inputPassword = data.at("password");
        validInput = false;
    }
    catch(const std::exception& e)
    {
        std::cout << "<div>Password incorrecte </div>";
        validInput = false;
    }

    inputEmail = handler->urlDecode(inputEmail);
    bool isValidUser = userManager->authenticateUser(inputEmail, inputPassword);
    auto loadData = userManager->loadUsers();

    std::ifstream adminFile("./admin.txt");
    std::string adminEmail, adminPassword;
    try {
        if (adminFile.is_open()) {
            adminFile >> adminEmail >> adminPassword;
            adminFile.close();
        }

        if (adminEmail == inputEmail && adminPassword == inputPassword) {
            userManager->displayUserTable();
        }

        else {
            try {
                std::string name;        
                for (const User& user : userManager->getUsers()) {
                    if ( handler->urlDecode(user.getEmail()) == inputEmail){                        
                        name = user.getName();
                        break;
                    }
                }
            
                if (isValidUser) {
                    // std::cout <<"Set-Cookie: session_token=" << session_token << "; path=/; HttpOnly\r\n"; 
                    std::cout << R"(
                        <style>
                            .glass-card {
                                background: #202222;
                                border-radius: 15px; 
                                padding: 20px; 
                                box-shadow: 0 4px 30px rgba(0, 0, 0, 0.1); 
                                backdrop-filter: blur(10px); 
                                border: 1px solid rgba(255, 255, 255, 0.5); 
                                width: 300px; 
                                color: #f5f5f5;
                                text-align: center; 
                            }

                            .glass-card div {
                                margin: 10px 0; 
                            }
                        </style>
                        <div style='display:flex flex-direction:flex-col gap: 10px;'>
                            <div class='glass-card'>
                                <h3 style='margin: 10px;'>Welcome</h3> 
                                <h1>)"<<  name  << R"( </h1>
                            </div>
                            <div class='glass-card'>
                                <a href='/'>Deconnexion</a>
                            </div>
                        </div>
                        )";
                }
                else {
                    std::cout << R"(
                        <style>
                            .error-message {
                                background-color: red;
                                font-size: 1rem;
                                margin-bottom: 15px;
                                color: #f5f5f5;
                                padding: 10px;
                            }
                            a {
                                background: #d69002;
                            }
                        </style>
                        <div style='flex flex-col'>
                            <div class="error-message">Mot de passe invalide. Veuillez réessayer.</div>
                            <a href='login'>Reconnectez</a>
                        <div>
                    )";
                }
            }
            catch(const std::exception& e) {
                std::cerr << "Erreur " << e.what();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur attrapée : " << e.what();
    }
       
    return EXIT_SUCCESS;
}