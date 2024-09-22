#ifndef Bochka_hpp
#define Bochka_hpp

class Bochka{
    
    double obyom;
    double koncetSpirta;
    
public:
    
    Bochka();
    
    Bochka(double ob, double konS);
    
    void pereliv(Bochka &bochka, double obyomKrujki);
    
    double getKoncet();
    
    void minusOb(double ob);
};

#endif
