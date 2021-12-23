`include "rv32is.v"
`include "hex7seg.v"
`include "clk_gen.v"
`include "ps2_keyboard.v"
`include "vga_ctrl.v"

module mycpu(

	//////////// CLOCK //////////
	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,

	//////////// KEY //////////
	input 		     [3:0]		KEY,

	//////////// SW //////////
	input 		     [9:0]		SW,

	//////////// LED //////////
	output		     [9:0]		LEDR,

	//////////// Seg7 //////////
	output		     [6:0]		HEX0,
	output		     [6:0]		HEX1,
	output		     [6:0]		HEX2,
	output		     [6:0]		HEX3,
	output		     [6:0]		HEX4,
	output		     [6:0]		HEX5,

	//////////// VGA //////////
	output		          		VGA_BLANK_N,
	output		     [7:0]		VGA_B,
	output		          		VGA_CLK,
	output		     [7:0]		VGA_G,
	output		          		VGA_HS,
	output		     [7:0]		VGA_R,
	output		          		VGA_SYNC_N,
	output		          		VGA_VS,

	//////////// Audio //////////
	input 		          		AUD_ADCDAT,
	inout 		          		AUD_ADCLRCK,
	inout 		          		AUD_BCLK,
	output		          		AUD_DACDAT,
	inout 		          		AUD_DACLRCK,
	output		          		AUD_XCK,

	//////////// PS2 //////////
	inout 		          		PS2_CLK,
	inout 		          		PS2_CLK2,
	inout 		          		PS2_DAT,
	inout 		          		PS2_DAT2,

	//////////// I2C for Audio and Video-In //////////
	output		          		FPGA_I2C_SCLK,
	inout 		          		FPGA_I2C_SDAT
);

wire clk;
/*
clkgen #(12500000) my_clkgen(
    .clkin(CLOCK_50),
    .rst(1'b0),
    .clken(1'b1),
    .clkout(clk)
);*/
assign clk = CLOCK_50;
//assign clk = ~KEY[3];

wire imemclk;
wire [31:0] imemaddr, imemdataout;

wire dmemrdclk, dmemwrclk;
wire [31:0] dmemaddr, dmemdatain;
reg [31:0] dmemdataout;
wire [2:0] dmemop;
wire dmemwe, dmemrd;



reg reset, initialed;
initial begin
	reset = 1'b1;
	initialed = 1'b0;
end
always @(negedge clk) begin
	initialed <= 1'b1;
end
always @(posedge clk) begin
	if(initialed) reset <= 1'b0;
end

wire [31:0] pc;

rv32is mycpu(
	.clock(clk),
	.reset(reset),
	.imemaddr(imemaddr),
	.imemdataout(imemdataout),
	.imemclk(imemclk),
	.dmemaddr(dmemaddr),
	.dmemdataout(dmemdataout),
	.dmemdatain(dmemdatain),
	.dmemrdclk(dmemrdclk),
	.dmemwrclk(dmemwrclk),
	.dmemop(dmemop),
	.dmemwe(dmemwe),
	.dmemrd(dmemrd),
	.dbgdata(pc)
);

imem my_imem(
	.address(imemaddr[16:2]),
	.clock(imemclk),
	.q(imemdataout)
);

parameter   dmem_mem  = 4'd1,
			dmem_kbd  = 4'd2,
			dmem_vga  = 4'd3,
			dmem_hex  = 4'd4,
			dmem_ledr = 4'd5,
			dmem_sw   = 4'd6,
			dmem_key  = 4'd7,
			dmem_clk  = 4'd8,
			dmem_vga_ctrl= 4'd9,
			dmem_gmem  = 4'd10;

wire [3:0] dmem_tag;
assign dmem_tag = dmemaddr[27:24];
wire [31:0] dmem_mem_dataout;

wire key_ready;
wire [7:0] dmem_keycode;

wire [31:0] dmem_clks_out [3:0];

always @(*) begin
	case(dmem_tag)
		dmem_mem:  dmemdataout = dmem_mem_dataout;
		dmem_kbd:  dmemdataout = {24'd0, dmem_keycode};
		dmem_sw:   dmemdataout = {22'd0, SW};
		dmem_clk:  dmemdataout = dmem_clks_out[dmemaddr[3:2]];
		default:   dmemdataout = 32'd0;
	endcase
end

dmem_ctrl my_dmem(
	.addr(dmemaddr[17:0]),
	.datain(dmemdatain),
	.rdclk(dmemrdclk),
	.wrclk(dmemwrclk),
	.memop(dmemop),
	.we(dmem_tag == dmem_mem && dmemwe),
    .dataout(dmem_mem_dataout)
);


reg [3:0] hex_data [5:0];
hex7seg my_hexout[5:0](
	.en(6'b111111),
	.b(/*{dmemdatain[11:0],pc[11:0]}*/{hex_data[5], hex_data[4], hex_data[3], hex_data[2], hex_data[1], hex_data[0]}),
	.h({HEX5, HEX4, HEX3, HEX2, HEX1, HEX0})
);

reg [9:0] ledr_data;
assign LEDR = ledr_data[9:0];

initial begin
	hex_data[0] = 0;
	hex_data[1] = 0;
	hex_data[2] = 0;
	hex_data[3] = 0;
	hex_data[4] = 0;
	hex_data[5] = 0;
	ledr_data = 0;
end

always @(posedge dmemwrclk) begin
	if(dmemwe)begin
		if(dmem_tag==dmem_hex && dmemaddr[2:1]!=2'b11) hex_data[dmemaddr[2:0]] <= dmemdatain[3:0];
		if(dmem_tag==dmem_ledr) ledr_data <= dmemdatain[9:0];
	end
	
end

clkcount #(1000000) clk_us(
    .clkin(CLOCK_50),
    .clkcount(dmem_clks_out[0])
);

clkcount #(1000) clk_ms(
    .clkin(CLOCK_50),
    .clkcount(dmem_clks_out[1])
);

clkcount #(10) clk_ds(
    .clkin(CLOCK_50),
    .clkcount(dmem_clks_out[2])
);

clkcount #(1) clk_s(
    .clkin(CLOCK_50),
    .clkcount(dmem_clks_out[3])
);


wire [7:0] keycode_data;
wire ps2_ready;
reg nextdata_n;
initial begin
	nextdata_n = 1'b1;
end
always @(negedge dmemrdclk) begin
	if(nextdata_n == 1'b0) nextdata_n <= 1'b1;
	else if(ps2_ready && dmem_tag == dmem_kbd && dmemrd) nextdata_n <= 1'b0;
end
ps2_keyboard myps2(
	.clk(dmemrdclk),
	.clrn(1'b1),
	.ps2_clk(PS2_CLK),
	.ps2_data(PS2_DAT),
	.data(keycode_data),
	.ready(ps2_ready),
	.nextdata_n(nextdata_n)
);
assign dmem_keycode = ps2_ready && nextdata_n ? keycode_data : 8'd0;

// ---vga_begin---
wire [23:0] vga_data;
wire [9:0] v_addr, h_addr;
wire [4:0] scan_vaddr;
wire [6:0] scan_haddr;
wire [11:0] vmem_rdaddress;
assign scan_vaddr = v_addr[8:4];
assign scan_haddr = h_addr[9:3];
assign vmem_rdaddress = {scan_vaddr, scan_haddr};
wire [3:0] font_v;
wire [2:0] font_h;
assign font_v = v_addr[3:0];
assign font_h = h_addr[2:0];

clkgen #(25000000) vga_clkgen(
    .clkin(CLOCK_50),
    .rst(~KEY[2]),
    .clken(1'b1),
    .clkout(VGA_CLK)
);

vga_ctrl my_vga_ctrl(
    .pclk(VGA_CLK),
    .reset(~KEY[2]),
    .vga_data(vga_data),
    .h_addr(h_addr),
    .v_addr(v_addr),
    .hsync(VGA_HS),
    .vsync(VGA_VS),
    .valid(VGA_BLANK_N),
    .vga_r(VGA_R),
    .vga_g(VGA_G),
    .vga_b(VGA_B)
);

assign VGA_SYNC_N = 1'b0;

/*
wire [15:0] vmem_in_data;
wire [11:0] vmem_wraddress;
wire vmem_wren;
*/

wire [15:0] vmem_out_data;
wire font_bspecial, font_fspecial;
wire [2:0]font_bspec_code, font_fspec_code;
wire [7:0] vmem_ascii;
assign {font_bspecial, font_bspec_code,
		font_fspecial, font_fspec_code,
		vmem_ascii} = vmem_out_data;

wire [23:0] font_bcolor_rgb, font_fcolor_rgb;
assign font_bcolor_rgb = font_bspecial ?
							{{8{font_bspec_code[0]}}, {8{font_bspec_code[1]}}, {8{font_bspec_code[2]}}} :
							24'd0;
assign font_fcolor_rgb = font_fspecial ?
							{{8{font_fspec_code[0]}}, {8{font_fspec_code[1]}}, {8{font_fspec_code[2]}}} :
							24'hffffff;

vmem my_vmem(
	.data(dmemdatain[15:0]),
	.rdaddress(vmem_rdaddress),
	.rdclock(~CLOCK_50),
	.wraddress(dmemaddr[12:1]),
	.wrclock(dmemwrclk),
	.wren(dmem_tag == dmem_vga && dmemwe),
	.q(vmem_out_data)
);

wire [23:0] vga_font_data, vga_gmem_data;
assign vga_font_data = font_out[font_h] ? font_fcolor_rgb : font_bcolor_rgb;

wire [7:0] font_out;
vga_font my_vga_font(
	.address({vmem_ascii, font_v}),
	.clock(CLOCK_50),
	.q(font_out)
);

wire [5:0] gmem_in_data, gmem_out_data;
assign gmem_in_data = {dmemdatain[23:22], dmemdatain[15:14], dmemdatain[7:6]};
assign vga_gmem_data = {{4{gmem_out_data[5:4]}}, {4{gmem_out_data[3:2]}}, {4{gmem_out_data[1:0]}}};
wire [31:0] gmem_addr_tmp, gmem_addr;
_32_adder vga_adder1(
    .A({15'd0, v_addr, 7'd0}),
    .B({13'd0, v_addr, 9'd0}),
    .Cin(1'b0),
    .F(gmem_addr_tmp)
);
_32_adder vga_adder2(
    .A(gmem_addr_tmp),
    .B({22'd0, h_addr}),
    .Cin(1'b0),
    .F(gmem_addr)
);
gmem my_gmem(
	.data(gmem_in_data),
	.rdaddress(gmem_addr/*{2'd0, v_addr, 7'd0} + {v_addr, 9'd0} + {9'd0, h_addr}*/),
	.rdclock(~CLOCK_50),
	.wraddress(dmemaddr[20:2]),
	.wrclock(dmemwrclk),
	.wren(dmem_tag == dmem_gmem && dmemwe),
	.q(gmem_out_data)
);

reg vga_ctrl;
initial begin
	vga_ctrl = 1'b0;
end
always @(posedge dmemwrclk) begin
	if(dmem_tag == dmem_vga_ctrl && dmemwe) vga_ctrl <= dmemdatain[0];
end

assign vga_data = vga_ctrl ? vga_gmem_data : vga_font_data;

/*
wire cur_shade;
clkgen #(1) my_cur_shade_clkgen(
    .clkin(CLOCK_50),
    .rst(1'b0),
    .clken(1'b1),
    .clkout(cur_shade)
);

assign vga_data = {scan_vaddr, scan_haddr} == vmem_wraddress && cur_shade ? 
					{24{1'b1}} : {24{font_out[font_h]}};

*/

// ---vga_end---

endmodule
