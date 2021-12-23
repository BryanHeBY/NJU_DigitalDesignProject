module dmem_ctrl(
	input  [17:0] addr,
	input  [31:0] datain,
	input  rdclk,
	input  wrclk,
	input [2:0] memop,
	input we,
    output reg [31:0] dataout
);

reg [31:0] in_datain;
reg [3:0] wren_arr;
reg [3:0] wren_arr_shift;
always @(*) begin
	case(memop[1:0])
		2'b00: wren_arr = 4'b0001;
		2'b01: wren_arr = 4'b0011;
		2'b10: wren_arr = 4'b1111;
		default: wren_arr = 4'b0000;
	endcase
	case(addr[1:0])
		2'b00: begin
			in_datain = datain;
			wren_arr_shift = wren_arr;
		end
		2'b01: begin
			in_datain = {datain[23:0], 8'd0};
			wren_arr_shift = {wren_arr[2:0], 1'b0};
		end
		2'b10: begin
			in_datain = {datain[15:0], 16'd0};
			wren_arr_shift = {wren_arr[1:0], 2'b00};
		end
		2'b11: begin
			in_datain = {datain[7:0], 24'd0};
			wren_arr_shift = {wren_arr[0], 3'b000};
		end
		default: begin
			in_datain = datain;
			wren_arr_shift = wren_arr;
		end
	endcase
end

wire [31:0] in_dataout;
dmem in_dmem(
	.byteena_a(wren_arr_shift),
	.data(in_datain),
	.rdaddress(addr[17:2]),
	.rdclock(rdclk),
	.wraddress(addr[17:2]),
	.wrclock(wrclk),
	.wren(we),
	.q(in_dataout)
);

reg [7:0] bg;
wire [15:0] hg;
wire [31:0] ext_bg, ext_hg;
always @(*) begin
	case(addr[1:0])
		2'b00: bg = in_dataout[7:0];
		2'b01: bg = in_dataout[15:8];
		2'b10: bg = in_dataout[23:16];
		2'b11: bg = in_dataout[31:24];
		default: bg = in_dataout[7:0];
	endcase
end
assign hg = addr[1] ? in_dataout[31:16] : in_dataout[15:0];
assign ext_bg = {{24{~memop[2]&bg[7]}}, bg};
assign ext_hg = {{16{~memop[2]&hg[15]}}, hg};

always @(*) begin
	case(memop[1:0])
		2'b00: dataout = ext_bg;
		2'b01: dataout = ext_hg;
		2'b10: dataout = in_dataout;
		default: dataout = ext_bg;
	endcase
end

endmodule
