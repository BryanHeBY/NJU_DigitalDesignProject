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
    if(reset) dnpc = 32'd0;
    else if(IF_dnpc_add_imm)      dnpc = IF_pc_add_imm;
    else if(OF_dnpc_pc_loaduse)   dnpc = IF_OF_pc_add_4;
    else if(OF_dnpc_busA_add_imm) dnpc = OF_pc_busA_add_imm;
    else if(EX_dnpc_busA_add_imm) dnpc = EX_pc_busA_add_imm;
    else if(EX_dnpc_branch)       dnpc = EX_pc_branch;
    else if(IF_branch_pred_jmp)   dnpc = IF_pc_add_imm; 
    else                          dnpc = IF_pc_add_4;
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
