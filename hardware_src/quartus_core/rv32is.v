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
module barrel(
    input [31:0] indata,
    input [4:0] shamt,
    input lr,
    input al,
    output [31:0] outdata
);

reg [31:0] sh_data [4:0];
wire hin;

assign hin = al ? indata[31] : 1'b0;
assign outdata = sh_data[4];

always @(*) begin
    if(lr)begin
        sh_data[0] = shamt[0] ? {indata[30:0], 1'd0} : indata;
        sh_data[1] = shamt[1] ? {sh_data[0][29:0], 2'd0} : sh_data[0];
        sh_data[2] = shamt[2] ? {sh_data[1][27:0], 4'd0} : sh_data[1];
        sh_data[3] = shamt[3] ? {sh_data[2][23:0], 8'd0} : sh_data[2];
        sh_data[4] = shamt[4] ? {sh_data[3][15:0], 16'd0} : sh_data[3];
    end
    else begin
        sh_data[0] = shamt[0] ? {{1{hin}}, indata[31:1]} : indata;
        sh_data[1] = shamt[1] ? {{2{hin}}, sh_data[0][31:2]} : sh_data[0];
        sh_data[2] = shamt[2] ? {{4{hin}}, sh_data[1][31:4]} : sh_data[1];
        sh_data[3] = shamt[3] ? {{8{hin}}, sh_data[2][31:8]} : sh_data[2];
        sh_data[4] = shamt[4] ? {{16{hin}}, sh_data[3][31:16]} : sh_data[3];
    end
end

endmodule
/*
`include "adder.v"
`include "barrel.v"
`include "alu.v"
`include "reg_file.v"
`include "immGen.v"
`include "contrGen.v"
`include "dnpcGen.v"
*/

module rv32is(
	input 	clock,
	input 	reset,
	output [31:0] imemaddr,
	input  [31:0] imemdataout,
	output 	imemclk,
	output [31:0] dmemaddr,
	input  [31:0] dmemdataout,
	output [31:0] dmemdatain,
	output 	dmemrdclk,
	output	dmemwrclk,
	output [2:0] dmemop,
	output	dmemwe,
    output  dmemrd,
	output reg [31:0] dbgdata,
    output reg finish_a_inst
);

parameter ALUAsrc_busA = 1'b0;
parameter ALUAsrc_pc  = 1'b1;

parameter ALUBsrc_busB = 2'b00;
parameter ALUBsrc_imm = 2'b01;
parameter ALUBsrc_4   = 2'b10;

parameter Branch_jal  = 3'b001;
parameter Branch_jalr = 3'b010;
parameter Branch_eq   = 3'b100;
parameter Branch_ne   = 3'b101;
parameter Branch_lt   = 3'b110;
parameter Branch_ge   = 3'b111;

/*========================================*/

parameter BRANCH_PRED_ADDR_LEN = 9;
parameter BRANCH_PRED_SIZE = 2**BRANCH_PRED_ADDR_LEN;

reg [1:0] branch_pred [BRANCH_PRED_SIZE-1:0];

//IF
wire [6:0] IF_op;
wire [4:0] IF_rd, IF_rs1, IF_rs2;
wire [2:0] IF_funct3;
wire [6:0] IF_funct7;

wire [31:0] IF_imm;

wire [31:0] IF_pc, IF_pc_add_4, IF_pc_add_imm;
wire IF_branch_pred_jmp;

wire [2:0] IF_ExtOP;
wire IF_RegWr;
wire IF_ALUAsrc;
wire [1:0] IF_ALUBsrc;
wire [3:0] IF_ALUctr;
wire [2:0] IF_Branch;
wire IF_MemtoReg;
wire IF_MemWr, IF_MemRd;

wire IF_dnpc_add_imm;
wire IF_flushnow;

// IF/OF

reg [4:0] IF_OF_rd, IF_OF_rs1, IF_OF_rs2;
reg [2:0] IF_OF_funct3;
reg [31:0] IF_OF_imm;
reg [31:0] IF_OF_pc, IF_OF_pc_add_4, IF_OF_pc_add_imm;
reg IF_OF_branch_pred_jmp;
reg IF_OF_ALUAsrc;
reg [1:0] IF_OF_ALUBsrc;
reg [3:0] IF_OF_ALUctr;

reg IF_OF_flushed;
reg IF_OF_MemtoReg;
reg IF_OF_RegWr;
reg IF_OF_MemWr, IF_OF_MemRd;
reg [2:0] IF_OF_Branch;

// OF

wire [31:0] OF_pc_busA_add_imm;
wire OF_dnpc_busA_add_imm;

wire [31:0] OF_reg_busA, OF_reg_busB;
wire [31:0] OF_real_busA, OF_real_busB;

wire OF_dnpc_pc_loaduse;
wire OF_flushpre, OF_flushnow;

// OF/EX

reg OF_EX_jalr_solved;

reg [4:0] OF_EX_rd, OF_EX_rs2;
reg [2:0] OF_EX_funct3;
reg [31:0] OF_EX_imm;
reg [31:0] OF_EX_pc, OF_EX_pc_add_4, OF_EX_pc_add_imm;
reg OF_EX_branch_pred_jmp;
reg [31:0] OF_EX_busA, OF_EX_busB;
reg OF_EX_ALUAsrc;
reg [1:0] OF_EX_ALUBsrc;
reg [3:0] OF_EX_ALUctr;

reg OF_EX_flushed;
reg OF_EX_MemtoReg;
reg OF_EX_RegWr;
reg OF_EX_MemWr, OF_EX_MemRd;
reg [2:0] OF_EX_Branch;

// EX

wire [31:0] EX_pc_busA_add_imm;
wire EX_dnpc_busA_add_imm;

wire [31:0] EX_dataa, EX_datab;
wire EX_zero, EX_less;

wire [31:0] EX_real_busB;

wire EX_Branch_hit;
reg EX_Branch_jmp;
wire EX_dnpc_branch;
wire [31:0] EX_pc_branch;

wire [31:0] EX_ALUres;
wire EX_flushpre, EX_flushnow;

// EX/M

reg [4:0] EX_M_rd;
reg [2:0] EX_M_funct3;
reg [31:0] EX_M_busB, EX_M_ALUres;

reg EX_M_flushed;
reg EX_M_MemtoReg;
reg EX_M_RegWr;
reg EX_M_MemWr, EX_M_MemRd;

// M

wire [31:0] M_busW;
wire M_flushnow;


/*========================================*/

reg [31:0] EX_M_pc;
always @(negedge clock) begin
    EX_M_pc <= OF_EX_pc;
    finish_a_inst <= !M_flushnow;
    dbgdata <= !EX_flushnow ? OF_EX_pc :
                !OF_flushnow ? IF_OF_pc :
                !IF_flushnow ? IF_pc : 32'd0;
end

initial begin
    IF_OF_flushed = 1'b1;
    OF_EX_flushed = 1'b1;
    EX_M_flushed  = 1'b1;
end

// ============ pc

reg  [31:0] pc;
reg  [31:0] dnpc;

always @(*) begin
    if(reset) dnpc <= 32'd0;
    else if(IF_dnpc_add_imm)      dnpc <= IF_pc_add_imm;
    else if(OF_dnpc_pc_loaduse)   dnpc <= IF_OF_pc_add_4;
    else if(OF_dnpc_busA_add_imm) dnpc <= OF_pc_busA_add_imm;
    else if(EX_dnpc_busA_add_imm) dnpc <= EX_pc_busA_add_imm;
    else if(EX_dnpc_branch)       dnpc <= EX_pc_branch;
    else if(IF_branch_pred_jmp)   dnpc <= IF_pc_add_imm; 
    else                          dnpc <= IF_pc_add_4;
end

always @(negedge clock) begin
    pc <= dnpc;
end

//=========== IF begin

assign imemaddr = reset ? 32'd0 : dnpc;
assign imemclk = ~clock;

assign IF_flushnow = reset || OF_flushpre || EX_flushpre;

assign IF_pc = pc;
assign {IF_funct7, IF_rs2, IF_rs1, IF_funct3, IF_rd, IF_op} = imemdataout;

_32_adder IF_pc_add_4_adder(
    .A(IF_pc),
    .B(32'd4),
    .Cin(1'b0),
    .F(IF_pc_add_4)
);

_32_adder IF_pc_add_imm_adder(
    .A(IF_pc),
    .B(IF_imm),
    .Cin(1'b0),
    .F(IF_pc_add_imm)
);

assign IF_branch_pred_jmp = IF_Branch[2] &&
        branch_pred[IF_pc[BRANCH_PRED_ADDR_LEN - 1 : 0]][1];

contrGen my_contrGen(
    .op(IF_op),
    .funct3(IF_funct3),
    .funct7_5(IF_funct7[5]),
    .ExtOP(IF_ExtOP),
    .RegWr(IF_RegWr),
    .ALUAsrc(IF_ALUAsrc),
    .ALUBsrc(IF_ALUBsrc),
    .ALUctr(IF_ALUctr),
    .Branch(IF_Branch),
    .MemtoReg(IF_MemtoReg),
    .MemWr(IF_MemWr),
    .MemRd(IF_MemRd)
);

immGen my_immGen(
    .instr(imemdataout),
    .ExtOP(IF_ExtOP),
    .imm(IF_imm)
);


assign IF_dnpc_add_imm = !IF_flushnow && 
                        (IF_Branch == Branch_jal);

//============= IF/OF

always @(negedge clock) begin
    IF_OF_rd <= IF_rd;
    IF_OF_rs1 <= IF_rs1;
    IF_OF_rs2 <= IF_rs2;
    IF_OF_funct3 <= IF_funct3;
    IF_OF_imm <= IF_imm;
    IF_OF_pc <= IF_pc;
    IF_OF_pc_add_4 <= IF_pc_add_4;
    IF_OF_pc_add_imm <= IF_pc_add_imm;
    IF_OF_branch_pred_jmp <= IF_branch_pred_jmp;
    IF_OF_ALUAsrc <= IF_ALUAsrc;
    IF_OF_ALUBsrc <= IF_ALUBsrc;
    IF_OF_ALUctr <= IF_ALUctr;
    IF_OF_flushed <= IF_flushnow;
    if(IF_flushnow) begin
        IF_OF_MemtoReg <= 1'b0;
        IF_OF_RegWr <= 1'b0;
        IF_OF_MemWr <= 1'b0;
        IF_OF_MemRd <= 1'b0;
        IF_OF_Branch <= 3'd0;
    end
    else begin
        IF_OF_MemtoReg <= IF_MemtoReg;
        IF_OF_RegWr <= IF_RegWr;
        IF_OF_MemWr <= IF_MemWr;
        IF_OF_MemRd <= IF_MemRd;
        IF_OF_Branch <= IF_Branch;
    end
end

//============= OF
assign OF_flushnow = IF_OF_flushed || EX_flushpre;

reg_file myregfile(
    .Ra(IF_OF_rs1),
    .Rb(IF_OF_rs2),
    .Rw(EX_M_rd),
    .busW(M_busW),
    .RegWr(EX_M_RegWr),
    .WrClk(~clock),
    .busA(OF_reg_busA),
    .busB(OF_reg_busB)
);

_32_adder OF_pc_busA_add_imm_adder(
    .A(OF_reg_busA),
    .B(IF_OF_imm),
    .Cin(1'b0),
    .F(OF_pc_busA_add_imm)
);

assign OF_dnpc_busA_add_imm = !OF_flushnow &&
                        (IF_OF_Branch == Branch_jalr) &&
                        !(OF_EX_RegWr && IF_OF_rs1 != 5'd0 && OF_EX_rd == IF_OF_rs1) &&
                        !(EX_M_RegWr && IF_OF_rs1 != 5'd0 && EX_M_rd == IF_OF_rs1);


assign OF_real_busA = IF_OF_rs1 == 5'd0 ? 32'd0 :
                    (OF_EX_RegWr && OF_EX_rd == IF_OF_rs1) ? 
                    EX_ALUres : 
                    ((EX_M_RegWr && EX_M_rd == IF_OF_rs1) ? M_busW : 
                                OF_reg_busA );

assign OF_real_busB = IF_OF_rs2 == 5'd0 ? 32'd0 :
                    (OF_EX_RegWr && OF_EX_rd == IF_OF_rs2) ? 
                    EX_ALUres : 
                    ((EX_M_RegWr && EX_M_rd == IF_OF_rs2) ? M_busW : 
                                OF_reg_busB );

assign OF_dnpc_pc_loaduse = !OF_flushnow && IF_OF_MemtoReg &&
                        ((IF_ALUAsrc == ALUAsrc_busA && IF_rs1 != 5'd0 && IF_OF_rd == IF_rs1) ||
                        (IF_ALUBsrc == ALUBsrc_busB && IF_rs2 != 5'd0 && IF_OF_rd == IF_rs2));
assign OF_flushpre = OF_dnpc_pc_loaduse || OF_dnpc_busA_add_imm;

// ============= OF/EX

always @(negedge clock) begin
    OF_EX_jalr_solved <= OF_dnpc_busA_add_imm;

    OF_EX_rd <= IF_OF_rd;
    OF_EX_rs2 <= IF_OF_rs2;
    OF_EX_funct3 <= IF_OF_funct3; 
    OF_EX_imm <= IF_OF_imm;
    OF_EX_pc <= IF_OF_pc;
    OF_EX_pc_add_4 <= IF_OF_pc_add_4;
    OF_EX_pc_add_imm <= IF_OF_pc_add_imm;
    OF_EX_branch_pred_jmp <= IF_OF_branch_pred_jmp;
    OF_EX_busA <= OF_real_busA;
    OF_EX_busB <= OF_real_busB;
    OF_EX_ALUAsrc <= IF_OF_ALUAsrc;
    OF_EX_ALUBsrc <= IF_OF_ALUBsrc;
    OF_EX_ALUctr <= IF_OF_ALUctr;
    OF_EX_flushed <= OF_flushnow;
    if(OF_flushnow) begin
        OF_EX_MemtoReg <= 1'b0;
        OF_EX_RegWr <= 1'b0;
        OF_EX_MemWr <= 1'b0;
        OF_EX_MemRd <= 1'b0;
        OF_EX_Branch <= 3'd0;
    end
    else begin
        OF_EX_MemtoReg <= IF_OF_MemtoReg;
        OF_EX_RegWr <= IF_OF_RegWr;
        OF_EX_MemWr <= IF_OF_MemWr;
        OF_EX_MemRd <= IF_OF_MemRd;
        OF_EX_Branch <= IF_OF_Branch;
    end
end


// ============= EX

assign EX_flushnow = OF_EX_flushed;

_32_adder EX_pc_busA_add_imm_adder(
    .A(OF_EX_busA),
    .B(OF_EX_imm),
    .Cin(1'b0),
    .F(EX_pc_busA_add_imm)
);

assign EX_dnpc_busA_add_imm = !EX_flushnow && !OF_EX_jalr_solved &&
                        (OF_EX_Branch == Branch_jalr);

assign EX_dataa = OF_EX_ALUAsrc ? OF_EX_pc : OF_EX_busA;
assign EX_datab = OF_EX_ALUBsrc[0] ? OF_EX_imm :
                OF_EX_ALUBsrc[1] ? 32'd4 :
                OF_EX_busB;

alu my_alu(
	.dataa(EX_dataa),
	.datab(EX_datab),
	.ALUctr(OF_EX_ALUctr),
	.less(EX_less),
	.zero(EX_zero),
	.aluresult(EX_ALUres)
);

assign EX_real_busB = OF_EX_rs2 == 5'd0 ? 32'd0 :
                        (EX_M_MemtoReg && EX_M_rd == OF_EX_rs2 ? 
                        M_busW : OF_EX_busB);

always @(*) begin
    case(OF_EX_Branch)
        Branch_eq:   EX_Branch_jmp =  EX_zero;
        Branch_ne:   EX_Branch_jmp = ~EX_zero;
        Branch_lt:   EX_Branch_jmp =  EX_less;
        Branch_ge:   EX_Branch_jmp = ~EX_less;
        default  :   EX_Branch_jmp =  1'b0;
    endcase
end

assign EX_Branch_hit = (EX_Branch_jmp == OF_EX_branch_pred_jmp);

always @(negedge clock) begin
    if(!EX_flushnow && OF_EX_Branch[2]) begin
        if(EX_Branch_hit) begin
            branch_pred[OF_EX_pc[BRANCH_PRED_ADDR_LEN - 1 : 0]][0] = 1'b1;
        end
        else begin
            if (branch_pred[OF_EX_pc[BRANCH_PRED_ADDR_LEN - 1 : 0]][0] == 1'b1)
                branch_pred[OF_EX_pc[BRANCH_PRED_ADDR_LEN - 1 : 0]][0] = 1'b0;
            else 
                branch_pred[OF_EX_pc[BRANCH_PRED_ADDR_LEN - 1 : 0]] = {EX_Branch_jmp, 1'b0};
        end
    end
end


assign EX_dnpc_branch = !EX_flushnow && (EX_dnpc_busA_add_imm || (OF_EX_Branch[2] && !EX_Branch_hit));
assign EX_pc_branch = EX_Branch_jmp ? OF_EX_pc_add_imm : OF_EX_pc_add_4;

assign EX_flushpre = EX_dnpc_busA_add_imm || EX_dnpc_branch;

// ========== EX/M

always @(negedge clock) begin
    EX_M_rd <= OF_EX_rd;
    EX_M_funct3 <= OF_EX_funct3;
    EX_M_busB <= EX_real_busB;
    EX_M_ALUres <= EX_ALUres; 
    EX_M_flushed <= EX_flushnow;
    if(EX_flushnow) begin
        EX_M_MemtoReg <= 1'b0;
        EX_M_RegWr <= 1'b0;
        EX_M_MemWr <= 1'b0;
        EX_M_MemRd <= 1'b0;
    end
    else begin
        EX_M_MemtoReg <= OF_EX_MemtoReg;
        EX_M_RegWr <= OF_EX_RegWr;
        EX_M_MemWr <= OF_EX_MemWr;
        EX_M_MemRd <= OF_EX_MemRd;
    end
end

// =========== M
assign M_flushnow = EX_M_flushed;

assign dmemaddr = EX_M_ALUres;
assign M_busW = EX_M_MemtoReg ? dmemdataout : EX_M_ALUres;
assign dmemdatain = EX_M_busB;
assign dmemrdclk = clock;
assign dmemwrclk = ~clock;
assign dmemop = EX_M_funct3;
assign dmemwe = EX_M_MemWr;
assign dmemrd = EX_M_MemRd;


endmodule
module contrGen (
    input [6:0] op,
    input [2:0] funct3,
    input funct7_5,
    output reg [2:0] ExtOP,
    output reg RegWr,
    output reg ALUAsrc,
    output reg [1:0] ALUBsrc,
    output reg [3:0] ALUctr,
    output reg [2:0] Branch,
    output reg MemtoReg,
    output reg MemWr,
    output reg MemRd
);

parameter lui           = 7'b0110111;
parameter auipc         = 7'b0010111;
parameter Itype_compute = 7'b0010011;
parameter load          = 7'b0000011;
parameter jalr          = 7'b1100111;
parameter Rtype         = 7'b0110011;
parameter jal           = 7'b1101111;
parameter Btype         = 7'b1100011;
parameter store         = 7'b0100011;

parameter ExtItype = 3'b000;
parameter ExtUtype = 3'b001;
parameter ExtStype = 3'b010;
parameter ExtBtype = 3'b011;
parameter ExtJtype = 3'b100;


parameter ALUAsrc_busA = 1'b0;
parameter ALUAsrc_pc  = 1'b1;

parameter ALUBsrc_busB = 2'b00;
parameter ALUBsrc_imm = 2'b01;
parameter ALUBsrc_4   = 2'b10;

parameter ALUctr_add  = 4'b0000;
parameter ALUctr_srcB = 4'b1111;

parameter Branch_snpc = 3'b000;
parameter Branch_jal  = 3'b001;
parameter Branch_jalr = 3'b010;
parameter Branch_eq   = 3'b100;
parameter Branch_ne   = 3'b101;
parameter Branch_lt   = 3'b110;
parameter Branch_ge   = 3'b111;

parameter EN = 1'b1;
parameter NOT = 1'b0;

parameter BusWSrc_ALU = 1'b0;
parameter BusWSrc_MEM = 1'b1;


always @(*) begin
    case(op)
        lui:            ExtOP   = ExtUtype;
        auipc:          ExtOP   = ExtUtype;
        Itype_compute:  ExtOP   = ExtItype;
        Rtype:          ExtOP   = ExtItype;
        jal:            ExtOP   = ExtJtype;
        jalr:           ExtOP   = ExtItype;
        Btype:          ExtOP   = ExtBtype;
        load:           ExtOP   = ExtItype;
        store:          ExtOP   = ExtStype;
        default:        ExtOP   = ExtItype;
    endcase

    case(op)
        lui:            RegWr   = EN;
        auipc:          RegWr   = EN;
        Itype_compute:  RegWr   = EN;
        Rtype:          RegWr   = EN;
        jal:            RegWr   = EN;
        jalr:           RegWr   = EN;
        Btype:          RegWr   = NOT;
        load:           RegWr   = EN;
        store:          RegWr   = NOT;
        default:        RegWr   = NOT;
    endcase

    case(op)
        lui:            ALUAsrc = ALUAsrc_busA;
        auipc:          ALUAsrc = ALUAsrc_pc;
        Itype_compute:  ALUAsrc = ALUAsrc_busA;
        Rtype:          ALUAsrc = ALUAsrc_busA;
        jal:            ALUAsrc = ALUAsrc_pc;
        jalr:           ALUAsrc = ALUAsrc_pc;
        Btype:          ALUAsrc = ALUAsrc_busA;
        load:           ALUAsrc = ALUAsrc_busA;
        store:          ALUAsrc = ALUAsrc_busA;
        default:        ALUAsrc = ALUAsrc_busA;
    endcase

    case(op)
        lui:            ALUBsrc = ALUBsrc_imm;
        auipc:          ALUBsrc = ALUBsrc_imm;
        Itype_compute:  ALUBsrc = ALUBsrc_imm;
        Rtype:          ALUBsrc = ALUBsrc_busB;
        jal:            ALUBsrc = ALUBsrc_4;
        jalr:           ALUBsrc = ALUBsrc_4;
        Btype:          ALUBsrc = ALUBsrc_busB;
        load:           ALUBsrc = ALUBsrc_imm;
        store:          ALUBsrc = ALUBsrc_imm;
        default:        ALUBsrc = ALUBsrc_busB;
    endcase

    case(op)
        lui:            ALUctr  = ALUctr_srcB;
        auipc:          ALUctr  = ALUctr_add;
        Itype_compute:  ALUctr  = {funct3 == 3'b101 & funct7_5, funct3};
        Rtype:          ALUctr  = {funct7_5, funct3};
        jal:            ALUctr  = ALUctr_add;
        jalr:           ALUctr  = ALUctr_add;
        Btype:          ALUctr  = {funct3[2:1] == 2'b00, 1'b0, funct3[2:1]};
        load:           ALUctr  = ALUctr_add;
        store:          ALUctr  = ALUctr_add;
        default:        ALUctr  = ALUctr_add;
    endcase

    case(op)
        lui:            Branch  = Branch_snpc;
        auipc:          Branch  = Branch_snpc;
        Itype_compute:  Branch  = Branch_snpc;
        Rtype:          Branch  = Branch_snpc;
        jal:            Branch  = Branch_jal;
        jalr:           Branch  = Branch_jalr;
        Btype:          Branch  = {1'b1, funct3[2], funct3[0]};
        load:           Branch  = Branch_snpc;
        store:          Branch  = Branch_snpc;
        default:        Branch  = Branch_snpc;
    endcase

    case(op)
        lui:            MemtoReg = BusWSrc_ALU;
        auipc:          MemtoReg = BusWSrc_ALU;
        Itype_compute:  MemtoReg = BusWSrc_ALU;
        Rtype:          MemtoReg = BusWSrc_ALU;
        jal:            MemtoReg = BusWSrc_ALU;
        jalr:           MemtoReg = BusWSrc_ALU;
        Btype:          MemtoReg = BusWSrc_ALU;
        load:           MemtoReg = BusWSrc_MEM;
        store:          MemtoReg = BusWSrc_ALU;
        default:        MemtoReg = BusWSrc_ALU;
    endcase

    case(op)
        lui:            MemWr    = NOT;
        auipc:          MemWr    = NOT;
        Itype_compute:  MemWr    = NOT;
        Rtype:          MemWr    = NOT;
        jal:            MemWr    = NOT;
        jalr:           MemWr    = NOT;
        Btype:          MemWr    = NOT;
        load:           MemWr    = NOT;
        store:          MemWr    = EN;
        default:        MemWr    = NOT;
    endcase

    case(op)
        lui:            MemRd    = NOT;
        auipc:          MemRd    = NOT;
        Itype_compute:  MemRd    = NOT;
        Rtype:          MemRd    = NOT;
        jal:            MemRd    = NOT;
        jalr:           MemRd    = NOT;
        Btype:          MemRd    = NOT;
        load:           MemRd    = EN;
        store:          MemRd    = NOT;
        default:        MemRd    = NOT;
    endcase

end
    
endmodule
module reg_file (
    input [4:0] Ra,
    input [4:0] Rb,
    input [4:0] Rw,
    input [31:0] busW,
    input RegWr,
    input WrClk,
    output reg [31:0] busA,
    output reg [31:0] busB
);

reg [31:0] regs [31:1];

always @(*) begin
    if(Ra == 5'd0) busA = 32'd0;
    else busA = regs[Ra];
    if(Rb == 5'd0) busB = 32'd0;
    else busB = regs[Rb];
end

always @(posedge WrClk) begin
    if(RegWr && Rw != 5'd0) regs[Rw] <= busW;
end

endmodule
module immGen (
    input [31:0] instr,
    input [2:0] ExtOP,
    output reg [31:0] imm
);

parameter ExtItype = 3'b000;
parameter ExtUtype = 3'b001;
parameter ExtStype = 3'b010;
parameter ExtBtype = 3'b011;
parameter ExtJtype = 3'b100;

wire [31:0] immI, immU, immS, immB, immJ;

assign immI = {{20{instr[31]}}, instr[31:20]};
assign immU = {instr[31:12], 12'b0};
assign immS = {{20{instr[31]}}, instr[31:25], instr[11:7]};
assign immB = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};
assign immJ = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};

always @(*) begin
    case(ExtOP)
        ExtItype: imm = immI;
        ExtUtype: imm = immU;
        ExtStype: imm = immS;
        ExtBtype: imm = immB;
        ExtJtype: imm = immJ;
        default: imm = immI;
    endcase
end
    
endmodule
module alu(
	input [31:0] dataa,
	input [31:0] datab,
	input [3:0]  ALUctr,
	output less,
	output zero,
	output reg [31:0] aluresult
);

wire sub;
wire sf, cf, zf, of;
wire [31:0] adder_out;

_32_adder a_32_adder(
    .A(dataa),
    .B({32{sub}}^datab),
    .Cin(sub),
    .F(adder_out),
    .cf(cf),
    .zf(zf),
    .of(of)
);
assign sf = adder_out[31];

wire lr, al;
wire [31:0] barrel_out;

barrel a_barrel(
    .indata(dataa),
    .shamt(datab[4:0]),
    .lr(lr),
    .al(al),
    .outdata(barrel_out)
);

assign sub = ALUctr[3] | ALUctr[1];
assign lr = ~ALUctr[2];
assign al = ALUctr[3];
assign less = ALUctr[0] ? cf : sf^of;
assign zero = zf;
always @(*) begin
    casex(ALUctr)
        4'bx000: aluresult = adder_out;
        4'bxx01: aluresult = barrel_out;
        4'b001x: aluresult = {31'd0, less};
        4'b1111: aluresult = datab;
        4'b0100: aluresult = dataa ^ datab;
        4'b0110: aluresult = dataa | datab;
        4'b0111: aluresult = dataa & datab;
        default: aluresult = adder_out;
    endcase
end

endmodule
