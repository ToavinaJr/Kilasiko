#include "../include/User.hpp"
#include <iostream>

/*********************************** */

User::User(const std::string& _id, const std::string &_name, const std::string &_email, const std::string& _birthday, const std::string &_password)
    : id(_id), name(_name), email(_email), birthday(_birthday), password(_password)
{

}

/*********************************** */

void User::setName(const std::string &_name) {
    name = _name;
}

/*********************************** */

void User::setEmail(const std::string &_email) {
    email = _email;
}

/*********************************** */

void User::setId(const std::string& _id) {
    id = _id;
}

/*********************************** */

void User::setPassword(const std::string &_password) {
    password = _password;
}

/*********************************** */

void User::setBirthday(const std::string& _birthday) {
    birthday = _birthday;
}

/*********************************** */

std::string User::getEmail() const {
    return email;
}

/*************************** */

std::string User::getName() const {
    return name;
}

/*************************** */

std::string User::getPassword() const {
    return password;
}

/*************************** */

std::string User::getBirthday() const {
    return birthday;
}

/*************************** */

std::string User::getId()const {
    return id;
}

/*************************** */

bool User::operator==(const User& user) const{
    return (email == user.email);
}

void User::printHTML() const
{
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
        <div class="glass-card">
            <div>
                Name: )"
                    << name << R"(
            </div>
            <div>
                Email: )"
                    << email << R"(
            </div>
        </div>
    )";
}
