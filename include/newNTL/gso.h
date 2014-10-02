#ifndef NEWNTL_GSO_H
#define NEWNTL_GSO_H

#include <newNTL/mat_ZZ.h>
#include <newNTL/mat_RR.h>

newNTL_OPEN_NNS

template<typename NUMERIC>
NUMERIC normsq(const Mat<NUMERIC> m) {
  NUMERIC r = 0;
  for (long i=1; i<=m.NumRows(); ++i)
    r += m(i)*m(i);
  return r;
}

template<typename LFLOAT>
class GSO {
    static const unsigned long _MU=1;
    static const unsigned long _C=2;
    static const unsigned long _Q=4;
    long n;
    long m;
    unsigned long set_flag;
    mutable Mat<LFLOAT>* mu;
    mutable Mat<LFLOAT>* Lij;
    mutable Mat<LFLOAT>* Rij;
    mutable Vec<LFLOAT>* C;
    mutable Mat<LFLOAT>* Bstar;
    mutable Mat<LFLOAT>* Q;
    void Lij_to_mu() const {
	    mu = new Mat<LFLOAT>();
	    mu->SetDims(n,n);
	    for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                (*mu)(i,j)=(*Lij)(i,j)/(*Lij)(j,j);
    }
    void Rij_to_mu() const {
	    mu = new Mat<LFLOAT>();
	    mu->SetDims(n,n);
	    for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                (*mu)(i,j)=(*Rij)(i,j)/(*Rij)(j,j);
    }
    void Rij_to_Lij() const {
	    Lij = new Mat<LFLOAT>();
	    Lij->SetDims(n,n);
	    for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                (*Lij)(i,j)=(*Rij)(i,j)/sqrt((*Rij)(j,j));
    }
    void Lij_to_C() const {
        C = new Vec<LFLOAT>();
        C->SetLength(n);
        for (int i=1; i<=n; i++) (*C)(i)=sqr((*Lij)(i,i));
    }
    void Rij_to_C() const {
        C = new Vec<LFLOAT>();
        C->SetLength(n);
        for (int i=1; i<=n; i++) (*C)(i)=(*Rij)(i,i);
    }
    void Bstar_to_C() const {
        C = new Vec<LFLOAT>();
        C->SetLength(n);
        for (int i=1; i<=n; i++) (*C)(i)=(*Bstar)(i) * (*Bstar)(i);
    }
    void mu_C_to_Lij() const {
	    Lij = new Mat<LFLOAT>();
	    Lij->SetDims(n,n);
	    for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                (*Lij)(i,j)=(*mu)(i,j)*sqrt((*C)(j));
    }
    void Lij_to_Rij() const {
	    Rij = new Mat<LFLOAT>();
	    Rij->SetDims(n,n);
	    for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                (*Rij)(i,j)=Lij(i,j)*Lij(j,j);
    }
    void mu_C_to_Rij() const {
	    Rij = new Mat<LFLOAT>();
	    Rij->SetDims(n,n);
	    for (int i=1; i<=n; i++)
            for (int j=1; j<=i; j++)
                (*Rij)(i,j)=(*mu)(i,j) * (*C)(j);
    }
    void Q_C_to_Bstar() const {
        Bstar = new Mat<LFLOAT>();
        Bstar->SetDims(n,m);
        for (int i=1; i<=n; i++)
            (*Bstar)(i)=sqrt((*C)(i))*(*Q)(i);
    }
    void C_Bstar_to_Q() const {
        Q = new Mat<LFLOAT>();
        Q->SetDims(n,m);
        for (int i=1; i<=n; i++)
            (*Q)(i)=(1./sqrt((*C)(i)))*(*Bstar)(i);
    }
    
