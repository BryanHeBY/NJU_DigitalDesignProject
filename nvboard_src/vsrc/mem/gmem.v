module gmem (
    input [5:0] data,
    input [18:0] rdaddress,
    input rdclock,
    input [18:0] wraddress,
    input wrclock,
    input wren,
    output reg [5:0] q
);

reg [5:0] ram [307199:0];

always@(posedge rdclock)
	q <= ram[rdaddress];

always @(posedge wrclock) begin
    if(wren)ram[wraddress] <= data;
end

endmodule
