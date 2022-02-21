module vga_font(
    input [11:0] address,
    input clock,
    output reg [7:0] q
);

reg [7:0] ram [4095:0];

initial begin
    $readmemh({`PWD, "/resource/vga_font.hex"}, ram);
end

always@(posedge clock)
    q <= ram[address];

endmodule
