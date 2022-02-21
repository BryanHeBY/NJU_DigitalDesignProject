module imem(
	address,
	clock,
	q);

	input	[14:0]  address;
	input	  clock;
	output reg	[31:0]  q;
	
	reg [31:0] ram [32767:0];

    initial begin
		$readmemh({`PWD, "/resource/build/imem.hex"}, ram);
	end

	always@(posedge clock)
		q <= ram[address];
		
endmodule