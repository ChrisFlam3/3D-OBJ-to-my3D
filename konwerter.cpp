#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "windows.h"
using namespace std;
class sub{
public:
int matnum;
int vcount;
int fcount;
int fstart;
int vstart;

};
int main(){
ifstream klucz;
ifstream kluczmtl;
ofstream wyjscie;
klucz.open("vena2.obj");
kluczmtl.open("vena2.mtl");
wyjscie.open("konwersja.txt");
string a;
string b;




int linia=0;

int ilev=0;
int ilef=0;
int subset=0;
int material=0;
int wsk;
int wsk2;




for(int i=0;i<1000000;i++){
getline(klucz,a);
if(a[0]=='v'&&a[1]==' ')
 ilev++;

 if(a[0]=='f'&&a[1]==' ')
 ilef++;

string subsets;
subsets=a.substr(0,6);

if(subsets=="usemtl")
    subset++;
}


for(int i=0;i<1000;i++){
getline(kluczmtl,b);
if(b[0]=='n'&&b[1]=='e')
material++;


}




cout<<ilev<<endl;
cout<<ilef<<endl;
cout<<subset<<endl;
cout<<material<<endl;
wyjscie<<"***************m3d-File-Header***************"<<endl;
wyjscie<<"#Materials "<<material<<endl;
wyjscie<<"#Subsets "<<subset<<endl;
wyjscie<<"#Vertices ";
wsk=wyjscie.tellp();
wyjscie<<endl;
wyjscie<<"#Triangles "<<ilef<<endl;
wyjscie<<"#Bones 0"<<endl;
wyjscie<<"#AnimationClips 0"<<endl;
wyjscie<<"***************Materials*********************"<<endl;



kluczmtl.close();
kluczmtl.open("vena2.mtl");
string ambient;
string diffuse;
string specular;
string specpower;
string diffusemap;


for(int i=0;i<10000;i++){
 getline(kluczmtl,b);


b.erase(0,1);

if(b[0]=='N'&&b[1]=='s')
specpower=b.substr(2);

if(b[0]=='K'&&b[1]=='a')
    ambient=b.substr(2);

if(b[0]=='K'&&b[1]=='d')
    diffuse=b.substr(2);

if(b[0]=='K'&&b[1]=='s')
    specular=b.substr(2);

if(b[0]=='K'&&b[1]=='e'){
    getline(kluczmtl,b);
    b.erase(0,1);
    cout<<b<<endl;
if(b.substr(0,6)=="map_Ka"){

int pozycja=0;
    pozycja=b.rfind('\\');
    diffusemap=b.substr(pozycja+1);}


wyjscie<<"Ambient: "<<ambient<<endl;
wyjscie<<"Diffuse: "<<diffuse<<endl;
wyjscie<<"Specular "<<specular<<endl;
wyjscie<<"SpecPower: "<<specpower<<endl;
wyjscie<<"Reflectivity: 0 0 0"<<endl;
wyjscie<<"AlphaClip: 1"<<endl;
wyjscie<<"Effect: Normal"<<endl;
wyjscie<<"DiffuseMap: "<<diffusemap;
if(diffusemap=="")
    wyjscie<<"-"<<endl;
else
    wyjscie<<endl;
wyjscie<<"NormalMap: -"<<endl;
wyjscie<<endl;


}



}
klucz.close();
klucz.open("vena2.obj");

string v[200000];
string *vn;
vn=new string [200000];
string vt[200000];
string mat[1000];
int posmat=0;

string *face;
face=new string[1000000];
sub *s;
s=new sub[subset];
int currs=0;
int currw=0;
int numv=0;
int numf=0;
int spr=0;
int spr1=0;
int spr2=0;
int bez=0;
int l=0;
int l1=0;
int l2=0;
for(int i=0;i<1000000;i++){
     getline(klucz,a);
     if(a[0]=='v'&&a[1]==' '){
    v[l]=a;

     l++;}

     if(a[0]=='v'&&a[1]=='n'){
        vn[l1]=a;
     l1++;}

      if(a[0]=='v'&&a[1]=='t'){
        vt[l2]=a;
     l2++;}





}

wyjscie<<"***************SubsetTable*******************"<<endl;
wsk2=wyjscie.tellp();

wyjscie<<"***************Vertices**********************"<<endl;

kluczmtl.close();
kluczmtl.open("vena2.mtl");
for(int i=0;i<10000;i++){
    getline(kluczmtl,b);

    if(b.substr(0,6)=="newmtl"){
        mat[posmat]=b.substr(7);
        posmat++;

    }






    }




klucz.close();
klucz.open("vena2.obj");
for(int i=0;i<1000000;i++){
    getline(klucz,a);

if(a.substr(0,6)=="usemtl"){

    string m=a.substr(7);
    for(int i=0;i<1000;i++){
        if(m==mat[i]){
        s[currs].matnum=i;

        }
    }

}

if(a.substr(0,6)=="usemtl"&&currs!=0){

s[currs-1].vcount=numv;
numv=0;
s[currs-1].fcount=numf;
numf=0;
s[currs].vstart=s[currs-1].vstart+s[currs-1].vcount;
s[currs].fstart=s[currs-1].fstart+s[currs-1].fcount;
currs++;


}

if(a.substr(0,6)=="usemtl"&&currs==0){
s[currs].vstart=0;
s[currs].fstart=0;
currs++;
}

if(a.substr(0,1)=="#"&&currs==subset&&bez==0){
cout<<a<<"   "<<numv<<"  "<<numf<<"   "<<currs<<"  "<<bez<<endl;
s[currs-1].vcount=numv;


s[currs-1].fcount=numf;


bez=1;


}



if(a.substr(0,1)=="f"){
        numf++;
        int p1;
        int p2;
        int p3;
        int p4;
        int p5;
        int p6;
        int p7;
        int p8;
        int p9;
        p1=a.find("/",0);
        p2=a.find("/",p1+1);
        p3=a.find(" ",2);
        p4=a.find("/",p3);
        p5=a.find("/",p4+1);
        p6=a.find(" ",p5);
        p7=a.find("/",p6);
        p8=a.find("/",p7+1);
        p9=a.find(" ",p8);
if(currw<1000){
for(int i=0;i<1000;i++){
   if(a.substr(2,p3-2)==face[i])
        spr=1;

  if(a.substr(p3+1,p6-p3-1)==face[i])
       spr1=1;

if(a.substr(p6+1,p9-p6-1)==face[i])
       spr2=1;

}}
else{
for(int i=currw-1000;i<currw;i++){
   if(a.substr(2,p3-2)==face[i]){
        spr=1;}


  if(a.substr(p3+1,p6-p3-1)==face[i])
       spr1=1;

    if(a.substr(p6+1,p9-p6-1)==face[i])
       spr2=1;

}
}










if(spr==0){
 face[currw]=a.substr(2,p3-2);
 currw++;

 stringstream konwersja(a.substr(2,p1-2));
 int liczba1;
 konwersja>>liczba1;
 liczba1--;


 stringstream konwersja1(a.substr(p1+1,p2-p1));
 int liczba2;
 konwersja1>>liczba2;
 liczba2--;

 stringstream konwersja2(a.substr(p2+1,p3-p2));
 int liczba3;
 konwersja2>>liczba3;
 liczba3--;

int wazne=vt[liczba2].find(" ",15);

wyjscie<<"Position: "<<v[liczba1].substr(3)<<endl;

wyjscie<<"Tangent: 0 0 0 0"<<endl;
 wyjscie<<"Normal: "<<vn[liczba3].substr(3)<<endl;
 wyjscie<<"Tex-Coords: "<<vt[liczba2].substr(3,wazne-3)<<endl;
 wyjscie<<endl;
numv++;
}else
spr=0;

if(spr1==0){
 face[currw]=a.substr(p3+1,p6-p3-1);
 currw++;

 stringstream konwersja(a.substr(p3+1,p4-p3));
 int liczba1;
 konwersja>>liczba1;
 liczba1--;

 stringstream konwersja1(a.substr(p4+1,p5-p4));
 int liczba2;
 konwersja1>>liczba2;
 liczba2--;

 stringstream konwersja2(a.substr(p5+1,p6-p5));
 int liczba3;
 konwersja2>>liczba3;
 liczba3--;


int wazne=vt[liczba2].find(" ",15);
wyjscie<<"Position: "<<v[liczba1].substr(3)<<endl;
wyjscie<<"Tangent: 0 0 0 0"<<endl;
 wyjscie<<"Normal: "<<vn[liczba3].substr(3)<<endl;
 wyjscie<<"Tex-Coords: "<<vt[liczba2].substr(3,wazne-3)<<endl;
 wyjscie<<endl;
numv++;
}else
spr1=0;

if(spr2==0){
 face[currw]=a.substr(p6+1,p9-p6-1);
 currw++;


 stringstream konwersja(a.substr(p6+1,p7-p6));
 int liczba1;
 konwersja>>liczba1;
 liczba1--;

 stringstream konwersja1(a.substr(p7+1,p8-p7));
 int liczba2;
 konwersja1>>liczba2;
 liczba2--;

 stringstream konwersja2(a.substr(p8+1,p9-p8));
 int liczba3;
 konwersja2>>liczba3;
 liczba3--;

int wazne=vt[liczba2].find(" ",15);

wyjscie<<"Position: "<<v[liczba1].substr(3)<<endl;
wyjscie<<"Tangent: 0 0 0 0"<<endl;
 wyjscie<<"Normal: "<<vn[liczba3].substr(3)<<endl;
 wyjscie<<"Tex-Coords: "<<vt[liczba2].substr(3,wazne-3)<<endl;
 wyjscie<<endl;
numv++;
}else
spr2=0;
}
}




wyjscie.seekp(wsk);
wyjscie<<currw<<endl;
wyjscie.seekp(0,ios::end);
wyjscie<<"***************Triangles*********************"<<endl;
klucz.close();
klucz.open("vena2.obj");
int num=0;
int pamiec=1000;
for(int i=0;i<1000000;i++){
        int f=-1;
        int f1=-1;
        int f2=-1;

    getline(klucz,a);
       int po=a.find(" ",2);
       int po1=a.find(" ",po+1);
       int po2=a.find(" ",po1+1);
       int po3=a.find("/",0);


    if(a.substr(0,1)=="f"){
            num++;

    stringstream kon(a.substr(2,po3-2));
       int l;
       kon>>l;

for(int i=pamiec-1000;i<pamiec+1000;i++){
   if(a.substr(2,po-2)==face[i])
    f=i;

    if(a.substr(po+1,po1-po-1)==face[i])
    f1=i;

    if(a.substr(po1+1,po2-po1-1)==face[i]){
    f2=i;
if(i>1000)
pamiec=i;}
if(f!=-1&&f1!=-1&&f2!=-1)
    break;
}
if(f==-1||f1==-1||f2==-1){
  for(int i=0;i<350000;i++){
   if(a.substr(2,po-2)==face[i]){
    f=i;
    cout<<a.substr(2,po-2)<<"    "<<face[i]<<"    "<<i<<"   "<<num<<endl;
   }
    if(a.substr(po+1,po1-po-1)==face[i]){
    f1=i;
cout<<a.substr(po+1,po1-po-1)<<"    "<<face[i]<<"    "<<i<<"   "<<num<<endl;
}
    if(a.substr(po1+1,po2-po1-1)==face[i]){
    f2=i;
cout<<a.substr(po1+1,po2-po1-1)<<"    "<<face[i]<<"    "<<i<<"   "<<num<<endl;
pamiec=i;
}
if(f!=-1&&f1!=-1&&f2!=-1)
    break;
}
}

}





if(f!=-1&&f1!=-1&&f2!=-1){
wyjscie<<f<<" "<<f1<<" "<<f2<<endl;
f=-1;
f1=-1;
f2=-1;
}
}


wyjscie.seekp(wsk2);
        ofstream wyjscie2;
wyjscie2.open("konwersjas.txt");
for(int i=0;i<subset;i++){

wyjscie2<<"SubsetID: "<<i<<" "<<"VertexStart: "<<s[i].vstart<<" "<<"VertexCount: "<<s[i].vcount<<" "<<"FaceStart: "<<s[i].fstart<<" "<<"FaceCount: "<<s[i].fcount<<" "<<"Mat: "<<s[i].matnum<<endl;

}

return 0;
}
