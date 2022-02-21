module vmem(
    input [15:0] data,
	input [11:0] rdaddress,
	input rdclock,
	input [11:0] wraddress,
	input wrclock,
	input wren,
	output reg [15:0] q);

	
	reg [15:0] ram [4095:0];

	always@(posedge rdclock)
		q <= ram[rdaddress];

    always @(posedge wrclock) 
        if(wren)ram[wraddress] <= data;
		
endmodule