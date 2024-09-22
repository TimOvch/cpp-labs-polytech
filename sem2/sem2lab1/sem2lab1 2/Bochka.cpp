#include "Bochka.hpp"

Bochka::Bochka(){
    obyom = 0;
    koncetSpirta = 0;
}

Bochka::Bochka(double ob, double konS){
    obyom = ob;
    koncetSpirta = konS;
}

void Bochka::minusOb(double ob){
    obyom-=ob;
}

void Bochka::pereliv(Bochka &bochka, double obyomKrujki){
    bochka.minusOb(obyomKrujki);
    koncetSpirta = (obyom*koncetSpirta + (bochka.getKoncet()*obyomKrujki))/(obyom+obyomKrujki);
    obyom+=obyomKrujki;
}

double Bochka::getKoncet(){
    return koncetSpirta;
}
