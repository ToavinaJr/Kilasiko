#include "../include/Renderer.hpp"

Renderer::Renderer(const std::string& title, const std::string& styleFile) {   
    std::cout << "Content-type: text/html\r\n\n";
    std::cout << R"(
                <!DOCTYPE html>
                <html lang="fr">
                <head>
                    <meta charset="UTF-8">
                    <meta name="viewport" content="width=device-width, initial-scale=1.0">
                    <title>Page d'inscription</title>
                    <link rel="stylesheet" href="style.css">
                </head>
                <body>)";
}

Renderer::~Renderer() {
     std::cout << R"(
                    </body>
                    </html>
        )";
}