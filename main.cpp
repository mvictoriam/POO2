#include <iostream>

using namespace std;

class Complex
{
    float re,im;
public:
    Complex(){re=0;im=0;}
    Complex(float r){re=r;im=0;}
    Complex(float r, float i){re=r; im=i;}
    Complex(const Complex &z){re=z.re;im=z.im;}//constructor copiere
    friend istream &operator >>(istream &,Complex &);
    friend ostream& operator <<(ostream &, const Complex &);
    void citire(){cin>>re; cin>>im;}
    void afisare(){cout<<re; cout<<im;}
    Complex& operator = (const Complex& z);
    Complex operator +(Complex z);
    ~Complex(){};
};
/*Complex Complex::operator +(Complex z){
Complex rez;
rez.re = this->re + z.re;
rez.im = this->im + z.im;
return rez;
}*/
Complex& Complex::operator = (const Complex &z)
{
    if ( this != &z)
    {
        this->re = z.re;
        this->im = z.im;
    }
    return *this;
}
istream& operator >>(istream &in,Complex &c)
{
    in>>c.re>>c.im;
    return in;
}
ostream& operator <<(ostream & out, const Complex &c)
{
    out<<c.re;
    out<<c.im;
    return out;
}
class Matrice
{
    Complex **ma;
    int m,n;
public:
    Matrice(int row=0, int col=0)
    {
        m = row;
        n = col;
        ma = new Complex*[m];
        for (int i = 0; i < m; i++)
            ma[i] = new Complex[n];
    }
    ~Matrice()
    {
        for (int i = 0; i < m; i++)
            delete ma[i];
        delete ma;
    }
    friend istream& operator>>(istream&,Matrice&);
    friend ostream& operator<<(ostream&,Matrice);
   // Complex* operator()(int,int);
    virtual void afisare()
    {
        for(int i=0;i<m;i++)
            {
                for(int j=0;j<n;j++)
                   cout<<ma[i][j]<<" ";
                cout<<endl;
            }
    }
    virtual void citire()
    {
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
               cin>>ma[i][j];
    }
};
istream& operator>>(istream& in,Matrice& a)
{
	for(int i=0;i<a.m;i++)
	for(int j=0;j<a.n;j++)
	{
		cout<<"\n["<<i+1<<"]["<<j+1<<"]= ";
		in>>a.ma[i][j];
    }
return in;
}

ostream& operator<<(ostream& o,Matrice a)
{
	for(int i=0;i<a.m;i++)
	{
		for(int j=0;j<a.n;j++)
		o<<'\n'<<a.ma[i][j];
		o<<endl;
	}
return o;
}
/*Complex** Matrice::operator()(int i,int j)
{
	return ma+i*n+j;
}*/
class Matrice_oarecare: public Matrice
{
    int lin,col;
};

class Matrice_patratica: public Matrice
{
    int dim;
    Complex val;
    public:
    void afisare()
    {
        for(int i=0;i<dim;i++)
            {
                for(int j=0;j<dim;j++)
                    cout<<ma[i][j]<<" ";
                cout<<endl;
            }
    }
    void citire()
    {
        for(int i=0;i<dim;i++)
            for(int j=0;j<dim;j++)
               cin>>ma[i][j];
    }
    int tri_drept()
    {
        int i,j;
        for(i=0;i<dim;i++)
            for(j=0;j<dim;j++)
               if(Matrice_patratica.val[i][j]!=0 && i!=j)
                 return 0;
               else if(Matrice_patratica.val[i][i]==0)
                return 0;
        return 1;
    }
    Complex** calcul_minor(Complex **ma,int lin, int col, int n)
    {
        int i,j;
        Complex **a=new Complex *[n-1];
        for(i=0; i<n-1; i++)
        {
            a[i]=new Complex[n-1];
        }
        for(i=0; i<n-1; i++)
            for(j=0; j<n-1; j++)
                if(i<lin)
                {
                    if(j<col)
                        a[i][j]=ma[i][j];
                    else
                        a[i][j]=ma[i][j+1];
                }
                else{
                    if(j<col)
                        a[i][j]=ma[i+1][j];
                    else
                        a[i][j]=ma[i+1][j+1];
                }
        return a;
    }
    Complex determinant(int** ma,int n)
    {
        if(n<=1) return ma[0][0];
        Complex S=0;
        for(int i=0; i<n; i++)
            S+=ma[0][i]*(i%2?-1:1)*determinant(calcul_minor(ma,0,i,n),n-1);
        return S;
    }
};

int main()
{
    int n,m;
    cin>>n>>m;
    Matrice_oarecare **ma;
    ma.citire();
    ma.afisare();
    return 0;
}
