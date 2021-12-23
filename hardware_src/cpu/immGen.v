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
