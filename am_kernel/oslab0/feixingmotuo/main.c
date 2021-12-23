#include<legacy.h>
static inline void Vyi8XZjDoj(const char *PNOyOWxJpK) {
  for (; *PNOyOWxJpK; PNOyOWxJpK++) _putc(*PNOyOWxJpK);
}
enum {JIGYRzzmas = 0, J_Sl6Dag5p, Lr13OEObb4, RsBhhiFFvE, yAFGLz8ME3, TSiSLYknYn};
char ExGIFMPbha = 0;
struct K7z_BayAM3{
 int qBLBhlntx_;
 int JCyb92PO2X;
 int WxSdxkcUJN;
} eZelonvCFU, hck0ckSSZL;
char XD7kFstGd3[(800/4)][(600/4)]={};
void UQRn26Bmz5();
void kZ6hP_qvSg();
int akI2wblQIp();
void oT4p6Ulx7J();
void W2yp9bnpy5(int erf1kA3ufC);
void IOjC2fkbCg(char SU7984_mkw);
void GDOlvXNmhT();
int main() {
#ifdef FPGA_GRAGHIC_ON
  VGA_GRAPHIC_ON();
#endif
  _ioe_init();
  UQRn26Bmz5();
 kZ6hP_qvSg();
 GDOlvXNmhT();
  uint32_t XQvYgn4qpu=akI2wblQIp();
 while (1) {
  uint32_t c0esYbnYow=akI2wblQIp();
  if(c0esYbnYow/40 != XQvYgn4qpu/40){
   XQvYgn4qpu=c0esYbnYow;
   oT4p6Ulx7J();
   GDOlvXNmhT();
   if(ExGIFMPbha == 1){
    Vyi8XZjDoj("Player A (Jade) lost!\n");
    break;
   }
   else if (ExGIFMPbha == 2){
    Vyi8XZjDoj("Player B (Violet) lost!\n");
    break;
   }
  }
  }
 while(1);
 return 0;
}
int pu0XGjLhxR(int erf1kA3ufC){
 switch(erf1kA3ufC){
  case _KEY_W: return _KEY_S;
  case _KEY_S: return _KEY_W;
  case _KEY_A: return _KEY_D;
  case _KEY_D: return _KEY_A;
  case _KEY_UP: return _KEY_DOWN;
  case _KEY_DOWN: return _KEY_UP;
  case _KEY_LEFT: return _KEY_RIGHT;
  case _KEY_RIGHT: return _KEY_LEFT;
 }
 return 0;
}
void oT4p6Ulx7J(){
  int UaykZDyUUN = 0, ufBizpkLbx = 0, QkSY7m7Gvu = 0;
  UaykZDyUUN = read_key();
 while(((UaykZDyUUN) & ~0x8000)!=_KEY_NONE && (((UaykZDyUUN) & 0x8000) != 0)){
  switch(((UaykZDyUUN) & ~0x8000)){
   case _KEY_W: case _KEY_S: case _KEY_A: case _KEY_D:
     ufBizpkLbx = UaykZDyUUN; break;
   case _KEY_UP: case _KEY_DOWN: case _KEY_LEFT: case _KEY_RIGHT:
     QkSY7m7Gvu = UaykZDyUUN; break;
   default: Vyi8XZjDoj("ILLEGAL KEY\n");
  }
    UaykZDyUUN = read_key();
 }
  if(((ufBizpkLbx) & ~0x8000) != _KEY_NONE && (((ufBizpkLbx) & 0x8000) != 0)
    && ((ufBizpkLbx) & ~0x8000) != pu0XGjLhxR(eZelonvCFU.WxSdxkcUJN))
   W2yp9bnpy5(((ufBizpkLbx) & ~0x8000));
 else
  W2yp9bnpy5(eZelonvCFU.WxSdxkcUJN);
 IOjC2fkbCg(1);
 if(((QkSY7m7Gvu) & ~0x8000) != _KEY_NONE && (((QkSY7m7Gvu) & 0x8000) != 0)
    && ((QkSY7m7Gvu) & ~0x8000) != pu0XGjLhxR(hck0ckSSZL.WxSdxkcUJN))
  W2yp9bnpy5(((QkSY7m7Gvu) & ~0x8000));
 else
  W2yp9bnpy5(hck0ckSSZL.WxSdxkcUJN);
 IOjC2fkbCg(2);
}
int ukvKuleR4X, h72Vdp9m1b;
void UQRn26Bmz5() {
  ukvKuleR4X = screen_width();
  h72Vdp9m1b = screen_height();
}
void vZkqLfCIMW(int gZ5nzpxC8r, int OqmibpybCn, int ukvKuleR4X, int h72Vdp9m1b, uint32_t PbckqMrTl2) {
  uint32_t XaRzohPKKN[ukvKuleR4X * h72Vdp9m1b];
  for (int cZ5d65ts5U = 0; cZ5d65ts5U < ukvKuleR4X * h72Vdp9m1b; cZ5d65ts5U++) {
    XaRzohPKKN[cZ5d65ts5U] = PbckqMrTl2;
  }
  draw_rect(XaRzohPKKN, gZ5nzpxC8r, OqmibpybCn, ukvKuleR4X, h72Vdp9m1b);
}
void GDOlvXNmhT(){
 int h7WHgbkyVu[] = {0x283232, 0x51CC99, 0xFF66FF, 0xFFFFFF, 0xFF00000,0xFFFF00};
 for(int gZ5nzpxC8r=0;gZ5nzpxC8r*4<ukvKuleR4X;gZ5nzpxC8r++){
  for(int OqmibpybCn=0;OqmibpybCn*4<h72Vdp9m1b;OqmibpybCn++){
   vZkqLfCIMW(gZ5nzpxC8r*4,OqmibpybCn*4,4,4,h7WHgbkyVu[(int)XD7kFstGd3[gZ5nzpxC8r][OqmibpybCn]]);
  }
 }
  draw_sync();
}
int akI2wblQIp(){
  return uptime();
}
void kZ6hP_qvSg(){
 int Apv7PJcujL = ukvKuleR4X / 4;
 int raB0cxTuRP = h72Vdp9m1b / 4;
 eZelonvCFU.qBLBhlntx_= Apv7PJcujL / 4;
 eZelonvCFU.JCyb92PO2X= raB0cxTuRP / 2;
 eZelonvCFU.WxSdxkcUJN=_KEY_D;
 hck0ckSSZL.qBLBhlntx_= Apv7PJcujL * 3 / 4;
 hck0ckSSZL.JCyb92PO2X= raB0cxTuRP / 2;
 hck0ckSSZL.WxSdxkcUJN=_KEY_LEFT;
 for(int gZ5nzpxC8r=0;gZ5nzpxC8r<Apv7PJcujL;gZ5nzpxC8r++){
  XD7kFstGd3[gZ5nzpxC8r][0]=RsBhhiFFvE;
  XD7kFstGd3[gZ5nzpxC8r][raB0cxTuRP-1]=RsBhhiFFvE;
 }
 for(int OqmibpybCn=0;OqmibpybCn<raB0cxTuRP;OqmibpybCn++){
  XD7kFstGd3[0][OqmibpybCn]=RsBhhiFFvE;
  XD7kFstGd3[Apv7PJcujL-1][OqmibpybCn]=RsBhhiFFvE;
 }
}
void W2yp9bnpy5(int erf1kA3ufC){
 switch(erf1kA3ufC){
  case _KEY_W:
   eZelonvCFU.WxSdxkcUJN = _KEY_W;
   eZelonvCFU.JCyb92PO2X--;
   break;
  case _KEY_S:
   eZelonvCFU.WxSdxkcUJN = _KEY_S;
   eZelonvCFU.JCyb92PO2X++;
   break;
  case _KEY_A:
   eZelonvCFU.WxSdxkcUJN = _KEY_A;
   eZelonvCFU.qBLBhlntx_--;
   break;
  case _KEY_D:
   eZelonvCFU.WxSdxkcUJN = _KEY_D;
   eZelonvCFU.qBLBhlntx_++;
   break;
  case _KEY_UP:
   hck0ckSSZL.WxSdxkcUJN = _KEY_UP;
   hck0ckSSZL.JCyb92PO2X--;
   break;
  case _KEY_DOWN:
   hck0ckSSZL.WxSdxkcUJN = _KEY_DOWN;
   hck0ckSSZL.JCyb92PO2X++;
   break;
  case _KEY_LEFT:
   hck0ckSSZL.WxSdxkcUJN = _KEY_LEFT;
   hck0ckSSZL.qBLBhlntx_--;
   break;
  case _KEY_RIGHT:
   hck0ckSSZL.WxSdxkcUJN = _KEY_RIGHT;
   hck0ckSSZL.qBLBhlntx_++;
   break;
  default: printf("No such direction");
 }
}
void IOjC2fkbCg(char SU7984_mkw){
 switch(SU7984_mkw){
  case 1:
   if(XD7kFstGd3[eZelonvCFU.qBLBhlntx_][eZelonvCFU.JCyb92PO2X]==JIGYRzzmas){
    XD7kFstGd3[eZelonvCFU.qBLBhlntx_][eZelonvCFU.JCyb92PO2X]=J_Sl6Dag5p;
   }
   else{
    XD7kFstGd3[eZelonvCFU.qBLBhlntx_][eZelonvCFU.JCyb92PO2X]=yAFGLz8ME3;
    XD7kFstGd3[eZelonvCFU.qBLBhlntx_-1][eZelonvCFU.JCyb92PO2X-1]=TSiSLYknYn;
    XD7kFstGd3[eZelonvCFU.qBLBhlntx_-1][eZelonvCFU.JCyb92PO2X+1]=TSiSLYknYn;
    XD7kFstGd3[eZelonvCFU.qBLBhlntx_+1][eZelonvCFU.JCyb92PO2X-1]=TSiSLYknYn;
    XD7kFstGd3[eZelonvCFU.qBLBhlntx_+1][eZelonvCFU.JCyb92PO2X+1]=TSiSLYknYn;
    ExGIFMPbha = 1;
   }
   break;
  case 2:
   if(XD7kFstGd3[hck0ckSSZL.qBLBhlntx_][hck0ckSSZL.JCyb92PO2X]==JIGYRzzmas){
    XD7kFstGd3[hck0ckSSZL.qBLBhlntx_][hck0ckSSZL.JCyb92PO2X]=Lr13OEObb4;
   }
   else{
    XD7kFstGd3[hck0ckSSZL.qBLBhlntx_][hck0ckSSZL.JCyb92PO2X]=yAFGLz8ME3;
    XD7kFstGd3[hck0ckSSZL.qBLBhlntx_-1][hck0ckSSZL.JCyb92PO2X-1]=TSiSLYknYn;
    XD7kFstGd3[hck0ckSSZL.qBLBhlntx_-1][hck0ckSSZL.JCyb92PO2X+1]=TSiSLYknYn;
    XD7kFstGd3[hck0ckSSZL.qBLBhlntx_+1][hck0ckSSZL.JCyb92PO2X-1]=TSiSLYknYn;
    XD7kFstGd3[hck0ckSSZL.qBLBhlntx_+1][hck0ckSSZL.JCyb92PO2X+1]=TSiSLYknYn;
    ExGIFMPbha = 2;
   }
   break;
 }
}
