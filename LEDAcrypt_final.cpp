#include <iostream>
#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <stdint.h>
#include <bitset>
#include <math.h>
#include <cmath>
#include <set>
#include <ctime>
#include <fstream>
using namespace std;

const int p = 25;
bitset<p> random_bitset(int w){
    int r;
    bitset<p> test_bitset;
    for ( int i = 0; i < p; i++){
        test_bitset[i]=0;
    }
    for ( int i = 0; i < w; i++){
        r=rand()%p;
        if(test_bitset[r]==1){i--;}else{test_bitset[r]=1;}
    }
    return test_bitset;
}

int main(){
    srand(static_cast<unsigned int>(time(0)));
    const int n0 = 2;
    const int dv = 3;
    const int bh = 10;
    const int bq = 10;
    const int m0 = 2;
    const int m1 = 1;
    const int n = p * n0;
    const int Tt = 1;
    bitset<p> h[n0];
    check:
    for ( int i = 0; i < n; i++){
        h[i/p][i%p]=0;
    }
    int r;
    for ( int i = 0; i < dv; i++){
        r=rand()%p;
        if(h[0][r]==1){i--;}else{h[0][r]=1;}
    }
    for ( int i = 0; i < dv; i++){
        r=rand()%p;
        if(h[1][r]==1){i--;}else{h[1][r]=1;}
    }
    int HM[n0][p][p];
    int Q[n0][n0][p][p];
    int a = 0;
    int s = 0;
    int d = 0;
    int t = 0;
    int b = 0;
    for ( int i = 0; i < n0; i++) {
        a+=h[i].count();
    };
    if (a!=2*dv){cout<<"wrong weight"<<endl;}else{
        for ( int i = 0; i < n0; i++){
            s=0;
            for ( int j = 0; j < p; j++){
                for ( int k = p-1; k >= 0; k--){
                    HM[i][j][k]=(h[i])[(p-1-k+s)%p];
                }
                s++;

            }
        }
        bitset<p> test_bitset;
        test_bitset = random_bitset(m0);
        s = 0;
        for ( int i = 0; i < p; i++){
            for ( int j = p-1; j >= 0; j--){
                Q[0][0][i][j] = test_bitset[(p-1-j+s)%p];
            }
            s++;

        }
        test_bitset = random_bitset(m1);

        s = 0;
        for ( int i = 0; i < p; i++){
            for ( int j = p-1; j >= 0; j--){
                Q[0][1][i][j] = test_bitset[(p-1-j+s)%p];
            }
            s++;

        }
        test_bitset = random_bitset(m1);
        s = 0;
        for ( int i = 0; i < p; i++){
            for ( int j = p-1; j >= 0; j--){
                Q[1][0][i][j] = test_bitset[(p-1-j+s)%p];
            }
            s++;

        }
        test_bitset = random_bitset(m0);
        s = 0;
        for ( int i = 0; i < p; i++){
            for ( int j = p-1; j >= 0; j--){
                Q[1][1][i][j] = test_bitset[(p-1-j+s)%p];
            }
            s++;
        }

        int HM1[n0][p][p];
        int Q1[n0][n0][p][p];
        int L1[n0][p][p];
        bitset<p> h1[n0];
        int ind;
        int dop;
        int sumL;
        int L[n0][p][p];
        int L_res[n0][p][p];
        int mat_sum = 1;
        bool is_det_zero;
        int res_mat[p][p];
        int M[n0][p][p];
        for ( int i = 0; i < p; i++){
            for ( int j = 0; j < n; j++){
                s = 0;
                for ( int k = 0; k < n; k++){
                    s += HM[k/p][i][k%p] * Q[k/p][j/p][k%p][j%p];
                }
                L[j/p][i][j%p] = s%2;
            }
        }
        int l_0_weight = 0;
        int l_1_weight = 0;
        int l_0_weight_new = 0;
        int l_1_weight_new = 0;
        int m_weight = 0;
        for ( int i = 0; i < p; i++){
            l_0_weight += L[0][0][i];
            l_1_weight += L[1][0][i];
        }
        int mat1[p][p];
        int rev[p][p];
        for ( int i = 0; i < p; i++){
            for ( int j = 0; j < p; j++){
                mat1[i][j] = L[n0-1][i][j];
            }
        }
        for ( int i = 0; i < p; i++){
            for ( int j = 0; j < p; j++){
                rev[i][j]=0;
            }
        }
        for ( int i = 0; i < p; i++){rev[i][i]=1;}
        for ( int i = 0; i < p; i++){
            t=mat1[i][i];
            if(t==0){
                d=0;
                while(t==0){
                    d++;
                    t=mat1[i+d][i];
                    if(i+d>=p){cout<<"det=0"<<endl; goto check;}
                }
                for ( int j = 0; j < p; j++){
                    b=mat1[i+d][j]; mat1[i+d][j]=mat1[i][j]; mat1[i][j]=b;
                    b=rev[i+d][j]; rev[i+d][j]=rev[i][j]; rev[i][j]=b;
                }
            };
            for ( int k = i+1; k < p; k++){
                t=mat1[k][i];
                for ( int j = 0; j < p; j++){
                    mat1[k][j]=abs((mat1[k][j]-t*mat1[i][j])%2);
                    rev[k][j]=abs((rev[k][j]-t*rev[i][j])%2);
                }
            }
        }
        for ( int i = p-2; i >= 0; i--){
            for ( int j = i+1; j < p; j++){
                t=mat1[i][j];
                if (t!=0){
                    for ( int k = 0; k < p; k++){
                        mat1[i][k]=abs((mat1[i][k]-t*mat1[j][k])%2);
                        rev[i][k]=abs((rev[i][k]-t*rev[j][k])%2);
                    }
                }
            }
        }

        for ( int k = 0; k < n0; k++){
            for ( int i = 0; i < p; i++){
                for ( int j = 0; j < p; j++){
                    s = 0;
                    for ( int i1 = 0; i1 < p; i1++){
                        s += L[n0 - k - 1][i1][j] * rev[i][i1];
                    }
                    M[k][j][i] = s%2;
                }
            }
        }
        for ( int i = 0; i < p; i++){
            m_weight += M[1][0][i];
        }
        bitset<n> c1;
        bitset<n> c;
        bitset<n> e;
        bitset<n> cI;
        bitset<p> mes;
        bitset<p> mes1;
        int l1[n];
        set<int> IS;
        set<int> IS1;
        int resv[p];
        int G1[p][p];
        int attempt = 0;
        while (mat_sum > 0 and attempt <= 20000){
            is_det_zero = false;
            attempt++;
            for ( int i = 0; i < n-p; i++) {
                mes[i] = rand()%2;
            };

            for ( int i = 0; i < n; i++){
                s = 0;
                for ( int j = 0; j < n-p; j++){
                    s += M[i/p][j][i%p] * mes[n-p-j-1];
                }
                c1[i] = s%2;
            }
            for ( int i = 0; i < n; i++){
                e[n-i-1]=0;
            }
            for ( int i = 0; i < Tt; i++){
                s=rand()%n;
                if(e[s]==1){i--;}else{e[s]=1;}
            }
            for ( int i = 0; i < n; i++){c[i]=(c1[i]+e[i])%2;}

            IS.clear();
            IS1.clear();
            //---------------------------------------------------------

            for ( int i = 0; i < n; i++){
                h1[i/p][i%p]=0;
            }
            for ( int i = 0; i < bh; i++){
                r=rand()%p;
                if(h1[0][r]==1){i--;}
                else{
                    h1[0][r]=1;
                }
            }
            for ( int i = 0; i < bh; i++){
                r=rand()%p;
                if(h1[0][r]==1){i--;}
                else{
                    h1[1][r]=1;
                }
            }
            for ( int i = 0; i < n0; i++){
                s=0;
                for ( int j = 0; j < p; j++){
                    for ( int k = p-1; k >= 0; k--){
                        HM1[i][j][k]=(h1[i])[(p-1-k+s)%p];
                    }
                    s++;
                }
            }
            test_bitset = random_bitset(bq);
            s = 0;
            for ( int i = 0; i < p; i++){
                for ( int j = p-1; j >= 0; j--){
                    Q1[0][0][i][j] = test_bitset[(p-1-j+s)%p];
                }
                s++;
            }
            test_bitset = random_bitset(bq);
            s = 0;
            for ( int i = 0; i < p; i++){
                for ( int j = p-1; j >= 0; j--){
                    Q1[0][1][i][j] = test_bitset[(p-1-j+s)%p];
                }
                s++;
            }
            test_bitset = random_bitset(bq);
            s = 0;
            for ( int i = 0; i < p; i++){
                for ( int j = p-1; j >= 0; j--){
                    Q1[1][0][i][j] = test_bitset[(p-1-j+s)%p];
                }
                s++;
            }
            test_bitset = random_bitset(bq);
            s = 0;
            for ( int i = 0; i < p; i++){
                for ( int j = p-1; j >= 0; j--){
                    Q1[1][1][i][j] = test_bitset[(p-1-j+s)%p];
                }
                s++;
            }
            for ( int i = 0; i < p; i++){
                for ( int j = 0; j < n; j++){
                    s = 0;
                    for ( int k = 0; k < n; k++){
                        s += HM1[k/p][i][k%p] * Q1[k/p][j/p][k%p][j%p];
                    }
                    L1[j/p][i][j%p] = s%2;
                }

            }
            s = 0;
            ind = 0;
            sumL = 0;
            for ( int i = 0; i < p; i++){sumL += L1[0][0][i];}
            dop = int(p/2)-(p-sumL);
            while(s<int(p/2)){
                if (L1[0][0][ind] == 0){IS.insert(ind+1); s++;}
                else{
                    if(dop>0){IS.insert(ind+1); dop--; s++;}
                }
                ind++;
            }
            s = 0;
            ind = 0;
            sumL = 0;
            for ( int i = 0; i < p; i++){sumL += L1[1][0][i];}
            dop = int((p+1)/2)-(p-sumL);
            while(s<int((p+1)/2)){
                if (L1[1][0][ind] == 0){IS.insert(ind+p+1); s++;}
                else{
                    if(dop>0){IS.insert(ind+p+1); dop--; s++;}
                }
                ind++;
            }
            set <int> :: iterator iter=IS.begin();
            iter = IS.begin();
            for ( int j = 0; j < p; j++){
                s = *iter - 1;
                for ( int i = 0; i < p; i++){
                    G1[i][j] = M[int(s)/p][i][int(s)%p];
                }
                l1[s] = 0;
                iter++;
            }
            for ( int i = 0; i < p; i++){
                for ( int j = 0; j < p; j++){
                    mat1[i][j] = G1[i][j];
                }
            }
            for ( int i = 0; i < p; i++){
                for ( int j = 0; j < p; j++){
                    rev[i][j]=0;
                }
            }
            for ( int i = 0; i < p; i++){rev[i][i]=1;}
            for ( int i = 0; i < p; i++){
                t=mat1[i][i];
                if(t==0){
                    d=0;
                    while(t==0){
                        d++;
                        t=mat1[i+d][i];
                        if(i+d>=p){ is_det_zero = true; break;}
                    }
                    if (is_det_zero){break;}
                    for ( int j = 0; j < p; j++){
                        b=mat1[i+d][j]; mat1[i+d][j]=mat1[i][j]; mat1[i][j]=b;
                        b=rev[i+d][j]; rev[i+d][j]=rev[i][j]; rev[i][j]=b;
                    }
                };
                if (is_det_zero){break;}
                for ( int k = i+1; k < p; k++){
                    t=mat1[k][i];
                    for ( int j = 0; j < p; j++){
                        mat1[k][j]=abs((mat1[k][j]-t*mat1[i][j])%2);
                        rev[k][j]=abs((rev[k][j]-t*rev[i][j])%2);
                    }
                }
            }
            if (is_det_zero == false){
                for ( int i = p-2; i >= 0; i--){
                    for ( int j = i+1; j < p; j++){
                        t=mat1[i][j];
                        if (t!=0){
                            for ( int k = 0; k < p; k++){
                                mat1[i][k]=abs((mat1[i][k]-t*mat1[j][k])%2);
                                rev[i][k]=abs((rev[i][k]-t*rev[j][k])%2);
                            }
                        }
                    }
                }
                iter = IS.begin();
                for ( int i = 0; i < p; i++){
                    s = 0;
                    for ( int j = 0; j < p; j++){
                        s += cI[j] * rev[j][i];
                    }
                    mes1[i] = s%2;
                }
                for ( int i = 1; i <= n; i++){
                    if(IS.count(i) == 0){IS1.insert(i);};
                }
                for ( int i = 0; i < p; i++){
                    iter = IS1.begin();
                    for ( int j = 0; j < p; j++){
                        mat1[i][j] = M[(*iter - 1)/p][i][(*iter - 1)%p];
                        iter++;
                    }
                }
                iter = IS1.begin();
                for ( int i = 0; i < p; i++){
                    l1[*iter - 1] = 1;
                    iter++;
                }
                a = 0;
                for ( int i = 0; i < p-1+a; i++){
                    t=mat1[i-a][i];
                    if(t==0){
                        d=0;
                        while(t==0 and d<p-i+a){
                            d++;
                            t=mat1[i+d-a][i];
                        }
                        if(d<p-i+a){
                            for ( int j = 0; j < p; j++){
                                b=mat1[i+d-a][j]; mat1[i+d-a][j]=mat1[i-a][j]; mat1[i-a][j]=b;
                            }
                        }
                    };
                    if(d<p-i+a){
                        for ( int k = i+1; k < p; k++){
                            t=mat1[k-a][i];
                            for ( int j = 0; j < p; j++){
                                mat1[k-a][j]=abs((mat1[k-a][j]-t*mat1[i-a][j])%2);
                            }
                        }
                    }else{a = 1;}
                }
                for ( int i = p-1; i >= 0; i--){
                    for ( int j = i; j < p; j++){
                        t=mat1[i][j];
                        if (t!=0){
                            for ( int k = i-1; k >= 0; k--){
                                if (mat1[k][j] != 0){
                                    for ( int k1 = i; k1 < p; k1++){
                                        mat1[k][k1]=(mat1[k][k1]+mat1[i][k1])%2;
                                    }
                                }
                            }
                        }
                    }
                }
                for ( int i = p-2; i >= 0; i--){
                    iter = IS1.begin();
                    s = 0;
                    for ( int j = 0; j < p; j++){
                        if (mat1[i][j] == 1){s++; a = j+1;}
                    }
                    if (s == 1){
                        for ( int j = 0; j < a-1; j++){iter++;}
                        l1[*iter-1] = 0;
                    }
                }
                for ( int i = 0; i < p; i++){
                    for ( int j = 0; j < n; j++){
                        L_res[j/p][i][j%p] = l1[(j+i)%p + (j/p)*p];
                    }
                }
                l_0_weight_new = 0;
                l_1_weight_new = 0;
                for ( int i = 0; i < p; i++){
                    l_0_weight_new += L_res[0][0][i];
                    l_1_weight_new += L_res[1][0][i];
                }
                mat_sum = 0;
                for ( int i = 0; i < p; i++){
                    for ( int j = 0; j < p; j++){
                        s = 0;
                        for ( int k = 0; k < n; k++){
                            s += L_res[k/p][i][k%p] * M[k/p][j][k%p];
                        }
                        res_mat[i][j] = s%2;
                        mat_sum += s%2;
                    }
                }
            }
        }
        if (attempt == 20001){cout<<"Can't find Information Set"<<endl;}else{
            cout<<"H0 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (HM[0][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != dv){cout<<" + ";}
                }
            }
            cout<<endl<<"H1 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (HM[1][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != dv){cout<<" + ";}
                }
            }
            cout<<endl<<"Q00 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (Q[0][0][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != m0){cout<<" + ";}
                }
            }
            cout<<endl<<"Q01 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (Q[0][1][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != m1){cout<<" + ";}
                }
            }
            cout<<endl<<"Q10 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (Q[1][0][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != m1){cout<<" + ";}
                }
            }
            cout<<endl<<"Q11 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (Q[1][1][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != m0){cout<<" + ";}
                }
            }
            cout<<endl<<"L0 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (L[0][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != l_0_weight){cout<<" + ";}
                }
            }
            cout<<endl<<"L1 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (L[1][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != l_1_weight){cout<<" + ";}
                }
            }
            cout<<endl<<"M0 = 1";
            cout<<endl<<"M1 = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (M[1][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != m_weight){cout<<" + ";}
                }
            }
            cout<<endl<<"attempt = "<<attempt;
            set <int> :: iterator iter=IS.begin();
            cout<<endl<<"Information set =";
            for ( int i = 0; i < p; i++){
                cout<<" "<<*iter;
                iter++;
            }
            cout<<endl<<"L0_new = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (L_res[0][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != l_0_weight_new){cout<<" + ";}
                }
            }
            cout<<endl<<"L1_new = ";
            s = 0;
            for ( int i = 0; i < p; i++){
                if (L_res[1][0][i] == 1){
                    if (i == 0){cout<<"1";}else{if(i == 1){cout<<"x";}else{cout<<"x^"<<i;}}
                    s++;
                    if (s != l_1_weight_new){cout<<" + ";}
                }
            }
        }
    }
    return 0;
}




