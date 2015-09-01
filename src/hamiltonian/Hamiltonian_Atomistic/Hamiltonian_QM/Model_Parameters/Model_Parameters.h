/*********************************************************************************
* Copyright (C) 2015 Alexey V. Akimov
*
* This file is distributed under the terms of the GNU General Public License
* as published by the Free Software Foundation, either version 2 of
* the License, or (at your option) any later version.
* See the file LICENSE in the root directory of this distribution
* or <http://www.gnu.org/licenses/>.
*
*********************************************************************************/

#ifndef MODEL_PARAMETERS_H
#define MODEL_PARAMETERS_H


#include "../../../../qchem/libqchem.h"
using namespace libqchem;
using namespace libqchem::libqobjects;

#include "../Control_Parameters/libcontrol_parameters.h"
using namespace libhamiltonian::libhamiltonian_atomistic::libhamiltonian_qm::libcontrol_parameters;



namespace libhamiltonian{
namespace libhamiltonian_atomistic{
namespace libhamiltonian_qm{
namespace libmodel_parameters{





class HF_integrals{

  // HF - Coulomb and exchange integrals in AO basis
  struct data_element{
    int a, b, c, d;
    double J_abcd;
    double K_adcb; // !!! no, really - it should be adcb, not abcd here
  };

  vector<data_element> data;

  int find_data(int,int,int,int);  


  public:

  HF_integrals(){ ; ; }

  void set_JK_values(int,int,int,int,double, double);  
  void get_JK_values(int,int,int,int,double&,double&);  

  friend bool operator == (const HF_integrals& m1, const HF_integrals& m2){
    // Equal
    int res = 1;
    if(m1.data.size()!=m2.data.size()){  res = 0; }
    else{ 
      for(int i=0;i<m1.data.size();i++){  
        res *= (m1.data[i].a==m2.data[i].a);  
        res *= (m1.data[i].b==m2.data[i].b);  
        res *= (m1.data[i].c==m2.data[i].c);  
        res *= (m1.data[i].d==m2.data[i].d);  
        res *= (m1.data[i].J_abcd==m2.data[i].J_abcd);  
        res *= (m1.data[i].K_adcb==m2.data[i].K_adcb);  
      }
    }
    return  res;  
  }
  friend bool operator != (const HF_integrals& m1, const HF_integrals& m2){
    return  (!(m1==m2));
  }



};

typedef std::vector<HF_integrals > HF_integralsList;
typedef std::vector<vector<HF_integrals> > HF_integralsMap;



class EHT_K{
// This data type realizes a container for a bunch of K constants for EHT
// with some access methods

  struct data_element{
    // Example:   H  1s   Si  3s   1.34   K1_value
    std::string elt1;
    std::string orb_type1;
    std::string elt2;
    std::string orb_type2;

    // H_ij = 0.5*K*(H_ii+H_jj)*S_ij + (K1 + K2*S_ij/sqrt(1+R^2))
    double K_value;
    double K1_value; // units of energy
    double K2_value; // units of energy
    double K3_value; // units of energy
    double K4_value; // units of lengths

    double C0_value; // units of energy
    double C1_value; // units of energy/length
    double C2_value; // units of energy/length^2
    double C3_value; // units of energy/length^3
    double C4_value; // units of lengths

  };

  struct pp_data_element{

    std::string elt1;
    std::string orb_type1;

    double PPa_value; // units of 1/length
    double PP0_value; // units of energy
    double PP1_value; // units of energy/length
    double PP2_value; // units of energy/length^2

  };

  struct psps_data_element{

    int n1,n2,n3,n4;
    double K;
  };



  int find_data(std::string,std::string);  // in data
  int find_data(std::string,std::string,std::string,std::string); // in PP_data
  int find_data(int, int, int, int); // in PSPS_data
 


public:

  vector<data_element> data;  
  vector<pp_data_element> pp_data;  
  vector<psps_data_element> psps_data;


