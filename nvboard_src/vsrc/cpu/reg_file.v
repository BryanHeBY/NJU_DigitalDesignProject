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
