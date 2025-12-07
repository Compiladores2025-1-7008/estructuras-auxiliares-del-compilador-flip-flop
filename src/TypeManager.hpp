#pragma once
#include "TypeTable.hpp"
#include <string>

class TypeManager {
public:
    // Define la jerarquía según el PDF
    static int getHierarchy(const std::string& name) {
        if (name == "void")   return 0;
        if (name == "bool")   return 1;
        if (name == "char")   return 2;
        if (name == "int")    return 3;
        if (name == "float")  return 4;
        if (name == "double") return 5;
        return -1; // No es un tipo numérico básico
    }

    // max(t1, t2): retorna el tipo de mayor jerarquía
    static int max(const TypeTable &TT, int t1, int t2) {
        if (!TT.exists(t1) || !TT.exists(t2)) return -1;

        int h1 = getHierarchy(TT.getName(t1));
        int h2 = getHierarchy(TT.getName(t2));

        // Si alguno no es compatible (ej. arrays o structs sin sobrecarga), error
        if (h1 == -1 || h2 == -1) return -1;

        return (h1 >= h2) ? t1 : t2;
    }

    // min(t1, t2): retorna el tipo de menor jerarquía
    static int min(const TypeTable &TT, int t1, int t2) {
        if (!TT.exists(t1) || !TT.exists(t2)) return -1;

        int h1 = getHierarchy(TT.getName(t1));
        int h2 = getHierarchy(TT.getName(t2));

        if (h1 == -1 || h2 == -1) return -1;

        return (h1 <= h2) ? t1 : t2;
    }

    // ampliar(dir, t1, t2): verifica si t1 se puede ampliar a t2
    // Retorna t2 si es válido, -1 si no.
    static int ampliar(int dir, int t1, int t2, const TypeTable &TT) {
        if (t1 == t2) return t1;

        int h1 = getHierarchy(TT.getName(t1));
        int h2 = getHierarchy(TT.getName(t2));

        // Solo se puede ampliar si t1 < t2
        if (h1 != -1 && h2 != -1 && h1 <= h2) {
            return t2;
        }
        return -1; // Error de tipos
    }

    // reducir(dir, t1, t2): conversión explícita
    // Retorna t2 si es válido (aunque sea con pérdida de datos).
    static int reducir(int dir, int t1, int t2, const TypeTable &TT) {
         if (t1 == t2) return t1;

         int h1 = getHierarchy(TT.getName(t1));
         int h2 = getHierarchy(TT.getName(t2));

         // En reducir permitimos conversión si ambos son numéricos,
         // aunque t1 > t2 (pérdida de precisión)
         if (h1 != -1 && h2 != -1) {
             return t2;
         }
         return -1;
    }
};