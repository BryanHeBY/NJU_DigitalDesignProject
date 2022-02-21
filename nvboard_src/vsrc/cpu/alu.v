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
