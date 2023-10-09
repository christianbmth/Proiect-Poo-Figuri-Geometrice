#include <iostream>
#include <bits/stdc++.h>
#include<vector>
using namespace std;
class Meniu;
class Punct
{
    float x,y;
public:
    Punct(){x=y=0;}
    Punct(float x1,float y1){x=x1;y=y1;}
    Punct(const Punct& ob){x=ob.x;y=ob.y;}
    ~Punct(){x=0;y=0;};
    Punct& operator=(const Punct& ob){x=ob.x;y=ob.y;return *this;}
    friend istream& operator>>(istream&, Punct&);
    friend ostream& operator<<(ostream&, Punct&);
    void set_x(float a){x=a;}
    void set_y(float a){y=a;}
    float get_x(){return x;}
    float get_y(){return y;}
};
class Patrat
{protected:
    Punct stanga_jos;
    float latura;
    bool valid=1;
public:
    friend class Meniu;
    Patrat(){stanga_jos.set_x(0);stanga_jos.set_y(0); latura=0;}
    Patrat(Punct s, float l){stanga_jos=s;latura=l;}
    Patrat(const Patrat& ob){stanga_jos=ob.stanga_jos;latura=ob.latura;}
    virtual ~Patrat(){latura=0;};
    Patrat& operator=(const Patrat& ob){stanga_jos=ob.stanga_jos;latura=ob.latura;return *this;}
    friend istream& operator>>(istream&,Patrat&);
    friend ostream& operator<<(ostream&,Patrat&);
    static void verificare(Patrat& ob){if(ob.latura<0)ob.valid=0;}
    static float aria(Patrat& ob)
    {
        verificare(ob);
        if(ob.valid)return ob.latura*ob.latura;
         else {cout<<"NU POTI SA FACI ARIA"<<endl;return -1;}
    }
    virtual void citire()
    {cout<<"Punctul din stanga jos:"<<endl;
    cin>>stanga_jos;
    cout<<"Lungimea primei laturi:";
    cin>>latura;
    }
};
class Dreptunghi:virtual public Patrat
{protected:
    float latura2;
public:
     friend class Meniu;
    Dreptunghi():Patrat(){latura2=0;}
    Dreptunghi(Punct s, float l, float l2):Patrat(s , l){latura2=l2;}
    Dreptunghi(const Dreptunghi& ob):Patrat(ob){latura2=ob.latura2;}
    virtual ~Dreptunghi(){latura2=0;}
    Dreptunghi& operator=(const Dreptunghi& ob){stanga_jos=ob.stanga_jos;latura=ob.latura;latura2=ob.latura2;return *this;}
    friend istream& operator>>(istream&,Dreptunghi&);
    friend ostream& operator<<(ostream&,Dreptunghi&);
    static void verificare(Dreptunghi& ob){if(ob.latura<0 && ob.latura2<0)ob.valid=0;}
    static float aria(Dreptunghi& ob)
    {
        verificare(ob);
        if(ob.valid)return ob.latura*ob.latura2;
            else {cout<<"NU POTI SA FACI ARIA"<<endl;return -1;}
    }
    virtual void citire()
    {
    cout<<"Punctul din stanga jos:"<<endl;
    cin>>stanga_jos;
    cout<<"Lungimea primei laturi:";
    cin>>latura;
    cout<<"Lungimea celeilalte laturi:";
    cin>>latura2;
    }
};
class Romb:virtual public Patrat
{
protected:
    Punct colt_opus;
public:
     friend class Meniu;
    Romb():Patrat(){colt_opus.set_x(0);colt_opus.set_y(0);}
    Romb(Punct s,float l,Punct op):Patrat(s,l){colt_opus=op;}
    Romb(const Romb& ob):Patrat(ob){colt_opus=ob.colt_opus;}
    virtual ~Romb(){}
    Romb& operator=(const Romb& ob){stanga_jos=ob.stanga_jos;latura=ob.latura;colt_opus=ob.colt_opus;return *this;}
    friend istream& operator>>(istream&,Romb&);
    friend ostream& operator<<(ostream&,Romb&);
    static void verificare(Romb& ob){if(ob.latura<0)ob.valid=0;if(sqrt(pow(ob.stanga_jos.get_x()-ob.colt_opus.get_x(),2)-pow(ob.stanga_jos.get_y()-ob.colt_opus.get_y(),2))<ob.latura)ob.valid=0;}
    static float aria(Romb& ob)
    {
         verificare(ob);
         if(ob.valid)
        {   double d1,d2;
            d1=pow(ob.stanga_jos.get_x()-ob.colt_opus.get_x(),2)-pow(ob.stanga_jos.get_y()-ob.colt_opus.get_y(),2);
            d1=sqrt(d1);
            d2=sqrt(4*ob.latura*ob.latura-d1*d1);
            return d1*d2/2;
        }
            else {cout<<"NU POTI SA FACI ARIA"<<endl;return -1;}

    }
    virtual void citire()
    {
    cout<<"Punctul din stanga jos:"<<endl;
    cin>>stanga_jos;
    cout<<"Lungimea laturii:";
    cin>>latura;
    cout<<"Coltul opus:"<<endl;
    cin>>colt_opus;
    }
};
class Paralelogram:virtual public Dreptunghi,virtual public Romb
{
public:
    friend class Meniu;
    Paralelogram():Dreptunghi(),Romb(){};
    Paralelogram(Punct s,float l,float l2,Punct o):Dreptunghi(s,l,l2){colt_opus=o;};
    Paralelogram(const Paralelogram& ob):Dreptunghi(ob){colt_opus=ob.colt_opus;};
    virtual ~Paralelogram(){}
    Paralelogram& operator=(const Paralelogram& ob){stanga_jos=ob.stanga_jos;latura=ob.latura;latura2=ob.latura2;colt_opus=ob.colt_opus;return *this;}
    friend istream& operator>>(istream&, Paralelogram&);
    friend ostream& operator<<(ostream&, Paralelogram&);
    static void verificare(Paralelogram& ob)
    {
        if(ob.latura<0)ob.valid=0;
        if(ob.latura2<0)ob.valid=0;
        if(sqrt(pow(ob.stanga_jos.get_x()-ob.colt_opus.get_x(),2)-pow(ob.stanga_jos.get_y()-ob.colt_opus.get_y(),2))<ob.latura)ob.valid=0;
    }
    static float aria(Paralelogram& ob)
    {
         verificare(ob);
         if(ob.valid)
        {
            double colt_gradat,p,h;
            p=pow(ob.stanga_jos.get_x()-ob.colt_opus.get_x(),2)-pow(ob.stanga_jos.get_y()-ob.colt_opus.get_y(),2);
            p=sqrt(p);
            colt_gradat=acos(p*p-ob.latura*ob.latura-ob.latura2*ob.latura2)/((-2)*ob.latura*ob.latura2);
            h=ob.latura*sin(colt_gradat);
            return h*ob.latura;
        }
            else {cout<<"NU POTI SA FACI ARIA"<<endl;return -1;}
    }
    virtual void citire()
    {
    cout<<"Punctul din stanga jos:"<<endl;
    cin>>stanga_jos;
    cout<<"Lungimea primei laturi:";
    cin>>latura;
    cout<<"Lungimea celeilalte laturi:";
    cin>>latura2;
    cout<<"Coltul opus:"<<endl;
    cin>>colt_opus;
    }
};
class Trapez:public Paralelogram
{protected:
    float baza2;
public:
    friend class Meniu;
    Trapez():Paralelogram(){baza2=0;}
    Trapez(Punct s,float l, float l2, Punct o, float b):Paralelogram(s,l,l2,o){baza2=b;}
    Trapez(const Trapez& ob):Paralelogram(ob){baza2=ob.baza2;}
    ~Trapez(){baza2=0;}
    Trapez& operator=(const Trapez& ob){stanga_jos=ob.stanga_jos;latura=ob.latura;latura2=ob.latura2;colt_opus=ob.colt_opus;baza2=ob.baza2;return *this;}
    friend istream& operator>>(istream&,Trapez&);
    friend ostream& operator<<(ostream&,Trapez&);
    static void verificare(Trapez& ob)
    {
        if(ob.latura<0)ob.valid=0;
        if(ob.latura2<0)ob.valid=0;
        if(ob.baza2<0)ob.valid=0;
        if(ob.colt_opus.get_x()!=ob.stanga_jos.get_x()+ob.latura2)ob.valid=0;
        if(ob.colt_opus.get_y()!=ob.stanga_jos.get_y()+ob.baza2)ob.valid=0;
    }
    static float aria(Trapez& ob)
    {
         verificare(ob);
         if(ob.valid)
            return ((ob.latura+ob.baza2)/2)*ob.latura2;
             else {cout<<"NU POTI SA FACI ARIA"<<endl;return -1;}
    }
    virtual void citire()
    {
    cout<<"Punctul din stanga jos:"<<endl;
    cin>>stanga_jos;
    cout<<"Lungimea bazei mari:";
    cin>>latura;
    cout<<"Lungimea laturii:";
    cin>>latura2;
    cout<<"Coltul opus:"<<endl;
    cin>>colt_opus;
    cout<<"Lungimea bazei mici:";
    cin>>baza2;
    }

};
class Meniu
{
    vector <Patrat*> v;
public:
    void adaugare_figuri(string);
    void cele_mai_multe_figuri();
    void cea_mai_mare_arie();
    void arie_totala();
    int afisare_meniu();
};
void Meniu::adaugare_figuri(string tip)
{
    if (tip=="Patrat") v.push_back(new Patrat());
    else if (tip=="Dreptunghi")v.push_back(new Dreptunghi());
    else if (tip=="Romb")v.push_back(new Romb());
    else if (tip=="Paralelogram")v.push_back(new Paralelogram());
    else if(tip=="Trapez") v.push_back(new Trapez());
    (*v.back()).citire();
}
void Meniu::cele_mai_multe_figuri()
{
    int nrpat=0;
    int nrdr=0;
    int nrro=0;
    int nrparal=0;
    int nrtr=0;

    vector<Patrat*>::iterator p;
    for( p=v.begin();p!=v.end();p++)
            if(typeid(**p)==typeid(Patrat))nrpat++;
                else if(typeid(**p)==typeid(Dreptunghi))nrdr++;
                        else if(typeid(**p)==typeid(Romb))nrro++;
                                else if(typeid(**p)==typeid(Paralelogram))nrparal++;
                                        else if(typeid(**p)==typeid(Trapez))nrtr++;
    int nrmax=nrpat;
    string smax="Patrat";
    if(nrdr>nrmax){nrmax=nrdr;smax="Dreptunghi";}
    if(nrro>nrmax){nrmax=nrro;smax="Romb";}
    if(nrparal>nrmax){nrmax=nrparal;smax="Paralelogram";}
    if(nrtr>nrmax){nrmax=nrtr;smax="Trapez";}
    cout<<smax<<endl;
}
void Meniu::cea_mai_mare_arie()
{
    float ariemax=0;
    string smax="";
    vector<Patrat*>::iterator p;
    for(p=v.begin();p!=v.end();p++)
            {
               if(typeid(**p)==typeid(Patrat))if(Patrat::aria(**p)>ariemax)smax="Patrat";
               if(typeid(**p)==typeid(Dreptunghi))if(Dreptunghi::aria(*dynamic_cast<Dreptunghi*>(*p))>ariemax)smax="Dreptunghi";
               if(typeid(**p)==typeid(Romb))if(Romb::aria(*dynamic_cast<Romb*>(*p))>ariemax)smax="Romb";
               if(typeid(**p)==typeid(Paralelogram))if(Paralelogram::aria(*dynamic_cast<Paralelogram*>(*p))>ariemax)smax="Paralelogram";
               if(typeid(**p)==typeid(Trapez))if(Trapez::aria(*dynamic_cast<Trapez*>(*p))>ariemax)smax="Trapez";
            }
        cout<<smax<<endl;
}
void Meniu::arie_totala()
{
    float arietotala=0;
    vector<Patrat*>::iterator p;
    for(p=v.begin();p!=v.end();p++)
        {
            if(typeid(**p)==typeid(Patrat))arietotala+=Patrat::aria(**p);
            if(typeid(**p)==typeid(Dreptunghi))arietotala+=Dreptunghi::aria(*dynamic_cast<Dreptunghi*>(*p));
            if(typeid(**p)==typeid(Romb))arietotala+=Romb::aria(*dynamic_cast<Romb*>(*p));
            if(typeid(**p)==typeid(Paralelogram))arietotala+=Paralelogram::aria(*dynamic_cast<Paralelogram*>(*p));
            if(typeid(**p)==typeid(Trapez))arietotala+=Trapez::aria(*dynamic_cast<Trapez*>(*p));
        }
    cout<<arietotala<<endl;
}

