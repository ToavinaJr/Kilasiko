#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <string>

class Renderer {
    public:
        Renderer(const std::string& title, const std::string& styleFile);
        ~Renderer();

        void drawHTML(const std::string& balise, const std::string& style, const std::string& text);
};

#endif