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