int Meniu::afisare_meniu()
{
    int x;
    try{
        cout<<"Bine ati venit in paradisul figurilor geometrice!"<<endl;
        cout<<"1.Adauga o figura noua"<<endl;
        cout<<"2.Care este figura voastra preferata"<<endl;
        cout<<"3.Afiseaza ce tip de figura are cea mai mare arie"<<endl;
        cout<<"4.Afiseaza aria totala"<<endl;
        cout<<"5.Iesire"<<endl;
        cout<<"Ce doriti?"<<endl;
        cin>>x;
        if(x < 1 || x > 5)
            throw 1;
    }
    catch(...){
        do{
            cout << "Optiunea aleasa trebuie sa fie cuprinsa intre 1 si 5." << endl;
            cout<<"Ce doriti?"<<endl;
            cin>>x;
        }
        while(x < 1 || x > 5);
    }
        switch(x)
        {
            case 1:
                {
                    string s;
                    cout<<"Ce tip de figura vreti sa cititi?(Patrat/Dreptunghi/Romb/Paralelogram/Trapez)"<<endl;
                    cin>>s;
                    adaugare_figuri(s);
                    break;
                }
            case 2:
                {
                    cout<<"Figura preferata este: ";
                    cele_mai_multe_figuri();
                    break;
                }
            case 3:
                {
                    cout<<"Figura cu cea mai mare arie este un ";
                    cea_mai_mare_arie();
                        break;
                }
            case 4:
                {
                    cout<<"Aria totala este ";
                    arie_totala();
                    cout<<endl<<"Am facut doar suma ariilor. Doar nu stateam sa verific daca se suprapun figurile :)";
                    break;
                }
            case 5:
                {
                        return 0;
                }

     }
     cout << endl;
     Meniu::afisare_meniu();
}

