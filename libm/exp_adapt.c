#include <math.h>
#include "rlibm.h"
#include "exp2.h"

// This is the adapted piecewise polynomial
double rlibm_exp_adapt(float x) {
  float_x fx;
  fx.f = x;
  
  // Take care of special cases
  if ((fx.x & 0x7FFFFFFF) == 0) return 1.0;

  if (fx.x <= 872415231) {
    if (fx.x <= 864026623) return 1.0000000298023223876953125;
    return 1.0000000894069671630859375;
  }

  if (1118925336 <= fx.x && fx.x <= 3011510272) {
    if (fx.x < 0x80000000) {
      if (fx.x < 0x7F800000) return 3.40282361850336062550457001444955389952e+38;
      if (fx.x == 0x7F800000) return 1.0 / 0.0;
      return 0.0/0.0;
    }
    
    // negative counterpart
    if (fx.x <= 3003121664) return 0.99999998509883880615234375;
    
    return 0.99999995529651641845703125;
  }

  if (fx.x >= 3268407733) {
    if (fx.x == 0xFF800000) return 0.0;
    if (fx.x < 0xFF800000) return ldexp(1.0, -151);
    return 0.0/0.0;
  }
  
  // Perform range reduction
  double xp = x * 92.332482616893656768297660164535045623779296875;
  int N = (int)xp;
  int N2 = N % 64;
  if (N2 < 0) N2 += 64;
  int N1 = N - N2;
  
  int M = N1 / 64;
  int J = N2;
  double R = x - N *
  0.01083042469624914509729318723429969395510852336883544921875;
  
  double_x dX;
  dX.d = R;
  double y,z;
  
  if (R < -9.64999884445205680094659328460693359375e-08) {
    switch (dX.x) {
      case 0xbf83e80a05598800:
        y = 9.9032716247990881797136353270616382360458374023437500000000000000000000e-01;
        break;
      case 0xbf6f925ff5140000:
        y = 9.9615344038951469940457172924652695655822753906250000000000000000000000e-01;
        break;
      case 0xbf6e08d3e0000000:
        y = 9.9634039402008067742855246251565404236316680908203125000000000000000000e-01;
        break;
      case 0xbf6c57f87ab4d800:
        y = 9.9654606220206354283419614148442633450031280517578125000000000000000000e-01;
        break;
      case 0xbf262097d5680000:
        y = 9.9983119621919913644347843728610314428806304931640625000000000000000000e-01;
        break;
      default:
        // Compute polynomial
        z = R + 1.5098710622327549124577217298792675137519836425781250000000000000000000e+00;
        z *= R;
        z += 1.1632415450691333091981505276635289192199707031250000000000000000000000e+01;
        y = z + R + -1.4995064469805441831340431235730648040771484375000000000000000000000000e+01;
        y *= z;
        y += 6.3234426882417437809635885059833526611328125000000000000000000000000000e+01;
        y *= 4.1461610537053508740434892843040870502591133117675781250000000000000000e-02;
    }
  } else {
    switch(dX.x) {
      case 0x3f38d7cb60000000:
        y = 1.0003791451454164818102299250313080847263336181640625000000000000000000e+00;
        break;
      case 0x3f64687aa6f9bc00:
        y = 1.0024942919583126332838673988590016961097717285156250000000000000000000e+00;
        break;
      case 0x3f6473eeec825800:
        y = 1.0024997740198287043966729470412246882915496826171875000000000000000000e+00;
        break;
      case 0x3f8322aa79dbc800:
        y = 1.0093871966857201893930096048279665410518646240234375000000000000000000e+0;
        break;
      default:
        z = R + 1.4899763308528306549050057583372108638286590576171875000000000000000000e+00;
        z *= R;
        z += 1.1617494780790503128287127765361219644546508789062500000000000000000000e+01;
        y = z + R + -1.5005011824576452994506325921975076198577880859375000000000000000000000e+01;
        y *= z;
        y += 6.3234428388497889272912289015948772430419921875000000000000000000000000e+01;
        y *= 4.1876105099005592191652169731241883710026741027832031250000000000000000e-02;
    }
  }
  
  
  
  // Perform output compensation
  y *= ldexp(exp2JBy64[J], M);
  return y;
}