  EHT_K(){ ;; }

  void set_PSPS_value(int, int, int, int, double);

  void set_PPa_value(std::string, std::string, double ); 
  void set_PP0_value(std::string, std::string, double ); 
  void set_PP1_value(std::string, std::string, double ); 
  void set_PP2_value(std::string, std::string, double ); 

  double get_PPa_value(std::string, std::string ); 
  double get_PP0_value(std::string, std::string ); 
  double get_PP1_value(std::string, std::string ); 
  double get_PP2_value(std::string, std::string ); 



  void set_K_value(std::string,std::string,std::string,std::string, double);
  double get_K_value(std::string,std::string,std::string,std::string);

  void set_K1_value(std::string,std::string,std::string,std::string, double);
  double get_K1_value(std::string,std::string,std::string,std::string);

  void set_K2_value(std::string,std::string,std::string,std::string, double);
  double get_K2_value(std::string,std::string,std::string,std::string);

  void set_K3_value(std::string,std::string,std::string,std::string, double);
  double get_K3_value(std::string,std::string,std::string,std::string);

  void set_K4_value(std::string,std::string,std::string,std::string, double);
  double get_K4_value(std::string,std::string,std::string,std::string);



  void set_C0_value(std::string,std::string,std::string,std::string, double);
  double get_C0_value(std::string,std::string,std::string,std::string);

  void set_C1_value(std::string,std::string,std::string,std::string, double);
  double get_C1_value(std::string,std::string,std::string,std::string);

  void set_C2_value(std::string,std::string,std::string,std::string, double);
  double get_C2_value(std::string,std::string,std::string,std::string);

  void set_C3_value(std::string,std::string,std::string,std::string, double);
  double get_C3_value(std::string,std::string,std::string,std::string);

  void set_C4_value(std::string,std::string,std::string,std::string, double);
  double get_C4_value(std::string,std::string,std::string,std::string);


  friend bool operator == (const EHT_K& m1, const EHT_K& m2){
    // Equal
    int res = 1;
    if(m1.data.size()!=m2.data.size()){  res = 0; }
    else{ 
      for(int i=0;i<m1.data.size();i++){  
        res *= (m1.data[i].elt1==m2.data[i].elt1);  
        res *= (m1.data[i].orb_type1==m2.data[i].orb_type1);  
        res *= (m1.data[i].elt2==m2.data[i].elt2);  
        res *= (m1.data[i].orb_type2==m2.data[i].orb_type2);  

        res *= (m1.data[i].K_value==m2.data[i].K_value);  
        res *= (m1.data[i].K1_value==m2.data[i].K1_value);  
        res *= (m1.data[i].K2_value==m2.data[i].K2_value);  
        res *= (m1.data[i].K3_value==m2.data[i].K3_value);  
        res *= (m1.data[i].K4_value==m2.data[i].K4_value);  

        res *= (m1.data[i].C0_value==m2.data[i].C0_value);  
        res *= (m1.data[i].C1_value==m2.data[i].C1_value);  
        res *= (m1.data[i].C2_value==m2.data[i].C2_value);  
        res *= (m1.data[i].C3_value==m2.data[i].C3_value);  
        res *= (m1.data[i].C4_value==m2.data[i].C4_value);  

      }// for i
    }// m1.data

    if(m1.pp_data.size()!=m2.pp_data.size()){  res = 0; }
    else{ 
      for(int i=0;i<m1.pp_data.size();i++){  
        res *= (m1.pp_data[i].elt1==m2.pp_data[i].elt1);  
        res *= (m1.pp_data[i].orb_type1==m2.pp_data[i].orb_type1);  

        res *= (m1.pp_data[i].PPa_value==m2.pp_data[i].PPa_value);  
        res *= (m1.pp_data[i].PP0_value==m2.pp_data[i].PP0_value);  
        res *= (m1.pp_data[i].PP1_value==m2.pp_data[i].PP1_value);  
        res *= (m1.pp_data[i].PP2_value==m2.pp_data[i].PP2_value);  

      }// for i
    }// m1.pp_data

    if(m1.psps_data.size()!=m2.psps_data.size()){  res = 0; }
    else{ 
      for(int i=0;i<m1.psps_data.size();i++){  
        res *= (m1.psps_data[i].n1==m2.psps_data[i].n1);  
        res *= (m1.psps_data[i].n2==m2.psps_data[i].n2);  
        res *= (m1.psps_data[i].n3==m2.psps_data[i].n3);  
        res *= (m1.psps_data[i].n4==m2.psps_data[i].n4);
  
        res *= (m1.psps_data[i].K==m2.psps_data[i].K);  

      }// for i
    }// m1.pp_data

    return  res;  
  }

