//1位全加器
module full_adder (
    input A,
    input B,
    input Cin,
    output F,
    output G,
    output P
);

assign G=A&B; //进位生成函数
assign P=A|B; //进位传递函数
assign F=(~G&P) ^ Cin;

endmodule

//4位CLU
module _4_CLU (
    input [3:0] G, //进位生成函数
    input [3:0] P, //进位传递函数
    input Cin,
    output [3:0] C,
    output Gs0,
    output Ps0
);

// C3-C0(C4-C1)的布尔表达式如下
assign C = {
    G[3] | G[2]&P[3] | &{G[1],P[3:2]} | &{G[0],P[3:1]} | &{Cin,P[3:0]},
    G[2] | G[1]&P[2] | &{G[0],P[2:1]} | &{Cin,P[2:0]},
    G[1] | G[0]&P[1] | &{Cin,P[1:0]},
    G[0] | Cin&P[0]
};

//为串联生成16位加法器做准备
assign Gs0 = G[3] | G[2]&P[3] | G[1]&(&P[3:2]) | G[0]&(&P[3:1]);
assign Ps0 = &P;

endmodule

//封装加法器，生成标志位
module _4_adder (
    input [3:0] A,
    input [3:0] B,
    input Cin,
    output [3:0] F,
    output Gg,
    output Pg,
    output C4,
    output C3
);
    
wire [4:0] C;
wire [3:0] G;
wire [3:0] P;

assign C[0]=Cin;

full_adder full_adders[3:0](
    .A(A),
    .B(B),
    .Cin(C[3:0]),
    .F(F),
    .G(G),
    .P(P)
);

_4_CLU a_4_CLU(
    .G(G),
    .P(P),
    .Cin(C[0]),
    .C(C[4:1]),
    .Gs0(Gg),
    .Ps0(Pg)
);

assign C4=C[4];
assign C3=C[3];//用来生成OF标志

endmodule

//16位加法器
module _16_adder (
    input [15:0] A,
    input [15:0] B,
    input Cin,
    output [15:0] F,
    output Gg,
    output Pg,
    output C16,
    output C15
);
    
wire [4:0] C;
wire [3:0] G;
wire [3:0] P;

assign C[0]=Cin;

_4_adder _4_adders[3:0](
    .A(A),
    .B(B),
    .Cin(C[3:0]),
    .F(F),
    .Gg(G),
    .Pg(P)
);

_4_CLU a_4_CLU(
    .G(G),
    .P(P),
    .Cin(C[0]),
    .C(C[4:1]),
    .Gs0(Gg),
    .Ps0(Pg)
);

assign C16=C[4];
assign C15=C[3];

endmodule

module _32_adder (
    input [31:0] A,
    input [31:0] B,
    input Cin,
    output [31:0] F,
    output cf,
    output zf,
    output of
);

wire [1:0] C;
wire [1:0] G;
wire [1:0] P;
wire [1:0] C16s, C15s;
wire C32, C31;

assign C = {
    G[0] | P[0] & Cin,
    Cin
};
assign C32 = C16s[1];
assign C31 = C15s[1];

_16_adder two_16_adders[1:0](
    .A(A),
    .B(B),
    .Cin(C[1:0]),
    .F(F),
    .Gg(G),
    .Pg(P),
    .C16(C16s),
    .C15(C15s)
);

assign cf = C32 ^ Cin; //CF = Cout ^ Cin
assign of = C32 ^ C31; //OF = Cn ^ Cn-1
assign zf = ~(|F); 
    
endmodule
