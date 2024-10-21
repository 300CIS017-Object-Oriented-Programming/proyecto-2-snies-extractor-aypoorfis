//
// Created by User on 13/10/2024.
//
#ifndef GESTOR_JSON_H
#define GESTOR_JSON_H

#include "GestorDatos.h"

#include <string>
#include <vector>
#include <map>

using std::string;
using std::map;
using std::vector;


class GestorJson : public GestorDatos {
public:
    void exportarDatos(const std::string& filePath, const std::vector<std::map<std::string, std::string>>& datos) override;
};

#endif // GESTOR_JSON_H