    void init() {
        mu=0;
        C=0;
        Q=0;
        Lij=0;
        Rij=0;
        Bstar=0;
        set_flag=0;
        n=0;
        m=0;
    }
    void destroy() {
        if (mu!=0) { delete mu; mu=0; }
        if (C!=0) { delete C; C=0; }
        if (Q!=0) { delete Q; Q=0; }
        if (Lij!=0) { delete Lij; Lij=0; }
        if (Rij!=0) { delete Rij; Rij=0; }
        if (Bstar!=0) { delete Bstar; Bstar=0; }
        set_flag=0;
        n=0;
        m=0;
        
    }
public:
    GSO() { init(); }
    GSO(const GSO& g) {PLANTE("forbidden to copy a GSO structure");}
    void operator=(const GSO& g) {PLANTE("forbidden to copy a GSO structure");}
    friend ostream& operator<<(ostream& out,const GSO& gso){
        out<<gso.n<<endl;
        out<<gso.m<<endl;
        out<<gso.set_flag<<endl;
        if(gso.mu)out<< true << " " << *gso.mu<<endl;
        else out<<false<<" "<<endl;
        if(gso.Lij)out<< true << " " << *gso.Lij<<endl;
        else out<<false<<" "<<endl;
        if(gso.Rij)out<< true << " " << *gso.Rij<<endl;
        else out<<false<<" "<<endl;
        if(gso.C)out<< true << " " << *gso.C<<endl;
        else out<<false<<" "<<endl;
        if(gso.Bstar)out<< true << " " << *gso.Bstar<<endl;
        else out<<false<<" "<<endl;
        if(gso.Q)out<< true << " " << *gso.Q<<endl;
        else out<<false<<" "<<endl;
        return out;
    }
    friend istream& operator>>(istream& in, GSO& gso){
        gso.reset();
        in>>gso.n;
        in>>gso.m;
        in>>gso.set_flag;
        bool b;in>>b;
        if(b) {
            gso.mu = new Mat<LFLOAT>();
            in>>*gso.mu;
        }
        in>>b;
        if(b) {
            gso.Lij =new Mat<LFLOAT>();
            in>>*gso.Lij;
        }
        in>>b;
        if(b) {
            gso.Rij =new Mat<LFLOAT>();
            in>>*gso.Rij;
        }
        in>>b;
        if(b) {
            gso.C =new Vec<LFLOAT>();
            in>>*gso.C;
        }
        in>>b;
        if(b) {
            gso.Bstar =new Mat<LFLOAT>();
            in>>*gso.Bstar;
        }
        in>>b;
        if(b) {
            gso.Q =new Mat<LFLOAT>();
            in>>*gso.Q;
        }
        return in;
    }
    
    
    
    ~GSO() {destroy();}
    void reset() {destroy();}
    
    void set_mu(const Mat<LFLOAT>& mu) {
        if (set_flag & _MU) PLANTE("FORBIDDEN TO OVERWRITE MU!");
        if (n>0 && n!=mu.NumRows()) PLANTE("DIMENSION MISMATCH FOR MU!");
        this->mu = new Mat<LFLOAT>(mu);
        this->n = mu.NumRows();
        this->set_flag |= _MU;
    }
    void set_C(const Vec<LFLOAT>& C) {
        if (set_flag & _MU) PLANTE("FORBIDDEN TO OVERWRITE C!");
        if (n>0 && n!=C.length()) PLANTE("DIMENSION MISMATCH FOR C!");
        this->C=new Vec<LFLOAT>(C);
        this->n=C.length();
        this->set_flag |= _C;
    }
    void set_Q(const Mat<LFLOAT>& Q) {
        if (set_flag & _Q) PLANTE("FORBIDDEN TO OVERWRITE Q!");
        if (n>0 && n!=Q.NumRows()) PLANTE("Row DIMENSION MISMATCH FOR Q!");
        if (m>0 && m!=Q.NumCols()) PLANTE("Col DIMENSION MISMATCH FOR Q!");
        this->Q=new Mat<LFLOAT>(Q);
        this->n=Q.NumRows();
        this->m=Q.NumCols();
        this->set_flag |= _Q;
    }
    void set_Lij(const Mat<LFLOAT>& Lij) {
        if (set_flag & (_MU | _C)) PLANTE("FORBIDDEN TO OVERWRITE Lij!");
        if (n>0 && n!=Lij.NumRows()) PLANTE("DIMENSION MISMATCH FOR Lij!");
        this->Lij = new Mat<LFLOAT>(Lij);
        this->n = Lij.NumRows();
        this->set_flag |= (_MU|_C);
    }
    void set_Rij(const Mat<LFLOAT>& Rij) {
        if (set_flag & (_MU | _C)) PLANTE("FORBIDDEN TO OVERWRITE Rij!");
        if (n>0 && n!=Rij.NumRows()) PLANTE("DIMENSION MISMATCH FOR Rij!");
        this->Rij = new Mat<LFLOAT>(Rij);
        this->n = Rij.NumRows();
        this->set_flag |= (_MU|_C);
    }
    void set_Bstar(const Mat<LFLOAT>& Bstar) {
        if (set_flag & (_C|_Q)) PLANTE("FORBIDDEN TO OVERWRITE Q!");
        if (n>0 && n!=Bstar.NumRows()) PLANTE("Row DIMENSION MISMATCH FOR Q!");
        if (m>0 && m!=Bstar.NumCols()) PLANTE("Col DIMENSION MISMATCH FOR Q!");
        this->Bstar=new Mat<LFLOAT>(Bstar);
        this->n=Bstar.NumRows();
        this->m=Bstar.NumCols();
        this->set_flag |= (_C|_Q);
    }
    
public:
    const Mat<LFLOAT>& get_mu() const {
        if (mu!=0) return *mu;
        if (Lij!=0) {
            Lij_to_mu();
            return *mu;
        }
        if (Rij!=0) {
            Rij_to_mu();
            return *mu;
        }
        PLANTE("Impossible de calculer mu!");
    }
    const Mat<LFLOAT>& get_Lij() const {
        if (Lij!=0) return *Lij;
        if (Rij!=0) {
            Rij_to_Lij();
            return *Lij;
        }
        if (mu!=0 && C==0 && Bstar!=0) get_C();
        if (mu!=0 && C!=0) {
            mu_C_to_Lij();
            return *Lij;
        }
        PLANTE("Impossible de calculer Lij!");
    }
    const Mat<LFLOAT>& get_Rij() const {
        if (Rij!=0) return *Rij;
        if (Lij!=0) {
            Lij_to_Rij();
            return *Rij;
        }
        if (mu!=0 && C==0 && Bstar!=0) get_C();
        if (mu!=0 && C!=0) {
            mu_C_to_Rij();
            return *Rij;
        }
        PLANTE("Impossible de calculer Rij!");
    }
    const Vec<LFLOAT>& get_C() const {
        if (C!=0) return *C;
        if (Rij!=0) { Rij_to_C(); return *C; }
        if (Lij!=0) { Lij_to_C(); return *C; }
        if (Bstar!=0) {Bstar_to_C(); return *C; }
        PLANTE("Impossible de calculer C");
    }
    const Mat<LFLOAT>& get_Bstar() const {
        if (Bstar!=0) return *Bstar;
        if (Q!=0 && C!=0) {Q_C_to_Bstar(); return *Bstar; }
        if (Q!=0 && (set_flag & _C)) {
            get_C();
            Q_C_to_Bstar();
            return *Bstar;
        }
        PLANTE("Impossible de calculer Bstar");
    }
    const Mat<LFLOAT>& get_Q() const {
        if (Q!=0) return *Q;
        if (Bstar!=0 && C!=0) {C_Bstar_to_Q(); return *Q; }
        PLANTE("Impossible de calculer Q");
    }
    
    
    
};

