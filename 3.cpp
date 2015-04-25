
#include "3_recursive_down.h"

int main()
{
    char AST [1000] = {};

    FILE* tree = fopen ("ast.txt", "r");
    fread (AST, 1, filelength (fileno (tree)), tree);

    node*   ruta    = new node()      ;
    string* tablef   = new string [10];
    string* tablev   = new string [10];

    ruta = Preparation (AST, tablev, tablef);
    Print (ruta);
    //puts (tablev[0].c_str());
    FILE* ASM = fopen ("code_back.txt", "w");

    GetFuncs (ruta, ASM, tablef, tablev);
    GetVars  (ruta -> child [0], ASM, tablef, tablev);
    GetMain (ruta -> child [ruta _N - 1], ASM, tablef, tablev);

    return 0;
}

