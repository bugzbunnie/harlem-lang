
#include "2_recursive_down.h"

int main()
{
    char AST [1000] = {};

    FILE* tree = fopen ("ast.txt", "r");
    fread (AST, 1, filelength (fileno (tree)), tree);

    node*   ruta     = new node()     ;
    string* tablef   = new string [10];
    string* tablev   = new string [10];

    ruta = Preparation (AST, tablev, tablef);
    Print (ruta);

    m_count = ruta _N - 3;

    FILE* ASM = fopen ("asm.txt", "w");

    GetVars  (ruta -> child [0], ASM);
    GetMain (ruta -> child [ruta _N - 1], ASM);
    GetFuncs (ruta, ASM);

    return 0;
}