template<typename NUMERIC, typename LFLOAT>
void LQ_householder(const Mat<NUMERIC>& B,Mat<LFLOAT>& Lij, Mat<LFLOAT>& Q) {
    int n = B.NumRows();
    int m = B.NumCols();
    conv(Lij,B);
    Q.SetDims(n,m);
    Mat<LFLOAT> T; T.SetDims(m,m);
    Vec<LFLOAT> symv; symv.SetLength(m);
    ident(T,m);
    for (int i=1; i<=n; i++) {
        if (Lij(i,i)>0) {
            //negate the i-th column of L and T
            for (int j=1; j<=n; j++) Lij(j,i)=-Lij(j,i);
            for (int j=1; j<=m; j++) T(j,i)=-T(j,i);
        }
        //compute the partial norm
        LFLOAT nrm = 0;
        for (int j=i; j<=m; j++) nrm += sqr(Lij(i,j));
        nrm = sqrt(nrm);
        //compute the normal sym vector
        for (int j=1; j<i; j++) {symv(j)=0;}
        for (int j=i; j<=m; j++) {symv(j)=Lij(i,j); }
        symv(i) -= nrm;
        nrm=symv*symv;
        symv *= sqrt(2./nrm);
        //apply the symmetry to the block
        for (int k=i; k<=n; k++) {
            Lij(k) -= (Lij(k)*symv)*symv;
        }
        for (int k=1; k<=m; k++) {
            T(k) -= (T(k)*symv)*symv;
        }
    }
    //copy T into Q
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            Q(i,j)=T(j,i);
}
template<typename NUMERIC, typename LFLOAT>
void LQ_householder(const Mat<NUMERIC>& B,GSO<LFLOAT>& gso) {
    Mat<LFLOAT> Lij;
    Mat<LFLOAT> Q;
    LQ_householder(B,Lij,Q);
    gso.reset();
    gso.set_Lij(Lij);
    gso.set_Q(Q);
}


//size-reduit la base (precision RR)
//la matrice de gram schmidt Rij est renvoyée en sortie.
template<typename NUMERIC, typename LFLOAT>
void sizeReduction_householder(Mat<NUMERIC>& B, GSO<LFLOAT>& gso) {
    int n = B.NumRows();
    Mat<LFLOAT> Lij;
    Mat<LFLOAT> Q;
    LQ_householder(B,Lij,Q);
    for (int i=2; i<=n; i++) {
        for (int j=i-1; j>=1; j--){
            ZZ cZZ = RoundToZZ( Lij(i,j)/Lij(j,j)); 
            NUMERIC c; conv(c, cZZ);
            if (c!= 0) cerr <<". ";
            B(i)-= c*B(j);
            Lij(i) -= to<LFLOAT>(c)*Lij(j);
        }
    }
    gso.reset();
    gso.set_Lij(Lij);
    gso.set_Q(Q);
    cerr <<"end reduc "<<endl;
}

newNTL_CLOSE_NNS

#endif //NEWNTL_GSO_H

