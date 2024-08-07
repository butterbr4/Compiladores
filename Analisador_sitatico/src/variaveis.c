#include <stdio.h>
#include <stdlib.h>
#include "../headers/lexico.h"

char *transition_table[][3] = { // estado atual,  simbolo,  proximo estado
    // Transições a partir de q0
    {"q0", "a", "q1"}, {"q0", "b", "q1"}, {"q0", "c", "q1"}, // e assim por diante para todas as letras
    {"q0", "d", "q1"}, {"q0", "e", "q1"}, {"q0", "f", "q1"},
    {"q0", "g", "q1"}, {"q0", "h", "q1"}, {"q0", "i", "q1"},
    {"q0", "j", "q1"}, {"q0", "k", "q1"}, {"q0", "l", "q1"},
    {"q0", "m", "q1"}, {"q0", "n", "q1"}, {"q0", "o", "q1"},
    {"q0", "p", "q1"}, {"q0", "q", "q1"}, {"q0", "r", "q1"},
    {"q0", "s", "q1"}, {"q0", "t", "q1"}, {"q0", "u", "q1"},
    {"q0", "v", "q1"}, {"q0", "w", "q1"}, {"q0", "x", "q1"},
    {"q0", "y", "q1"}, {"q0", "z", "q1"},
    {"q0", "A", "q1"}, {"q0", "B", "q1"}, {"q0", "C", "q1"}, // e assim por diante para todas as letras maiúsculas
    {"q0", "D", "q1"}, {"q0", "E", "q1"}, {"q0", "F", "q1"},
    {"q0", "G", "q1"}, {"q0", "H", "q1"}, {"q0", "I", "q1"},
    {"q0", "J", "q1"}, {"q0", "K", "q1"}, {"q0", "L", "q1"},
    {"q0", "M", "q1"}, {"q0", "N", "q1"}, {"q0", "O", "q1"},
    {"q0", "P", "q1"}, {"q0", "Q", "q1"}, {"q0", "R", "q1"},
    {"q0", "S", "q1"}, {"q0", "T", "q1"}, {"q0", "U", "q1"},
    {"q0", "V", "q1"}, {"q0", "W", "q1"}, {"q0", "X", "q1"},
    {"q0", "Y", "q1"}, {"q0", "Z", "q1"},
    {"q0", "0", "q2"}, {"q0", "1", "q2"}, {"q0", "2", "q2"}, // e assim por diante para todos os números
    {"q0", "3", "q2"}, {"q0", "4", "q2"}, {"q0", "5", "q2"},
    {"q0", "6", "q2"}, {"q0", "7", "q2"}, {"q0", "8", "q2"},
    {"q0", "9", "q2"},
    {"q0", "+", "f3"}, {"q0", "-", "f4"}, {"q0", "*", "f5"},
    {"q0", "/", "f6"}, {"q0", "<", "q3"}, {"q0", ">", "q4"},
    {"q0", "=", "f7"}, {"q0", "(", "f16"}, {"q0", ")", "f17"},
    {"q0", ";", "f14"}, {"q0", ":", "q5"}, {"q0", ",", "f19"},
    {"q0", ".", "f15"}, {"q0", "{", "q6"},
    {"q0", " ", "q0"}, {"q0", "\t", "q0"}, {"q0", "\n", "q0"},
    
    // Transições a partir de q1
    {"q1", "a", "q1"}, {"q1", "b", "q1"}, {"q1", "c", "q1"},
    {"q1", "d", "q1"}, {"q1", "e", "q1"}, {"q1", "f", "q1"},
    {"q1", "g", "q1"}, {"q1", "h", "q1"}, {"q1", "i", "q1"},
    {"q1", "j", "q1"}, {"q1", "k", "q1"}, {"q1", "l", "q1"},
    {"q1", "m", "q1"}, {"q1", "n", "q1"}, {"q1", "o", "q1"},
    {"q1", "p", "q1"}, {"q1", "q", "q1"}, {"q1", "r", "q1"},
    {"q1", "s", "q1"}, {"q1", "t", "q1"}, {"q1", "u", "q1"},
    {"q1", "v", "q1"}, {"q1", "w", "q1"}, {"q1", "x", "q1"},
    {"q1", "y", "q1"}, {"q1", "z", "q1"},
    {"q1", "A", "q1"}, {"q1", "B", "q1"}, {"q1", "C", "q1"},
    {"q1", "D", "q1"}, {"q1", "E", "q1"}, {"q1", "F", "q1"},
    {"q1", "G", "q1"}, {"q1", "H", "q1"}, {"q1", "I", "q1"},
    {"q1", "J", "q1"}, {"q1", "K", "q1"}, {"q1", "L", "q1"},
    {"q1", "M", "q1"}, {"q1", "N", "q1"}, {"q1", "O", "q1"},
    {"q1", "P", "q1"}, {"q1", "Q", "q1"}, {"q1", "R", "q1"},
    {"q1", "S", "q1"}, {"q1", "T", "q1"}, {"q1", "U", "q1"},
    {"q1", "V", "q1"}, {"q1", "W", "q1"}, {"q1", "X", "q1"},
    {"q1", "Y", "q1"}, {"q1", "Z", "q1"},
    {"q1", "0", "q1"}, {"q1", "1", "q1"}, {"q1", "2", "q1"},
    {"q1", "3", "q1"}, {"q1", "4", "q1"}, {"q1", "5", "q1"},
    {"q1", "6", "q1"}, {"q1", "7", "q1"}, {"q1", "8", "q1"},
    {"q1", "9", "q1"},

    // Transições a partir de q2
    {"q2", "0", "q2"}, {"q2", "1", "q2"}, {"q2", "2", "q2"},
    {"q2", "3", "q2"}, {"q2", "4", "q2"}, {"q2", "5", "q2"},
    {"q2", "6", "q2"}, {"q2", "7", "q2"}, {"q2", "8", "q2"},
    {"q2", "9", "q2"},
    {"q2", "a", "e1"}, {"q2", "b", "e1"}, {"q2", "c", "e1"}, // e assim por diante para todas as letras
    {"q2", "d", "e1"}, {"q2", "e", "e1"}, {"q2", "f", "e1"},
    {"q2", "g", "e1"}, {"q2", "h", "e1"}, {"q2", "i", "e1"},
    {"q2", "j", "e1"}, {"q2", "k", "e1"}, {"q2", "l", "e1"},
    {"q2", "m", "e1"}, {"q2", "n", "e1"}, {"q2", "o", "e1"},
    {"q2", "p", "e1"}, {"q2", "q", "e1"}, {"q2", "r", "e1"},
    {"q2", "s", "e1"}, {"q2", "t", "e1"}, {"q2", "u", "e1"},
    {"q2", "v", "e1"}, {"q2", "w", "e1"}, {"q2", "x", "e1"},
    {"q2", "y", "e1"}, {"q2", "z", "e1"},
    {"q2", "A", "e1"}, {"q2", "B", "e1"}, {"q2", "C", "e1"}, // e assim por diante para todas as letras maiúsculas
    {"q2", "D", "e1"}, {"q2", "E", "e1"}, {"q2", "F", "e1"},
    {"q2", "G", "e1"}, {"q2", "H", "e1"}, {"q2", "I", "e1"},
    {"q2", "J", "e1"}, {"q2", "K", "e1"}, {"q2", "L", "e1"},
    {"q2", "M", "e1"}, {"q2", "N", "e1"}, {"q2", "O", "e1"},
    {"q2", "P", "e1"}, {"q2", "Q", "e1"}, {"q2", "R", "e1"},
    {"q2", "S", "e1"}, {"q2", "T", "e1"}, {"q2", "U", "e1"},
    {"q2", "V", "e1"}, {"q2", "W", "e1"}, {"q2", "X", "e1"},
    {"q2", "Y", "e1"}, {"q2", "Z", "e1"},

    // Transições a partir de q3
    {"q3", "=", "f8"}, {"q3", ">", "f9"},

    // Transições a partir de q4
    {"q4", "=", "f11"},
    // Transições a partir de q5
    {"q5", "=", "f13"},

    // Transições a partir de q6
    {"q6", "}", "q0"}, {"q6", "\n", "e2"},
        
    {NULL, NULL, NULL}  
};