  friend bool operator != (const EHT_K& m1, const EHT_K& m2){
    return  (!(m1==m2));
  }



};

typedef std::vector<EHT_K > EHT_KList;
typedef std::vector<vector<EHT_K> > EHT_KMap;



class mEHT_K{

public:
  int size; // is the size of the matrix (N below - number of AOs in the basis)
  vector<double> eht_K;
  vector<double> eht_K1;   // eht_K1[I*N+J] = is the parameter for pair of orbitals I and J - each of special type and on special atom
  vector<double> eht_K2;
  vector<double> eht_K3;
  vector<double> eht_K4;

  vector<double> eht_C0;
  vector<double> eht_C1;   // eht_C1[I*N+J] = is the parameter for pair of orbitals I and J - each of special type and on special atom
  vector<double> eht_C2;
  vector<double> eht_C3;
  vector<double> eht_C4;

    
  // Atomic-orbital pseudopotential variables
  vector<vector<double> >  eht_PPa;    // Nnucl x Ntyp(this depends on nucleus)
  vector<vector<double> >  eht_PP0;
  vector<vector<double> >  eht_PP1;
  vector<vector<double> >  eht_PP2;




  mEHT_K(){  size = -1; }
  void set_mapping(EHT_K& k, const vector<AO>& basis);
  void set_mapping1(EHT_K& k, int nat, vector<std::string>& mol_at_types);

  inline double get_K_value( int I,int J){ return eht_K[I*size+J];  }
  inline double get_K1_value(int I,int J){ return eht_K1[I*size+J]; }
  inline double get_K2_value(int I,int J){ return eht_K2[I*size+J]; }
  inline double get_K3_value(int I,int J){ return eht_K3[I*size+J]; }
  inline double get_K4_value(int I,int J){ return eht_K4[I*size+J]; }

  inline double get_C0_value(int I,int J){ return eht_C0[I*size+J];  }
  inline double get_C1_value(int I,int J){ return eht_C1[I*size+J]; }
  inline double get_C2_value(int I,int J){ return eht_C2[I*size+J]; }
  inline double get_C3_value(int I,int J){ return eht_C3[I*size+J]; }
  inline double get_C4_value(int I,int J){ return eht_C4[I*size+J]; }


  friend bool operator == (const mEHT_K& m1, const mEHT_K& m2){
    // Equal
    int res = m1.size==m2.size;

    res *= (m1.eht_K==m2.eht_K);  
    res *= (m1.eht_K1==m2.eht_K1);  
    res *= (m1.eht_K2==m2.eht_K2);  
    res *= (m1.eht_K3==m2.eht_K3);  
    res *= (m1.eht_K4==m2.eht_K4);  

    res *= (m1.eht_C0==m2.eht_C0);  
    res *= (m1.eht_C1==m2.eht_C1);  
    res *= (m1.eht_C2==m2.eht_C2);  
    res *= (m1.eht_C3==m2.eht_C3);  
    res *= (m1.eht_C4==m2.eht_C4);  

    res *= (m1.eht_PPa==m2.eht_PPa);  
    res *= (m1.eht_PP0==m2.eht_PP0);  
    res *= (m1.eht_PP1==m2.eht_PP1);  
    res *= (m1.eht_PP2==m2.eht_PP2);  


    return  res;  
  }

