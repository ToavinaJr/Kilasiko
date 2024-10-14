#include "../include/Controller.hpp"

/*************************************************** */

bool Controller::isValidEmail(const std::string &email)
{
    // Définir une expression régulière pour l'adresse email
    const std::regex pattern(R"((\w+)(\.{0,1}\w+)*@(\w+)(\.\w+)+)");

    // Utiliser std::regex_match pour vérifier si l'email correspond au modèle
    return std::regex_match(email, pattern);
}

/*************************************************** */

std::string Controller::trim(const std::string &str)
{
    // Trouver la première position non-blanche
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char ch)
                                  { return std::isspace(ch); });

    // Trouver la dernière position non-blanche
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch)
                                { return std::isspace(ch); })
                   .base();

    // Si la chaîne est entièrement composée d'espaces, renvoyer une chaîne vide
    if (start >= end)
    {
        return "";
    }

    // Retourner la sous-chaîne trimée
    return std::string(start, end);
}

/*************************************************** */

bool Controller::isValidDate(const std::string &date)
{
    // Expression régulière pour le format yyyy-mm-dd
    const std::regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");

    // Vérification du format général
    if (!std::regex_match(date, pattern))
    {
        return false;
    }

    // Extraction du jour, mois et année
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    // Vérification des valeurs de mois
    if (month < 1 || month > 12)
    {
        return false;
    }

    // Nombre de jours par mois
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Fonction pour vérifier si une année est bissextile
    auto isLeapYear = [](int _year) -> bool
    {
        return (_year % 4 == 0 && _year % 100 != 0) ||
               (_year % 400 == 0);
    };

    // Ajustement pour l'année bissextile
    if (isLeapYear(year))
    {
        daysInMonth[1] = 29; // Février a 29 jours dans une année bissextile
    }

    // Vérification du jour
    if (day < 1 || day > daysInMonth[month - 1])
    {
        return false;
    }

    return true;
}


/*************************************************** */