char *folower_table[][3] = { // Nao terminal,  seguidor,  seguidor
    // Seguidores de constante
    {"constante", "PROCEDURE", "PROCEDURE"},
    {"constante", "id", "id"},
    {"constante", "CALL", "CALL"},
    {"constante", "BEGIN", "BEGIN"},
    {"constante", "IF", "IF"},
    {"constante", "WHILE", "WHILE"},
    {"constante", "ponto", "ponto"},
    {"constante", "ponto_virgula", "ponto_virgula"},
    {"constante", "VAR", "VAR"},

    // Seguidores de variavel
    {"variavel", "PROCEDURE", "PROCEDURE"},
    {"variavel", "id", "id"},
    {"variavel", "CALL", "CALL"},
    {"variavel", "BEGIN", "BEGIN"},
    {"variavel", "IF", "IF"},
    {"variavel", "WHILE", "WHILE"},
    {"variavel", "ponto", "ponto"},
    {"variavel", "ponto_virgula", "ponto_virgula"},

    // Seguidores de procedimento
    {"procedimento", "id", "id"},
    {"procedimento", "CALL", "CALL"},
    {"procedimento", "BEGIN", "BEGIN"},
    {"procedimento", "IF", "IF"},
    {"procedimento", "WHILE", "WHILE"},
    {"procedimento", "ponto", "ponto"},
    {"procedimento", "ponto_virgula", "ponto_virgula"},

    // Seguidores de comando
    {"comando", "END", "END"},
    {"comando", "ponto", "ponto"},
    //{"comando", "ponto_virgula", "ponto_virgula"},

    // Seguidores de fator

    {NULL, NULL, NULL}
};