  friend bool operator != (const mEHT_K& m1, const mEHT_K& m2){
    return  (!(m1==m2));
  }



};

typedef std::vector<mEHT_K > mEHT_KList;
typedef std::vector<vector<mEHT_K> > mEHT_KMap;



class Element{

  public:

  // General atomic properties
  std::string elt_name;   // element symbol  
  int Z;                  // nuclear charge
  int PQN;                // principal quantum number
  int Nval;               // effective number of electrons(e.g. valence electrons)  
  double Zeff;            // effective(screened) nuclear charge
  double mass;            // mass


  // EHT, CNDO, CNDO/2, INDO
  map<std::string,double> IP;   // Ionization potential for a given shell (first = 1s, 2s, 2p, ... 3d, so on)
  map<std::string,double> EA;   // Electron affinity for a given shell (first = 1s, 2s, 2p, ... 3d, so on)  


  map<std::string, int > Nquant;    // principal quantum number for each shell
  map<std::string, int> Nzeta;   // number of different zetas (exponents for given shell)
  map<std::string, vector<double> > zetas;  // zetas for each shell 
  map<std::string, vector<double> > coeffs; // coefficients for each shell

  map<std::string,double> J_param1; // in .../sqrt(r^2 + f(J_param1))
  map<std::string,double> J_param2; // in f'(J_param2)/sqrt(...)
  map<std::string,double> J_param3; // in .../sqrt(r^2 + f(J_param1))  - for el-nucl interaction
  map<std::string,double> J_param4; // in f'(J_param2)/sqrt(...)       - for el-nucl interaction



  // CNDO, CNDO/2, INDO
  map<std::string,double> G1,F2;    // Slater-Condon factors
  map<std::string,double> beta0;    // proportionality constants for off-diagonal matrix elements
  double Zeta;                  // exponent of the radial part of the STOs

  
  Element(){}
  Element(std::string en,int z,int nv,map<std::string, double> ip){ elt_name = en; Z = z; Nval = nv; IP = ip; }

  ~Element(){ 
     if(IP.size()>0) { IP.clear();}
     if(EA.size()>0) { EA.clear();}
   }

  void _set(std::string en,int z){ elt_name = en; Z = z;  }
  void _set(std::string en,int z,int nv){ elt_name = en; Z = z; Nval = nv; }
  void _set(std::string en,int z,int nv,double zeff){ elt_name = en; Z = z; Nval = nv; Zeff = zeff; }
  void _set(std::string en,int z,int nv,double zeff,map<std::string, double> ip){ elt_name = en; Z = z; Nval = nv; IP = ip; Zeff = zeff;}

  void set_mass(double m_){ mass = m_; }



  friend bool operator == (const Element& m1, const Element& m2){
    // Equal
    int res = m1.elt_name==m2.elt_name;

    res *= (m1.Z==m2.Z);  
    res *= (m1.PQN==m2.PQN);  
    res *= (m1.Nval==m2.Nval);  
    res *= (m1.Zeff==m2.Zeff);  
    res *= (m1.mass==m2.mass);  

    res *= (m1.IP==m2.IP);  
    res *= (m1.EA==m2.EA);  
    res *= (m1.Nquant==m2.Nquant);  
    res *= (m1.Nzeta==m2.Nzeta);  
    res *= (m1.zetas==m2.zetas);  
    res *= (m1.coeffs==m2.coeffs);  

    res *= (m1.J_param1==m2.J_param1);  
    res *= (m1.J_param2==m2.J_param2);  
    res *= (m1.J_param3==m2.J_param3);  
    res *= (m1.J_param4==m2.J_param4);  

    res *= (m1.G1==m2.G1);  
    res *= (m1.F2==m2.F2);  
    res *= (m1.beta0==m2.beta0);  
    res *= (m1.Zeta==m2.Zeta);  


    return  res;  
  }