int main()
{
    Meniu m;
    m.afisare_meniu();
    return 0;
}
istream& operator>>(istream& in, Punct& ob)
{
    cout<<"Coordonata pe axa Ox:";
    in>>ob.x;
    cout<<"Coordonata pe axa Oy:";
    in>>ob.y;
    return in;
}
istream& operator>>(istream& in, Patrat& ob)
{
    cout<<"Punctul din stanga jos:"<<endl;
    in>>ob.stanga_jos;
    cout<<"Lungimea laturii:";
    in>>ob.latura;
    return in;
}
istream& operator>>(istream& in, Dreptunghi& ob)
{
   cout<<"Punctul din stanga jos:"<<endl;
    in>>ob.stanga_jos;
    cout<<"Lungimea primei laturi:";
    in>>ob.latura;
    cout<<"Lungimea celeilalte laturi:";
    in>>ob.latura2;
    return in;
}
istream& operator>>(istream& in, Romb& ob)
{
   cout<<"Punctul din stanga jos:"<<endl;
    in>>ob.stanga_jos;
    cout<<"Lungimea laturii:";
    in>>ob.latura;
    cout<<"Coltul opus:"<<endl;
    in>>ob.colt_opus;
    return in;
}
istream& operator>>(istream& in, Paralelogram& ob)
{
    cout<<"Punctul din stanga jos:"<<endl;
    in>>ob.stanga_jos;
    cout<<"Lungimea primei laturi:";
    in>>ob.latura;
    cout<<"Lungimea celeilalte laturi:";
    in>>ob.latura2;
    cout<<"Coltul opus:"<<endl;
    in>>ob.colt_opus;
    return in;
}
istream& operator>>(istream& in,Trapez& ob)
{
   cout<<"Punctul din stanga jos:"<<endl;
    in>>ob.stanga_jos;
    cout<<"Lungimea bazei mari:";
    in>>ob.latura;
    cout<<"Lungimea laturii:";
    in>>ob.latura2;
    cout<<"Coltul opus:"<<endl;
    in>>ob.colt_opus;
    cout<<"Lungimea bazei mici:";
    in>>ob.baza2;
    return in;
}

