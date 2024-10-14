#include "../include/Handler.hpp"

std::string Handler::query() const
{
    char *q = getenv("QUERY_STRING");
    if (q)
        return q;
    return "";
}

/**************************************/

std::string Handler::generateId() const {
    // Création d'un générateur d'UUID basé sur un générateur aléatoire
    boost::uuids::random_generator generator;

    // Génération de l'UUID
    boost::uuids::uuid id = generator();

    // Conversion de l'UUID en string
    return boost::uuids::to_string(id);
}

/**************************************/

std::map<std::string, std::string> Handler::getData() const
{
    std::map<std::string, std::string> req;
    // Récupérer la chaîne de requête

    auto queryString        = query();
    auto decodeQuery        = urlDecode(queryString);
    auto vec   = split(decodeQuery, '&');

    for (auto const &v : vec)
    {
        auto keyAndValue = split(v, '=');

        req[keyAndValue.at(0)] = keyAndValue[1];
    }

    return req;
}

/**********************************/

std::vector<std::string> Handler::split(const std::string &str, const char &delimiter) const
{
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> result;

    while (std::getline(ss, token, delimiter))
    {
        result.push_back(token);
    }

    return result;
}

std::string Handler::urlDecode(const std::string &url) const
{
    std::string result;
    
    for (std::size_t i = 0; i < url.length(); ++i)
    {
        if (url[i] == '%')
        {
            if (i + 2 < url.length() && std::isxdigit(url[i + 1]) && std::isxdigit(url[i + 2]))
            {
                // Convertir les deux caractères hexadécimaux suivants en caractère ASCII
                std::istringstream iss(url.substr(i + 1, 2));
                int hexValue;
                iss >> std::hex >> hexValue;
                result += static_cast<char>(hexValue);
                i += 2; // Ignorer les deux chiffres après le %
            }
        }
        else if (url[i] == '+')
        {
            result += ' '; // Convertir les '+' en espaces
        }
        else
        {
            result += url[i]; // Autres caractères inchangés
        }
    }
    return result;
}