  friend bool operator != (const Element& m1, const Element& m2){
    return  (!(m1==m2));
  }


};

typedef std::vector<Element > ElementList;
typedef std::vector<vector<Element> > ElementMap;



class OrbParams{

// Here we just keep parameters for a single orbital type (e.g. H(1s), Si(3p), etc.)

  public:

  // General atomic properties
  double IP, EA;
  int Nquant;             // principal quantum number for each shell
  int Nzeta;              // number of different zetas (exponents for given shell)
  vector<double> zetas;   // zetas for each shell 
  vector<double> coeffs;  // coefficients for each shell

  double J_param1; 
  double J_param2; 
  double J_param3; 
  double J_param4; 


  // CNDO, CNDO/2, INDO
  double G1,F2;          // Slater-Condon factors
  double beta0;          // proportionality constants for off-diagonal matrix elements

  
  OrbParams(){}

  ~OrbParams(){ 
     if(zetas.size()>0) { zetas.clear();}
     if(coeffs.size()>0) { coeffs.clear();}
  }

  friend bool operator == (const OrbParams& m1, const OrbParams& m2){
    // Equal
    int res = 1;

    res *= (m1.IP==m2.IP);  
    res *= (m1.EA==m2.EA);  
    res *= (m1.Nquant==m2.Nquant);  
    res *= (m1.Nzeta==m2.Nzeta);  
    res *= (m1.zetas==m2.zetas);  
    res *= (m1.coeffs==m2.coeffs);  

    res *= (m1.J_param1==m2.J_param1);  
    res *= (m1.J_param2==m2.J_param2);  
    res *= (m1.J_param3==m2.J_param3);  
    res *= (m1.J_param4==m2.J_param4);  

    res *= (m1.G1==m2.G1);  
    res *= (m1.F2==m2.F2);  
    res *= (m1.beta0==m2.beta0);  


    return  res;  
  }

  friend bool operator != (const OrbParams& m1, const OrbParams& m2){
    return  (!(m1==m2));
  }



};

typedef std::vector<OrbParams> OrbParamsList;
typedef std::vector<vector<OrbParams> > OrbParamsMap;





void set_default_elements(map<std::string,Element>&);


class Model_Parameters{

public:
//---------- Members --------

  // Parameters for semiempirical methods
  // Atomic parameters
  map<std::string,Element> PT;    // General and specific (for a given method) atomic parameters
  vector<OrbParams> orb_params;   // properties all orbitals!

  // Pair parameters
  EHT_K  eht_k;                   // K values for EHT

  // Mapped variables - for greater efficiency
  mEHT_K meht_k;                  // mapped EHT parameters

  


  HF_integrals  hf_int;           // precomputed J and K integrals in given basis

//  vector<double> eri;    // precomputed electron repulsion integrals - for all atoms
//  vector<> V_A

  
  //-------------- Constructor --------------
  Model_Parameters(){  
    set_default_elements(PT);
  }

  void set_PT_mapping(const vector<AO>&);

};


void set_parameters_eht(Control_Parameters&, Model_Parameters&);
void set_parameters_hf(Control_Parameters&, Model_Parameters&, vector<AO>&);
void set_parameters_indo(Control_Parameters&, Model_Parameters&);
void set_parameters_geht1(Control_Parameters& prms, Model_Parameters& modprms); // Model_Parameters_GEHT.cpp
void set_parameters_geht2(Control_Parameters& prms, Model_Parameters& modprms); // Model_Parameters_GEHT2.cpp

void set_parameters_eht_mapping(Model_Parameters& modprms, const vector<AO>& basis_ao);
void set_parameters_eht_mapping1(Model_Parameters& modprms, int nat, vector<std::string>& mol_at_types);



}// namespace libmodel_parameters
}// namespace libhamiltonian_qm
}// namespace libhamiltonian_atomistic
}// namespace libhamiltonian




#endif // MODEL_PARAMETERS_H