ostream& operator<<(ostream& out, Punct& ob)
{
    out<<"are coordonatele: "<<ob.x<<" "<<ob.y<<" ";
    return out;
}
ostream& operator<<(ostream& out, Patrat& ob)
{
    out<<"Punctul din stanga jos "<<ob.stanga_jos<<endl<<"Latura:"<<ob.latura<<endl;
    return out;
}
ostream& operator<<(ostream& out, Dreptunghi& ob)
{
    out<<"Punctul din stanga jos "<<ob.stanga_jos<<endl<<"Latura:"<<ob.latura<<endl;
    out<<"Cealalta latura:"<<ob.latura2<<endl;
    return out;
}
ostream& operator<<(ostream& out, Romb& ob)
{
    out<<"Punctul din stanga jos "<<ob.stanga_jos<<endl<<"Latura:"<<ob.latura<<endl;
    out<<"Coltul opus "<<ob.colt_opus<<endl;
    return out;
}
ostream& operator<<(ostream& out, Paralelogram& ob)
{
    out<<"Punctul din stanga jos "<<ob.stanga_jos<<endl<<"Latura:"<<ob.latura<<endl;
    out<<"Cealalta latura:"<<ob.latura2<<endl;
    out<<"Coltul opus "<<ob.colt_opus<<endl;
    return out;
}
ostream& operator<<(ostream& out,Trapez& ob)
{
    out<<"Punctul din stanga jos "<<ob.stanga_jos<<endl<<"Baza:"<<ob.latura<<endl;
    out<<"Cealalta latura:"<<ob.latura2<<endl;
    out<<"Coltul opus "<<ob.colt_opus<<endl;
    out<<"Baza mica:"<<ob.baza2<<endl;
    return out;
}
