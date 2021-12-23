#include<legacy.h>
struct Vyi8XZjDoj {
  int PNOyOWxJpK, JIGYRzzmas;
};
extern struct J_Sl6Dag5p Lr13OEObb4;
void RsBhhiFFvE();
void yAFGLz8ME3(int, int, int, int);
void TSiSLYknYn(struct Vyi8XZjDoj, int, uint32_t);
void ExGIFMPbha(char, int, int);
void K7z_BayAM3(const char*, int, int);
enum uint32_t {
  qBLBhlntx_ = 0xffffff,
  JCyb92PO2X = 0xf44336,
  WxSdxkcUJN = 0xffeb3b,
  eZelonvCFU = 0x9c27b0,
  hck0ckSSZL = 0x2196f3,
  XD7kFstGd3 = 0x00bcd4,
  UQRn26Bmz5 = 0x4caf50,
  kZ6hP_qvSg = 0xff9800
};
struct akI2wblQIp {
  struct Vyi8XZjDoj oT4p6Ulx7J;
  int W2yp9bnpy5;
};
struct erf1kA3ufC {
  struct Vyi8XZjDoj IOjC2fkbCg[4];
  uint32_t SU7984_mkw;
  int GDOlvXNmhT, XQvYgn4qpu;
};
struct J_Sl6Dag5p {
  int c0esYbnYow, pu0XGjLhxR, UaykZDyUUN;
  struct Vyi8XZjDoj ufBizpkLbx, QkSY7m7Gvu;
  int ukvKuleR4X, h72Vdp9m1b;
  int vZkqLfCIMW, gZ5nzpxC8r;
  struct akI2wblQIp OqmibpybCn;
  int PbckqMrTl2[3];
};
struct XaRzohPKKN {
  int cZ5d65ts5U;
  const char* h7WHgbkyVu;
  struct akI2wblQIp (*Apv7PJcujL) (struct akI2wblQIp, int8_t);
  int8_t raB0cxTuRP;
};
void AlM0UT25fL();
int8_t Wv1JqEgtYr(int);
int pVquJtRsOw();
struct akI2wblQIp hRIJHsqzlx();
struct akI2wblQIp mzR186wepk(struct akI2wblQIp, int8_t);
struct akI2wblQIp Ni4LED3jUH(struct akI2wblQIp, int8_t);
struct akI2wblQIp MTpeqVwHlI(struct akI2wblQIp, int8_t);
struct akI2wblQIp tl7Kc3Gx6U(struct akI2wblQIp, int8_t);
void Tr4A1w4VGP(struct akI2wblQIp);
void wcwGfNsCkC();
int8_t ceO5NPYidU(struct akI2wblQIp);
int8_t vK_Tb2f4LK(struct Vyi8XZjDoj);
int8_t T2L2xQFOiP(struct Vyi8XZjDoj);
int8_t ngSRbtwYAy(int);
void Fs8Hb_xg29(int, int);
void ly0rql8X0e(struct Vyi8XZjDoj, uint32_t);
void m5miMmA7_2();
void oHkucksBri(struct akI2wblQIp);
void c8HmnZyjKm();
void oafzhQLGOL();
extern struct J_Sl6Dag5p Lr13OEObb4;
extern char Y9gHrjRIJ9[128][8];
char *m95pjgcJqN(int tEM14SHDoj) {
  static char LMilhyuZ74[64];
  int lN3Q1bY4Lc = sizeof(LMilhyuZ74) - 1;
  do {
    LMilhyuZ74[--lN3Q1bY4Lc] = tEM14SHDoj % 10 + '0';
    tEM14SHDoj /= 10;
  } while(tEM14SHDoj > 0);
  return &LMilhyuZ74[lN3Q1bY4Lc];
}
void ExGIFMPbha(char ltHfkAWT49, int PNOyOWxJpK, int JIGYRzzmas) {
  int lN3Q1bY4Lc, K8LahUxCHv;
  char *Iu9obYq0S0 = Y9gHrjRIJ9[(int)ltHfkAWT49];
  uint32_t hlkzrt0baS = 0x000000, c3QL4Ztrp1 = 0xffffff;
  for (lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 16; lN3Q1bY4Lc ++) {
    for (K8LahUxCHv = 0; K8LahUxCHv < 16; K8LahUxCHv ++) {
      if (PNOyOWxJpK + K8LahUxCHv < Lr13OEObb4.c0esYbnYow && JIGYRzzmas + lN3Q1bY4Lc < Lr13OEObb4.pu0XGjLhxR) {
        draw_rect((Iu9obYq0S0[lN3Q1bY4Lc >> 1] >> (K8LahUxCHv >> 1)) & 1 ? &c3QL4Ztrp1 : &hlkzrt0baS, PNOyOWxJpK + K8LahUxCHv, JIGYRzzmas + lN3Q1bY4Lc, 1, 1);
      }
    }
  }
}
void K7z_BayAM3(const char *sLmI1owfcc, int PNOyOWxJpK, int JIGYRzzmas) {
  while (*sLmI1owfcc) {
    ExGIFMPbha(*sLmI1owfcc ++, PNOyOWxJpK, JIGYRzzmas);
    if (PNOyOWxJpK + 16 >= Lr13OEObb4.c0esYbnYow) {
      JIGYRzzmas += 16; PNOyOWxJpK = 0;
    } else {
      PNOyOWxJpK += 16;
    }
  }
}
char Y9gHrjRIJ9[128][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},
    { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},
    { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},
    { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},
    { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},
    { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},
    { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},
    { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},
    { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},
    { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},
    { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},
    { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},
    { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},
    { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},
    { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},
    { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},
    { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},
    { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},
    { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},
    { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},
    { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},
    { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},
    { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},
    { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},
    { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},
    { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},
    { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},
    { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},
    { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},
    { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},
    { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},
    { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},
    { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},
    { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},
    { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},
    { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},
    { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},
    { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},
    { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},
    { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},
    { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},
    { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},
    { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},
    { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},
    { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},
    { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},
    { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},
    { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},
    { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},
    { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},
    { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
    { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},
    { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},
    { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},
    { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},
    { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},
    { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},
    { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},
    { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},
    { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},
    { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},
    { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},
    { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},
    { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},
    { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},
    { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},
    { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},
    { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},
    { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},
    { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},
    { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},
    { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},
    { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},
    { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},
    { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};
struct Vyi8XZjDoj X4odtExhGz[4] = {
  { 0, -1 },
  { 0, 1 },
  { -1, 0 },
  { 1, 0 }
};
struct J_Sl6Dag5p Lr13OEObb4;
int main() {
#ifdef FPGA_GRAGHIC_ON
  VGA_GRAPHIC_ON();
#endif
  _ioe_init();
  while (1) {
    RsBhhiFFvE();
    while (1) {
      while (uptime() < Lr13OEObb4.ukvKuleR4X) ;
      while ((Lr13OEObb4.gZ5nzpxC8r = read_key()) != _KEY_NONE) {
        if (Lr13OEObb4.gZ5nzpxC8r & 0x8000) continue;
        Wv1JqEgtYr(Lr13OEObb4.gZ5nzpxC8r);
      }
      if (uptime() >= Lr13OEObb4.h72Vdp9m1b) {
        if (!Wv1JqEgtYr(_KEY_NONE)) break;
        Lr13OEObb4.h72Vdp9m1b += 1000 / 2;
      }
      draw_sync();
      Lr13OEObb4.ukvKuleR4X += 1000 / 24;
    }
    while ((Lr13OEObb4.gZ5nzpxC8r = read_key()) != _KEY_SPACE) ;
  }
  return 0;
}
void RsBhhiFFvE() {
  Lr13OEObb4.c0esYbnYow = screen_width();
  Lr13OEObb4.pu0XGjLhxR = screen_height();
  Lr13OEObb4.UaykZDyUUN = (Lr13OEObb4.pu0XGjLhxR - 2) / 30;
  if (Lr13OEObb4.c0esYbnYow / Lr13OEObb4.UaykZDyUUN > 2 * 15) {
    Lr13OEObb4.ufBizpkLbx.PNOyOWxJpK = (Lr13OEObb4.c0esYbnYow - Lr13OEObb4.UaykZDyUUN * 15) / 4;
    Lr13OEObb4.ufBizpkLbx.JIGYRzzmas = (Lr13OEObb4.pu0XGjLhxR - Lr13OEObb4.UaykZDyUUN * 30) / 2;
  } else {
    Lr13OEObb4.ufBizpkLbx.PNOyOWxJpK = 0;
    Lr13OEObb4.ufBizpkLbx.JIGYRzzmas = (Lr13OEObb4.pu0XGjLhxR - Lr13OEObb4.UaykZDyUUN * 30) / 2;
  }
  Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK = Lr13OEObb4.ufBizpkLbx.PNOyOWxJpK + Lr13OEObb4.UaykZDyUUN * (15 + 3);
  Lr13OEObb4.QkSY7m7Gvu.JIGYRzzmas = Lr13OEObb4.ufBizpkLbx.JIGYRzzmas;
  Lr13OEObb4.ukvKuleR4X = 0;
  Lr13OEObb4.h72Vdp9m1b = 0;
  Lr13OEObb4.vZkqLfCIMW = 0;
  Lr13OEObb4.gZ5nzpxC8r = 0;
  yAFGLz8ME3(0, 0, Lr13OEObb4.c0esYbnYow, Lr13OEObb4.pu0XGjLhxR);
  printf("Welcome to TETRIS!\n");
  printf("Press SPACEBAR to start!\n");
  K7z_BayAM3("Welcome to TETRIS!", 0, 0);
  K7z_BayAM3("Press SPACEBAR to start!", 0, 16);
  draw_sync();
  while ((Lr13OEObb4.gZ5nzpxC8r = read_key()) != _KEY_SPACE) ;
  yAFGLz8ME3(0, 0, Lr13OEObb4.c0esYbnYow, Lr13OEObb4.pu0XGjLhxR);
  srand(uptime());
  Lr13OEObb4.ukvKuleR4X = uptime();
  Lr13OEObb4.h72Vdp9m1b = uptime();
  AlM0UT25fL();
}
void yAFGLz8ME3(int PNOyOWxJpK, int JIGYRzzmas, int IIsFjksDAJ, int ackFJ_S7eT) {
  uint32_t hlkzrt0baS = 0x000000;
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < ackFJ_S7eT; ++lN3Q1bY4Lc) {
    for (int K8LahUxCHv = 0; K8LahUxCHv < IIsFjksDAJ; ++K8LahUxCHv) {
      if ((PNOyOWxJpK + K8LahUxCHv >= 0 && PNOyOWxJpK + K8LahUxCHv < Lr13OEObb4.c0esYbnYow)
          && (JIGYRzzmas + lN3Q1bY4Lc >= 0 && JIGYRzzmas + lN3Q1bY4Lc < Lr13OEObb4.pu0XGjLhxR)) {
        draw_rect(&hlkzrt0baS, PNOyOWxJpK + K8LahUxCHv, JIGYRzzmas + lN3Q1bY4Lc, 1, 1);
      }
    }
  }
}
void TSiSLYknYn(struct Vyi8XZjDoj oT4p6Ulx7J, int t_Ond6SBcn, uint32_t T2Uhx4sRvS) {
  assert(t_Ond6SBcn < 20);
  assert(oT4p6Ulx7J.PNOyOWxJpK >= 0 && oT4p6Ulx7J.PNOyOWxJpK + t_Ond6SBcn < screen_width());
  assert(oT4p6Ulx7J.JIGYRzzmas >= 0 && oT4p6Ulx7J.JIGYRzzmas + t_Ond6SBcn < screen_height());
  uint32_t mOVxisy1nD[t_Ond6SBcn][t_Ond6SBcn];
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < t_Ond6SBcn; ++lN3Q1bY4Lc) {
    for (int K8LahUxCHv = 0; K8LahUxCHv < t_Ond6SBcn; ++K8LahUxCHv) {
      mOVxisy1nD[lN3Q1bY4Lc][K8LahUxCHv] = T2Uhx4sRvS;
    }
  }
  draw_rect((uint32_t*) mOVxisy1nD, oT4p6Ulx7J.PNOyOWxJpK, oT4p6Ulx7J.JIGYRzzmas, t_Ond6SBcn, t_Ond6SBcn);
}
const int ZmBnADhg5k[5] = {
  0, 500, 1000, 2000, 4000
};
const struct Vyi8XZjDoj dVcc1z7igq = { 15 / 2, 2 };
const struct akI2wblQIp Tv6KTe3f4h = { {-1, -1}, 0 };
const struct erf1kA3ufC cDu7PTAYYw[20] = {
  {{{ 0, 0}, { 0, 0}, { 0, 0}, { 0, 0}}, qBLBhlntx_, 0, 0},
  {{{-1, 0}, { 0, 0}, { 1, 0}, { 2, 0}}, JCyb92PO2X, 2, 2},
  {{{ 0, -1}, { 0, 0}, { 0, 1}, { 0, 2}}, JCyb92PO2X, 1, 1},
  {{{ 0, 0}, { 0, -1}, { 0, -2}, {-1, 0}}, WxSdxkcUJN, 6, 4},
  {{{ 0, 0}, {-1, 0}, {-2, 0}, { 0, 1}}, WxSdxkcUJN, 3, 5},
  {{{ 0, 0}, { 0, 1}, { 0, 2}, { 1, 0}}, WxSdxkcUJN, 4, 6},
  {{{ 0, 0}, { 1, 0}, { 2, 0}, { 0, -1}}, WxSdxkcUJN, 5, 3},
  {{{ 0, 0}, { 0, -1}, { 0, -2}, { 1, 0}}, eZelonvCFU, 10, 8},
  {{{ 0, 0}, {-1, 0}, {-2, 0}, { 0, -1}}, eZelonvCFU, 7, 9},
  {{{ 0, 0}, { 0, 1}, { 0, 2}, {-1, 0}}, eZelonvCFU, 8, 10},
  {{{ 0, 0}, { 1, 0}, { 2, 0}, { 0, 1}}, eZelonvCFU, 9, 7},
  {{{ 0, 0}, { 1, 0}, { 0, 1}, { 1, 1}}, hck0ckSSZL, 11, 11},
  {{{ 0, 0}, { 1, 0}, { 0, 1}, {-1, 1}}, XD7kFstGd3, 13, 13},
  {{{ 0, 0}, { 0, -1}, { 1, 0}, { 1, 1}}, XD7kFstGd3, 12, 12},
  {{{ 0, 0}, {-1, 0}, { 0, 1}, { 1, 0}}, UQRn26Bmz5, 17, 15},
  {{{ 0, 0}, { 0, -1}, {-1, 0}, { 0, 1}}, UQRn26Bmz5, 14, 16},
  {{{ 0, 0}, { 1, 0}, { 0, -1}, {-1, 0}}, UQRn26Bmz5, 15, 17},
  {{{ 0, 0}, { 0, 1}, { 1, 0}, { 0, -1}}, UQRn26Bmz5, 16, 14},
  {{{ 0, 0}, {-1, 0}, { 0, 1}, { 1, 1}}, kZ6hP_qvSg, 19, 19},
  {{{ 0, 0}, { 0, -1}, {-1, 0}, {-1, 1}}, kZ6hP_qvSg, 18, 18}
};
const int Shf9k7ygdD[8] = { 1, 2, 4, 4, 1, 2, 4, 2 };
const int F5XrFEuzJp = 7;
const int AgT0ezHDlv = 20;
const struct XaRzohPKKN LgD4fP0CW4[] = {
  { _KEY_NONE, "AUTO", &Ni4LED3jUH, 0},
  { _KEY_W, "SPIN", &MTpeqVwHlI, 1},
  { _KEY_S, "FALL", &Ni4LED3jUH, 1},
  { _KEY_A, "MOVL", &mzR186wepk, 1},
  { _KEY_D, "MOVR", &mzR186wepk, 0},
  { _KEY_UP, "SPIN", &MTpeqVwHlI, 1},
  { _KEY_DOWN, "FALL", &Ni4LED3jUH, 1},
  { _KEY_LEFT, "MOVL", &mzR186wepk, 1},
  {_KEY_RIGHT, "MOVR", &mzR186wepk, 0},
  {_KEY_SPACE, "SWAP", &tl7Kc3Gx6U, 0}
};
const int mh0RAtmVTW = sizeof(LgD4fP0CW4) / sizeof(struct XaRzohPKKN);
int fo1Tc4gKyq[30][15];
void AlM0UT25fL() {
  memset(fo1Tc4gKyq, 0, sizeof(fo1Tc4gKyq));
  Lr13OEObb4.OqmibpybCn = hRIJHsqzlx();
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 3; ++lN3Q1bY4Lc) {
    Lr13OEObb4.PbckqMrTl2[lN3Q1bY4Lc] = pVquJtRsOw();
  }
  oHkucksBri(Lr13OEObb4.OqmibpybCn);
  c8HmnZyjKm();
}
int8_t Wv1JqEgtYr(int gZ5nzpxC8r) {
  Lr13OEObb4.vZkqLfCIMW--;
  struct akI2wblQIp CmxyfEd65Y = Lr13OEObb4.OqmibpybCn;
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < mh0RAtmVTW; ++lN3Q1bY4Lc) {
    if (gZ5nzpxC8r == LgD4fP0CW4[lN3Q1bY4Lc].cZ5d65ts5U) {
      if (gZ5nzpxC8r != _KEY_NONE) printf("\33[0m[\33[1;35mLog\33[0m]\33[1;34m[%s,%d,%s] " "[%s]" "\33[0m\n", "171860508/main.c", 469, __func__, LgD4fP0CW4[lN3Q1bY4Lc].h7WHgbkyVu);
      CmxyfEd65Y = LgD4fP0CW4[lN3Q1bY4Lc].Apv7PJcujL(CmxyfEd65Y, LgD4fP0CW4[lN3Q1bY4Lc].raB0cxTuRP);
      break;
    }
  }
  if (memcmp(&CmxyfEd65Y, &Tv6KTe3f4h, sizeof(struct akI2wblQIp)) == 0) {
    printf("Game Over!\n");
    printf("Your score: %d\n", Lr13OEObb4.vZkqLfCIMW);
    oafzhQLGOL();
    return 0;
  } else {
    Lr13OEObb4.OqmibpybCn = CmxyfEd65Y;
  }
  oHkucksBri(Lr13OEObb4.OqmibpybCn);
  return 1;
}
int pVquJtRsOw() {
  int A07MHv7SgQ = 0;
  int Yg4uY5m5GJ = rand() % (F5XrFEuzJp - 1) + 1;
  int W2yp9bnpy5 = rand() % Shf9k7ygdD[Yg4uY5m5GJ];
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < Yg4uY5m5GJ; ++lN3Q1bY4Lc) {
    A07MHv7SgQ += Shf9k7ygdD[lN3Q1bY4Lc];
  }
  return A07MHv7SgQ + W2yp9bnpy5;
}
struct akI2wblQIp hRIJHsqzlx() {
  struct akI2wblQIp CmxyfEd65Y;
  CmxyfEd65Y.oT4p6Ulx7J = dVcc1z7igq;
  CmxyfEd65Y.W2yp9bnpy5 = pVquJtRsOw();
  return CmxyfEd65Y;
}
struct akI2wblQIp tl7Kc3Gx6U(struct akI2wblQIp EBXJ01b3X8, int8_t fJYKmt6jcb) {
  if (fJYKmt6jcb) printf("\33[0m[\33[1;35mLog\33[0m]\33[1;34m[%s,%d,%s] " "233333" "\33[0m\n", "171860508/main.c", 507, __func__);
  struct akI2wblQIp HFiQY7M_0g;
  HFiQY7M_0g.oT4p6Ulx7J = dVcc1z7igq;
  HFiQY7M_0g.W2yp9bnpy5 = Lr13OEObb4.PbckqMrTl2[0];
  if (ceO5NPYidU(HFiQY7M_0g)) {
    Lr13OEObb4.PbckqMrTl2[0] = EBXJ01b3X8.W2yp9bnpy5;
    c8HmnZyjKm();
    return HFiQY7M_0g;
  } else {
    return EBXJ01b3X8;
  }
}
struct akI2wblQIp mzR186wepk(struct akI2wblQIp EBXJ01b3X8, int8_t n_IuJwlKn7) {
  struct akI2wblQIp HFiQY7M_0g = EBXJ01b3X8;
  HFiQY7M_0g.oT4p6Ulx7J.PNOyOWxJpK += n_IuJwlKn7 ? -1 : 1;
  return ceO5NPYidU(HFiQY7M_0g) ? HFiQY7M_0g : EBXJ01b3X8;
}
struct akI2wblQIp Ni4LED3jUH(struct akI2wblQIp N4HsEUMz4N, int8_t UQhKx6F_4t) {
  struct akI2wblQIp CmxyfEd65Y = N4HsEUMz4N;
  {
    int8_t OEtNX38_Bm = 0;
    struct akI2wblQIp Z8eCqHm27e = CmxyfEd65Y;
    do {
      Z8eCqHm27e.oT4p6Ulx7J.JIGYRzzmas++;
      OEtNX38_Bm = ceO5NPYidU(Z8eCqHm27e);
      CmxyfEd65Y = OEtNX38_Bm ? Z8eCqHm27e : CmxyfEd65Y;
    } while (UQhKx6F_4t && OEtNX38_Bm);
  }
  if (UQhKx6F_4t || memcmp(&CmxyfEd65Y, &N4HsEUMz4N, sizeof(struct akI2wblQIp)) == 0) {
    if (!ceO5NPYidU(CmxyfEd65Y)) {
      printf("\33[0m[\33[1;35mLog\33[0m]\33[1;34m[%s,%d,%s] " "Game over" "\33[0m\n", "171860508/main.c", 539, __func__);
      return Tv6KTe3f4h;
    } else {
      printf("\33[0m[\33[1;35mLog\33[0m]\33[1;34m[%s,%d,%s] " "Touch ground" "\33[0m\n", "171860508/main.c", 542, __func__);
      Tr4A1w4VGP(CmxyfEd65Y);
      wcwGfNsCkC();
      CmxyfEd65Y.oT4p6Ulx7J = dVcc1z7igq;
      CmxyfEd65Y.W2yp9bnpy5 = Lr13OEObb4.PbckqMrTl2[0];
      for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 3 - 1; ++lN3Q1bY4Lc) Lr13OEObb4.PbckqMrTl2[lN3Q1bY4Lc] = Lr13OEObb4.PbckqMrTl2[lN3Q1bY4Lc + 1];
      Lr13OEObb4.PbckqMrTl2[3 - 1] = pVquJtRsOw();
      if (ceO5NPYidU(CmxyfEd65Y)) {
        c8HmnZyjKm();
        printf("\33[0m[\33[1;35mLog\33[0m]\33[1;34m[%s,%d,%s] " "New tetromino: ((%d, %d), %d)" "\33[0m\n", "171860508/main.c", 551, __func__, CmxyfEd65Y.oT4p6Ulx7J.PNOyOWxJpK, CmxyfEd65Y.oT4p6Ulx7J.JIGYRzzmas, CmxyfEd65Y.W2yp9bnpy5);
        return CmxyfEd65Y;
      } else {
        return Tv6KTe3f4h;
      }
    }
  } else {
    return CmxyfEd65Y;
  }
}
struct akI2wblQIp MTpeqVwHlI(struct akI2wblQIp EBXJ01b3X8, int8_t qyWN7hIAhC) {
  struct akI2wblQIp HFiQY7M_0g = EBXJ01b3X8;
  HFiQY7M_0g.W2yp9bnpy5 = qyWN7hIAhC ? cDu7PTAYYw[EBXJ01b3X8.W2yp9bnpy5].GDOlvXNmhT : cDu7PTAYYw[EBXJ01b3X8.W2yp9bnpy5].XQvYgn4qpu;
  return ceO5NPYidU(HFiQY7M_0g) ? HFiQY7M_0g : EBXJ01b3X8;
}
void Tr4A1w4VGP(struct akI2wblQIp CmxyfEd65Y) {
  struct Vyi8XZjDoj Iu9obYq0S0;
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 4; ++lN3Q1bY4Lc) {
    Iu9obYq0S0.PNOyOWxJpK = CmxyfEd65Y.oT4p6Ulx7J.PNOyOWxJpK + cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].IOjC2fkbCg[lN3Q1bY4Lc].PNOyOWxJpK;
    Iu9obYq0S0.JIGYRzzmas = CmxyfEd65Y.oT4p6Ulx7J.JIGYRzzmas + cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].IOjC2fkbCg[lN3Q1bY4Lc].JIGYRzzmas;
    assert(vK_Tb2f4LK(Iu9obYq0S0));
    fo1Tc4gKyq[Iu9obYq0S0.JIGYRzzmas][Iu9obYq0S0.PNOyOWxJpK] = CmxyfEd65Y.W2yp9bnpy5;
  }
}
void wcwGfNsCkC() {
  for (int lN3Q1bY4Lc = 30 - 1; lN3Q1bY4Lc >= 0; --lN3Q1bY4Lc) {
    if (ngSRbtwYAy(lN3Q1bY4Lc)) {
      int Om5dYT6URx = 0;
      do {
        --lN3Q1bY4Lc, ++Om5dYT6URx;
      } while (ngSRbtwYAy(lN3Q1bY4Lc));
      Fs8Hb_xg29(lN3Q1bY4Lc, Om5dYT6URx);
      Lr13OEObb4.vZkqLfCIMW += ZmBnADhg5k[Om5dYT6URx];
      printf("\33[0m[\33[1;35mLog\33[0m]\33[1;34m[%s,%d,%s] " "Scored: %d" "\33[0m\n", "171860508/main.c", 587, __func__, ZmBnADhg5k[Om5dYT6URx]);
      return;
    }
  }
}
int8_t ceO5NPYidU(struct akI2wblQIp CmxyfEd65Y) {
  struct Vyi8XZjDoj Iu9obYq0S0;
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 4; ++lN3Q1bY4Lc) {
    Iu9obYq0S0.PNOyOWxJpK = CmxyfEd65Y.oT4p6Ulx7J.PNOyOWxJpK + cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].IOjC2fkbCg[lN3Q1bY4Lc].PNOyOWxJpK;
    Iu9obYq0S0.JIGYRzzmas = CmxyfEd65Y.oT4p6Ulx7J.JIGYRzzmas + cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].IOjC2fkbCg[lN3Q1bY4Lc].JIGYRzzmas;
    if (!vK_Tb2f4LK(Iu9obYq0S0)) return 0;
  }
  return 1;
}
int8_t vK_Tb2f4LK(struct Vyi8XZjDoj Iu9obYq0S0) {
  return T2L2xQFOiP(Iu9obYq0S0)
    && (fo1Tc4gKyq[Iu9obYq0S0.JIGYRzzmas][Iu9obYq0S0.PNOyOWxJpK] == 0);
}
int8_t T2L2xQFOiP(struct Vyi8XZjDoj Iu9obYq0S0) {
  return (Iu9obYq0S0.PNOyOWxJpK >= 0 && Iu9obYq0S0.PNOyOWxJpK < 15)
    && (Iu9obYq0S0.JIGYRzzmas >= 0 && Iu9obYq0S0.JIGYRzzmas < 30);
}
int8_t ngSRbtwYAy(int IOu_fJIsBF) {
  for (int K8LahUxCHv = 0; K8LahUxCHv < 15; ++K8LahUxCHv) {
    if (fo1Tc4gKyq[IOu_fJIsBF][K8LahUxCHv] == 0) return 0;
  }
  return 1;
}
void Fs8Hb_xg29(int IOu_fJIsBF, int Om5dYT6URx) {
  assert(IOu_fJIsBF >= 0 && Om5dYT6URx > 0 && IOu_fJIsBF + Om5dYT6URx < 30);
  for (int lN3Q1bY4Lc = IOu_fJIsBF; lN3Q1bY4Lc >= 0; --lN3Q1bY4Lc) {
    memcpy(&fo1Tc4gKyq[lN3Q1bY4Lc + Om5dYT6URx][0], &fo1Tc4gKyq[lN3Q1bY4Lc][0], 15 * sizeof(int));
  }
  memset(fo1Tc4gKyq, 0, Om5dYT6URx * 15 * sizeof(int));
}
void ly0rql8X0e(struct Vyi8XZjDoj oT4p6Ulx7J, uint32_t SU7984_mkw) {
  if (!T2L2xQFOiP(oT4p6Ulx7J)) return;
  struct Vyi8XZjDoj S63gJ0ohpw = {
    Lr13OEObb4.ufBizpkLbx.PNOyOWxJpK + oT4p6Ulx7J.PNOyOWxJpK * Lr13OEObb4.UaykZDyUUN,
    Lr13OEObb4.ufBizpkLbx.JIGYRzzmas + oT4p6Ulx7J.JIGYRzzmas * Lr13OEObb4.UaykZDyUUN
  };
  TSiSLYknYn(S63gJ0ohpw, Lr13OEObb4.UaykZDyUUN, SU7984_mkw);
}
void m5miMmA7_2() {
  struct Vyi8XZjDoj Iu9obYq0S0;
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 2; ++lN3Q1bY4Lc) {
    Iu9obYq0S0.JIGYRzzmas = Lr13OEObb4.ufBizpkLbx.JIGYRzzmas + 2 * Lr13OEObb4.UaykZDyUUN - lN3Q1bY4Lc;
    for (int K8LahUxCHv = 0; K8LahUxCHv < 15 * Lr13OEObb4.UaykZDyUUN; ++K8LahUxCHv) {
      Iu9obYq0S0.PNOyOWxJpK = Lr13OEObb4.ufBizpkLbx.PNOyOWxJpK + K8LahUxCHv;
      TSiSLYknYn(Iu9obYq0S0, 1, 0xff0000);
    }
  }
}
void oHkucksBri(struct akI2wblQIp CmxyfEd65Y) {
  struct Vyi8XZjDoj Iu9obYq0S0;
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 30; ++lN3Q1bY4Lc) {
    for (int K8LahUxCHv = 0; K8LahUxCHv < 15; ++K8LahUxCHv) {
      Iu9obYq0S0.PNOyOWxJpK = K8LahUxCHv, Iu9obYq0S0.JIGYRzzmas = lN3Q1bY4Lc;
      ly0rql8X0e(Iu9obYq0S0, cDu7PTAYYw[fo1Tc4gKyq[lN3Q1bY4Lc][K8LahUxCHv]].SU7984_mkw);
    }
  }
  m5miMmA7_2();
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 4; ++lN3Q1bY4Lc) {
    Iu9obYq0S0.PNOyOWxJpK = CmxyfEd65Y.oT4p6Ulx7J.PNOyOWxJpK + cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].IOjC2fkbCg[lN3Q1bY4Lc].PNOyOWxJpK;
    Iu9obYq0S0.JIGYRzzmas = CmxyfEd65Y.oT4p6Ulx7J.JIGYRzzmas + cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].IOjC2fkbCg[lN3Q1bY4Lc].JIGYRzzmas;
    ly0rql8X0e(Iu9obYq0S0, cDu7PTAYYw[CmxyfEd65Y.W2yp9bnpy5].SU7984_mkw);
  }
}
void c8HmnZyjKm() {
  struct Vyi8XZjDoj Iu9obYq0S0;
  char l_HEevn9d3[16] = "";
  sprintf(l_HEevn9d3, "%d", Lr13OEObb4.vZkqLfCIMW);
  yAFGLz8ME3(Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK - 3 * Lr13OEObb4.UaykZDyUUN, 0, (3 + 6 * 3) * Lr13OEObb4.UaykZDyUUN, Lr13OEObb4.pu0XGjLhxR);
  K7z_BayAM3("NEXT", Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK - Lr13OEObb4.UaykZDyUUN, Lr13OEObb4.QkSY7m7Gvu.JIGYRzzmas);
  for (int lN3Q1bY4Lc = 0; lN3Q1bY4Lc < 3; ++lN3Q1bY4Lc) {
    int W2yp9bnpy5 = Lr13OEObb4.PbckqMrTl2[lN3Q1bY4Lc];
    for (int K8LahUxCHv = 0; K8LahUxCHv < 4; ++K8LahUxCHv) {
      Iu9obYq0S0.PNOyOWxJpK = Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK + cDu7PTAYYw[W2yp9bnpy5].IOjC2fkbCg[K8LahUxCHv].PNOyOWxJpK * Lr13OEObb4.UaykZDyUUN;
      Iu9obYq0S0.JIGYRzzmas = Lr13OEObb4.QkSY7m7Gvu.JIGYRzzmas + 32 + (2 + 6 * lN3Q1bY4Lc + cDu7PTAYYw[W2yp9bnpy5].IOjC2fkbCg[K8LahUxCHv].JIGYRzzmas) * Lr13OEObb4.UaykZDyUUN;
      TSiSLYknYn(Iu9obYq0S0, Lr13OEObb4.UaykZDyUUN, cDu7PTAYYw[W2yp9bnpy5].SU7984_mkw);
    }
  }
  K7z_BayAM3("SCORE", Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK - Lr13OEObb4.UaykZDyUUN, Lr13OEObb4.QkSY7m7Gvu.JIGYRzzmas + 32 + (2 + 6 * 3) * Lr13OEObb4.UaykZDyUUN);
  K7z_BayAM3(l_HEevn9d3, Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK - Lr13OEObb4.UaykZDyUUN, Lr13OEObb4.QkSY7m7Gvu.JIGYRzzmas + 32 + (2 + 6 * 3) * Lr13OEObb4.UaykZDyUUN + 16);
}
void oafzhQLGOL() {
  K7z_BayAM3("Game Over", Lr13OEObb4.QkSY7m7Gvu.PNOyOWxJpK - Lr13OEObb4.UaykZDyUUN, Lr13OEObb4.QkSY7m7Gvu.JIGYRzzmas + 32 + (2 + 6 * 3) * Lr13OEObb4.UaykZDyUUN + 2 * 16);
}
