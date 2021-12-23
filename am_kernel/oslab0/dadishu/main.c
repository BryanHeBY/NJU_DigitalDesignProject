#include<legacy.h>
static inline void Vyi8XZjDoj(const char *PNOyOWxJpK) {
  for (; *PNOyOWxJpK; PNOyOWxJpK++) _putc(*PNOyOWxJpK);
}
void JIGYRzzmas();
void J_Sl6Dag5p(int Lr13OEObb4, int RsBhhiFFvE, int yAFGLz8ME3, int TSiSLYknYn, uint32_t ExGIFMPbha);
void K7z_BayAM3();
void qBLBhlntx_();
void JCyb92PO2X();
void WxSdxkcUJN();
int eZelonvCFU;
static int hck0ckSSZL[]={
    _KEY_1, _KEY_2, _KEY_3, _KEY_4, _KEY_5,
    _KEY_6, _KEY_7, _KEY_8, _KEY_9,
};
int XD7kFstGd3=0;
int UQRn26Bmz5=0;
int kZ6hP_qvSg[9][2];
int akI2wblQIp[9];
int oT4p6Ulx7J=0;
int main() {
#ifdef FPGA_GRAGHIC_ON
  VGA_GRAPHIC_ON();
#endif
  _ioe_init();
  while(uptime()<=10000);
  JIGYRzzmas();
  K7z_BayAM3();
  qBLBhlntx_();
  unsigned long W2yp9bnpy5, erf1kA3ufC=0, IOjC2fkbCg=0, SU7984_mkw=0;;
  srand(uptime());
  while(1){
    while(1){
        W2yp9bnpy5 = uptime();
        if(W2yp9bnpy5 >= SU7984_mkw) break;
    }
    SU7984_mkw += 1000/100;
    WxSdxkcUJN();
    if(W2yp9bnpy5 >= erf1kA3ufC){
        if(UQRn26Bmz5+XD7kFstGd3<30)
            JCyb92PO2X();
        erf1kA3ufC += 1000/3;
    }
    if(W2yp9bnpy5 >= IOjC2fkbCg){
        IOjC2fkbCg += 1000/30;
        qBLBhlntx_();
    }
    if(oT4p6Ulx7J==1) break;
  }
  qBLBhlntx_();
  return 0;
}
int yAFGLz8ME3,TSiSLYknYn;
void JIGYRzzmas() {
  yAFGLz8ME3 = screen_width();
  TSiSLYknYn = screen_height();
  if(yAFGLz8ME3/3>80 && TSiSLYknYn/3>80)
      eZelonvCFU = 80;
  else eZelonvCFU = (yAFGLz8ME3/3<TSiSLYknYn/3)?yAFGLz8ME3/3:TSiSLYknYn/3;
}
void K7z_BayAM3(){
    int GDOlvXNmhT = 0;
    for(int RsBhhiFFvE=0; RsBhhiFFvE<=TSiSLYknYn-TSiSLYknYn/3; RsBhhiFFvE+=TSiSLYknYn/3){
        for(int Lr13OEObb4=0; Lr13OEObb4<=yAFGLz8ME3-yAFGLz8ME3/3; Lr13OEObb4+=yAFGLz8ME3/3){
            kZ6hP_qvSg[GDOlvXNmhT][0]=Lr13OEObb4+(yAFGLz8ME3/3-eZelonvCFU)/2;
            kZ6hP_qvSg[GDOlvXNmhT][1]=RsBhhiFFvE+(TSiSLYknYn/3-eZelonvCFU)/2;
            GDOlvXNmhT++;
        }
    }
    for(int XQvYgn4qpu=0; XQvYgn4qpu<9; XQvYgn4qpu++)
        akI2wblQIp[XQvYgn4qpu] = 0;
}
void qBLBhlntx_(){
    for(int XQvYgn4qpu=0; XQvYgn4qpu<9; XQvYgn4qpu++){
        if(akI2wblQIp[XQvYgn4qpu]==0) J_Sl6Dag5p(kZ6hP_qvSg[XQvYgn4qpu][0], kZ6hP_qvSg[XQvYgn4qpu][1], eZelonvCFU, eZelonvCFU, 0xffffff);
        else J_Sl6Dag5p(kZ6hP_qvSg[XQvYgn4qpu][0], kZ6hP_qvSg[XQvYgn4qpu][1], eZelonvCFU, eZelonvCFU, 0xff0000);
    }
    draw_sync();
}
void JCyb92PO2X(){
    int XQvYgn4qpu = rand()%9;
    while(1){
        if(akI2wblQIp[XQvYgn4qpu]==0){
            akI2wblQIp[XQvYgn4qpu]=1;
            XD7kFstGd3++;
            break;
        }
        XQvYgn4qpu = rand()%9;
    }
    if(XD7kFstGd3==9){
        oT4p6Ulx7J=1;
        printf("Lose! You farm is filled with mice\n");
    }
}
void WxSdxkcUJN(){
    int c0esYbnYow = 0;
    int pu0XGjLhxR = read_key();
    for(int XQvYgn4qpu=0; XQvYgn4qpu<9; XQvYgn4qpu++){
        if(hck0ckSSZL[XQvYgn4qpu]==pu0XGjLhxR){
            if(akI2wblQIp[XQvYgn4qpu]==1){
                UQRn26Bmz5++;
                XD7kFstGd3--;
                akI2wblQIp[XQvYgn4qpu]=0;
            }else{
                c0esYbnYow = 1;
            }
            break;
        }
    }
    if(c0esYbnYow==1){
        oT4p6Ulx7J = 1;
        printf("Lose! You beat the wrong place\n");
    }
    if(UQRn26Bmz5==30){
        oT4p6Ulx7J = 1;
        printf("Win! You have killed all 20 mice\n");
    }
}
void J_Sl6Dag5p(int Lr13OEObb4, int RsBhhiFFvE, int yAFGLz8ME3, int TSiSLYknYn, uint32_t ExGIFMPbha) {
  uint32_t UaykZDyUUN[yAFGLz8ME3 * TSiSLYknYn];
  for (int XQvYgn4qpu = 0; XQvYgn4qpu < yAFGLz8ME3 * TSiSLYknYn; XQvYgn4qpu++) {
    UaykZDyUUN[XQvYgn4qpu] = ExGIFMPbha;
  }
  draw_rect(UaykZDyUUN, Lr13OEObb4, RsBhhiFFvE, yAFGLz8ME3, TSiSLYknYn);
}
