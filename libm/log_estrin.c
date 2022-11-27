#include "rlibm.h"
#include "log.h"
#include <math.h>

#define LN2HIGH 0.69314718055994528622676398299518041312694549560546875

double rlibm_log_estrin(float x) {
  float_x fix, fit;
  fix.f = x;
  int m = 0;
  
  if (x == 1.0) return 0.0;
  
  if (fix.x < 0x800000 || fix.x >= 0x7F800000) {
    if ((fix.x & 0x7FFFFFFF) == 0) { // log(+/-0) = -infty
      fix.x = 0xFF800000;
      return fix.f;
    }
    
    if (fix.x > 0x7FFFFFFF) return (x - x) / 0; // Log(-val) = NaN
    if (fix.x >= 0x7F800000) return x + x;
    fix.f *= 8.388608e+06;
    m -= 23;
  }
  
  m += fix.x >> 23;
  m -= 127;
  fix.x &= 0x007FFFFF;
  fix.x |= 0x3F800000;
  
  fit.x = fix.x & 0x007F0000;
  int FIndex = fit.x >> 16;
  fit.x |= 0x3F800000;
  
  double f = fix.f - fit.f;
  f *= log_oneByF[FIndex];
  
  // Find the index of polynomial coefficients
  double_x dX;
  dX.d = f;
  double y;
  
  if (f < 2.6440486729702099115424385189498934778384864330291748046875e-03) {
    if(f == 1.3731547764369419952629192138715552573557943105697631835937500000000000e-03) {
        y = 1.3722128615825670509137390595810757076833397150039672851562500000000000e-03;
    } else if(f == 1.7966015845941743847569149750142969423905014991760253906250000000000000e-03){
        y = 1.7949896263776412511786739756303177273366600275039672851562500000000000e-03;
    } else if(f == 1.8763504629060038294413592652176703268196433782577514648437500000000000e-03){
        y = 1.8745923162975519637996058008866384625434875488281250000000000000000000e-03;
    } else if(f == 1.9371839073615347397161468023796260240487754344940185546875000000000000e-03){
        y = 1.9353099863135827477661488060789451992604881525039672851562500000000000e-03;
    } else if(f == 2.6190722430193863652647667805695164133794605731964111328125000000000000e-03){
        y = 2.6156484501205783284316641612576859188266098499298095703125000000000000e-03;
    } else{
        y = f*9.9999999999999478195178426176426000893115997314453125000000000000000000e-01;
        y += f*f*(-4.9999999484153828666066488040087278932332992553710937500000000000000000e-01 + f*3.3332678431978252087120040414447430521249771118164062500000000000000000e-01);
        y += f*f*f*f*-2.4772062796356214553483710005821194499731063842773437500000000000000000e-01;
    }
  } else {
    if(f == 2.8749663254310346173492352050971021526493132114410400390625000000000000e-03){
        y = 2.8708408002322276415807511540378982317633926868438720703125000000000000e-03;
    } else if(f == 3.7279721707274009363797251381811292958445847034454345703125000000000000e-03){
        y = 3.7210405045140786291224532789101431262679398059844970703125000000000000e-03;
    } else if(f == 4.3492540020808991355072414819460391299799084663391113281250000000000000e-03){
        y = 4.3398233312593190516559538139063079142943024635314941406250000000000000e-03;
    } else if(f == 4.6590169270833330442127540038654842646792531013488769531250000000000000e-03){
        y = 4.6481973005924335021199489403898041928187012672424316406250000000000000e-03;
    } else if(f == 5.6768941600420317478148390932801703456789255142211914062500000000000000e-03){
        y = 5.6608341512090773819942945976890769088640809059143066406250000000000000e-03;
    } else if(f == 6.4167284783516222168575637851972714997828006744384765625000000000000000e-03){
        y = 6.3962286501419119907896337906549888430163264274597167968750000000000000e-03;
    } else if(f == 7.7207088470458984375000000000000000000000000000000000000000000000000000e-03){
        y = 7.6910567004233607382723825196535472059622406959533691406250000000000000e-03;
    } else{
        y = f*9.9999999992377652802133525256067514419555664062500000000000000000000000e-01;
        y += f*f*(-4.9999992762670575352501600718824192881584167480468750000000000000000000e-01 + f*3.3330828467805306836169165762839838862419128417968750000000000000000000e-01);
        y += f*f*f*f*-2.4627940464303718637317786033236188814043998718261718750000000000000000e-01;
    }
  }
  
  y += ln_lutHIGH[FIndex];
  y += m * LN2HIGH;
  
  return y;
}