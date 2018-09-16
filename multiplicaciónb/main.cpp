#include <iostream>
#include <bitset>
#include <string>
using namespace std;


/*template<int n, int s, int s1>
bitset<n+1> sumss(){
    bitset<n> a(s);
    bitset<n> b(s1);
    bitset<n> c(0);
    bitset<n+1> d(0);
    for(int i=0;i<n;i++){
        c[i]=(a[i]^b[i]);
        if((a[i]==1 && b[i])==1)
            d[i+1]=true;
        d[i]=c[i]^d[i];
    }
    return d;
}*/

template<int N>
bitset<N> suma(bitset<N> a, bitset<N> b){
    int c=0;
    bitset<N> res;
    for(int i=0;i<a.size();i++){
        res[i]=((a[i]^b[i])^c);
        c=((a[i] & b[i]) | ((a[i]^b[i])&c));
    }
    return res;
}

template<int N>
void csigno(bitset<N> &a){
    a.flip();
    bitset<N> b=a;
    bitset<N> c(1);
    b=suma<N>(b,c);
    a=b;
}

template<int N>
bitset<N> resta(bitset<N> a, bitset<N> b){
    int c=0;
    csigno<N>(b);
    bitset<N> res;
    for(int i=0;i<a.size();i++){
        res[i]=((a[i]^b[i])^c);
        c=((a[i] & b[i]) | ((a[i]^b[i])&c));
    }
    return res;
}

template <int n, int q, int m>
bitset<2*n> multss(){
    bitset<n+1> q1(q);
    bitset<n+1> m1(m);
    if(q<0)
        csigno<n+1>(q1);
    if(m<0)
        csigno<n+1>(m1);
    bitset<n+1>a(0);
    bitset<2*n>c(0);
    bool tmp;
    int cont=n;
    while(cont!=0){
        if(q1[0]==1){
            a=suma<n+1>(a,m1);
        }
        tmp=a[0];
        a>>=1;
        q1>>=1;
        q1[n-1]=tmp;
        cont--;
    }
    for(int i=0;i<n;i++){
        c[i]=q1[i];
        c[n+i]=a[i];
    }
    return c;
}

template <int n, int q, int m>
bitset<2*n> multcs(){
    bitset<n+1> q1(q);
    int q0=0;
    bitset<n+1> m1(m);
    bitset<n+1>a(0);
    bitset<2*n>c(0);
    bool tmp;
    int cont=n;
    while(cont!=0){
        if(q1[0]==1 && q0==0){
            a=resta<n+1>(a,m1);
        }
        if(q1[0]==0 && q0==1){
            a=suma<n+1>(a,m1);
        }
        tmp=a[0];
        a>>=1;
        a[n-1]=a[n-2];
        q0=q1[0];
        q1>>=1;
        q1[n-1]=tmp;
        cont--;
    }
    for(int i=0;i<n;i++){
        c[i]=q1[i];
        c[n+i]=a[i];
    }
    return c;
}


int main()
{
    cout<<multss<32,-3,7>()<<endl;
    cout<<multcs<32,-3,7>()<<endl;
    return 0;
}
